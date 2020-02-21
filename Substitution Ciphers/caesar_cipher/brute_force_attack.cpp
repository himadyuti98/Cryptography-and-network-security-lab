#include<iostream>

using namespace std;

string decrypt(string cipher_text, int key)
{
	string plain_text = "";
	for (int i = 0; i < cipher_text.length(); ++i)
	{
		if (cipher_text[i] != ' ')
		{
			plain_text += ((cipher_text[i] -'a' - key + 26) % 26) + 'a';
		}
		else
		{
			plain_text += ' ';
		}
	}
	return plain_text;
}

int main()
{
	string cipher_text;
	cout<<"Enter cipher text"<<endl;
	getline(cin, cipher_text);
	cout<<"Possible plain texts : "<<endl;
	for (int i = 1; i < 26; i++)
	{
		cout<<decrypt(cipher_text, i)<<endl;	
	}
	
}