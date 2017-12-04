# proj1-GreenShell

## WOWZERS TROWSERS WHAT IS THIS?
This is a `s h e l l`


## A SHELL?
No you fool. Not just any shell. This is a g r e e n shell

## OH MY BATMAN WHAT DOES IT DO
SO glad you asked.

_Features include:_

- The basis of a  shell that you can use to execute bash with
- Simple STDIO file redirection (ex. `ls > file`)
- Cake mix
- An a e s t h e t i c shell prompt



## DOES IT WORK PERFECTLY???
Do I look like frikkin Steve Wozniak to you? I don't think so. Your question is stupid.

_Known bugs include:_
- Intolerance towards spaces between semi colon dividers (ex. `ls; echo hi` is good but `ls ; echo hi` isn't)
- STDIO redirection support technically included but it doesn't work
- Not enough colors

_Missing Features include:_
- No piping (ES-AMEEEE)

## FILES AND FUNCTION HEADERS BECAUSE YOU CAN'T READ
Hey, I know. Opening up header files is tough. Shhh shhh, don't cry.

### shell.c

This is the shell, containing the main method and running the shell loop

**Methods**
- `int main()`: Main method. Runs a loop, displaying a prompt and parsing input

### parse.c

This lil' guy parses the shell arguments from a string, splitting it up by the spaces between two arguments

**Methods**
- `int is_arg_empty(char *arg)`: Returns whether a given argument is empty or not (no characters, whitespace, ect.).
                                 Used for determining which arguments to actually count
- `char **parse_args(char *args)`: Converts a string to an array of strings, each element an argument in a shell call\


### prompt.c

This thingy displays the prompt and makes it look _OH SO FABULOUS_

**Methods**
- `void make_prompt(char *buffer)`: Generates and stores a shell prompt in a given buffer. This prompt closely mimics
                                    the standard linux Bash prompt (`user@machine:directory$` 
                                    including the squiggly tilda for the home directory)

### exec.c

This baby is the meat and potatos of this whole spiel. It handles arguments and executes them.

**Methods**
- `void run_execvp(char **args)`: Cuns execvp on a set of arguments in a child process to make it faster to call execvp
- `void copy_args(char **src_args, char *dest_args[], int to_where)`: Copy all the characters from index 0 to `to_where`
                                                                     from `src_args` to `dest_args`
- `void exec_args(char **args)`: Given an array of string arguments, execute them. This checks for special
                                 keywords (`cd` and `exit`) and handles redirection of stdin and stdout



## OMG HOW DO I USE
How do you not know this

inside the directory, run `make run` and yadone
