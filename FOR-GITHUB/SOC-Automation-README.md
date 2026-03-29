<h1>SOC Automation Project</h1>

### [YouTube Guide (MyDFIR)](https://www.youtube.com/watch?v=5OessbOgyEo)

<h2>Description</h2>

In this project, I built an automated Security Operations Center (SOC) workflow that mimics what real companies use to handle security alerts. Instead of a SOC analyst manually investigating every single alert, this system automatically triages, enriches, and creates cases — so analysts can focus on real threats.

Think of it like this: imagine a fire alarm system that not only rings the alarm but also automatically calls the fire department, logs the incident, and pulls up the building's floor plan — all without anyone lifting a finger.

<p align="center">
Project Diagram: <br/>
<img src="Diagram.drawio" height="80%" width="80%" alt="SOC Automation Diagram"/>
</p>

<h2>Tools & Technologies Used</h2>

| Tool | Role | Plain English Explanation |
|---|---|---|
| **Wazuh** | EDR / SIEM | The "security camera" — monitors endpoints and generates alerts |
| **TheHive** | Case Management | The "incident ticket system" — organizes and tracks each alert as a case |
| **Shuffle SOAR** | Automation Engine | The "robot analyst" — connects everything and automates repetitive tasks |
| **MISP** | Threat Intelligence | The "threat database" — checks if IPs/hashes are known malicious indicators |
| **DigitalOcean** | Cloud Infrastructure | Where the servers live (cloud VMs instead of local VirtualBox) |

<h2>Architecture Overview</h2>

```
[Windows 10 Client]
       |
       | (sends logs/alerts)
       v
[Wazuh SIEM/EDR]  ──────────────────────────────────>  [Shuffle SOAR]
                                                              |
                                              ┌───────────────┼───────────────┐
                                              v               v               v
                                          [MISP]         [TheHive]       [Email Alert]
                                      (threat intel)   (case created)   (analyst notified)
```

**Flow:**
1. Wazuh detects suspicious activity on the Windows client
2. Alert is sent to **Shuffle SOAR** (the automation engine)
3. Shuffle checks the IOC (IP, file hash) against **MISP** for threat intel
4. Shuffle automatically creates a case in **TheHive** with all enriched data
5. Analyst receives an email notification with the full context

<h2>What I Learned</h2>

- How **SOAR (Security Orchestration, Automation & Response)** works in a real SOC environment
- How to connect multiple security tools via **API integrations** (webhooks, REST APIs)
- How **Wazuh** monitors endpoints and generates alerts for suspicious behavior
- How **case management** works in TheHive — creating cases, assigning tasks, tracking status
- How **threat intelligence platforms** (MISP) enrich alerts with known IOC data
- How to deploy and manage **cloud servers** on DigitalOcean (Linux VMs)
- The concept of **MTTR (Mean Time to Respond)** and how automation reduces it

<h2>Key Concepts (Plain English)</h2>

**SOAR** = A robot that connects your security tools and automates repetitive analyst tasks. Like a smart assistant that reads every alert and does the boring investigation steps for you.

**EDR (Wazuh)** = Software installed on computers that watches for suspicious behavior — like if a process tries to access sensitive files or a user logs in at 3am.

**Case Management (TheHive)** = A ticketing system for security incidents. Every alert becomes a "case" that can be assigned, tracked, and closed. Like Jira, but for cyberattacks.

**Threat Intelligence (MISP)** = A shared database of known bad actors — malicious IPs, file hashes, domain names. If an alert matches something in MISP, it's almost certainly malicious.

**IOC (Indicator of Compromise)** = Digital evidence that a system may have been compromised. Examples: a suspicious IP address, a known malware file hash, an unusual login time.

<h2>Skills Demonstrated</h2>

| Skill | Tool |
|---|---|
| SOAR Automation | Shuffle |
| SIEM & Endpoint Detection | Wazuh |
| Case Management | TheHive |
| Threat Intelligence | MISP |
| API Integration | REST APIs, Webhooks |
| Cloud Infrastructure | DigitalOcean Linux VMs |
| Incident Response Workflow | End-to-end alert triage |

<h2>Future Improvements</h2>

- [ ] Add Slack/Discord notification integration in Shuffle
- [ ] Build custom Wazuh detection rules for specific attack patterns
- [ ] Integrate VirusTotal API for automated file hash lookups
- [ ] Create a Grafana dashboard to visualize alert trends over time
- [ ] Document a full incident response walkthrough from alert to close

<h2>Related Projects</h2>

- [Active Directory HomeLab](https://github.com/JonathanAung/Active-Directory-Project-HomeLab-) — The foundation lab this project builds on
