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

// Port Number same for both server and client.
int portNumber=8080;

int main(int argc, char const *argv[])
{
	int client;
	char *buffer;

	struct sockaddr_in server_addr;

	client = socket(AF_INET, SOCK_STREAM, 0);
	
	if (client < 0) 
	{
		cout << "\nError establishing socket...." << endl;
		exit(1);
	}

	cout<<"Client Socket has been created...."<<endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNumber);

	// Connecting to the server
	if(connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
		cout<<"Connection to the server port number: "<< portNumber << endl;
	
	cout << "Waiting for confirmation from the server...." << endl;

	buffer = (char *)malloc(1024);
	strcpy(buffer,argv[1]);
	send(client, buffer, 1024, 0);

	int ret=recv(client, buffer, 1024, 0);
	
	//cout<<buffer<<endl;
	FILE *f;
	f = fopen("new.txt","w");

	while(ret)
	{
		for(int i=0;i<strlen(buffer);i++)
			fprintf(f,"%c",buffer[i]);
		ret=recv(client, buffer, 1024, 0);
	}
	fclose(f);
	cout << "Connection confirmed, you are connected to the server...."<<endl;

	cout<<"Connection terminated ...."<<endl;

	close(client);
	return 0;
}