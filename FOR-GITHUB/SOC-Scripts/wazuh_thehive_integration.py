#!/usr/bin/env python3
"""
wazuh_thehive_integration.py

Receives a Wazuh alert (JSON) and creates a case in TheHive 5.
This script is called by Shuffle SOAR as part of the automated pipeline.

Usage:
    python3 wazuh_thehive_integration.py <path_to_alert.json>

Environment variables required:
    THEHIVE_URL   - TheHive server URL (e.g. http://192.168.10.20:9000)
    THEHIVE_KEY   - TheHive API key
"""

import json
import sys
import os
import requests
from datetime import datetime


THEHIVE_URL = os.environ.get("THEHIVE_URL", "http://localhost:9000")
THEHIVE_KEY = os.environ.get("THEHIVE_KEY", "")

# Map Wazuh rule level (1-15) to TheHive severity (1=Low, 2=Medium, 3=High, 4=Critical)
SEVERITY_MAP = {
    range(1, 5):   1,  # Low
    range(5, 8):   2,  # Medium
    range(8, 12):  3,  # High
    range(12, 16): 4,  # Critical
}


def map_severity(rule_level: int) -> int:
    for level_range, severity in SEVERITY_MAP.items():
        if rule_level in level_range:
            return severity
    return 2  # default to Medium


def parse_wazuh_alert(alert: dict) -> dict:
    """Extract the fields we need from a Wazuh alert JSON."""
    rule = alert.get("rule", {})
    agent = alert.get("agent", {})
    data = alert.get("data", {})

    return {
        "rule_id":      rule.get("id", "unknown"),
        "description":  rule.get("description", "Wazuh alert"),
        "level":        int(rule.get("level", 5)),
        "agent_name":   agent.get("name", "unknown"),
        "agent_ip":     agent.get("ip", "unknown"),
        "src_ip":       data.get("srcip", ""),
        "timestamp":    alert.get("timestamp", datetime.utcnow().isoformat()),
    }


def create_thehive_alert(parsed: dict) -> dict:
    """Build the TheHive 5 alert payload from parsed Wazuh data."""
    return {
        "type":        "wazuh",
        "source":      "wazuh-integration",
        "sourceRef":   f"wazuh-{parsed['rule_id']}-{int(datetime.utcnow().timestamp())}",
        "title":       f"Wazuh Alert - {parsed['description']}",
        "description": (
            f"**Rule ID:** {parsed['rule_id']}\n"
            f"**Agent:** {parsed['agent_name']} ({parsed['agent_ip']})\n"
            f"**Source IP:** {parsed['src_ip']}\n"
            f"**Timestamp:** {parsed['timestamp']}"
        ),
        "severity":    map_severity(parsed["level"]),
        "tags":        ["wazuh", parsed["agent_name"], f"rule-{parsed['rule_id']}"],
        "tlp":         2,   # TLP:AMBER
        "pap":         2,
    }


def post_to_thehive(alert_payload: dict) -> None:
    """Send the alert to TheHive 5 API."""
    headers = {
        "Authorization": f"Bearer {THEHIVE_KEY}",
        "Content-Type": "application/json",
    }

    response = requests.post(
        f"{THEHIVE_URL}/api/v1/alert",
        headers=headers,
        json=alert_payload,
        timeout=10,
    )

    if response.status_code in (200, 201):
        case_id = response.json().get("_id", "unknown")
        print(f"[OK] TheHive case created: {case_id}")
    else:
        print(f"[ERROR] TheHive returned {response.status_code}: {response.text}")
        sys.exit(1)


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 wazuh_thehive_integration.py <alert.json>")
        sys.exit(1)

    with open(sys.argv[1], "r") as f:
        alert = json.load(f)

    parsed = parse_wazuh_alert(alert)
    print(f"[*] Processing alert: {parsed['description']} (level {parsed['level']})")

    payload = create_thehive_alert(parsed)
    post_to_thehive(payload)


if __name__ == "__main__":
    main()
