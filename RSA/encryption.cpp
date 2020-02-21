#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main(int argc, char* argv[])
{
	mpz_t public_key, n, plain_text, cipher_text;
	mpz_inits(public_key, n, plain_text, cipher_text, NULL);
	mpz_set_str(public_key, argv[1], 10);
	mpz_set_str(n, argv[2], 10);
	mpz_set_str(plain_text, argv[3], 10);
	mpz_powm(cipher_text, plain_text, public_key, n);
	cout<<"Cipher text: "<<cipher_text<<endl;
	mpz_clears(public_key, n, plain_text, cipher_text, NULL);
	return 0;
}