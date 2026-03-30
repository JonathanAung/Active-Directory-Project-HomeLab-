# SOC Automation Project — Wazuh · TheHive · Shuffle SOAR

**TL;DR:** Built a fully automated SOC pipeline from scratch. A security event fires on an endpoint, Wazuh detects it, Shuffle orchestrates enrichment and response, TheHive creates a case, analyst gets a notification. Zero manual intervention. End-to-end in under 3 minutes.

---

## Why I Built This

Most SOC training teaches you to use tools. I wanted to understand how they talk to each other and more importantly, how to make them act without waiting for a human in the loop. The goal wasn't to follow a guide. It was to build something that breaks, force myself to fix it, and document what I learned.

---

## Architecture

```
[Windows Endpoint]
        |
        | Sysmon + Wazuh Agent
        v
[Wazuh Manager] --- alert triggered ---> [Shuffle SOAR]
                                               |
        ---------------------------------------+-------------------------------
        v                    v                                v
[AbuseIPDB]          [VirusTotal]                    [TheHive Case]
IP Reputation         Hash Lookup                    Incident Created
        |                    |                                |
        ---------------------|                                v
                             |                       [Email / Webhook]
                      Enriched Alert                 Analyst Notified
```

**Stack:**

| Component | Role |
|---|---|
| Wazuh | SIEM - agent-based threat detection, rule matching, alert generation |
| Shuffle | SOAR - workflow orchestration, API chaining, automated response |
| TheHive | Case management - structured incident tracking |
| AbuseIPDB | Threat intel enrichment - IP reputation scoring |
| Sysmon | Windows telemetry - process creation, network connections, file events |

---

## Environment

- **Wazuh Manager:** Ubuntu 22.04 (VM / VPS)
- **Wazuh Agent:** Windows 10 endpoint
- **Shuffle:** Cloud instance (shuffler.io)
- **TheHive:** Self-hosted on Ubuntu
- **Network:** NAT / isolated lab environment

<!-- TODO: Update with your actual setup - local VMs, cloud provider, IP ranges -->

---

## What the Automated Pipeline Does

When a Wazuh rule fires (e.g., Mimikatz execution detected, brute force threshold hit, suspicious process spawn):

1. **Wazuh** generates an alert and forwards it to Shuffle via webhook
2. **Shuffle** parses the alert - extracts IP, hash, username, rule ID
3. **AbuseIPDB** lookup runs automatically - confidence score returned
4. **TheHive** case is created with full alert context, severity mapped from Wazuh rule level
5. **Email / webhook notification** fires to analyst with enriched summary
6. *(Optional)* **Active response** - Wazuh agent blocks the IP or isolates the host

Total time from event to enriched case: **under 3 minutes.**

Manual analyst steps required: **zero.**

---

## Key Technical Challenges and How I Solved Them

**1. Wazuh to TheHive API Compatibility**

TheHive 5 changed its API structure significantly from TheHive 4. The Shuffle TheHive app was built for v4, so alerts were being sent but cases weren't being created - no error, just silence.

Fix: Manually mapped the Shuffle HTTP action to TheHive 5's `/api/v1/alert` endpoint with the correct JSON body structure. Hardcoded the required `type` and `source` fields that TheHive 5 requires but v4 did not.

<!-- TODO: Add your specific version numbers and the exact fields that were missing -->

**2. Shuffle Webhook Authentication**

Wazuh's `ossec.conf` integration block requires a specific format for the webhook URL and authentication header. Initial alerts were firing but Shuffle wasn't receiving them.

Fix: Added the Shuffle webhook URL to the Wazuh integration block with correct `<hook_url>` and `<api_key>` tags. Validated by watching Shuffle execution logs in real time.

**3. AbuseIPDB Rate Limits in Testing**

During testing with repeated simulated alerts, AbuseIPDB's free tier rate limit (1,000 checks/day) was being hit quickly.

Fix: Added a conditional in the Shuffle workflow - only query AbuseIPDB if the alert contains an external IP (not RFC1918 private ranges). Reduced unnecessary API calls by ~70% during testing.

---

## Shuffle Workflow - Step by Step

```
Trigger: Wazuh Webhook
  |
  --- Parse JSON (extract: srcip, dstip, rule.id, rule.description, agent.name)
  |
  --- [IF srcip is public]
  |     --- AbuseIPDB GET /check?ipAddress={srcip}
  |     --- Extract: abuseConfidenceScore, countryCode, isp
  |
  --- TheHive POST /api/v1/alert
  |     title: Wazuh Alert - {rule.description}
  |     severity: mapped from rule.level (1-15 -> Low/Med/High/Crit)
  |     description: full enriched alert body
  |     tags: [wazuh, {agent.name}, {rule.id}]
  |
  --- Email/Webhook Notification
        Subject: [ALERT] {severity} - {rule.description}
        Body: IP: {srcip} | Score: {abuseScore} | Agent: {agent.name}
```

<!-- TODO: Screenshot your actual Shuffle workflow here -->

---

## Sample Alert Output

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
    "isp": "[redacted for lab]"
  },
  "thehive_case_id": "~1234567",
  "response_time_seconds": 142
}
```

<!-- TODO: Replace with a real sanitized output from your lab -->

---

## What I'd Do Differently

- **Add MITRE ATT&CK tagging** to every TheHive case automatically - map Wazuh rule IDs to ATT&CK technique IDs at the Shuffle layer
- **Build a Slack integration** instead of email - faster analyst response loop
- **Add a feedback loop** - when an analyst closes a TheHive case as false positive, automatically tune the Wazuh rule threshold
- **Containerize the stack** with Docker Compose so the whole lab spins up in one command

---

## References

- [Wazuh Documentation](https://documentation.wazuh.com)
- [TheHive Project](https://thehive-project.org)
- [Shuffle SOAR](https://shuffler.io)
- [AbuseIPDB API](https://docs.abuseipdb.com)
- [MyDFIR - Original Project Guide](https://www.youtube.com/watch?v=Lb_ukgtYK_U)

---

*Built as part of ongoing home lab development. Part of a broader security portfolio targeting SOC automation and incident response engineering.*
