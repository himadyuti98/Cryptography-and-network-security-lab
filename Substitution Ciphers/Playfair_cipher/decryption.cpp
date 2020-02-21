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
	string key, cipher_text;
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
	
	cout<<"Enter cipher text"<<endl;
	cin>>cipher_text;	
	cipher_text = to_upper(cipher_text);
	/*for(i = 0; i < cipher_text.length(); i++)
		if(cipher_text[i] == 'J')
			cipher_text[i] = 'I';
	*/
	string plain_text = "";
	
	/*if(cipher_text.length()%2 == 1)
		cipher_text += 'Z';
	*/
	for(i = 0; i < cipher_text.length(); i+=2)
	{
		char a = cipher_text[i];
		char b = cipher_text[i+1];
		char c, d;
		int a_col = key.find(a)%5;
		int b_col = key.find(b)%5;
		int a_row = key.find(a)/5;
		int b_row = key.find(b)/5;
		if( a_col == b_col)
		{
			plain_text += key_matrix[(a_row + 4)%5][a_col];
			plain_text += key_matrix[(b_row + 4)%5][b_col];
		}
		else if( a_row == b_row)
		{
			plain_text += key_matrix[a_row][(a_col + 4)%5];
			plain_text += key_matrix[b_row][(b_col + 4)%5];
		}
		else
		{
			plain_text += key_matrix[a_row][b_col];
			plain_text += key_matrix[b_row][a_col];
		}
	}
	cout<<"Plain text: "<<plain_text<<endl;
	return 0;
}
