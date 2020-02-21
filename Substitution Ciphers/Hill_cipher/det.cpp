#include<bits/stdc++.h>

using namespace std;

long int det(vector<vector<int> >mat, unsigned long int n)
{
	if (n == 2)
	{
		cout<<mat[0][0]<<" "<<mat[0][1]<<" "<<mat[1][0]<<" "<<mat[1][1]<<endl;
		cout<<mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]<<endl;
		return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
	}
	long int deter = 0;
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
	
	return deter;
}

int main()
{
	vector<vector<int> >mat;
	vector<int> v;
	v.push_back(6);
	v.push_back(24);
	v.push_back(1);
	mat.push_back(v);
	v.clear();
	v.push_back(13);
	v.push_back(16);
	v.push_back(10);
	mat.push_back(v);
	v.clear();
	v.push_back(20);
	v.push_back(17);
	v.push_back(15);
	mat.push_back(v);
	cout<<det(mat,3)<<endl;
}

