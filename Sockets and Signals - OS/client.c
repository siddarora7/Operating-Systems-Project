/********************************************************************************************************************************************

Author - Siddhartha Arora
Date - 11/11/2017

Description - This is the first command line program which bascially is the client side program and is used to connect to the server to transfer
data

The program runs in an infinite loop and waits for the user to input a alpha numeric string.
Now, it scans the string for the code  "C00L"

If that code is found it sends that string to the server.c program running on a differnt machine

Port - 8080

To execute

On the bash command line or the terminal run the follwing commands

1. gcc -c client.c
2. gcc -o c client.o
3. Run "./r"
4. TO exit type "EXIT"



References - 
http://beej.us/guide/bgipc/output/html/multipage/unixsock.html
http://users.pja.edu.pl/~jms/qnx/help/tcpip_4.25_en/prog_guide/sock_advanced_tut.html
http://www.thegeekstuff.com/2011/12/c-socket-programming/?utm_source=feedburner
https://stackoverflow.com/questions/19207745/htons-function-in-socket-programing

*****************************************************************************************************************************/

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/stat.h>



int main(int argc, char const *argv[])
{
	
	char *ip;
	char *port;

	printf("\nEnter the ip address you want to connect to");
	gets(ip);									//IP adrress
	printf("Enter the port ( It has to be 8080) ");
	gets(port);									//PORT

	int mysocket;
	char *check;
	struct sockaddr_in serveraddress;

	char *buffer = malloc(sizeof(char)*BUFSIZ);      // Dynamically allocating buffer size

	// Creating socket 

	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mysocket <0)
	{
		printf("\n There is an error in creating the socket . Exiting ");
		exit(1);

	}

	// Server side configuration 

	memset(&serveraddress, 0, sizeof serveraddress);
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(atoi(port));
	serveraddress.sin_addr.s_addr = inet_addr(ip);



	// Iniating connection to the server 

	if( connect(mysocket, (struct sockaddr*)&serveraddress, sizeof serveraddress ) < 0)
	{
		printf("\n Connection tot he server is unsuccessful");									//Can't connect to the server ;
		exit(1);

	}
	else
	{
		printf(" \n Connection is successful");
		printf("\n To close the connection and exit type 'EXIT'");						

	}

	while(1)
	{

		printf("\n enter the alpha numeric string with the secret code");
		memset(buffer, 0, sizeof buffer);
		fgets(buffer, BUFSIZ, stdin);										//Getting the string from the user					


		check = strstr( buffer, "EXIT");								//Checking to see if the user wants to EXIT or not

		if(check != NULL)
		{
			if(send(mysocket, buffer, strlen(buffer) , 0) < 0 )
			{
				printf(" Error");									// Sending the exit command to the server as the user wants to terminate the connection
				exit(1);

			}

			printf(" \n User has given exit command. Exiting ");
			exit(1);

		}

		check = strstr(buffer, "C00L");															//Checking fo rthe secret code word
		if(check!= NULL)
		{
			if(send(mysocket, buffer, strlen(buffer), 0) < 0 )										//Sending that string to the server
			{
				perror("some error");
			}

		}
	}

	close(mysocket);


	return 0;
}