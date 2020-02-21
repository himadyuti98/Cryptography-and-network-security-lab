#include<gmp.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char * argv[])
{
	mpz_t m, K, c1, c2, inv, pri, p;
	mpz_inits(m, K, c1, c2, inv, pri, p, NULL);
	mpz_set_str(pri, argv[1], 10);
	mpz_set_str(c1, argv[2], 10);
	mpz_set_str(c2, argv[3], 10);
	mpz_set_str(p, argv[4], 10);
	mpz_powm(K, c1, pri, p);
	mpz_invert(inv, K, p);
	mpz_mul(m, c2, inv);
	mpz_mod(m, m, p);
	cout<<"Plain text: "<<m<<endl;
	mpz_clears(m, K, c1, c2, inv, pri, p, NULL);
}
