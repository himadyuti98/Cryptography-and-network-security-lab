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

void decrypt(mpz_t plain_text, mpz_t cipher_text, mpz_t private_key, mpz_t n)
{
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

	mpz_t p, q;
	mpz_inits(p, q, NULL);
	mpz_set_str(p, argv[2], 10);
	mpz_nextprime(p, p);
	mpz_nextprime(q, p);
	key public_str, private_str;
	key_gen(public_str, private_str, p, q);
	//cout<<proxy_a_public_str.k<<" "<<proxy_a_public_str.n<<endl;
	send(sfd, public_str.k, strlen(public_str.k), 0);
	perror("send1");
	sleep(1);
	send(sfd, public_str.n, strlen(public_str.n), 0);
	perror("send2");
	cout<<"my public key: "<<public_str.k<<" "<<public_str.n<<endl;

	key b_public_str;
	memset(b_public_str.k, '\0', 1024);
	memset(b_public_str.n, '\0', 1024);
	read(sfd,b_public_str.k,1024);
	read(sfd,b_public_str.n,1024);
	cout<<"b's public key: ";
	cout<<b_public_str.k<<" "<<b_public_str.n<<endl;
	//printf("%s\n", buff);
	mpz_t b_public_e, b_public_n, private_n, private_d, msg;
	mpz_inits(b_public_e, b_public_n, private_n, private_d, msg, NULL);
	mpz_set_str(b_public_e, b_public_str.k, 10);
	mpz_set_str(b_public_n, b_public_str.n, 10);
	mpz_set_str(private_d, private_str.k, 10);
	mpz_set_str(private_n, private_str.n, 10);
	cout<<"my private key: "<<private_d<<" "<<private_n<<endl;
	char buff[1024];
	memset(buff, '\0', 1024);
	while(true)
	{
		cout<<"Data: ";
		cin>>msg;
		//mpz_set_str(msg, buff, 10);
		encrypt(msg, msg, private_d, private_n);
		cout<<"after authentication encryption "<<msg<<endl;
		encrypt(msg, msg, b_public_e, b_public_n);
		cout<<"after encryption "<<msg<<endl;
		mpz_get_str(buff, 10, msg);
		cout<<"str "<<buff<<endl;
		write(sfd, buff, strlen(buff));
		cout<<"sent "<<buff<<endl;
	}

}