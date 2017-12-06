# MyPass

### Project

Building a secure password manager app.

### Version 1

V1 is just a command line interface. You access your accounts with various commands.

Commands
1. mypass -init
    - Creates and encrypt (with password) data file if not here. Hidden file with some infos (header).
2. mypass -ls
    - This lists all accounts without password.
3. mypass -a
    - This adds an account, will then be prompted for infos about it.
4. mypass -s
    - This searches an account by name or user. 
