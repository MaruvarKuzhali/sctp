#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include<strings.h>
#include <arpa/inet.h>
#include<stdlib.h>

struct chunk_s {
int type;
int length;
char buff[80];
};

void main()
{
int b,sockfd,sin_size,con,n,len;
int choose;

if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("socket created sucessfully\n");
struct sockaddr_in servaddr;

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=6006;


sin_size = sizeof(struct sockaddr_in);
if((con=connect(sockfd,(struct sockaddr *) &servaddr, sin_size))==0); 
printf("connect sucessful\n");
struct chunk_s chunks;
bzero(&chunks,sizeof(chunks));
chunks.type=1;
strcpy(chunks.buff,"INIT");
chunks.length=sizeof(chunks.buff);
write(sockfd,&chunks,sizeof(chunks));
printf("INIT SENT\n");
bzero(&chunks,sizeof(chunks));
read(sockfd,&chunks,sizeof(chunks));
if(chunks.type == 2)
{
	printf("ACK RECEIVED\n");
	chunks.type=10;
	strcpy(chunks.buff,"COOKIE ECHO");
	chunks.length = sizeof(chunks.buff);
	printf("COOKIE ECHO SENT\n");
}
else
{
	printf("ACK NOT RECEIVED SUCCESSFULLY\n");
	exit(1);
}
write(sockfd,&chunks,sizeof(chunks));
bzero(&chunks,sizeof(chunks));
read(sockfd,&chunks,sizeof(chunks));
if(chunks.type == 11)
{
	printf("COOKIE ACK RECEIVED\n");
	for (;;)
	{
		bzero(&chunks,sizeof(chunks));
		printf("Enter the your choice: 1.Send Data 2.Heartbeat Request 3.Abort\n");
		scanf("%d",&choose);
		switch(choose)
		{
			case 1:
				n=0;
				printf("Enter the data to be sent : ");
				//while((chunks.buff[n++] = getchar()) != '\n');
				scanf("%s",&chunks.buff);
				char line;
				scanf("%c",&line);
				chunks.type = 0;
				chunks.length = sizeof(chunks.buff);
				write(sockfd,&chunks,sizeof(chunks));
				bzero(&chunks,sizeof(chunks));
				break;
			case 2:
				chunks.type = 4;
				strcpy(chunks.buff,"HEARTBEAT REQUEST");
				chunks.length = sizeof(chunks.buff);
				write(sockfd,&chunks,sizeof(chunks));
				bzero(&chunks,sizeof(chunks));
				break;
			case 3:
				chunks.type = 6;
				strcpy(chunks.buff,"");
				chunks.length = 0;
				write(sockfd,&chunks,sizeof(chunks));
				printf("SOCKET CLOSED. PROCESS ABORTED\n");
				close(sockfd);
				exit(1);
				bzero(&chunks,sizeof(chunks));
				break;
		}
		read(sockfd,&chunks,sizeof(chunks));
		switch(chunks.type)
		{
			case 0:
				printf("%s\n",chunks.buff);
				break;
			case 5:
				printf("%s\n",chunks.buff);
		}
	}
}
else
{
	printf("COOKIE SET NOT SUCCESSFUL\n");
	exit(1);
}
close(sockfd);

}
