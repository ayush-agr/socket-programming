#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Port Number same for both server and client. We have predefined it.
int portNumber=8080;

int main(int argc, char const *argv[])
{

	if(argc <= 1)
	{
		printf("Correct Usage: ./client [file name]\n");
		exit(1);
	}
    /*
       client is a file descriptor to store the values 
       returned by the socket system call and the accept 
       system call.
    */
	int client;
	
	/*
	   Characters exchanged on the socket connection are stored
	   into a dynamically defined variable "buffer".
	*/
	char *buffer;

    /*
    Structure of struct sockaddr_in is as follows : 

    struct sockaddr_in
        {
          short   sin_family;
          u_short sin_port;
          struct  in_addr sin_addr;
          char    sin_zero[8];
        };

    Its already defined in <netinet/in.h> header file.
    */

	// server_addr contains the address of the server
	struct sockaddr_in server_addr;


    /*
       socket() function takes 3 arguments for creating a new socket. They are as follows:
       a. AF_INET: It is the address domain of the socket.
       
       b. SOCK_STREAM: A stream socket in which characters are read in a continuous stream 
          i.e., Transmission Control Protocol (TCP)
       
       c. Third is a protocol argument: The OS chooses the most appropiate protocol.
       0 is given generally as an input for this.

       It returns a small integer and is used generally for all 
       references to this socket. A negative value is returned, if the socket call fails. 
    */
	client = socket(AF_INET, SOCK_STREAM, 0);
	
	if (client < 0) 
	{
		cout << "\nError establishing socket...." << endl;
		exit(1);
	}

	cout<<"Client Socket has been created...."<<endl;

    /* 
        server_addr is a structure of sockaddr_in as declared above. 
        sin_family contains a code for the address family. 
        It should always be set to AF_INET.

        htons() converts the port number from unsigned short host byte order 
        to a port number in network byte order.

    */
    
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNumber);

	// Connecting to the server

	/*
	    The connect function is called by the client to 
        establish a connection to the server. It takes 
        three arguments, the socket file descriptor, the 
        address of the host to which it wants to connect 
        (including the port number as mentioned in the struvture definition), 
        and the size of this address. 

        This function returns 0 on success and negative value 
        if it fails.
	*/

    /*if(inet_pton(AF_INET,"10.1.39.90",&server_addr.sin_addr)<=0)
    {
        printf("Invalid Address\n");
        return -1;
    }*/
	if(connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
		cout<<"Connection to the server port number: "<< portNumber << endl;
	
	cout << "Waiting for confirmation from the server...." << endl;

	buffer = (char *)malloc(1024);

	// argv[1] contains 
	strcpy(buffer,argv[1]);
	send(client, buffer, 1024, 0);

	int ret=recv(client, buffer, 1024, 0);
	
	//cout<<buffer<<endl;
	FILE *f;

	// Creating/Opening of the file to download from server.
	f = fopen(argv[1],"w");

    if(f == NULL)
    {
        cout<<"File Couldn't be opened\n";
        exit(1);
    }

	while(ret)
	{
		for(int i=0;i<strlen(buffer);i++)
			fprintf(f,"%c",buffer[i]);
		// receiveing data of the file from server.
		ret=recv(client, buffer, 1024, 0);
	}

	fclose(f);
	cout << "Connection confirmed, you are connected to the server...."<<endl;

	cout<<"Connection terminated ...."<<endl;

	// Closing the connection.
	close(client);
	return 0;
}
