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
int main()
{
	// Initializing Variables

	/*
       client is a file descriptor to store the values 
       returned by the socket system call and the accept 
       system call.
    */

	int client, server;

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
	
	// socklen_t  is an integer type of width at least 32 bits
	socklen_t size;
	
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

	if(client<0)
	{
		cout<<"\n....Error establishing socket...."<<endl;
		exit(1);
	}
	int en=1;
	if (setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int)) < 0)
    	printf("setsockopt(SO_REUSEADDR) failed");

	cout<<"Socket Server has been created...."<<endl;
	
    /* 
        server_addr is a structure of sockaddr_in as declared above. 
        sin_family contains a code for the address family. 
        It should always be set to AF_INET.

        INADDR_ANY contains the IP address of the host. For 
        server code, this will always be the IP address of 
        the machine on which the server is running.

        htons() converts the port number from unsigned short host byte order 
        to a port number in network byte order.
    */
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(portNumber);
	
	/* 
        The bind() system call binds a socket to an address, 
        in this case the address of the current host and port number 
        on which the server will run. The three arguments are: 
        the socket file descriptor, pointer to a structure of type 
        sockaddr which must be cast to the correct type.
    */
	if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) 
	{
		cout << "\nError binding connection, the socket has already been established..." << endl;
		return -1;
	}

	size = sizeof(server_addr);
	cout << "Looking for clients..." << endl;
	
	/* 
        The listen system call allows the process to listen 
        on the socket for connections. 

        The program will be stay idle here if there are no 
        incomming connections.

        The first argument is the client socket file descriptor, 
        and the second is the size for the number of clients(at max 5) 
        i.e the number of connections that the server can 
        handle while the process is handling a particular 
        connection.
    */

	listen(client,5);
	
	int client_count = 1;

	/*
		The accept system call causes the program to block until client 
		server connection takes place. It returns a new file descriptor
		that is used for all commnunications. (struct sockaddr *)&server_addr
		is a reference pointer to the address of client.
	*/
	server = accept(client, (struct sockaddr *)&server_addr, &size);

    // Checking Validity
	if (server < 0) 
    {
		cout << "Error on accepting..." << endl;
        exit(1);
    }

    // File pointer f is created for pointing a file.
	FILE *f;
	while(server>0)
	{
		buffer =(char *)malloc(1024);
		strcpy(buffer,"Server Connected.... \n");
		
		recv(server,buffer,1024,0);

		// opening the file in read binary mode
        char dirloc[1500]="../Data/";
        strcat(dirloc,buffer);

        printf("%s\n",dirloc);

		f = fopen(dirloc,"r");
		if( f == NULL)
		{
			cout<<"Cannot open file"<<endl;
			close(server);
			close(client);
			exit(1);
		}
		buffer = (char*)memset(buffer,0,1024);	
		int i=0;
		char ch;
		while(fgets(buffer,1024,f) != NULL)
		{
			//cout<<"Sending bytes ...."<<endl;
			send(server, buffer, 1024, 0);
			i++;
		}
		fclose(f);
		cout<<"Connection Terminated with IP "<<inet_ntoa(server_addr.sin_addr)<<endl;
		close(server);
		close(client);
		exit(1);
	}
	return 0;
}
