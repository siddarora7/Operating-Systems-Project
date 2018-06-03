/* ***************************************************************************************************************************

Author - Siddhartha Arora
Date - 09/28/2017

Description - This is a command line shell program in C which interacts with the user. The program by default gives a prompt to the user to enter 
a command. Once entered it asks if the user wants to append arguements to the command, For example " '-l' argument for the 'ls' command." etc 
Once entered, using the "fork()" command a child process is created. Then using the "execl()" commmand, the input entered by the user is executed.

Now the "fork()" command returns a processID for the child process bieng executed. 
If processID or pid = 0, that means the child process is created and the execution of the child process is handled by the 
"execl_func" function. 

If pid < 0 , that means an error has occured while executing the fork() command. 

If pid > 0 , that is the default case , which means the process Id of the parent process. 

For example
If the user enters "ls" , the shell prompts the user to enter a arguemnet or not.

If the user selects No. Then the shell displays the listing of the file in the current working directory.

If the user selects Yes. And lets say appends '-l' as the argument. then the shell inputs the command as "ls -l" which displays the listing of all files in long format.

TO EXECUTE - 

On the bash command line or terminal, run the follwing commands

gcc -o out sa4186_shell.c                  ---- This creates an executable out file named 'out' compiled from this source code
./out                                      ---- This execute the out file on the bash terminal.


REFERENCES - 
https://www.gnu.org/software/libc/manual/html_node/Executing-a-File.html
https://stackoverflow.com/questions/20381546/how-to-use-execl-to-execute-another-program
https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/waitpid.htm


*****************************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int execl_func(char*,char*,char*);

int main()
{
	/* code */
	char cmd[100];
	int pid = 0;
	//int temp = 0;
	char b;
	char arg[100];
	char p[100];
	int s;
while(1)
	{

		printf("\nEnter your command or enter 'exit' to exit the shell >> ");              //Enter your command
		scanf("%[^\n]%*c", cmd);


		if(strcmp(cmd, "exit")!=0)					
		{
			printf("\nEnter 'y' to append arguments and 'n' for not ");					//Enter arguments or not
			scanf("%c", &b);
			getchar();

			switch(pid=fork())														//Creating the child process
			{
		
				case 0:													//If child process is created 
				if(b=='y')												//If argument entered 
				{
					printf("Enter your argument ");							
					gets(arg);
					strcpy(p,"/usr/bin/");								//Pass the path , command and argument to the execl function
					execl_func(p,cmd,arg);
				}
				else
				{			
					strcpy(p,"/bin/");									//Else pass the chanded path, Command and NULL to the function
					execl_func(p,cmd,NULL);

				}
				break;

				default:												// Default Wait for the child process to execute 
				//wait(10);										
				if(waitpid(pid, &s, 0)!= pid)							//Wait for the child process to change state i.e execute in our case and 	
					s= -1;												// S = -1 indicates waiting for the child process
				//printf("\nParent Process");
				break;

				case -1:												// pid <= -1 . There is an error executing the fork() func.
				perror("There is an error");							// Display the error 
				s= -1;
				break;
				//exit(1);

			}
		}
		else
		{
			exit(1);												// If the user entered exit then exit
		}
	}

	return 0;
}

int execl_func(char* p,char* cmd, char* arg)					//Defining the execl_func
{
	int l;
	//char a[100];
	strcat(p, cmd);

	if(arg==NULL)												//If argument is NULL execute the execl functiomn accordingly 
		l = execl(p,cmd,NULL,NULL);
	else
	{	
		l = execl(p,cmd,arg,NULL);			
		if(l==-1)
		{														// If argument is entered, append path as "/usr/bin/"
			strcpy(p,"/bin/");
			strcat(p,cmd);
			l= execl(p,cmd,arg,NULL);
		}
	}
	return l;													
	

	// char path[100] = "/usr/bin/";
	// //printf("\n The string that yopu entered is %s",cmd);
	// int t = execl(strcat(path,cmd),cmd ,NULL ,NULL);
	// 	return (t);

}