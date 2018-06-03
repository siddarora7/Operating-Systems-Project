/********************************************************************************************************************************************

Author - Siddhartha Arora
Date - 11/28/2017

The program runs in an infinite loop.

The following program requires rcpbind to execute

to Install rcpbind
On mac, open terminal and type "brew install rpcbind"

On linux, open terminal and type "sudo apt-get install rpcbind"

To execute

On the bash command line or the terminal run the following commands

1. rpcgen file.x       -- This creates the client and server stubs (Those files are already created and attached with the assignment)
2. cc processor.c file_svc.c -o proc
3. cc receiver.c file_clnt.c -o rec
4. On one tab , execute the processor - ./proc
5. On another tab, execute the receiver program - ./rec localhost (if running on local host, otherwise enter hostname)


References - 
https://docs.oracle.com/cd/E19683-01/816-1435/rpcgenpguide-21470/index.html
http://www2.phys.canterbury.ac.nz/dept/docs/manuals/unix/DEC_4.0e_Docs/HTML/AQ0R5BTE/DOCU_003.HTM
https://docs.oracle.com/cd/E19683-01/816-1435/6m7rrfn9f/index.html

*****************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "file.h"
#include <rpc/rpc.h>
#include <stdlib.h>

main(int argc, char **argv)
{
	CLIENT * client;
	int * result;
	char * server;
	char * msg;
	char in[256];

	if(argc != 2)
	{
		fprintf(stderr, "\nUsage of the %s is resulting in an error\n", argv[0]);	//Error with the arguements entered
		exit(1);
	}

	server = argv[1];	//where arguement 1 defines the server address

	while(1)
	{
		printf("\nEnter the the alpha numeric string with the secret code ");
		gets(in);	//Get the text inputted by the user

		msg = in;

		client = clnt_create(server, ASSIGNMENT, ASSIGNMENTVERSION, "tcp");	// Create the onnection to be sent to the stub


		if( client == NULL)
		{
			clnt_pcreateerror(server);
			exit(1);			//Exit due to comnection refusual by the stub. printr error
		}


		result = myassignment_1(&msg, client);

		if(result == (int *) NULL)
		{
			clnt_perror(client, server);
			exit(1);
		}

		if( *result == 0)
		{
			printf(" \nMessage was not transmitted as the secret password entered was not entered/ entered incorrectly\n");
		}
		else
		{
			printf(" \nMessage was succesfully delivered to the server\n");
		}
	}
}