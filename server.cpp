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

int portNumber=8080;
int main()
{
	// Initializing Variable
	int client, server;
	char *buffer;

	struct sockaddr_in server_addr;
	socklen_t size;
	// Socket made
	client = socket(AF_INET, SOCK_STREAM, 0);

	if(client<0)
	{
		cout<<"\n....Error establishing socket...."<<endl;
		exit(1);
	}

	cout<<"\nSocket Server has been created"<<endl;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(portNumber);
	
	//Binding socket to ip and port
	
	if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) 
	{
		cout << "\nError binding connection, the socket has already been established..." << endl;
		return -1;
	}

	size = sizeof(server_addr);
	cout << "Looking for clients..." << endl;
	
	listen(client,5);
	
	int client_count = 1;
	server = accept(client, (struct sockaddr *)&server_addr, &size);

	// Checking validity
	if (server < 0) 
		cout << "Error on accepting..." << endl;

	FILE *f;
	while(server>0)
	{
		buffer =(char *)malloc(1024);
		strcpy(buffer,"Server Connected.... \n");
		
		recv(server,buffer,1024,0);
		char *filename = buffer;
		f = fopen(buffer,"r");
		if( f == NULL)
		{
			cout<<"Cannot open file"<<endl;
			fclose(f);
			close(server);
			close(client);
			exit(1);
		}
		buffer = (char*)memset(buffer,0,1024);	
		int i=0;
		char ch;
		while(fgets(buffer,1024,f) != NULL)
		{
			// if(!((ch>=65 && ch<=90) || (ch>=97 && ch<=122)))
			// {
			// 	printf("%c", ch);
			// // 	cnt++;
			// }
			//printf("%c",buffer[i]);
			send(server, buffer, 1024, 0);
			i++;
		}
		fclose(f);
		//send(server, buffer, 1024, 0);

		cout<<"Connection Terminated with IP \n"<<inet_ntoa(server_addr.sin_addr)<<endl;
		close(server);
		close(client);
		exit(1);
	}
	return 0;
}