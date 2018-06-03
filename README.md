## Operating-Systems-Project


### Shell simulator using parent and child processes
Description - This is a command line shell program in C which interacts with the user. The program by default gives a prompt to the user to enter a command. Once entered it asks if the user wants to append arguements to the command, For example " '-l' argument for the 'ls' command." etc Once entered, using the "fork()" command a child process is created. Then using the "execl()" commmand, the input entered by the user is executed.

### Shared Memory
Set of two programs to demonstrate sharing of a shared memory space.
* reciever.c
This is the first command line program which bascially scans the shared memory space between this program and the - processor.c program
The program runs in an infinite loop and waits for the user to input a alpha numeric string. Now, it scans the string for the code "C00L" If that code is found it copies that line of string on to the shared memory space where the second program i.i processor.c - - can access it.
* processor.c
This is the second command line program which bascially scans the shared memory space between this program and the
receiver.c program for any data saved on the shared space. As soon as one line is received it outputs that line and the no -- of digits in that line to a file named "secrets.out"
-This program also runs in an infinite loop.
