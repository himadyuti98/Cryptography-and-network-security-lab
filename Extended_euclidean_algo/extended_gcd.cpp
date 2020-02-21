#include <gmp.h>
#include<iostream>
#include<assert.h>
using namespace std;

void gcdfun(mpz_t gcd, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
{
	if (mpz_sgn(a) == 0)
	{
		mpz_set(gcd, b);
		mpz_set_ui(x, 0);
		mpz_set_ui(y, 1);
	}
	else
	{
		mpz_t x1, y1, b1, a1;
		mpz_inits(x1, y1, b1, a1, NULL);
		mpz_mod(b1, b, a);
		mpz_set(a1, a);
		gcdfun(gcd, b1, a1, x1, y1);
		mpz_fdiv_q(b, b, a);
		mpz_mul(b, b, x1);
		mpz_sub(y1, y1, b);
		mpz_set(x, y1);
		mpz_set(y, x1);
		mpz_clears(x1, y1, b1, a1, NULL);
	}
}

int main()
{
	mpz_t n1;
	mpz_t n2;
	mpz_t x;
	mpz_t y;
	mpz_t gcd;
		
	mpz_inits(n1, n2, x, y, gcd, NULL);
	cout<<"enter first number"<<endl;
	cin>>n1;
	cout<<"enter second number"<<endl;
	cin>>n2;
	cout<<"n1 = "<<n1;
	cout<<endl<<"n2 = "<<n2;
	cout<<endl;
	gcdfun(gcd, n1, n2, x, y);
	
	cout<<"gcd = "<<gcd<<endl;
	cout<<"x="<<x<<"\ty="<<y;
	cout<<endl;
	mpz_clears(n1, n2, x, y, gcd, NULL);
	
	return 0;
}
