
/********************************************************************************************************************************************

Author - Siddhartha Arora
Date - 10/15/2017

Description - This is the second command line program which bascially scans the shared memory space between this program and the receiver.c program
for any data saved on the shared space. As soon as one line is received it outputs that line and the no of digits in that line to a file named "secrets.out"

The program runs in an infinite loop.


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

	int shmid;
	int count,i;
	key_t key;
	char *shmem, *d;
	FILE *f;

	f = fopen("secrets.out", "rw+");							//Creating the file in read/write mode

	key = 4186;						// key is my net id 

	if( (shmid = shmget(key, memsize, 0666)) < 0)			//Again checking to see if there is an error 
	{
		perror("There is an error");
		exit(1);
	}

	if( (shmem = shmat(shmid, NULL, 0)) == (char *) -1)					//Accessing the shared memory space
	{
		perror("There is an error in accessing the shared memory ");
		exit(1);
	}

	while(1)
	{
		
		if(*shmem!= '\0')			// Searching the string until a line terminator is found i.e '\0'
		{
			count = 0;				//Initialising count 

			for(d =shmem;*d!='\0';d++)			//Pointimg to the memeory using pointer d and incrementing count for every digit found
			{
				if(*d=='0'||*d=='1'||*d=='2'||*d=='3'||*d=='4'||*d=='5'||*d=='6'||*d=='7'||*d=='8'||*d=='9')
					{
					count++;
					}
			}
		


		
		f = fopen("secrets.out", "a");				//opening the file in append mode

		fprintf(f, "%s - %d", shmem, count);		//Appendimg the string as well as the no of digits value

		fclose(f);

		*shmem ='\0';							//Appending '\0' so that receiver.c knows to come out of sleep and accept the next input
		}

	}

	if(shmdt(shmem) == -1)							//Detaching the shared memory segment
	{
		perror("Error in detaching the segment");
		exit(1);
	}

}