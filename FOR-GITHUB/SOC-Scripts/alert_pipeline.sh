#!/usr/bin/env bash
# alert_pipeline.sh
#
# End-to-end pipeline script that ties the automation together.
# Wazuh calls this script via its active-response or integration block
# when a rule fires. It enriches the alert and ships it to TheHive.
#
# Usage (called by Wazuh integration):
#   ./alert_pipeline.sh <alert_file.json>
#
# Required environment variables:
#   THEHIVE_URL    - TheHive server URL
#   THEHIVE_KEY    - TheHive API key
#   ABUSEIPDB_KEY  - AbuseIPDB API key

set -euo pipefail

ALERT_FILE="${1:-}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_FILE="/var/log/soc_pipeline.log"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*" | tee -a "$LOG_FILE"
}

if [[ -z "$ALERT_FILE" ]]; then
    log "ERROR: No alert file provided"
    exit 1
fi

if [[ ! -f "$ALERT_FILE" ]]; then
    log "ERROR: Alert file not found: $ALERT_FILE"
    exit 1
fi

log "Pipeline started for alert: $ALERT_FILE"

# Step 1 - extract source IP from the alert
SRC_IP=$(python3 -c "
import json, sys
with open('$ALERT_FILE') as f:
    a = json.load(f)
print(a.get('data', {}).get('srcip', ''))
")

# Step 2 - enrich the IP if we got one
if [[ -n "$SRC_IP" ]]; then
    log "Enriching IP: $SRC_IP"
    python3 "$SCRIPT_DIR/ip_enrichment.py" "$SRC_IP" | tee -a "$LOG_FILE"
else
    log "No source IP found in alert - skipping enrichment"
fi

# Step 3 - create the TheHive case
log "Creating TheHive case..."
python3 "$SCRIPT_DIR/wazuh_thehive_integration.py" "$ALERT_FILE"

log "Pipeline complete"
