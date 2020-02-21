#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main(int argc, char * argv[])
{
	mpz_t p, a, pri, pub, m, k, s1, s2, K, temp, v1, v2;
	mpz_inits(p, a, pri, pub, m, k, K, s1, s2, temp, v1, v2, NULL);
	mpz_set_str(p, argv[1], 10);
	mpz_set_str(a, argv[2], 10);
	mpz_set_str(pri, argv[3], 10);
	mpz_powm(pub, a, pri, p);
	cout<<"Public Key: ("<<pub<<", "<<a<<", "<<p<<")\n";
	cout<<"Private Key: "<<pri<<endl;
	cout<<"Enter hash value\n";
	cin>>m;
	cout<<"Enter random value k\n";
	cin>>k;
	mpz_powm(s1, a, k, p);
	mpz_sub_ui(temp, p, 1);
	mpz_invert(K, k, temp);
	mpz_mul(s2, pri, s1);
	mpz_sub(s2, m, s2);
	mpz_mul(s2, K, s2);
	mpz_mod(s2, s2, temp);

	cout<<"s1 = "<<s1<<"\ns2 = "<<s2<<"\n";

	mpz_powm(v1, a, m, p);
	mpz_powm(temp, pub, s1, p);
	mpz_powm(s1, s1, s2, p);
	mpz_mul(s1, temp, s1);
	mpz_mod(v2, s1, p);

	cout<<"v1 = "<<v1<<"\nv2 = "<<v2<<"\n";
	mpz_clears(p, a, pri, pub, m, k, K, s1, s2, temp, v1, v2, NULL);

}
