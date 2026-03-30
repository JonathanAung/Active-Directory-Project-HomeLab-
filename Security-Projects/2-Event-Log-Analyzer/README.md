<h1>Windows Event Log Analyzer</h1>

<h2>Description</h2>
In this project, I'm building a C++ tool that reads a CSV export of Windows Event Logs and automatically flags suspicious activity. This is the same kind of work I was doing manually in Splunk during my Active Directory HomeLab, except now I'm building the detection logic myself from scratch. It checks for brute force login attempts, new accounts being created, and privilege escalation.

<h2>Why This Is Relevant to Security</h2>

During my AD HomeLab I learned about Windows Event IDs and how to spot attacks in Splunk. This project takes that same knowledge and builds a detector around it. A real SOC analyst does this kind of analysis every day, and building it in C++ shows I understand what's happening under the hood, not just how to click buttons in a SIEM.

<h2>Event IDs This Tool Detects</h2>

| Event ID | What It Means | Why It Matters |
|---|---|---|
| 4625 | Failed login attempt | Multiple failures in a row = brute force attack |
| 4624 | Successful login | Logged for reference |
| 4720 | New user account created | Could be an attacker creating a backdoor |
| 4732 | User added to admin group | Privilege escalation - very suspicious |

<h2>Classes Used</h2>

- <b>LogEntry</b> - stores data from one single event log row
- <b>LogParser</b> - reads the CSV file and turns each row into a LogEntry object
- <b>AlertEngine</b> - analyzes all the entries and fires alerts for suspicious patterns

<h2>How to Compile and Run</h2>

```
g++ src/main.cpp src/LogEntry.cpp src/LogParser.cpp src/AlertEngine.cpp -o log-analyzer
./log-analyzer
```

When it asks for a filename, use the sample log included in this project:

```
sample-logs/sample-events.csv
```

<h2>Example Output</h2>

```
==========================================
     WINDOWS EVENT LOG ANALYZER
==========================================
Loaded 18 log entries.

[CHECK] Scanning for new account creation (Event ID 4720)...
  [ALERT] New account created: backdoor_user | 2024-01-15 09:20:15 | IP: 192.168.10.10

[CHECK] Scanning for privilege escalation (Event ID 4732)...
  [ALERT] Privilege escalation detected: backdoor_user | 2024-01-15 09:21:44

[CHECK] Scanning for brute force logins (Event ID 4625, threshold: 5)...
  [ALERT] Brute force detected on account: jsmith | 6 failed attempts
  [ALERT] Brute force detected on account: administrator | 6 failed attempts
```

<h2>Skills Practiced</h2>

| Skill | Where It Shows Up |
|---|---|
| Multiple classes working together | LogEntry, LogParser, AlertEngine |
| File I/O | Reading a CSV file with ifstream |
| String parsing | Splitting CSV rows with stringstream |
| Maps | Counting failures per username using std::map |
| Vectors | Storing all log entries |
| Real security logic | Detecting brute force and privilege escalation |
