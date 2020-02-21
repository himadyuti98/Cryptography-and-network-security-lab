#include<bits/stdc++.h>

using namespace std;
int ip_table[64] = {58, 50, 42, 34, 26, 18, 10, 2,
					60, 52, 44, 36, 28, 20, 12, 4,
					62, 54, 46, 38, 30, 22, 14, 6,
					64, 56, 48, 40, 32, 24, 16, 8,
					57, 49, 41, 33, 25, 17, 9, 1,
					59, 51, 43, 35, 27, 19, 11, 3,
					61, 53, 45, 37, 29, 21, 13, 5,
					63, 55, 47, 39, 31, 23, 15, 7 };

	
int fp_table[64] = {40, 8, 48, 16, 56, 24, 64, 32,
					39, 7, 47, 15, 55, 23, 63, 31,
					38, 6, 46, 14, 54, 22, 62, 30,
					37, 5, 45, 13, 53, 21, 61, 29,
					36, 4, 44, 12, 52, 20, 60, 28,
					35, 3, 43, 11, 51, 19, 59, 27,
					34, 2, 42, 10, 50, 18, 58, 26,
					33, 1, 41, 9, 49, 17, 57, 25 };

int s[8][4][16]= 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
  
  
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }}; 

int p[32]= {16,7,20,21, 
        	29,12,28,17, 
        	1,15,23,26, 
        	5,18,31,10, 
        	2,8,24,14, 
        	32,27,3,9, 
        	19,13,30,6, 
        	22,11,4,25 }; 

int shift_table[16]= {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 }; 

unsigned long long permute(unsigned long long original, int initial_size, int final_size, int permutation_table[])
{
	unsigned long long modified_block = 0;
	unsigned long long one = 1;
	for(int i = 0; i < final_size; i++)
    {
    	unsigned long long f = original & (one<<(initial_size-permutation_table[i]));
    	if(f != 0)
    	{
    		modified_block |= ((one<<(final_size-i-1)));
    	}
    }
    return modified_block;
}

unsigned long long parity_drop(unsigned long long key)
{
	int keyp[56]=  
    {    57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,           
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    }; 
    return permute(key, 64, 56, keyp);
}

long key_shift(unsigned long long key, int round_number)
{
	unsigned long long one = 1;
	long right = ((one<<28)-1) & (key);
	long left = ((one<<28)-1) & (key>>28);
	//printf("left: %lx\tright: %lx\n", left, right);
	right = (right << shift_table[round_number])|(right >> (28 - shift_table[round_number]));
	left = (left << shift_table[round_number])|(left>>(28 - shift_table[round_number]));
	right &= ((one<<28)-1);
	left &= ((one<<28)-1);
	//printf("left: %lx\tright: %lx\n", left, right);
	left = (left << 28);
	return (left | right);
}

unsigned long long key_compress(unsigned long long key)
{
	int key_comp[48]= 
    {    14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    }; 
    return permute(key, 56, 48, key_comp);
}


unsigned long long expand32to48(long block)
{
	int exp_p[48]=  
    {    32,1,2,3,4,5,4,5, 
        6,7,8,9,8,9,10,11, 
        12,13,12,13,14,15,16,17, 
        16,17,18,19,20,21,20,21, 
        22,23,24,25,24,25,26,27, 
        28,29,28,29,30,31,32,1 
    }; 
    return permute(block, 32, 48, exp_p);
}

unsigned long round(long right, long key)
{
	right = expand32to48(right);
	//printf("right expanded: %lx\n", right);
	right = right^key;
	//printf("after xoring: %lx\n", right);
	long plaintext = 0;
	for(int i = 0; i < 8; i++)
	{
		int block = ((1<<6)-1)&(right>>((7-i)*6));
		bool f1 = block & (1<<5);
		bool f2 = block & 1;
		int row = f1*2 + f2;
		int column = (block & 30)>>1; 		// 30 = 11110
		int plainblock = s[i][row][column];
		plaintext = plaintext<<4;
		plaintext |= plainblock;
	}
	//printf("after s boxes: %lx\n", ciphertext);
	return permute(plaintext, 32, 32, p);
}

vector<unsigned long long> generate_round_keys(unsigned long long key)
{
	vector<unsigned long long> subkeys;
	for(int i = 0; i < 16; i++)
	{
		key = key_shift(key,i);
		subkeys.push_back(key_compress(key));
		
	}
	return subkeys;
}

unsigned long long decrypt(unsigned long long int cipherblock, unsigned long long key)
{
	key = parity_drop(key);
	cipherblock = permute(cipherblock,64, 64, ip_table);
	printf("after initial permutation : %llx\n", cipherblock);
	unsigned long one = 1;
	unsigned long right = (((one<<32)-1) & (cipherblock));
	unsigned long left = ((one<<32)-1) & (cipherblock>>32);
	printf("left: %lx\t right: %lx\n", left, right);
	vector<unsigned long long> subkeys = generate_round_keys(key);
	for(int i = 0; i < 16; i++)
	{
		long temp = right;
		right = round(right, subkeys[15-i]);
		//printf("after p box: %lx\n", right);
		right = right^left;
		//printf("after xoring: %lx\n", right);
		left = temp;
		printf("After round %d: %lx%lx\t%llx\n", i+1, left, right, subkeys[i]);
	}
	unsigned long plainblock = ((right<<32)|left);
	return permute(plainblock, 64, 64, fp_table);
}

int main()
{
	unsigned long long int key;
	unsigned int number_of_blocks;

	cout<<"Enter 64 bits key in hexadecimal form"<<endl;
	scanf("%llx", &key);
	cout<<"How many blocks of ciphertext?"<<endl;
	cin>>number_of_blocks;
	unsigned long long ciphertext[number_of_blocks];
	cout<<"Enter cipher text in hexadecimal form in blocks of 64 bits"<<endl;
	for(int i = 0; i < number_of_blocks; i++)
		scanf("%llx", &ciphertext[i]);
	
	cout<<"plain text: ";
	for(int i = 0; i < number_of_blocks; i++)
		printf("%llx\n", decrypt(ciphertext[i], key));

	return 0;
}

/*
aabb09182736ccdd
1
c0b7a8d05f3a829c
*/