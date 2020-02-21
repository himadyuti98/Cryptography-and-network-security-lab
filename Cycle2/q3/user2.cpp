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
	//cout<<plain_text<<" "<<public_key<<" "<<n<<endl;
	mpz_powm(cipher_text, plain_text, public_key, n);
}
void decrypt(mpz_t plain_text, mpz_t cipher_text, mpz_t private_key, mpz_t n)
{
	cout<<cipher_text<<" "<<private_key<<" "<<n<<endl;
	mpz_powm(plain_text, cipher_text, private_key, n);
}

void key_gen(key &public_key, key &private_key, mpz_t p, mpz_t q)
{
	mpz_t n, e, d, to_n;
	mpz_inits(n, to_n, e, d, NULL);
	mpz_mul(n, p, q);
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(to_n, p, q);
	mpz_set_ui(e, 65537);
	mpz_invert(d, e, to_n);
	mpz_get_str(public_key.k, 10, e);
	mpz_get_str(private_key.k, 10, d);
	mpz_get_str(public_key.n, 10, n);
	mpz_get_str(private_key.n, 10, n);

}

int main(int argc, char const *argv[])
{
	int sfd1;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	if((sfd1 = socket(AF_INET,SOCK_STREAM,0))==-1)
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

	
	int nsfd1;
	nsfd1 = accept(sfd1 , NULL, NULL);
		perror("\n accept ");
	key a_public_str;
	memset(a_public_str.k, '\0', 1024);
	memset(a_public_str.n, '\0', 1024);
	int s = recv(nsfd1,a_public_str.k,1024, 0);
	perror("recv");
	recv(nsfd1,a_public_str.n,1024, 0);
	perror("recv");
	//printf("%s\n", buff);
	cout<<"a's public key: ";
	cout<<a_public_str.k<<" "<<a_public_str.n<<endl;


	mpz_t a_public_e, a_public_n;
	mpz_inits(a_public_e, a_public_n, NULL);
	mpz_set_str(a_public_e, a_public_str.k, 10);
	mpz_set_str(a_public_n, a_public_str.n, 10);

	//cout<<a_proxy_public_e<<" "<<a_proxy_public_n<<" "<<a_b_public_e<<" "<<a_b_public_n<<endl;
	mpz_t p, q;
	mpz_inits(p, q, NULL);
	mpz_set_str(p, argv[2], 10);
	mpz_nextprime(p, p);
	mpz_nextprime(q, p);
	key public_str, private_str;
	key_gen(public_str, private_str, p, q);
	//cout<<proxy_a_public_str.k<<" "<<proxy_a_public_str.n<<endl;
	send(nsfd1, public_str.k, strlen(public_str.k), 0);
	perror("send1");
	sleep(1);
	send(nsfd1, public_str.n, strlen(public_str.n), 0);
	perror("send2");
	cout<<"my public key: "<<public_str.k<<" "<<public_str.n<<endl;

	mpz_t private_d, private_n, msg;
	mpz_inits(private_d, private_n, msg, NULL);
	mpz_set_str(private_d, private_str.k, 10);
	mpz_set_str(private_n, private_str.n, 10);
	cout<<"my private key: "<<private_d<<" "<<private_n<<endl;

	char buff[1024];
	while(true)
	{
		memset(buff, '\0', 1024);
		int k = read(nsfd1, buff, 1024);
		if(k<=0)
			continue;
		cout<<"recvd "<<buff<<endl;
		mpz_set_str(msg, buff, 10);
		decrypt(msg, msg, private_d, private_n);
		cout<<"after decryption: "<<msg<<endl;
		decrypt(msg, msg, a_public_e, a_public_n);
		cout<<"after verification of authentication: "<<msg<<endl;
		
	}

	return 0;
}