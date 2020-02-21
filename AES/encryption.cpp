#include<bits/stdc++.h>

using namespace std;

unsigned int state[4][4];
unsigned int key[4][4];

unsigned int s_box[16][16] = {
 {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01 , 0x67 , 0x2b , 0xfe , 0xd7 , 0xab , 0x76 },
 {0xca,	0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4 , 0xa2 , 0xaf , 0x9c , 0xa4 , 0x72 , 0xc0 },
 {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5 , 0xe5 , 0xf1 , 0x71 , 0xd8 , 0x31 , 0x15 },
 {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12 , 0x80 , 0xe2 , 0xeb , 0x27 , 0xb2 , 0x75 },
 {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b , 0xd6 , 0xb3 , 0x29 , 0xe3 , 0x2f , 0x84 },
 {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb , 0xbe , 0x39 , 0x4a , 0x4c , 0x58 , 0xcf },
 {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9 , 0x02 , 0x7f , 0x50 , 0x3c , 0x9f , 0xa8 },
 {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6 , 0xda , 0x21 , 0x10 , 0xff , 0xf3 , 0xd2 },
 {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44,	0x17, 0xc4, 0xa7 , 0x7e , 0x3d , 0x64 , 0x5d , 0x19 , 0x73 },
 {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee , 0xb8 , 0x14 , 0xde , 0x5e , 0x0b , 0xdb },
 {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3 , 0xac , 0x62 , 0x91 , 0x95 , 0xe4 , 0x79 },
 {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56 , 0xf4 , 0xea , 0x65 , 0x7a , 0xae , 0x08 },
 {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd , 0x74 , 0x1f , 0x4b , 0xbd , 0x8b , 0x8a },
 {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35 , 0x57 , 0xb9 , 0x86 , 0xc1 , 0x1d , 0x9e },
 {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e , 0x87 , 0xe9 , 0xce , 0x55 , 0x28 , 0xdf },
 {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99 , 0x2d , 0x0f , 0xb0 , 0x54 , 0xbb , 0x16 } };

int mix_mat[4][4] = {
		{2,3,1,1},
		{1,2,3,1},
		{1,1,2,3},
		{3,1,1,2}
	};

unsigned int rc[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

unsigned int roundkey[10][4][4];

void keyschedule()
{
	unsigned int temp[4];
	for(int j = 1; j < 4; j++)
	{
		temp[j-1] = key[j][3];
	}
	temp[3] = key[0][3];
	for(int j = 0; j < 4; j++)
	{
		temp[j] = s_box[temp[j]/16][temp[j]%16];
		roundkey[0][j][0] = temp[j]^key[j][0];
	}
	roundkey[0][0][0] = roundkey[0][0][0]^rc[0];
		
	for(int i = 1; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			roundkey[0][j][i] = roundkey[0][j][i-1]^key[j][i];
		}	
		
	}
	for(int c = 1; c < 10; c++)
	{
		for(int j = 1; j < 4; j++)
		{
			temp[j-1] = roundkey[c-1][j][3];
		}
		temp[3] = roundkey[c-1][0][3];

		for(int j = 0; j < 4; j++)
		{
			temp[j] = s_box[temp[j]/16][temp[j]%16];
			//printf("%x ", temp[j]);
			roundkey[c][j][0] = temp[j]^roundkey[c-1][j][0];
		}
		//cout<<endl;
		roundkey[c][0][0] = roundkey[c][0][0]^rc[c];
			
		for(int i = 1; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				roundkey[c][j][i] = roundkey[c][j][i-1]^roundkey[c-1][j][i];
			}	
			
		}
	}
	for(int c = 0; c < 10; c++)
	{
		printf("\n\nRound %d\n", c+1);
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				printf("%x ", roundkey[c][i][j]);
			}
			printf("\n");
		}
	}
	
}
void subbytes()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			state[i][j] = s_box[state[i][j]/16][state[i][j]%16];
			//printf("%x ", state[i][j]);
		}
		//printf("\n");
	}
}	

void shiftrows()
{
	unsigned int temp1 = state[1][0], temp2, temp3;
	for(int i = 1; i < 4; i++)
		state[1][i-1] = state[1][i];
	state[1][3] = temp1;
	temp1 = state[2][0]; temp2 = state[2][1];
	state[2][0] = state[2][2]; state[2][1] = state[2][3];
	state[2][2] = temp1; state[2][3] = temp2;
	temp1 = state[3][3];
	for(int i = 3; i >= 1; i--)
		state[3][i] = state[3][i-1];
	state[3][0] = temp1;
	/*for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%x ", state[i][j]);
		}
		printf("\n");
	}*/
}

unsigned int multiply(unsigned int a, unsigned int b)
{
	unsigned int one = 1;
	unsigned int ans = 0;
	unsigned int irreducible_pol = 0x1b;
	int n = 8;
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

void mixcols()
{
	unsigned int col[4][4], temp[4];
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			col[i][j] = state[j][i];
		}
	}
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			temp[j] = 0;
			for(int k = 0; k < 4; k++)
			{
				temp[j] = temp[j]^multiply(mix_mat[j][k],col[i][k]);
			}
		}
		for(int j = 0; j < 4; j++)
			state[j][i] = temp[j];
	}
	/*for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%x ", state[i][j]);
		}
		printf("\n");
	}*/
}

void addroundkey(int nRound)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			state[i][j] ^= roundkey[nRound][i][j];
	}
}

void encrypt()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			state[i][j] ^= key[i][j];
	}
	cout<<"Before Rounds "<<endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			printf("%x ", state[i][j]);
		cout<<endl;
	}
	for(int i = 0; i < 9; i++)
	{
		subbytes();
		shiftrows();
		mixcols();
		addroundkey(i);
		cout<<"\n\nRound "<<i+1<<endl;
		for(int k = 0; k < 4; k++)
		{
			for(int j = 0; j < 4; j++)
				printf("%x ", state[k][j]);
			cout<<endl;
		}
	}
	subbytes();
	shiftrows();
	addroundkey(9);
	cout<<"\n\nRound "<<10<<endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			printf("%x ", state[i][j]);
		cout<<endl;
	}
}

int main(int argc, char const *argv[])
{
	cout<<"Enter 128 bits key as 16 bytes in hexadecimal form\n";
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			scanf("%x",&key[j][i]);

	cout<<"Enter one block (128 bits) plaintext as 16 bytes in hexadecimal form\n";
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			scanf("%x",&state[j][i]);
	cout<<"Round keys\n";
	keyschedule();
	cout<<"\n\n";
	encrypt();
	cout<<"\n\nCipher text block as 16 bytes in hexadecimal: ";
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			printf("%x ", state[j][i]);
		
	cout<<endl;
	return 0;
}

