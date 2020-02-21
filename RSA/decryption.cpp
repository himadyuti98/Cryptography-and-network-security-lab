#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main(int argc, char* argv[])
{
	mpz_t private_key, n, plain_text, cipher_text;
	mpz_inits(private_key, n, plain_text, cipher_text, NULL);
	mpz_set_str(private_key, argv[1], 10);
	mpz_set_str(n, argv[2], 10);
	mpz_set_str(cipher_text, argv[3], 10);
	mpz_powm(plain_text, cipher_text, private_key, n);
	cout<<"Plain text: "<<plain_text<<endl;
	mpz_clears(private_key, n, plain_text, cipher_text, NULL);
	return 0;
}