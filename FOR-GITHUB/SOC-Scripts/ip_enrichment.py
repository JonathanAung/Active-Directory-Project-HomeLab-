#!/usr/bin/env python3
"""
ip_enrichment.py

Queries AbuseIPDB to enrich an IP address with reputation data.
Called by Shuffle SOAR after Wazuh fires an alert containing an external IP.
Skips RFC1918 private IPs to avoid wasting API calls during testing.

Usage:
    python3 ip_enrichment.py <ip_address>

Environment variables required:
    ABUSEIPDB_KEY - AbuseIPDB API key
"""

import sys
import os
import ipaddress
import requests


ABUSEIPDB_KEY = os.environ.get("ABUSEIPDB_KEY", "")
ABUSEIPDB_URL = "https://api.abuseipdb.com/api/v2/check"


def is_private(ip: str) -> bool:
    """Return True if the IP is RFC1918 private - skip enrichment for these."""
    try:
        return ipaddress.ip_address(ip).is_private
    except ValueError:
        return False


def query_abuseipdb(ip: str) -> dict:
    """Query AbuseIPDB and return the enrichment result."""
    headers = {
        "Key": ABUSEIPDB_KEY,
        "Accept": "application/json",
    }
    params = {
        "ipAddress":       ip,
        "maxAgeInDays":    90,
        "verbose":         "",
    }

    response = requests.get(ABUSEIPDB_URL, headers=headers, params=params, timeout=10)

    if response.status_code != 200:
        print(f"[ERROR] AbuseIPDB returned {response.status_code}: {response.text}")
        sys.exit(1)

    return response.json().get("data", {})


def format_result(ip: str, data: dict) -> None:
    """Print a clean summary of the enrichment result."""
    score   = data.get("abuseConfidenceScore", 0)
    country = data.get("countryCode", "unknown")
    isp     = data.get("isp", "unknown")
    reports = data.get("totalReports", 0)

    print(f"\n[ENRICHMENT] {ip}")
    print(f"  Abuse Confidence Score : {score}/100")
    print(f"  Country                : {country}")
    print(f"  ISP                    : {isp}")
    print(f"  Total Reports          : {reports}")

    if score >= 80:
        print(f"  [HIGH RISK] Score {score} - recommend blocking")
    elif score >= 40:
        print(f"  [MEDIUM RISK] Score {score} - monitor closely")
    else:
        print(f"  [LOW RISK] Score {score}")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 ip_enrichment.py <ip_address>")
        sys.exit(1)

    ip = sys.argv[1]

    if is_private(ip):
        print(f"[SKIP] {ip} is a private RFC1918 address - skipping AbuseIPDB lookup")
        sys.exit(0)

    print(f"[*] Querying AbuseIPDB for {ip}...")
    data = query_abuseipdb(ip)
    format_result(ip, data)


if __name__ == "__main__":
    main()
