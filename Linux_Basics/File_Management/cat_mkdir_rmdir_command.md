# cat, mkdir, rmdir command

# cat

> ## cat [options] [filename]
```
cat -b [filename]    // number the non-blank lines
```
```markdown
cat -n [filename]    // number the output lines
```

> ## cat << [terminal condition word] >> [output file name]
>
> ```cpp
> cat << [terminal condition word] >> [output file name]>>> [terminal condition word]
> >
> >
> > [terminal condition word]
> ```
>
> ### For coding cpp program:
>
> #### 	alias cpp='g++ -x c++ -std=c++20 -o temp - && ./temp'
>
> ```cpp
> ➜  File_Management git:(main) ✗ cat << EOF | cpp
> cmdand heredoc> #include<iostream>
> cmdand heredoc> int main(){
> cmdand heredoc>   std::cout << "Hello World\n";
> cmdand heredoc> 	return 0;
> cmdand heredoc> }
> cmdand heredoc> EOF
> Hello World
> ```
>
> 



> ## cat >> [output file name]
>
> * control + d to exit
>
> ```
> ➜  File_Management git:(main) ✗ cat >> output.txt
> first
> scond
> third
> ➜  File_Management git:(main) ✗ bat output.txt
> ───────┬───────────────────────────────────────────────────────────────────────
>        │ File: output.txt
> ───────┼───────────────────────────────────────────────────────────────────────
>    1   │ first
>    2   │ scond
>    3   │ third
> ───────┴───────────────────────────────────────────────────────────────────────
> ```
>
> 

* ## Bonus:

  >## echo '[statement]' >> [output file name]
  >
  >```
  >➜  File_Management git:(main) ✗ echo 'here is a test' >> output.txt
  >➜  File_Management git:(main) ✗ bat output.txt
  >───────┬───────────────────────────────────────────────────────────────────────
  >       │ File: output.txt
  >───────┼───────────────────────────────────────────────────────────────────────
  >   1   │ first
  >   2   │ scond
  >   3   │ third
  >   4   │ here is a test
  >───────┴───────────────────────────────────────────────────────────────────────
  >```
  >
  >

# mkdir

> mkdir [options] [foldername]

```
mkdir [foldername]
```
```
mkdir -p [parent]/[children]
```
```
mkdir -p [parent]/{[children1],[children2],[children3]} // space between childrens is no needed

➜  File_Management git:(main) ✗ mkdir -p parent/{f1,f2,f3} && ls parent
f1 f2 f3

```
# rmdir

> ## rmdir [options] [foldername] // Remove the empty directory

```
➜  File_Management git:(main) ✗ rmdir a/b/c/d/e
➜  File_Management git:(main) ✗ ls -R
a                     

./a:
b

./a/b:
c

./a/b/c:
d

./a/b/c/d:
```
> ## rmdir -p [directory]    //Each directory argument is treated as a pathname of which all 

```
components will be removed, if they are empty, starting with the last most component.

➜  File_Management git:(main) ✗ rmdir -p a/b/c/d/e
                        or
➜  File_Management git:(main) ✗ rmdir -pv a/b/c/d/e
a/b/c/d/e
a/b/c/d
a/b/c
a/b
a
```

> ## rm -r [directory]
>

```
➜  ~ rm -rv a
a/b/c/d/e
a/b/c/d
a/b/c
a/b
a
```
