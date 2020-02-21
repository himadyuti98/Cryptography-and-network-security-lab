#include<bits/stdc++.h>
//#include<gmp.h>

using namespace std;

long int det(vector<vector<int> >mat, unsigned long int n)
{
	if (n == 2)
	{
		return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
	}
	long long int deter = 0;
	for(unsigned long j = 0; j < n; j++)
	{
		vector<vector<int> >mat2;
		for(unsigned long i1 = 1; i1 < n; i1++)
		{
			vector<int> v;
			for(unsigned long j1 = 0; j1 < n; j1++)
			{
				if (j1 == j)
					continue;
				v.push_back(mat[i1][j1]);
			}
			mat2.push_back(v);
		}
		if (j%2 == 0)
			deter += (mat[0][j] * det(mat2, n-1));
		else
			deter -= (mat[0][j] * det(mat2, n-1));
	}
	
	return (deter%26);
}

int inverse(int a)
{
	if(__gcd(a,26)!=1)
		return 27;
	for(int i = 1; i <= 25; i++)
	{
		if((a*i)%26 == 1)
			return i;
	}
}

vector<vector<int> > mat_inv(vector<vector<int> >mat, unsigned long int n)
{
	vector<vector<int> >adj(n, vector<int> (n));
	int deter = det(mat, n);
	if(deter < 0)
		deter += 26;
	int det_inv = inverse(det(mat,n));
	cout<<det_inv<<endl;
	if(det_inv == 27)
	{
		cout<<"Key is unsuitable. Enter valid key\n";
		return adj;
	}
	for(unsigned long i = 0; i < n; i++)
	{
		for(unsigned long j = 0; j < n; j++)
		{
			vector<vector<int> >mat2;
			for(unsigned long i1 = 0; i1 < n; i1++)
			{
				vector<int> v;
				for(unsigned long j1 = 0; j1 < n; j1++)
				{
					if (j1 == j || i1 == i)
						continue;
					v.push_back(mat[i1][j1]);
				}
				if(!v.empty())
					mat2.push_back(v);
			}
			int d = det(mat2,n-1);
			adj[j][i] = (det_inv * d);
			if((i+j)%2 == 1){
				adj[j][i] *= -1;
			}
		}
	}
	for(unsigned long i = 0; i < n; i++){
		for(unsigned long j = 0; j < n; j++){
			adj[i][j] = (adj[i][j] + 26*26*26)%26;
			cout<<adj[i][j]<<"\t";
		}
		cout<<endl;
	}
	return adj;
}

int main()
{
	string key, cipher_text;
	cout<<"Enter valid key"<<endl;
	cin>>key;
	/*mpz_t n;
	mpz_init(n);
	mpz_set_ui(n, key.length());
	mpz_sqrt(n,n);
	*/cout<<"Enter cipher text"<<endl;
	cin>>cipher_text;
	//unsigned long int no = mpz_get_ui(n);
	unsigned long int no  = sqrt(key.length());
	vector<vector<int> >key_matrix(no, vector<int> (no));
	for(unsigned long i = 0; i < no; i++){
		for(unsigned long j = 0; j < no; j++){
			key_matrix[i][j] = (key[i*no + j] - 'A')%26;
			cout<<key_matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	key_matrix = mat_inv(key_matrix, no);
	string plain_text = "";
	string x = "";
	int int_vec[no][1];
	for(unsigned long i = 0; i < cipher_text.length(); i++)
	{
		x += cipher_text[i];
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
				plain_text += (result[j][0]%26 + 'A');
			}
			x = "";
		}
	}
	cout<<"Plain text: "<<plain_text<<endl;
	return 0;
}
