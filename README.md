<h1>Active Directory Home Lab</h1>

### [YouTube Guide (MyDFIR)](https://www.youtube.com/watch?v=5OessbOgyEo&list=PLG6KGSNK4PuBWmX9NykU0wnWamjxdKhDJ&index=13)

<h2>Description</h2>

In this project I set up an Active Directory home lab with Splunk, Kali Linux, and Atomic Red Team. I wanted to understand how a domain environment actually works, how to get Windows events into a SIEM, and what real attacks look like from the defender's side. Reading about Mimikatz is one thing. Watching Splunk light up when you run a credential dumping simulation against a domain controller you configured yourself is something else.

<p align="center">
Diagram of Project: <br/>
<img src="https://i.imgur.com/SKUzoNX.png" height="80%" width="80%" alt="Project Diagram"/>
</p>

<h2>VirtualBox VMs Used</h2>

- <b>Windows Server 2022</b> - Active Directory Domain Controller (192.168.10.7)
- <b>Windows 10</b> - Domain-joined target endpoint (192.168.10.100)
- <b>Ubuntu Server</b> - Splunk SIEM (192.168.10.10)
- <b>Kali Linux</b> - Attack machine (192.168.10.250)

<h2>Network Setup</h2>

All VMs need to be on the same network. Go to Tools, then Network in VirtualBox. Select NAT Network and click create. I named mine "AD Project" with IPv4 Prefix 192.168.10.0/24. Leave DHCP enabled and hit apply.

<p align="center">
<img src="https://i.imgur.com/42E2xEe.png" height="80%" width="80%" alt="NAT Network setup"/>
</p>

Once your Splunk VM is running, check the IP with `ip a`. If it doesn't show 192.168.10.10, you need to set it manually:

```bash
sudo nano /etc/netplan/00-installer-config.yaml
```

Update it to look like this (indentation matters):

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

Then run `sudo netplan apply` and check `ip a` again.

<h2>Attacks Simulated and What to Look For in Splunk</h2>

<b>Brute Force - RDP/SMB via Crowbar (from Kali)</b>

```bash
crowbar -b rdp -s 192.168.10.100/32 -u administrator -C /usr/share/wordlists/rockyou.txt
```

Splunk query to catch it:
```
index=endpoint EventCode=4625
| stats count by src_ip, user, host
| where count > 10
| sort -count
```

What you'll see: a spike of EventID 4625 (failed login) from the same IP in a short window.

<b>Credential Dumping - Mimikatz via Atomic Red Team</b>

```powershell
Invoke-AtomicTest T1003.001
```

Splunk query:
```
index=endpoint EventCode=1
(CommandLine="*mimikatz*" OR CommandLine="*sekurlsa*" OR CommandLine="*lsadump*")
| table _time, host, user, CommandLine, ParentImage
```

What you'll see: Sysmon Event ID 1 with Mimikatz arguments showing up in the command line, usually launched from PowerShell.

<b>Persistence - New Admin Account Created</b>

```
index=endpoint EventCode=4720 OR EventCode=4732
| table _time, host, user, MemberSid, TargetUserName
```

What you'll see: EventID 4720 (account created) followed by 4732 (added to Administrators group).

<h2>Troubleshooting</h2>

<b>Splunk not receiving events:</b>
- Check outputs.conf on the forwarder, verify the Splunk server IP and port 9997
- Make sure firewall allows inbound TCP 9997 on the Ubuntu machine
- Run `./splunk list forward-server` on the forwarder to confirm it's connected

<b>Sysmon events missing:</b>
- Confirm Sysmon is running: `sc query sysmon64`
- Check inputs.conf includes the Sysmon channel
- Restart the forwarder after any config change

<b>Domain join failing:</b>
- Windows 10 DNS needs to point to the DC's IP, not 8.8.8.8
- Make sure the DC has the DNS role installed

<h2>What I Learned</h2>

- Logs lie by omission. Sysmon without a good config gives you almost no useful context. The config matters as much as the tool.
- Volume is an attacker's best camouflage. 1,000 failed logins in 60 seconds is obvious. 10 per minute over 100 minutes is not. You need time-window queries, not just raw counts.
- MITRE ATT&CK is a map, not a script. Atomic Red Team runs the documented technique. Real attackers obfuscate. Your detection needs to account for variations.

<h2>Skills Demonstrated</h2>

| Skill | Tool |
|---|---|
| SIEM and Log Analysis | Splunk |
| Attack Simulation | Atomic Red Team, Kali Linux |
| Domain Administration | Windows Server 2022, Active Directory |
| Network Configuration | VirtualBox NAT, static IP, netplan |
| Threat Detection | Windows Event IDs, Splunk SPL queries |
| Virtualization | VirtualBox, 4-VM environment |

<h2>What I Want to Add Next</h2>

- [ ] <b>Automated Splunk alerts</b> - trigger notable events when thresholds are crossed instead of running manual searches
- [ ] <b>SOAR integration</b> - hook Splunk alerts into the [SOC Automation pipeline](https://github.com/JonathanAung/SOC-Automation-Project)
- [ ] <b>More ATT&CK coverage</b> - add Lateral Movement (pass-the-hash, PsExec) and Exfiltration simulations

<h2>References</h2>

- [MyDFIR YouTube Guide](https://www.youtube.com/watch?v=5OessbOgyEo&list=PLG6KGSNK4PuBWmX9NykU0wnWamjxdKhDJ&index=13)
- [Atomic Red Team](https://github.com/redcanaryco/atomic-red-team)
- [Sysmon SwiftOnSecurity Config](https://github.com/SwiftOnSecurity/sysmon-config)
- [MITRE ATT&CK](https://attack.mitre.org)
