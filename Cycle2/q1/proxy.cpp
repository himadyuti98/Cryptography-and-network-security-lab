#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char * argv[])
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

	
	system("openssl genrsa -out proxy_a_private.pem 2048");
	system("openssl rsa -check -in proxy_a_private.pem");
	system("openssl rsa -in proxy_a_private.pem -out proxy_a_private.pem");
	system("openssl rsa -in proxy_a_private.pem -outform PEM -pubout -out proxy_a_public.pem");
	int fd = open("proxy_a_public.pem", O_RDONLY);
	char buf[10240];
	int s = read(fd, buf, 10240);
	cout<<s<<endl;
	send(sfd, buf, strlen(buf), 0);
	perror("write");
	sleep(1);
	int sfd1 = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	int port1 = atoi(argv[2]);
	client.sin_port = htons(port1);
	bind(sfd1, (struct sockaddr*)&client, clilen);
	perror("bind");
	listen(sfd1, 10);

	int nsfd = accept(sfd1, NULL, NULL);
	perror("accept");
	char buff[1024];
	read(nsfd,buff,1024);
	//printf("%s\n", buff);
	fd = open("proxy_b_public.pem", O_RDWR|O_CREAT);
	write(fd, buff, strlen(buff));

	while(true)
	{
		read(sfd, buff, 1024);
		system("openssl rsautl -in buff -out enc_msg.dec -inkey proxy_a_private.pem -decrypt");
		system("openssl rsautl -in enc_msg.dec -out enc_msg.enc -pubin -inkey proxy_b_public.pem -encrypt");
		fd = open("enc_msg.enc", O_RDONLY);
		read(fd, buff, 1024);
		write(nsfd, buff, strlen(buff));
	}

}