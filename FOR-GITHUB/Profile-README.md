<h1>Hi, I'm Jonathan (Tun Tun Aung)</h1>

Cybersecurity student at John Jay College of Criminal Justice. B.S. Computer Science and Information Security (in progress). Also hold a B.S. in Computer Science from Boston University.

CompTIA Security+ · TryHackMe Top 4% · New York, NY

<h2>A little background</h2>

I started in CS at Boston University, left when the 2021 Myanmar military coup upended everything, and spent two years in New York working service industry jobs while teaching myself security on the side. I came back to finish my degree at John Jay specifically to study information security, not just computer science. That choice was deliberate.

My lab work is focused on SOC automation, SOAR engineering, and penetration testing. I build things, they break, I figure out why and write it down.

<h2>Projects</h2>

<b><a href="https://github.com/JonathanAung/SOC-Automation-Project">SOC Automation Pipeline</a></b>
Wazuh · TheHive · Shuffle SOAR · AbuseIPDB

Built an automated incident response pipeline on DigitalOcean. A security event fires on a Windows endpoint, Wazuh picks it up, Shuffle enriches the alert and creates a TheHive case automatically. No manual steps. Under 3 minutes from event to case.

The part that took the most debugging: TheHive 5 changed its API structure from v4 and the Shuffle app didn't account for it. Cases were silently not being created. Had to manually remap the HTTP action to the correct endpoint and add the required fields TheHive 5 expects.

<b><a href="https://github.com/JonathanAung/Active-Directory-Project-HomeLab-">Active Directory Home Lab</a></b>
Splunk · Kali Linux · Atomic Red Team · Sysmon

Set up a full domain environment with a Windows Server 2022 DC, a domain-joined Windows 10 machine, Splunk on Ubuntu, and Kali as the attacker. Used Atomic Red Team to run MITRE ATT&CK mapped attacks, brute force, credential dumping, persistence, and wrote Splunk detection queries for each one.

<h2>Skills</h2>

| | |
|---|---|
| Blue Team | Wazuh, Splunk, ELK, Suricata, Snort, TheHive, Shuffle |
| Red Team | Burp Suite, Nmap, Metasploit, Mimikatz, Kali, Atomic Red Team |
| Languages | Python, Bash, SQL, PowerShell, Java, C++ (coursework) |
| Frameworks | MITRE ATT&CK, NIST SP 800-171, NIST CSF, OWASP Top 10 |

<h2>Certifications</h2>

CompTIA Security+ · Google Cybersecurity Professional

<h2>Find me</h2>

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=flat&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/jonathan-xiong/)
[![TryHackMe](https://img.shields.io/badge/TryHackMe-Top%204%25-red?style=flat&logo=tryhackme&logoColor=white)](https://tryhackme.com/p/Relguntan)
