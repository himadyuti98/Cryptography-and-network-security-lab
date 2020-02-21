#include<bits/stdc++.h>

using namespace std;

unsigned long long multiply(unsigned long long a, unsigned long long b, long n, unsigned long long irreducible_pol)
{
	unsigned long long one = 1;
	unsigned long long ans = 0;
	if(b&1)
		ans = a;
	for(unsigned long long i = 1; i < n; i++)
	{
		if((one<<(n-1)) & a)
		{
			a = a<<1;
			a = a & ((one<<n)-1);
			a = a^irreducible_pol;
		}
		else
		{
			a = a<<1;
			a = a & ((one<<n)-1);
		}
		if((one<<i) & (b))
			ans = ans ^ a; 
	}
	return ans;
}

int main()
{
	long n;
	cout<<"Enter the value of n in GF(2^n)"<<endl;
	cin>>n;
	unsigned long long irred_pol;
	cout<<"Enter irreducible polynomial of degree n in hexadecimal form\n";
	scanf("%llx", &irred_pol);
	unsigned long long x = pow(2,n);
	irred_pol -= x;
	cout<<"Addition group table\n";
	for(unsigned long long i = 0; i < x; i++){
		for(unsigned long long j = 0; j < x; j++)
			printf("%llx ", i^j);
		cout<<endl;
	}
	cout<<"\nMultiplication group table\n";
	for(unsigned long long i = 1; i < x; i++){
		for(unsigned long long j = 1; j < x; j++)
			cout<<multiply(i,j,n,irred_pol)<<" ";
		cout<<endl;
	}
	
}
