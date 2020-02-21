#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<gmp.h>


using namespace std;

struct key
{
	char k[1024];
	char n[1024];
};

void encrypt(mpz_t cipher_text, mpz_t plain_text, mpz_t public_key, mpz_t n)
{
	cout<<plain_text<<" "<<public_key<<" "<<n<<endl;
	mpz_powm(cipher_text, plain_text, public_key, n);
}

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

	listen(sfd1,10);

	
	int nsfd1, nsfd2;
	nsfd1 = accept(sfd1 , NULL, NULL);
		perror("\n accept ");
	cout<<"nsfd1 "<<nsfd1<<endl;
	key a_proxy_public_str;
	int s = recv(nsfd1,a_proxy_public_str.k,1024, 0);
	perror("recv");
	cout<<s<<endl;
	recv(nsfd1,a_proxy_public_str.n,1024, 0);
	perror("recv");
	//printf("%s\n", buff);
	cout<<"recd public key from proxy\n";
	cout<<a_proxy_public_str.k<<" "<<a_proxy_public_str.n<<endl;


	port_no=atoi(argv[2]);
	serv_addr.sin_port = htons(port_no);
	if(bind(sfd2,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
		perror("\n bind : ");
	else printf("\n bind successful \n");

	
	listen(sfd2,10);

	nsfd2 = accept(sfd2 , NULL, NULL);
		perror("\n accept ");
	
	
	key a_b_public_str;
	s = recv(nsfd2, a_b_public_str.k, 1024, 0);
	cout<<s<<endl;
	perror("recv");
	recv(nsfd2, a_b_public_str.n, 1024, 0);
	perror("recv");
	cout<<"recd public key from b\n";
	cout<<a_b_public_str.k<<" "<<a_b_public_str.n<<endl;

	mpz_t a_b_public_e, a_b_public_n, a_proxy_public_e, a_proxy_public_n, msg;
	mpz_inits(a_proxy_public_e, a_proxy_public_n, a_b_public_e, a_b_public_n, msg, NULL);
	mpz_set_str(a_proxy_public_e, a_proxy_public_str.k, 10);
	mpz_set_str(a_proxy_public_n, a_proxy_public_str.n, 10);
	mpz_set_str(a_b_public_e, a_b_public_str.k, 10);
	mpz_set_str(a_b_public_n, a_b_public_str.n, 10);

	//cout<<a_proxy_public_e<<" "<<a_proxy_public_n<<" "<<a_b_public_e<<" "<<a_b_public_n<<endl;
	
	char buff[1024];
	while(true)
	{
		cout<<"Data: ";
		cin>>msg;
		//mpz_set_str(msg, buff, 10);
		encrypt(msg, msg, a_b_public_e, a_b_public_n);
		cout<<"after first encryption "<<msg<<endl;
		encrypt(msg, msg, a_proxy_public_e, a_proxy_public_n);
		cout<<"after second encryption "<<msg<<endl;
		mpz_get_str(buff, 10, msg);
		cout<<"str "<<buff<<endl;
		write(nsfd1, buff, strlen(buff));
		cout<<"sent "<<buff<<endl;
	}

	return 0;
}