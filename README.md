<h1>Active-Directory-Project-HomeLab</h1>

 ### [YouTube Guide](https://www.youtube.com/watch?v=5OessbOgyEo&list=PLG6KGSNK4PuBWmX9NykU0wnWamjxdKhDJ&index=13)

<h2>Description</h2>
In this project, I’m setting up an Active Directory home lab with Splunk, Kali Linux, and Atomic Red Team. I'll try to simulate how a domain environment works, how to feed events into a SIEM, and generate telemetry from real-world attacks to help me get familiar with them for future projects/jobs.
<br />
<p align="center">
Diagram of Project: <br/>
 <img src="https://i.imgur.com/SKUzoNX.png" height="80%" width="80%" alt="Project Diagram"/>
</p>

<h2>Virtual Box VM Machines used</h2>

- <b>Windows 10</b> 
- <b>Windows 2022 Server</b>
- <b>Ubuntu Server Splunk</b>
- <b>Kali Linux</b>

<h2>Installations & Configurations:</h2>
Before we do anything, we want to make sure our Virtual Machines are on the same network. We do this by going to "Tools", then "Network". Once we are there, select NAT-network and click on create. For simplicty purpose, I will be naming the network as "AD Project" and have the IPv4 Prefix as : 192.168.10.0/24 as shown in the diagram. Leave the "Enable DHCP" as it is and once we are done with all that, hit apply.
<p align="center">
Launch the utility: <br/>
<img src="https://i.imgur.com/42E2xEe.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Select the disk:  <br/>
<img src="https://i.imgur.com/tcTyMUE.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Enter the number of passes: <br/>
<img src="https://i.imgur.com/nCIbXbg.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Confirm your selection:  <br/>
<img src="https://i.imgur.com/cdFHBiU.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Wait for process to complete (may take some time):  <br/>
<img src="https://i.imgur.com/JL945Ga.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Sanitization complete:  <br/>
<img src="https://i.imgur.com/K71yaM2.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Observe the wiped disk:  <br/>
<img src="https://i.imgur.com/AeZkvFQ.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
