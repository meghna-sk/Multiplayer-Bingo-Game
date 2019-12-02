#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include"bingo.h"

#define PORT 4444
int main()
{

	int clientSocket, ret,exi,exi2,choice,numb,count,m;
	struct sockaddr_in serverAddr;
	player mycard;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1)
	{
		printf("\nDo you want to play the game (1) or exit (2)?");
		scanf("%d",&choice);

		if(choice==1)
		{
			printf("\nEnter a 5X5 matrix in an order:\n");
			mycard.input();
			send(clientSocket,mycard.arr,25*sizeof(int),0);

			recv(clientSocket,&m,sizeof(int),0);
			do
			{
				if(m==1)
				{
					printf("\nEnter a number to be stricken:");
					scanf("%d",&numb);
					send(clientSocket,&numb,sizeof(int),0);
					recv(clientSocket,mycard.arr,25*sizeof(int),0);
					mycard.display();
					m=2;

				}
				else
				{
					recv(clientSocket,mycard.arr,25*sizeof(int),0);
					mycard.display();
					m=1;
				}
				send(clientSocket,&m,sizeof(int),0);
				recv(clientSocket,&count,sizeof(int),0);
				
				//send(clientSocket,&m,sizeof(int),0);

			}while(count==0);
			
			if(count==1)
			{
				printf("\nPlayer 1 has won!!");
				break;
			}
			if(count ==2)
			{
				printf("\nPlayer 2 has won!!");
				break;
		    }
		}
		else
		{
			break;
		}
		

		
	}
	close(clientSocket);


	return 0;
}