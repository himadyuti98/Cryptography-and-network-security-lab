#include<bits/stdc++.h>
#include<gmp.h>

using namespace std;

int main()
{
	string key, plain_text;
	cout<<"Enter valid key"<<endl;
	cin>>key;
	mpz_t n;
	mpz_init(n);
	mpz_set_ui(n, key.length());
	mpz_sqrt(n,n);
	cout<<"Enter plain text"<<endl;
	cin>>plain_text;
	unsigned long int no = mpz_get_ui(n);
	int key_matrix[no][no];
	for(unsigned long i = 0; i < no; i++){
		for(unsigned long j = 0; j < no; j++){
			key_matrix[i][j] = (key[i*no + j] - 'A')%26;
			cout<<key_matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	string cipher_text = "";
	string x = "";
	int int_vec[no][1];
	for(unsigned long i = 0; i < plain_text.length(); i++)
	{
		x += plain_text[i];
		if(x.length() == no)
		{
			for(unsigned long j = 0; j < no; j++)
				int_vec[j][0] = (x[j] - 'A')%26;
			long int result[no][1];
			for(unsigned long j = 0; j < no; j++){
				result[j][0] = 0;
				for(unsigned long k = 0; k < no; k++)
					result[j][0] += (key_matrix[j][k] * int_vec[k][0])%26;
				cout<<result[j][0]%26<<endl;
				cipher_text += (result[j][0]%26 + 'A');
			}
			x = "";
		}
	}
	cout<<"Cipher text: "<<cipher_text<<endl;
	return 0;
}
