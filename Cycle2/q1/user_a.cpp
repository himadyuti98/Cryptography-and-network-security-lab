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
	int sfd1, sfd2;
	struct sockaddr_in serv_addr,cli_addr1, cli_addr2;
	socklen_t cli_len1, cli_len2;
	int port_no=atoi(argv[1]);

	if((sfd1 = socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("\n socket ");
	else printf("\n socket created successfully");
	if((sfd2 = socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
	
	if(bind(sfd1,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
		perror("\n bind : ");
	else printf("\n bind successful ");

	port_no=atoi(argv[2]);
	serv_addr.sin_port = htons(port_no);
	if(bind(sfd2,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
		perror("\n bind : ");
	else printf("\n bind successful \n");

	listen(sfd1,10);
	listen(sfd2,10);

	cli_len1=sizeof(cli_addr1);
	cli_len2=sizeof(cli_addr2);
	int nsfd1, nsfd2;
	if(nsfd1 = accept(sfd1 , NULL, NULL)==-1)
		perror("\n accept ");
	else printf("\n accept successful");
	if(nsfd2 = accept(sfd2 , NULL, NULL)==-1)
		perror("\n accept ");
	else printf("\n accept successful\n");
	
	char buff[1024];
	read(nsfd1,buff,1024);
	//printf("%s\n", buff);
	int fd = open("a_proxy_public.pem", O_RDWR|O_CREAT);
	write(fd, buff, strlen(buff));
	read(nsfd2, buff, 1024);
	fd = open("a_b_public.pem", O_RDWR|O_CREAT);
	write(fd, buff, strlen(buff));
	while(true)
	{
		cin>>buff;
		fd = open("msg.txt", O_RDWR|O_CREAT);
		write(fd, buff, strlen(buff));
		system("openssl rsautl -in msg.txt -out enc_msg.enc -pubin -inkey a_b_public.pem -encrypt");
		system("openssl rsautl -in enc_msg.enc -out enc_msg.enc -pubin -inkey a_proxy_public.pem -encrypt");
		fd = open("enc_msg.enc", O_RDONLY);
		read(fd, buff, 1024);
		write(nsfd1, buff, strlen(buff));
	}

	return 0;
}