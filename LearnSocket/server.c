#include <sys/types.h>      
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAXSIZE 1024
int main(void){
	struct sockaddr_in serveraddr,clientaddr;
	int sockfd,addrlen,confd,len;
	char ipstr[128];
	char buffer[MAXSIZE];
	//1、创建socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2、bind
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(8000);
	bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	//3、listen
	listen(sockfd,128);
	//4、accept
	while (1) {
        //4.accept阻塞监听客户端链接请求
        addrlen = sizeof(clientaddr);
        confd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);
        //输出客户端IP地址和端口号
        inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipstr, sizeof(ipstr));
        printf("client ip %s\tport %d\n", 
                inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipstr, sizeof(ipstr)),
                ntohs(clientaddr.sin_port));
		len = read(confd,buffer,sizeof(buffer));
		int i;
		for(i = 0; i < len ; i++)
			buffer[i] = toupper(buffer[i]);
		write(confd,buffer,len);
		close(confd);
	}
	close(sockfd);
	
}