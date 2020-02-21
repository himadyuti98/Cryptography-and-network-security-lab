#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main(int argc, char* argv[])
{
	mpz_t p, q, n, to_n, e, d, i, gcd;
	mpz_inits(p, q, n, to_n, e, d, i, gcd, NULL);
	mpz_set_str(p, argv[1], 10);
	mpz_nextprime(p, p);
	mpz_nextprime(q, p);
	mpz_mul(n, p, q);
	cout<<"p = "<<p<<endl;
	cout<<"q = "<<q<<endl;
	cout<<"n = "<<n<<endl;
	
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(to_n, p, q);
	mpz_root(i, n, 2);
	while(mpz_cmp(i, to_n) < 0)
	{
		mpz_gcd(gcd, i, to_n);
		if(mpz_cmp_ui(gcd, 1) == 0)
		{
			mpz_set(e, i);
			mpz_invert(d, e, to_n);
			break;
		}
		mpz_add_ui(i, i, 1);
	}
	cout<<"Public key: ("<<e<<" ,"<<n<<")\n";
	cout<<"Private key: ("<<d<<" ,"<<n<<")\n";
	
	mpz_clears(p, q, n, to_n, e, d, i, gcd, NULL);
	
	return 0;
}