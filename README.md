<h1 align="Center" style="font-size:50px">Smaug - The OSINT for database's</h1>

<p align="Center">
    Search inside every file, folder and subfolder for OSINT<br>
    (based on the book The Hobbit, Smaug the dragon)
</p>

<p align="Center">
    <a href="https://github.com/waifro/smaug"><img src="https://i.imgur.com/DCvMnqH.png"></a>
</p>

<p align="Center">
    in case you wanted to sort out your database to save up space,<br>
    look at the tool under this branch <a href="https://github.com/waifro/smaug/tree/smaug-db-sorter">smaug-db-sorter</a>
</p>

<p align="Center">
    <a href="https://github.com/waifro/smaug#compile">Compile</a> • 
    <a href="https://github.com/waifro/smaug#usage">Usage</a>
</p>

<p align="Center">
    There are only available old Windows builds from smaug v0.1<br><br>
    It is **not** an online tool. This program scans your local database to search a variable you specified inside each file with bruteforce.<br>
    This tool has been created for utility to search inside every file which contains your input,<br>
    and also not all files/folders are supported (outside UTF-8 unicode) atm.<br>
    Could be useful for osint individuals.<br>
</p>

<h1 align="Center" style="font-size:30px">Compile</h1>

- Unix: run `make` inside `smaug-main`

- Windows: 
    - linux enviroment, example WSL or Chocolatey, run `make` inside `smaug-main`.
    - otherwise, if you are running inside an IDE, just compile the program specifying the `Makefile` under `smaug-main`.

<h1 align="Center" style="font-size:30px">Usage</h1>

- Place it (smaug.exe) under the root directory containing all files and subfolders.
- Run cmd.exe inside that folder
- run: smaug.exe text_variable 
- Now you wait till it finishes searching. 

Under development, builds available under release.
