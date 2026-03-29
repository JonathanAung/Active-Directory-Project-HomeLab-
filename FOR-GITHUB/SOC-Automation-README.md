<h1>SOC Automation Project</h1>

### [YouTube Guide](https://www.youtube.com/watch?v=5OessbOgyEo)

<h2>Description</h2>
In this project, I'm building an automated SOC workflow that mimics what real companies use to handle security alerts. The idea is that instead of a SOC analyst manually triaging every single alert, the system does it automatically. I wanted to understand how these tools connect to each other and how real teams use automation to cut down on repetitive work.
<br />
<p align="center">
Diagram of Project: <br/>
<img src="Diagram.drawio" height="80%" width="80%" alt="SOC Automation Project Diagram"/>
</p>

<h2>Tools Used</h2>

- <b>Wazuh</b> - SIEM and EDR, monitors the Windows endpoint and generates alerts
- <b>Shuffle SOAR</b> - the automation engine that connects all the tools together
- <b>TheHive</b> - case management, every alert gets turned into a tracked case here
- <b>MISP</b> - threat intelligence platform, checks if IPs or file hashes are known bad indicators
- <b>DigitalOcean</b> - cloud VMs where all the servers are hosted

<h2>How It Works</h2>

Once everything is set up, the flow goes like this:
<br />
1. Wazuh detects something suspicious on the Windows 10 client and fires an alert
<br />
2. That alert gets sent to Shuffle SOAR
<br />
3. Shuffle checks the IOC (IP address or file hash) against MISP to see if it's a known threat
<br />
4. Shuffle automatically creates a case in TheHive with all the enriched information
<br />
5. An email notification goes out so the analyst knows to take a look
<br />

<h2>Installations and Configurations</h2>

<p align="center">
Setting up Wazuh on DigitalOcean: <br/>
<br />
Setting up TheHive: <br/>
<br />
Configuring Shuffle workflows: <br/>
<br />
</p>

<h2>What I Learned</h2>

- How SOAR (Security Orchestration, Automation and Response) works in a real SOC environment
- How to connect multiple security tools using API integrations and webhooks
- How Wazuh monitors endpoints and what its alerts look like
- How case management works in TheHive and how analysts track incidents
- How threat intelligence platforms like MISP enrich alerts with known IOC data
- How to deploy and manage cloud servers on DigitalOcean
- What MTTR (Mean Time to Respond) means and how automation helps bring it down

<h2>Skills Demonstrated</h2>

| Skill | Tool |
|---|---|
| SOAR Automation | Shuffle |
| SIEM and Endpoint Detection | Wazuh |
| Case Management | TheHive |
| Threat Intelligence | MISP |
| API Integration | REST APIs, Webhooks |
| Cloud Infrastructure | DigitalOcean Linux VMs |

<h2>Future Improvements</h2>

- [ ] <b>Slack/Discord notifications</b> - add a messaging integration into the Shuffle workflow
- [ ] <b>Custom Wazuh rules</b> - write detection rules for specific attack patterns
- [ ] <b>VirusTotal integration</b> - automate file hash lookups inside Shuffle
- [ ] <b>Grafana dashboard</b> - visualize alert trends over time
- [ ] <b>Full IR walkthrough</b> - document a complete incident from alert to case close

<h2>Related Projects</h2>

- [Active Directory HomeLab](https://github.com/JonathanAung/Active-Directory-Project-HomeLab-)
