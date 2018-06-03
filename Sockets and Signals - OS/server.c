/********************************************************************************************************************************************

Author - Siddhartha Arora
Date - 10/15/2017

Description - This is the second command line program which bascially scans input sent to it by the client.c program bieng run on a differnet machine. 
As soon as one line is received it outputs that line and the no of digits in that line to a file named "secrets.out". Also when the user presses CTRL+C, it outputs a summary
of all lines recieved and the total number of digits recieved accross all inputs 

The program runs in an infinite loop.


To execute

On the bash command line or the terminal run the follwing commands

1. gcc -c server.c
2. gcc -o s server.o
3. Run "./s"
4. To see a summary press CTRL +C 


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
#include <netinet/in.h>
#include <signal.h>
#include <math.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

#define port 8080

int l=0, d=0, s=0;						//Initizing Lines and digits

int count_digits(char *data)
{
	int i =0;

	while (*data != '\0')
	{
		if(isdigit(*data))
			i++;
		data++;
	}

	return i;
}


void ctr_c(int a)							// To service CTRL + C request
{
	printf("\n The total number of lines received by the server are %d",l);
	printf("\n The total number of digits in all the input received by the server is %d ", d);
}
 
int main(int argc, char const *argv[])
{
	
	FILE *f;

	signal(SIGINT, ctr_c);
	int sockfd, new_sock, conn, buf_len;
	struct sockaddr_in s_address, c_address;
	int opt= 1;
	char data[100];	
	char *flag;
	//int addrlen = sizeof(address);
	char buffer[1024] = {0};	

	if(( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Creating the socket failed");
		exit(1);
	}

	if(setsocketopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsocketopt error");
		exit(1);
	}

	memset(&s_address,0,sizeof(s_address));
	s_address.sin_family = AF_INET;
	s_address.sin_addr.s_addr = htonl(INADDR_ANY);
	s_address.sin_port = htons(port);


	//Attaching/binding socket to the port

	if(bind(sockfd, (struct sockaddr*)&s_address, sizeof(s_address)) < 0)
	{
		perror("Error in binding");
		exit(1);
	}

	if(listen(sockfd, 3) < 0)					//Listening on the defined socket with a backlog limit of 3
	{
		perror("Listening error");
		exit(1);
	}

	printf("\n Waiting for a connection");

	int signal_size = sizeof(c_address);
	if(conn = accept(sockfd, (struct sockaddr*)&c_address, &signal_size) < 0)
	{
		perror("accept the conn");
	}

	printf("\nServer");
	printf("\n A connection estabilished with %s ", inet_ntop(AF_INET, &c_address.sin_addr, data, sizeof(data)));



	while(1)
	{
		if((buf_len = recv(conn, buffer, 1023, 0)) < 0)
		{
			printf("\n Could not receive anything from client. Exiting.....");
			exit(1);
		}

		buffer[buf_len] = '\0';

		flag = strstr(buffer, "EXIT");				//Checking to see if the user is trying to exit or not

		if(flag!= NULL)
		{
			printf(" \n User wants to exit");
			exit(1);
		}

		flag = strstr(buffer, "C00L");    // Checking to see the code word - C00L

		if(flag!= NULL)
		{
			l++;

			printf(" \n The string recieved is %s \n", buffer);

			f = fopen("secrets.out", "a");   // Opening file in Append mode
			s = count_digits(buffer);
			d = d + s;

			fprintf(f, "\n Total number of digits are %d", s);
			fprintf(f, "\n The line to print is : %s", buffer);
			fclose(f);
		}

		close(sockfd);

	}
	return 0;
}


