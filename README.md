# MyPass

### Project

Building a secure password manager app.

### Version 1
A command line interface. You access your accounts with various commands. Testing for gitlab

Commands:
1. mypass -init
    - Creates and encrypt (with password) data file if not here. Hidden file with some infos (header).
2. mypass -reset
    - Reset the file.
3. mypass -list
    - This lists all accounts without password.
4. mypass -add
    - This adds an account, will then be prompted for infos about it.
5. mypass -s
    - This searches an account by name or user.
