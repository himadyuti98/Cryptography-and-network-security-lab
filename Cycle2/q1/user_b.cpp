#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int sfd= socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(atoi(argv[1]));
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.2");
	socklen_t clilen=sizeof(client);
	bind(sfd,(struct sockaddr*)&client,clilen);
	
	connect(sfd,(struct sockaddr*)&saddr, sizeof(saddr));
	perror("connect");

	int sfd1= socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.2");
	saddr.sin_port = htons(atoi(argv[2]));
	connect(sfd1,(struct sockaddr*)&saddr, sizeof(saddr));
	perror("connect");
	
	system("openssl genrsa -out b_a_private.pem 2048");
	system("openssl rsa -check -in b_a_private.pem");
	system("openssl rsa -in b_a_private.pem -out b_a_private.pem");
	system("openssl rsa -in b_a_private.pem -outform PEM -pubout -out b_a_public.pem");
	int fd = open("b_a_public.pem", O_RDONLY);
	char buf[1024];
	read(fd, buf, 1024);
	write(sfd, buf, strlen(buf));
	close(sfd);
	
	system("openssl genrsa -out b_proxy_private.pem 2048");
	system("openssl rsa -check -in b_proxy_private.pem");
	system("openssl rsa -in proxy_a_private.pem -out b_proxy_private.pem");
	system("openssl rsa -in b_proxy_private.pem -outform PEM -pubout -out b_proxy_public.pem");
	fd = open("b_proxy_public.pem", O_RDONLY);
	read(fd, buf, 1024);
	write(sfd, buf, strlen(buf));
	while(true)
	{
		read(sfd, buf, 1024);
		
		system("openssl rsautl -in buff -out enc_msg.dec -inkey b_proxy_private.pem -decrypt");
		system("openssl rsautl -in enc_msg.dec -out enc_msg.dec -inkey b_a_private.pem -decrypt");
		system("cat enc_msg.dec");
	}
	return 0;
}