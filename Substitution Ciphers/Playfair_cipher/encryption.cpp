#include<bits/stdc++.h>

using namespace std;

string to_upper(string text)
{
	for(int i = 0; i < text.length(); i++)
		if(text[i] >= 'a' && text[i] <= 'z')
			text[i] -= 32;
	return text;
}

int main()
{
	string key, plain_text;
	cout<<"Enter valid key"<<endl;
	cin>>key;
	key = to_upper(key);
	char key_matrix[5][5];
	int i = 0;
	for(int j = 0; j < key.length(); j++)
	{
		if(j%5 == 0 && j != 0)
			i++;
		key_matrix[i][j%5] = key[j];
	}
	char s = 'A';
	if(key.length()%5 != 0)
	{
		int j = key.length()%5;
		for(char k = 'A'; k <= 'Z'; k++)
		{
			if(key.find(k) >= key.length())
			{
				key_matrix[i][j++] = k;
				key += k;
				if(j == 5)
					break;
			}
		}
		i++;
	}
	int j = 0;
	for(char k = 'A'; k <= 'Z'; k++)
	{
		if(k == 'J')
			continue;
		if(key.find(k) >= key.length())
		{
			key_matrix[i][j++] = k;
			key += k;
			if(j == 5)
			{
				j = 0;
				i++;
				if (i == 5)
					break;
			}
		}
	}
	
	cout<<"Enter plain text"<<endl;
	cin>>plain_text;	
	plain_text = to_upper(plain_text);
	for(i = 0; i < plain_text.length(); i++)
		if(plain_text[i] == 'J')
			plain_text[i] = 'I';
	
	string cipher_text = "";
	
	if(plain_text.length()%2 == 1)
		plain_text += 'Z';
	for(i = 0; i < plain_text.length(); i+=2)
	{
		char a = plain_text[i];
		char b = plain_text[i+1];
		char c, d;
		int a_col = key.find(a)%5;
		int b_col = key.find(b)%5;
		int a_row = key.find(a)/5;
		int b_row = key.find(b)/5;
		if( a_col == b_col)
		{
			cipher_text += key_matrix[(a_row + 1)%5][a_col];
			cipher_text += key_matrix[(b_row + 1)%5][b_col];
		}
		else if( a_row == b_row)
		{
			cipher_text += key_matrix[a_row][(a_col + 1)%5];
			cipher_text += key_matrix[b_row][(b_col + 1)%5];
		}
		else
		{
			cipher_text += key_matrix[a_row][b_col];
			cipher_text += key_matrix[b_row][a_col];
		}
	}
	cout<<"Cipher text: "<<cipher_text<<endl;
	return 0;
}
