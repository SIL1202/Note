# Commands for pwd, ls, cd 

## Shows the current directory
    pwd  

## Lists the content of the directory
> #### ls [option] [fd]
> man ls
```
ls
``` 
```
ls -l    // For list out long format

➜  ~ ls -l
total 8
drwxr-xr-x    4 sil  staff    128  2  6 12:24 App develop
drwx------@   8 sil  staff    256  4 24 21:56 Applications
drwx------@   4 sil  staff    128  4 20 11:48 Desktop
drwx------@  13 sil  staff    416  4 24 11:39 Documents
drwx------@ 498 sil  staff  15936  4 25 11:11 Downloads
-rw-r--r--@   1 sil  staff   3037  3 28 15:08 goFile.cpp
drwxr-xr-x@   5 sil  staff    160  4 12 10:34 Hack
drwx------@ 114 sil  staff   3648  4 14 22:45 Library
drwx------@   8 sil  staff    256  7 17  2024 Movies
drwx------@   6 sil  staff    192  2  9 21:54 Music
drwx------   12 sil  staff    384  4 20 01:15 Nextcloud
drwx------+   9 sil  staff    288  4 10 10:00 Pictures
drwxr-xr-x@  20 sil  staff    640  4  5 21:44 Projects
drwxr-xr-x+   5 sil  staff    160  4 16  2024 Public
drwxr-xr-x@   8 sil  staff    256  4 19 23:35 RaylibGame
drwxr-xr-x@  22 sil  staff    704  2 12 16:21 SFML
drwxr-xr-x@   7 sil  staff    224  4 22 11:48 Sophomore
```
```
ls -a    // For list all hidden files

➜  Projects ls -a
.                  .ipynb_checkpoints CSES               GameProject        MyQtApp            Practice           sil.github.io
..                 AtCoder            EchoMind           HackerEarth        NDHU Projects      Python             UVA
.DS_Store          Bash               Game2              Leetcode           NOTE               ShellScript                                  .zsh
```
```
ls -al    // For list all the hidden files in long format

➜  Projects ls -al
total 32
drwxr-xr-x@ 20 sil  staff    640  4  5 21:44 .
drwxr-x---+ 67 sil  staff   2144  4 26 11:39 ..
-rw-r--r--@  1 sil  staff  12292  4 23 22:34 .DS_Store
drwxr-xr-x   3 sil  staff     96  5 24  2024 .ipynb_checkpoints
drwxr-xr-x@ 11 sil  staff    352  4 12 10:34 AtCoder
drwxr-xr-x@  4 sil  staff    128  2 15 21:05 Bash
drwxr-xr-x@  7 sil  staff    224  4 12 10:34 CSES
drwxr-xr-x@ 13 sil  staff    416  4 12 10:34 EchoMind
drwxr-xr-x@ 14 sil  staff    448  4  6 15:19 Game2
drwxr-xr-x@ 13 sil  staff    416  4  5 22:46 GameProject
drwxr-xr-x@  8 sil  staff    256  4 12 10:34 HackerEarth
drwxr-xr-x@ 13 sil  staff    416  4 12 10:34 Leetcode
drwxr-xr-x@  8 sil  staff    256  4 12 10:34 MyQtApp
drwxr-xr-x@  6 sil  staff    192  4 21 12:46 NDHU Projects
drwxr-xr-x@  7 sil  staff    224  4 26 10:41 NOTE
drwxr-xr-x@  9 sil  staff    288  4 12 10:34 Practice
drwxr-xr-x@  3 sil  staff     96  3 10 17:10 Python
drwxr-xr-x@  7 sil  staff    224  4 12 10:34 ShellScript
drwxr-xr-x@  8 sil  staff    256  3  8 14:42 sil.github.io
drwxr-xr-x@  9 sil  staff    288  4 12 10:34 UVA
```
```
ls -R     // Recursively list subdirectories encountered

➜  File_Management git:(main) ✗ ls -R parent
f1 f2 f3

parent/f1:

parent/f2:

parent/f3:
```

