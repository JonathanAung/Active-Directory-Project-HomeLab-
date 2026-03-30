<h1>C++ Port Scanner</h1>

<h2>Description</h2>
In this project, I'm building a basic port scanner in C++ that checks which ports are open on a target IP address. It works by trying to make a TCP connection to each port - if the connection succeeds, the port is open and something is listening on it. This is the same thing Nmap does, just built from scratch so I understand how it works at the socket level.

<h2>Why This Is Relevant to Security</h2>

Port scanning is the first step in almost every penetration test and network audit. During my AD HomeLab I used Kali Linux to attack my own network - now I'm building one of the tools attackers use so I understand it from the ground up. Knowing how a tool works at the code level makes you a much better defender.

<h2>Important</h2>

Only run this scanner on:
- Your own machines (like your VirtualBox VMs from the AD HomeLab)
- Networks you own or have explicit written permission to test

Scanning networks you don't own is illegal.

<h2>Classes Used</h2>

- <b>Target</b> - stores the IP address and the list of open ports found
- <b>Scanner</b> - does the actual TCP connection attempts using Linux sockets

<h2>How to Compile and Run</h2>

This project uses Linux socket libraries so it needs to be compiled on Linux or Kali:

```
g++ src/main.cpp src/Target.cpp src/Scanner.cpp -o port-scanner
./port-scanner
```

Try it against your Splunk VM from the AD HomeLab (192.168.10.10) or your Windows Server (192.168.10.7).

<h2>Example Output</h2>

```
==========================================
           C++ PORT SCANNER
==========================================
Note: only use this on networks you own or have permission to scan.

Enter target IP: 192.168.10.10
Enter start port: 1
Enter end port: 1024

Scanning 192.168.10.10 ports 1 to 1024...
  [OPEN] Port 22 (SSH)
  [OPEN] Port 80 (HTTP)
  [OPEN] Port 8000 (Splunk Web)

Scan complete.
Results for 192.168.10.10:
  Open ports: 22, 80, 8000
```

<h2>Skills Practiced</h2>

| Skill | Where It Shows Up |
|---|---|
| Linux socket programming | socket(), connect(), close() system calls |
| Classes and Objects | Target and Scanner classes |
| Network fundamentals | TCP connections, IP addresses, port numbers |
| Passing objects by reference | Scanner modifies the Target object directly |
| Real offensive security concept | Port scanning is step one of every pentest |
