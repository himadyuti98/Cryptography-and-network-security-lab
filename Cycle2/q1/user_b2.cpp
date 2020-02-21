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
	
	mpz_t p, q;
	mpz_inits(p, q, NULL);
	mpz_set_str(p, argv[3], 10);
	mpz_nextprime(p, p);
	mpz_nextprime(q, p);
	key b_a_public_str, b_a_private_str;
	key_gen(b_a_public_str, b_a_private_str, p, q);
	
	write(sfd, b_a_public_str.k, sizeof(b_a_public_str.k));
	sleep(1);
	write(sfd, b_a_public_str.n, sizeof(b_a_public_str.n));
	cout<<"sent public key to a\n";
	close(sfd);
	
	mpz_set_str(p, argv[4], 10);
	mpz_nextprime(p, p);
	mpz_nextprime(q, p);
	key b_proxy_public_str, b_proxy_private_str;
	key_gen(b_proxy_public_str, b_proxy_private_str, p, q);
	
	write(sfd1, b_proxy_public_str.k, sizeof(b_proxy_public_str.k));
	sleep(1);
	write(sfd1, b_proxy_public_str.n, sizeof(b_proxy_public_str.n));
	cout<<"sent public key to proxy\n";
	mpz_t b_proxy_private_d, b_proxy_private_n, b_a_private_n, b_a_private_d, msg;
	mpz_inits(b_proxy_private_d, b_proxy_private_n, b_a_private_n, b_a_private_d, msg, NULL);
	mpz_set_str(b_proxy_private_d, b_proxy_private_str.k, 10);
	mpz_set_str(b_proxy_private_n, b_proxy_private_str.n, 10);
	mpz_set_str(b_a_private_d, b_a_private_str.k, 10);
	mpz_set_str(b_a_private_n, b_a_private_str.n, 10);
	char buff[1024];
	memset(buff, '\0', 1024);
	while(true)
	{
		int k = read(sfd1, buff, 1024);
		if(k<=0)
			continue;
		cout<<"recvd "<<buff<<endl;
		mpz_set_str(msg, buff, 10);
		decrypt(msg, msg, b_proxy_private_d, b_proxy_private_n);
		cout<<"after first decryption "<<msg<<endl;
		decrypt(msg, msg, b_a_private_d, b_a_private_n);
		cout<<"Message recvd from a: "<<msg<<endl;
	}
	return 0;
}