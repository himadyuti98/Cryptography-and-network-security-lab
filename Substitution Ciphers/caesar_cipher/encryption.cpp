#include<iostream>

using namespace std;

string encrypt(string plain_text, int key)
{
	string cipher_text = "";
	for (int i = 0; i < plain_text.length(); ++i)
	{
		if (plain_text[i] != ' ')
		{
			cipher_text += ((plain_text[i] - 'a' + key) % 26) + 'a';
		}
		else
		{
			cipher_text += ' ';
		}
	}
	return cipher_text;
}

int main()
{
	string plain_text;
	cout<<"Enter plain text"<<endl;
	getline(cin, plain_text);
	cout<<"Enter key"<<endl;
	int key;
	cin>>key;
	cout<<"Cipher text : "<<encrypt(plain_text, key)<<endl;
}