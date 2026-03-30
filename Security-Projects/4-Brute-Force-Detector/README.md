<h1>Brute Force Detection System</h1>

<h2>Description</h2>
In this project, I'm building a C++ tool that reads a login attempt log file and automatically detects brute force attacks. It tracks how many times each username and each IP address appears in failed logins, and fires an alert when the count goes above a threshold. This is the detection logic behind the Splunk alerts I was building in my AD HomeLab, except now I'm coding it myself.

<h2>Why This Is Relevant to Security</h2>

In my Active Directory HomeLab I used Atomic Red Team to simulate brute force attacks and watched them show up in Splunk as a flood of Event ID 4625 (failed login). This project builds the detection side of that from scratch. If I can explain how brute force detection works at the code level in an interview, that's a big deal.

<h2>How It Works</h2>

The tool reads a CSV log file where each row is one login attempt. It then:
<br />
1. Counts failed attempts per username - if jsmith fails 6 times, that's suspicious
<br />
2. Counts failed attempts per IP address - if 192.168.10.250 fails 8 times, that attacker IP gets flagged
<br />
3. Prints a summary of total, failed, and successful attempts
<br />

<h2>Classes Used</h2>

- <b>LoginAttempt</b> - stores one single login event from the log file
- <b>DetectionEngine</b> - loads the file, counts failures, and fires alerts

<h2>How to Compile and Run</h2>

```
g++ src/main.cpp src/LoginAttempt.cpp src/DetectionEngine.cpp -o brute-detector
./brute-detector
```

Use the sample log included in this project:

```
sample-logs/sample-logins.csv
```

<h2>Example Output</h2>

```
==========================================
     BRUTE FORCE DETECTION SYSTEM
==========================================
Enter log file path: sample-logs/sample-logins.csv

Summary: 20 total attempts | 15 failed | 5 successful

[CHECK] Brute force by username (threshold: 5 failures)
  [ALERT] jsmith - 6 failed login attempts
  [ALERT] administrator - 8 failed login attempts

[CHECK] Brute force by IP address (threshold: 5 failures)
  [ALERT] 192.168.10.5 - 6 failed attempts
  [ALERT] 192.168.10.250 - 8 failed attempts
```

<h2>Skills Practiced</h2>

| Skill | Where It Shows Up |
|---|---|
| File I/O | Reading a CSV with ifstream |
| Maps | std::map to count failures per username and per IP |
| Classes and Objects | LoginAttempt and DetectionEngine |
| Boolean logic | Tracking success vs failure per attempt |
| Real defensive security | This is literally how IDS tools work |
