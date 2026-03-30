<h1>Password Strength Checker</h1>

<h2>Description</h2>
In this project, I'm building a command line tool in C++ that checks how strong a password is. The program takes a password as input, runs it through a series of checks, gives it a score out of 100, and tells you what to improve. This is the warmup project to get back into C++ before the bigger security tools.

<h2>What It Does</h2>

- Takes a password as input from the user
- Checks for uppercase letters, lowercase letters, numbers, and special characters
- Checks the length (8+ is okay, 16+ is strong)
- Gives the password a score out of 100
- Rates it as Weak, Fair, Strong, or Very Strong
- Prints suggestions for how to make it stronger

<h2>Why This Is Relevant to Security</h2>

Weak passwords are one of the most common ways attackers get into systems. In my Active Directory HomeLab, I simulated brute force attacks where an attacker tries thousands of passwords automatically. A strong password policy is one of the first defenses against that. This tool checks if a password would hold up.

<h2>Classes Used</h2>

- <b>Password</b> - takes the input string, runs all the checks, stores the score and feedback

<h2>How to Compile and Run</h2>

Make sure you have g++ installed. Then run:

```
g++ src/main.cpp src/Password.cpp -o password-checker
./password-checker
```

<h2>Example Output</h2>

```
Enter a password to check: hello

==========================================
  PASSWORD STRENGTH REPORT
==========================================
  Score  : 20 / 100
  Rating : Weak

  Suggestions to improve:
   - Use at least 8 characters (16+ is much stronger)
   - Add at least one uppercase letter (A-Z)
   - Add at least one number (0-9)
   - Add at least one special character (!@#$%^&* etc.)
==========================================
```

<h2>Skills Practiced</h2>

| Skill | Where It Shows Up |
|---|---|
| Classes and Objects | Password class with private data and public methods |
| Private vs Public | Helper methods are private, report methods are public |
| Loops | Looping through each character to check it |
| Vectors | Storing feedback suggestions in a vector |
| String methods | Using .length() and .find() |
| Boolean logic | Each check returns true or false |
