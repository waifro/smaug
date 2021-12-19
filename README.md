# Smaug - The OSINT for database's
### Search inside every file, folder and subfolder for OSINT
(based on the book The Hobbit, Smaug the dragon)

![image_display](https://i.imgur.com/DCvMnqH.png)

ps: in case you want to sort the database, use [smaug-db-sorter](https://github.com/waifro/smaug/tree/smaug-db-sorter), still under development, it might not give perfect results still. This statement will probably change in the future. By default, it doesn't delete any file after parsing the file, but you can uncomment the line which removes the file (under db_core.c).

### Windows builds only at the moment.

It is **not** an online tool. This program scans your local database to search a variable you specified inside each file with bruteforce.
This tool has been created for utility to search inside every file the containing text input, not all files/folders are supported (outside UTF-8 unicode) atm.
Could be useful for osint individuals.

## usage:

- Place it (smaug.exe) under the root directory containing all files and subfolders.
- Run cmd.exe inside that folder
- run: smaug.exe text_variable 
- Now you wait till it finishes searching. 

Under development, builds available under release.
