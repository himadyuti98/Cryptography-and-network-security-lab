#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main(int argc, char * argv[])
{
	mpz_t p, a, pri, pub;
	mpz_inits(p, a, pri, pub, NULL);
	mpz_set_str(p, argv[1], 10);
	mpz_set_str(a, argv[2], 10);
	mpz_set_str(pri, argv[3], 10);
	mpz_powm(pub, a, pri, p);
	cout<<"Public Key: ("<<pub<<", "<<a<<", "<<p<<")\n";
	cout<<"Private Key: "<<pri<<endl;
	mpz_clears(p, a, pri, pub, NULL);
}
