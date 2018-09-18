# shell-simulator
A C program that simulates the linux shell. It simulates basic shell commands. For my operating systems class.

# Sample run
![screenshot from 2018-09-15 09-57-47](https://user-images.githubusercontent.com/24194821/45587703-f6e86800-b8ce-11e8-970d-fd0e19fab152.png)

# How to Run
1. run ```gcc shell_program.c -o shell```
2. run ```./shell```

# How it works
* In the main, the getPath function is called to get the system path,
  the getPath function also parses the path data into a 
  2D array which is accessible from the main function.
* A for loop is used to run the shell forever.
* In the for loop, the user input is received and stored.
* The user input is checked, if the user enters the "quit" or "exit", the program stops.
* Otherwise a child process is created.
* In the child process, the executeCommands function is called to execute the users commands.

