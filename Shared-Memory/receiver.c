/********************************************************************************************************************************************

Author - Siddhartha Arora
Date - 10/15/2017

Description - This is the first command line program which bascially scans the shared memory space between this program and the processor.c program

The program runs in an infinite loop and waits for the user to input a alpha numeric string.
Now, it scans the string for the code  "C00L"

If that code is found it copies that line of string on to the shared memory space where the second program i.i processor.c can access it.

To execute

On the bash command line or the terminal run the follwing commands

1. gcc -c receiver.c
2. gcc -c processor.c
3. gcc -o r receiver.o
4. gcc -o p processor.c
5. On one tab run "./r"
6. On the other tab run "./p"
7. To exit - "CtrlZ"



References - 
http://simplestcodings.blogspot.com/2010/08/ipc-shared-memory-implementation-in-c.html
http://beej.us/guide/bgipc/output/html/multipage/shm.html
http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmget.html

*****************************************************************************************************************************/


#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>

# define memsize 2046                  //Defining the size of the shared memory


int main()
{
	/* code */
	key_t key;
	int shmid;
	char *shmem;
	char data[100];

	key = 4186;						     //Key of the IPC is my net id

	if ((shmid= shmget(key, memsize, IPC_CREAT |  0666)) < 0)				//Creating the shared memory with paramters key as 4186, size of shared memory
	{																		// and permission levels
		perror("There is an error with creating shared memory segment ");	// If the value returned is less than zero then there is an error with creating the mem
		exit(1);
	}

	if ((shmem =shmat(shmid, NULL, 0)) == (char *) -1 )						// Using the function shmat to access the memory space
	{
		perror("There is an error in acessing the shared space");
		exit(1);
	}

	while(1)													//Infinite loop
	{

		printf("\n Enter your data ");							
		gets(data);											//Getting the data from the user

		if(strstr(data,"C00L")!= NULL)					//Using the strstr function to find the code "C00L"
		{

			strcpy(shmem, data);							//Copying the data to the memory and displaying the user found
			printf("\n FOUNDDDD");
		}

		while(*shmem!='\0')										/*Waiting for the processor.c program to append a terminator at the end
																so that receiver.c knows to get another input from the user. In the meantime its in wait stage.*/		
		{
			sleep(1);
		}
	}


	//return 0;
}
