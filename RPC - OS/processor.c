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
#include  <stdio.h>
#include  "file.h"
#include  <string.h>


int * myassignment_1_svc( char ** msg , struct svc_req * req)
{

	FILE *f;

	static int result;
    f =fopen("secrets.out", "a");	//Opening file in append mode to edit

    if(f == (FILE *) NULL){

    	result = 0;					//If the file is empty returning 0 as the result
    	return (&result);
    }


	int length = strlen (*msg);
	char s[1000];

	strcpy(s,*msg);

	char *flag;

	flag = strstr(s, "C00L");		//Checking the string for the secret word "C00L"	

	// if(flag == NULL)
	// {	
	// 	fclose(f);
	// 	result =0;
	// 	printf("\n Secret word");
	// 	return (&result);
	// }

	
	if(flag!= NULL){
	
	printf("\nCorrect password entered");
	}
	else
	{
		fclose(f);
		result = 0;
		//printf(" Secret pass not found");
		return (&result);
	}

	int cnt = 0;
	for (int i = 0; i<length; i++)
	{
		if(s[i] >='0' && s[i] <='9')	// Counting the number of digits in the string
			{cnt++;
			}
	}

	cnt = cnt -2;			//Subtracting 2 so as to not include the digits in the password
 fprintf(f,"%d : %s\n", cnt, *msg);		// Appending the count and message to the file secrets.out 
	fclose(f);
	result = 1;

	return(&result);

}
