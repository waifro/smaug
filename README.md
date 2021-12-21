# smaug-db-sorter - organize and save space on your Database
### Search inside every file, folder and subfolder for OSINT
(based on the book The Hobbit, Smaug the dragon)

![image_display](https://i.imgur.com/DCvMnqH.png)

(old screenshot)

### Windows builds only at the moment.

smaug-db-sorter is a modified version of [smaug-c9de92](https://github.com/waifro/smaug/commit/1c9de92c9c59e0c09a416e5dd84fa7bad6cb3546)


```
./database
  -/db-sort
    -/!symbols
    -/!numbers
    -/a-A
    -/b-B
    -/c-C
    -/d-D
    -/e-E
    etc...
```

It sorts your database in the following directory tree, and also deletes the files successfully parsed (disabled by Default untill further developmnent).
It also skips none `*.txt` files.

## Compile:
theres no third-party library involved other then mman-win32 for Windows builds.
- Unix: run `Make` under `smaug-master` folder.
- Windows: uncomment line 3 on Makefile, save, and run `Make` under `smaug-master` folder.

## usage:

- Place it (smaug-db-sorter.exe) under the root directory containing all files and subfolders.
- Run cmd.exe inside that folder
- run: smaug-db-sorter
- Now you wait till it finishes sorting.

Under development, builds not available atm.
