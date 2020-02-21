#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

struct point{
	mpz_t x;
	mpz_t y;	
};

point add(point a, point b, bool same, mpz_t q, mpz_t ap)
{
	point ans;
	mpz_t l, m;
	if(same)
	{
		
		mpz_init(l);
		mpz_mul_ui(l, a.y, 2);
		mpz_invert(l,l,q);
		mpz_init(m);
		mpz_mul(m, a.x, a.x);
		mpz_mul_ui(m, m, 3);
		mpz_add(m, m, ap);
		mpz_mul(m, m, l);
		mpz_mod(m, m, q);

	}
	else
	{
		mpz_init(l);
		mpz_sub(l, b.x, a.x);
		mpz_invert(l,l,q);
		mpz_init(m);
		mpz_sub(m, b.y, a.y);
		mpz_mul(m, m, l);
		mpz_mod(m, m, q);

	}
	//cout<<"lamda: "<<m<<endl;
	mpz_inits(ans.x, ans.y, NULL);
	mpz_t temp;
	mpz_init(temp);
	mpz_mul(temp, m, m);
	mpz_sub(temp, temp, a.x);
	mpz_sub(temp, temp, b.x);
	mpz_mod(ans.x, temp, q);
	mpz_sub(temp, a.x, ans.x);
	mpz_mul(temp, temp, m);
	mpz_sub(temp, temp, a.y);
	mpz_mod(ans.y, temp, q);
	return ans;
}

point multiply(mpz_t n, point g, mpz_t q, mpz_t a)
{
	//cout<<n<<" "<<g.x<<" "<<g.y<<" "<<q<<" "<<a<<endl;
	point ans;
	mpz_inits(ans.x, ans.y, NULL);
	mpz_set(ans.x, g.x);
	mpz_set(ans.y, g.y);
	mpz_t i;
	mpz_init(i);
	mpz_set_ui(i, 1);
	bool f = 1;
	while(mpz_cmp(i, n)!=0)
	{
		ans = add(ans, g, f, q, a);
		//cout<<ans.x<<" "<<ans.y<<endl;
		mpz_add_ui(i, i, 1);
		f=0;
	}
	return ans;
}

int main()
{
	mpz_t q, a, b, na, nb;
	point g, pra, prb, k;
	mpz_inits(q, a, b, na, nb, g.x, g.y, pra.x, pra.y, prb.x, prb.y, k.x, k.y, NULL);
	cout<<"Enter the parameters of elliptic curve\n";
	cin>>q>>a>>b;
	cout<<"Enter base point\n";
	cin>>g.x>>g.y;
	cout<<"Enter a's private key\n";
	cin>>na;
	pra = multiply(na, g, q, a);
	cout<<"Public key of a: "<<pra.x<<" "<<pra.y<<"\n";
	cout<<"Enter b's private key\n";
	cin>>nb;
	prb = multiply(nb, g, q, a);
	cout<<"Public key of b: "<<prb.x<<" "<<prb.y<<"\n";
	k = multiply(na, prb, q, a);
	cout<<"Secret key of a: "<<k.x<<" "<<k.y<<"\n";
	k = multiply(nb, pra, q, a);
	cout<<"Secret key of b: "<<k.x<<" "<<k.y<<"\n";
	
	return 0;
}