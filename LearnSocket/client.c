#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXSIZE 1024
#define SERVER_PORT 8000
int main(int argc,char argv[]){
	struct sockaddr_in serveraddr;
	int confd,len;
	char ipstr[] = "172.27.62.172";
	char buf[MAXSIZE];
	if(argc < 2){
		printf("./client str\n");
		return 0;
	}
	confd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;

    inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port  = htons(SERVER_PORT);
    //3.链接服务器
    connect(confd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    //4.请求服务器处理数据
    write(confd, argv[1], strlen(argv[1]));
    len = read(confd, buf, sizeof(buf));
    printf(buf);

    //5.关闭socket
    close(confd);
    return 0;
	
}