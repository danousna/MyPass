# MyPass

### Project

Building a secure password manager app.

### Version 1

Version 1 is a command line interface. You access your accounts with various commands.

Tools    
1. Parser or something to recognize with which argurment program is called.
2. Read and write functions.

App functionality

1. mypass -init
    ...*Creates and encrypt (with password) data file if not here. Hidden file with some infos (header).
2. mypass -ls
    ...*This lists all accounts without password.
3. mypass -a
    ...*This adds an account, will then be prompted for infos about it.
4. mypass -s
    ...*This searches an account by name or user. 
