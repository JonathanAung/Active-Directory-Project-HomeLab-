<h1>Hey, I'm Jonathan Aung</h1>

<h2>Cybersecurity Enthusiast | Aspiring SOC Analyst | Home Lab Builder</h2>

<p align="center">
  <a href="https://www.linkedin.com/in/jonathan-xiong">LinkedIn</a> |
  <a href="https://github.com/JonathanAung">GitHub</a>
</p>

<h2>About Me</h2>

I'm a cybersecurity student who's been building hands-on skills through home labs and real-world attack simulations. I focus on defensive security and I'm trying to understand how attacks actually happen so I can get better at detecting and stopping them. I follow along with MyDFIR's project guides and try to document everything I learn along the way.

- Currently studying: <b>Active Directory, SIEM, SOC Automation</b>
- Working toward: <b>SOC Analyst / Cybersecurity Internship</b>
- Learning platforms: TryHackMe, MyDFIR
- Ask me about: Splunk, Active Directory, Kali Linux, Wazuh

<h2>Projects</h2>

<h3>Active Directory Home Lab</h3>

In this project, I set up a full Windows domain environment and used it to simulate real-world attacks. I wanted to understand how a domain works, how to get events into a SIEM, and what attacks actually look like from a defender's perspective.

- Set up <b>Windows Server 2022</b> as a Domain Controller with Active Directory
- Deployed <b>Splunk</b> on Ubuntu to ingest and monitor Windows Event Logs
- Used <b>Kali Linux</b> and <b>Atomic Red Team</b> to simulate brute force and lateral movement attacks
- Analyzed Windows Event IDs (4625, 4624, 4720) to detect threats inside Splunk

[View Project](https://github.com/JonathanAung/Active-Directory-Project-HomeLab-)

<h3>SOC Automation Project</h3>

In this project, I built an automated SOC workflow so that when Wazuh generates an alert, the system automatically enriches it with threat intel and creates a case in TheHive without any manual work. I wanted to get a feel for how real SOC teams reduce alert fatigue using automation.

- Connected <b>Wazuh</b> as the SIEM/EDR backbone to monitor a Windows endpoint
- Used <b>Shuffle SOAR</b> to automate the alert triage pipeline
- Integrated <b>TheHive</b> for case management and <b>MISP</b> for threat intelligence lookups
- Deployed all servers on <b>DigitalOcean</b> cloud VMs

[View Project](https://github.com/JonathanAung/SOC-Automation-Project)

<h2>Skills</h2>

| Category | Tools and Technologies |
|---|---|
| SIEM and Monitoring | Splunk, Wazuh |
| Threat Detection | Windows Event IDs, IOC analysis |
| Attack Simulation | Atomic Red Team, Kali Linux |
| SOC Automation | Shuffle SOAR, TheHive, MISP |
| Networking | Active Directory, NAT, TCP/IP |
| Operating Systems | Windows Server 2022, Ubuntu, Kali Linux |
| Programming | Python, C++ |
| Virtualization | VirtualBox, DigitalOcean |

<h2>Certifications and Learning</h2>

- [ ] <b>CompTIA Security+</b> (in progress)
- [ ] <b>TryHackMe SOC Level 1 Path</b>
- [ ] <b>Google Cybersecurity Certificate</b>

<h2>Currently Working On</h2>

- Finishing the SOC Automation lab (Wazuh + TheHive + Shuffle)
- Writing custom Splunk detection rules for the AD HomeLab
- Working through TryHackMe rooms and documenting the writeups
