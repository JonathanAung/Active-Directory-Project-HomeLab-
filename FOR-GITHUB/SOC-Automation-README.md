<h1>SOC Automation Project</h1>

### [YouTube Guide (MyDFIR)](https://www.youtube.com/watch?v=Lb_ukgtYK_U)

<h2>Description</h2>

In this project I built an automated SOC pipeline on DigitalOcean. The idea was that when Wazuh detects something suspicious, the whole response happens automatically without anyone needing to manually triage the alert. I wanted to understand how these tools actually talk to each other and what it takes to get them working together.

The cloud infrastructure has since been taken down to manage costs. Everything is documented here so it can be rebuilt.

<p align="center">
<img src="Diagram.drawio" height="80%" width="80%" alt="SOC Automation Diagram"/>
</p>

<h2>Tools Used</h2>

- <b>Wazuh 4.7.3</b> - SIEM and EDR, monitors the Windows endpoint and generates alerts
- <b>Shuffle SOAR</b> - the automation layer that connects everything together
- <b>TheHive 5.2.4</b> - case management, every alert becomes a tracked incident here
- <b>AbuseIPDB</b> - checks source IPs against a reputation database
- <b>DigitalOcean</b> - cloud VMs where the servers were hosted

<h2>How the Pipeline Works</h2>

1. Wazuh detects something on the Windows 10 endpoint and fires an alert
2. The alert gets forwarded to Shuffle via webhook
3. Shuffle checks if the source IP is external, then queries AbuseIPDB for a reputation score
4. Shuffle creates a case in TheHive with the enriched alert data
5. An email notification goes out so an analyst knows to look

Total time from event to case: under 3 minutes. No manual steps.

<h2>Environment</h2>

- <b>Wazuh Manager:</b> Ubuntu 22.04 on DigitalOcean (4GB RAM / 2 vCPU)
- <b>Wazuh Agent:</b> Windows 10 endpoint
- <b>Shuffle:</b> shuffler.io cloud instance
- <b>TheHive:</b> self-hosted on Ubuntu 22.04 DigitalOcean Droplet
- <b>Network:</b> DigitalOcean private networking

<h2>Challenges I Ran Into</h2>

<b>TheHive v4 vs v5 API</b>

The Shuffle app for TheHive was built for v4. TheHive 5.2.4 changed the API endpoint from `/api/alert` to `/api/v1/alert` and added two required fields (`type` and `source`) that v4 didn't enforce. Cases were being sent but silently not creating - no error, just nothing showing up in TheHive. Fixed it by switching the Shuffle HTTP action to the correct endpoint and hardcoding the missing fields.

<b>Shuffle webhook not receiving alerts</b>

Wazuh's `ossec.conf` integration block needs the webhook URL and auth header in a specific format. Initial alerts were firing from Wazuh but Shuffle wasn't receiving them. Fixed by correcting the `<hook_url>` and `<api_key>` tags in the integration config and validating through Shuffle's execution logs.

<b>AbuseIPDB rate limits</b>

The free tier allows 1,000 lookups per day. During testing with repeated simulated alerts this got eaten up fast. Fixed by adding a condition in Shuffle to only query AbuseIPDB if the source IP is a public address, not an RFC1918 private range. Reduced unnecessary calls by about 70%.

<h2>Sample Alert Output</h2>

```json
{
  "alert_id": "1714023901.12345",
  "rule": {
    "id": "100002",
    "description": "Mimikatz credential dumping detected",
    "level": 12
  },
  "agent": {
    "name": "WIN10-LAB",
    "ip": "192.168.10.50"
  },
  "data": {
    "srcip": "203.0.113.42",
    "abuse_confidence_score": 87,
    "country": "CN",
    "isp": "[redacted]"
  },
  "thehive_case_id": "~1234567",
  "response_time_seconds": 142
}
```

<h2>What I'd Change</h2>

- Add MITRE ATT&CK tags to every TheHive case automatically by mapping Wazuh rule IDs at the Shuffle layer
- Use Slack instead of email for notifications, faster response loop
- Containerize the whole stack with Docker Compose so it spins up in one command instead of setting up each server manually

<h2>Scripts</h2>

The Python and Bash scripts used for the integration are in the `/scripts` folder.

<h2>References</h2>

- [Wazuh Documentation](https://documentation.wazuh.com)
- [TheHive Project](https://thehive-project.org)
- [Shuffle SOAR](https://shuffler.io)
- [AbuseIPDB API](https://docs.abuseipdb.com)
- [MyDFIR Project Guide](https://www.youtube.com/watch?v=Lb_ukgtYK_U)
