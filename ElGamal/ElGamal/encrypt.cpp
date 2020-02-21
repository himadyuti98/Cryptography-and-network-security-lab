#include<gmp.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char * argv[])
{
	mpz_t m, k, K, c1, c2, pub, a, p, ip, gcd;
	mpz_inits(m, k, c1, c2, K, pub, a, p, ip, gcd, NULL);
	mpz_set_str(pub, argv[1], 10);
	mpz_set_str(a, argv[2], 10);
	mpz_set_str(p, argv[3], 10);
	mpz_set_str(m, argv[4], 10);
	mpz_sub_ui(ip, p, 1);
	do{
		gmp_randstate_t st;
		gmp_randinit_mt(st);
		gmp_randseed_ui(st, 214567);
		mpz_urandomm(k, st, ip);
		mpz_gcd(gcd, k, ip);
		
	}while(mpz_cmp_ui(gcd, 1) != 0);
	mpz_powm(K, pub, k, p);
	mpz_powm(c1, a, k, p);	
	mpz_mul(c2, K, m);
	mpz_mod(c2, c2, p);
	cout<<"Cipher text: ("<<c1<<" ,"<<c2<<endl;
	mpz_clears(m, k, c1, c2, K, pub, a, p, ip, gcd, NULL);
}
