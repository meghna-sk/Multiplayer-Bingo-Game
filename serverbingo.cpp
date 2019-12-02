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
int main(){

	int sockfd, ret,count=0,c=0,exi,y=0,v;
	struct sockaddr_in serverAddr;
	static int inp;
	player mycard1,mycard2;

	int newSocket1,newSocket2;
	struct sockaddr_in newAddr1,newAddr2;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", PORT);

	if(listen(sockfd, 2) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}
	newSocket1 = accept(sockfd, (struct sockaddr*)&newAddr1, &addr_size);
	if(newSocket1 < 0)
		return 1;
	else
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr1.sin_addr), ntohs(newAddr1.sin_port));
	newSocket2 = accept(sockfd, (struct sockaddr*)&newAddr2, &addr_size);
	if(newSocket2 < 0)
		return 1;
	else
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr1.sin_addr), ntohs(newAddr1.sin_port));

	while(1)
	{
		recv(newSocket1,mycard1.arr,25*sizeof(int),0);
		recv(newSocket2,mycard2.arr,25*sizeof(int),0);
		printf("\nWhich player wants to play first?(1/2)");
		scanf("%d",&y);

		if(y==1)
		{
			send(newSocket1,&y,sizeof(int),0);
			y=2;
			send(newSocket2,&y,sizeof(int),0);
		}
		else 
		{
			send(newSocket1,&y,sizeof(int),0);
			y=1;
			send(newSocket2,&y,sizeof(int),0);

		}
		
		
        while(1)
        {
        	recv(newSocket1,&y,sizeof(int),0);
        	mycard1.move(y);
            mycard2.move(y);
            send(newSocket1,mycard1.arr,25*sizeof(int),0);
		    send(newSocket2,mycard2.arr,25*sizeof(int),0);
        	recv(newSocket2,&y,sizeof(int),0);
            mycard1.move(y);
            mycard2.move(y);
            send(newSocket1,mycard1.arr,25*sizeof(int),0);
		    send(newSocket2,mycard2.arr,25*sizeof(int),0);
		    if(mycard1.checkwin()==1)
		    {
		    	 count = 1;
		    	 break;
		    }
		    else if(mycard2.checkwin()==2)
		    {
		    	 count = 2;
		    	 break;
		    }
		    else
		    {
		    	count = 0;
		    	recv(newSocket1,&v,sizeof(int),0);
		    	recv(newSocket2,&v,sizeof(int),0);
		    	send(newSocket1,&count,sizeof(int),0);
		    	send(newSocket2,&count,sizeof(int),0);
        
		    }


        }
        
        send(newSocket1,&count,sizeof(int),0);
		send(newSocket2,&count,sizeof(int),0);
        

		
	}
	return 0;
}