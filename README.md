# Active Directory Home Lab — Splunk · Kali Linux · Atomic Red Team

**TL;DR:** Simulated a real enterprise domain environment, fed attack telemetry into a SIEM, and used Atomic Red Team to generate real-world TTPs — then hunted them in Splunk. Built to understand what attacks actually look like from the defender's side.

---

## Why I Built This

Reading about Active Directory attacks is one thing. Watching Splunk light up when you run a credential harvesting simulation against a domain controller you configured yourself is something else. This lab was built to close the gap between knowing what Mimikatz *is* and recognizing what it looks like in a log.

---

## Architecture

```
NAT Network: 192.168.10.0/24

[Windows Server 2022]          [Windows 10]
Active Directory DC             Target Machine
192.168.10.7                   192.168.10.100
        |                               |
        ---------------------------------
                        |
                [Ubuntu Server]
                 Splunk SIEM
                192.168.10.10
                        |
                [Kali Linux]
                Attacker Machine
                192.168.10.250
```

**Stack:**

| Component | Role |
|---|---|
| Windows Server 2022 | Active Directory Domain Controller |
| Windows 10 | Domain-joined target endpoint |
| Splunk (Ubuntu) | SIEM - log aggregation, search, alerting |
| Kali Linux | Attack platform - Crowbar, Nmap, Mimikatz |
| Atomic Red Team | Adversary simulation - MITRE ATT&CK-mapped test cases |
| Sysmon | Windows telemetry - enriched event logging |

---

## Lab Setup - Key Steps

**1. Network Configuration (VirtualBox NAT Network)**

All VMs placed on the same NAT network (`192.168.10.0/24`) for isolated lab communication.

```bash
# Ubuntu Splunk server - static IP assignment
sudo nano /etc/netplan/00-installer-config.yaml
```

```yaml
network:
  ethernets:
    enp0s3:
      dhcp4: no
      addresses: [192.168.10.10/24]
      gateway4: 192.168.10.1
      nameservers:
        addresses: [8.8.8.8, 8.8.4.4]
  version: 2
```

```bash
sudo netplan apply
ip a # verify 192.168.10.10 is active
```

**2. Splunk Installation and Forwarding**

- Installed Splunk Enterprise on Ubuntu server
- Deployed Splunk Universal Forwarder on Windows machines
- Configured `inputs.conf` to forward Windows Event Logs and Sysmon events
- Created index: `endpoint` for all Windows telemetry

**3. Active Directory Setup**

- Promoted Windows Server 2022 to Domain Controller
- Created domain: `[your-domain].local`
- Added Windows 10 machine to domain
- Created test user accounts for attack simulation

**4. Sysmon Deployment**

Deployed Sysmon with SwiftOnSecurity config on all Windows machines for enriched telemetry - process creation (Event ID 1), network connections (Event ID 3), file creation (Event ID 11).

---

## Attacks Simulated and What to Look For in Splunk

**Brute Force - RDP / SMB (Crowbar)**

```bash
# From Kali
crowbar -b rdp -s 192.168.10.100/32 -u administrator -C /usr/share/wordlists/rockyou.txt
```

Splunk detection query:
```
index=endpoint EventCode=4625
| stats count by src_ip, user, host
| where count > 10
| sort -count
```

What it looks like: Spike of EventID 4625 (failed logon) from a single source IP in a short window.

---

**Credential Dumping - Mimikatz (Atomic Red Team)**

```powershell
# On Windows target - run Atomic Red Team test
Invoke-AtomicTest T1003.001
```

Splunk detection query:
```
index=endpoint EventCode=1
(CommandLine="*mimikatz*" OR CommandLine="*sekurlsa*" OR CommandLine="*lsadump*")
| table _time, host, user, CommandLine, ParentImage
```

What it looks like: Sysmon Event ID 1 showing a process spawning with known Mimikatz command line arguments, often launched from PowerShell or cmd.exe.

---

**Persistence - New Local Admin Account**

```
index=endpoint EventCode=4720 OR EventCode=4732
| table _time, host, user, MemberSid, TargetUserName
```

What it looks like: EventID 4720 (user account created) followed quickly by 4732 (added to Administrators group).

---

## Key Troubleshooting Notes

**Splunk not receiving events from Windows forwarder:**
- Check `outputs.conf` on the forwarder - verify Splunk server IP and port 9997
- Verify firewall allows inbound TCP 9997 on the Ubuntu Splunk server
- Run `./splunk list forward-server` on the forwarder to confirm connection

**Sysmon events not appearing in Splunk:**
- Confirm Sysmon is installed: `sc query sysmon64`
- Check `inputs.conf` includes `Application=Sysmon` or the Microsoft-Windows-Sysmon/Operational channel
- Restart the Splunk forwarder service after config changes

**AD domain join failing:**
- Ensure Windows 10 DNS is pointing to the DC's IP (not 8.8.8.8)
- Verify the DC has the DNS role installed and the forward lookup zone exists

---

## What I Learned

- **Logs lie by omission.** Sysmon without a good config gives you Event ID 1 with almost no useful context. The config matters as much as the tool.
- **Volume is the attacker's best camouflage.** A brute force attack generating 1,000 EventID 4625s in 60 seconds is obvious. Ten failed logins per minute over 100 minutes is not - you need time-window aggregations, not just raw counts.
- **MITRE ATT&CK is a map, not a script.** Atomic Red Team runs the technique as documented. Real attackers obfuscate. The detection has to account for variations, not just the canonical form.

---

## What I'd Add Next

- **Alerts in Splunk** - automated notable events when brute force thresholds are crossed, not just manual searches
- **SOAR integration** - connect Splunk alerts to the [SOC Automation pipeline](https://github.com/JonathanAung/SOC-Automation-Project) for automated response
- **More ATT&CK coverage** - currently focused on Initial Access and Credential Access; want to add Lateral Movement (pass-the-hash, PsExec) and Exfiltration simulations

---

## References

- [MyDFIR - Project Guide](https://www.youtube.com/watch?v=5OessbOgyEo&list=PLG6KGSNK4PuBWmX9NykU0wnWamjxdKhDJ&index=13)
- [Atomic Red Team](https://github.com/redcanaryco/atomic-red-team)
- [Sysmon SwiftOnSecurity Config](https://github.com/SwiftOnSecurity/sysmon-config)
- [MITRE ATT&CK](https://attack.mitre.org)
- [Splunk Documentation](https://docs.splunk.com)

---

*Part of an ongoing home lab series. See also: [SOC Automation Project](https://github.com/JonathanAung/SOC-Automation-Project)*
