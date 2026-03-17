<h1>Active-Directory-Project-HomeLab</h1>

 ### [YouTube Guide](https://www.youtube.com/watch?v=5OessbOgyEo&list=PLG6KGSNK4PuBWmX9NykU0wnWamjxdKhDJ&index=13)

<h2>Description</h2>
In this project, I’m setting up an Active Directory home lab with Splunk, Kali Linux, and Atomic Red Team. I'll try to simulate how a domain environment works, how to feed events into a SIEM, and generate telemetry from real-world attacks to help me get familiar with them for future projects/jobs.
<br />
<p align="center">
Diagram of Project: <br/>
 <img src="https://i.imgur.com/SKUzoNX.png" height="80%" width="80%" alt="Project Diagram"/>
</p>

<h2>Virtual Box VM Machines used</h2>

- <b>Windows 10</b> 
- <b>Windows 2022 Server</b>
- <b>Ubuntu Server Splunk</b>
- <b>Kali Linux</b>

<h2>Installations & Configurations:</h2>
Before we do anything, we want to make sure our Virtual Machines are on the same network. We do this by going to "Tools", then "Network" on the VirtualBox. Once we are there, select NAT-network and click on create. For simplicty purpose, I will be naming the network as "AD Project" and have the IPv4 Prefix as : 192.168.10.0/24 as shown in the diagram. Leave the "Enable DHCP" as it is and once we are done with all that, hit apply.
<p align="center">
Change the network to NAT-network: <br/>
<img src="https://i.imgur.com/42E2xEe.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Launch our Splunk Server:
 note: make sure you are on the right network setting by using the command `` ` ip a ` ``
 <br/>
<img src=https://i.imgur.com/lU48vle.png height="80%" width="80%" alt="Checking IP address step using ```ip a ```"/>
<br />
Awesome, we see that the line "inet 192.168.10.10/24 ... " does indeed reflect our network configurations! <br />
However, if it doesn't reflect the same ip address (which is what happened to me at first), you want to type in <br /> ```sudo nano /etc/netplan/00-installer-config.yaml`` 
<br />
You want to change your settings from this: <br/>
<img src=https://i.imgur.com/xouvqhg.png height="80%" width="80%" alt="Original 00-installer-config.yaml settings"/>
<br />
<br />
To this (Make sure the indentation are correct!):  <br/>
<img src=https://i.imgur.com/aoAte5F.png height="80%" width="80%" alt="Modified 00-installer-config.yaml settings"/>
<br />
 once we are done with it, type ```sudo netplan apply``` to apply our changes and try out our ```ip a``` command once more, and this time the ip should be correct.
<br />
Wait for process to complete (may take some time):  <br/>
<img src="https://i.imgur.com/JL945Ga.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Sanitization complete:  <br/>
<img src="https://i.imgur.com/K71yaM2.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
text:  <br/>
<img src="https://i.imgur.com/AeZkvFQ.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
 <br/>
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>

<h2>What I Learned</h2>

- How to build and configure a **Windows Active Directory domain environment** from scratch
- How to set up **Splunk** as a SIEM to ingest and monitor Windows event logs
- How to use **Kali Linux** and **Atomic Red Team** to simulate real-world attacks (e.g., brute force, lateral movement)
- How to read and interpret **Windows Event IDs** (4625 = failed login, 4624 = successful login, 4720 = new account created)
- How to identify **indicators of compromise (IOCs)** in Splunk dashboards
- How Virtual Machines communicate over a **NAT network** and the importance of static IP assignment
- Practical experience with **netplan**, **YAML configuration files**, and Linux CLI

<h2>Skills Demonstrated</h2>

| Skill | Tool/Technology |
|---|---|
| SIEM & Log Analysis | Splunk |
| Attack Simulation | Atomic Red Team, Kali Linux |
| Domain Administration | Windows Server 2022, Active Directory |
| Network Configuration | VirtualBox NAT Network, static IP |
| Threat Detection | Windows Event Logs, custom Splunk alerts |
| Virtualization | VirtualBox, multiple OS management |

<h2>Future Project Ideas (Roadmap)</h2>

- [ ] **Honeypot Deployment** — Set up a decoy server and log attacker behavior
- [ ] **CTF Writeups** — Document TryHackMe / HackTheBox solutions to build offensive skills
- [ ] **Custom Splunk Detection Rules** — Write SPL queries to catch specific attack patterns from this lab
- [ ] **Phishing Email Analyzer** — Build a Python script to parse email headers and flag suspicious indicators
- [ ] **Incident Response Playbook** — Document step-by-step response procedures for alerts generated in this lab

