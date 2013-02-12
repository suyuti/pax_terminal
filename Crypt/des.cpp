#include "des.h"
#include "..\globaldef.h"

//#define DECRYPT = 1;
//#define ENCRYPT = 0;

/* constant for DES */
byte key_1[8] = {'1','2','3','4','5','6','7','8'};
/*byte input_buffer1[8] = {'1','8','7','6','9','\0'};*/
byte input_buffer1[8] = {0x18, 0x76, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff}; 
/* data for DES */
byte result[8];
byte output_buffer[8];


#define SECRET_PIN  0x80
#define SECRET_KEY  0x0

#define MAC_KEY     0
#define CONF_KEY    1

#define KEYTYPE_INT 0
#define KEYTYPE_CONF 1
#define KEYTYPE_AC   2
#define KEYTYPE_EXT 3

#define SUCCEDED	100	


const byte crypt_shifttab   [16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
const byte decrypt_shifttab [16] = { 0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

const byte seltab[8][64] ={
   { 14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,
      3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,
      4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,
     15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13 },

   { 15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14,
      9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
      0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2,
      5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9 },

   { 10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10,
      1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1,
     13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7,
     11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12 },

   {  7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3,
      1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9,
     10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8,
     15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14 },

   {  2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1,
      8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6,
      4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13,
     15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3 },

   { 12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5,
      0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8,
      9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10,
      7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13 },

   {  4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10,
      3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6,
      1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7,
     10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12 },

   { 13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4,
     10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2,
      7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13,
      0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11 }
};

const byte permkey1[56] ={ 
	 56, 48, 40, 32, 24, 16,  8,
      0, 57, 49, 41, 33, 25, 17,
      9,  1, 58, 50, 42, 34, 26,
     18, 10,  2, 59, 51, 43, 35,
     62, 54, 46, 38, 30, 22, 14,
      6, 61, 53, 45, 37, 29, 21,
     13,  5, 60, 52, 44, 36, 28,
     20, 12,  4, 27, 19, 11,  3 
	 };

const byte permkey2[56] ={ 
     13, 16, 10, 23,  0,  4,
      2, 27, 14,  5, 20,  9,
     22, 18, 11,  3, 25,  7,
     15,  6, 26, 19, 12,  1,
     40, 51, 30, 36, 46, 54,
     29, 39, 50, 44, 32, 47,
     43, 48, 38, 55, 33, 52,
     45, 41, 49, 35, 28, 31 
	 };

const byte permefunc[48] ={
     31,  0,  1,  2,  3,  4,
      3,  4,  5,  6,  7,  8,
      7,  8,  9, 10, 11, 12,
     11, 12, 13, 14, 15, 16,
     15, 16, 17, 18, 19, 20,
     19, 20, 21, 22, 23, 24,
     23, 24, 25, 26, 27, 28,
     27, 28, 29, 30, 31,  0 
	 };

const byte perm32[32] ={
     15,  6, 19, 20,
     28, 11, 27, 16,
      0, 14, 22, 25,
      4, 17, 30,  9,
      1,  7, 23, 13,
     31, 26,  2,  8,
     18, 12, 29,  5,
     21, 10,  3, 24 
	 };

const byte iniperm[64] =
   { 57, 49, 41, 33, 25, 17,  9,  1,
     59, 51, 43, 35, 27, 19, 11,  3,
     61, 53, 45, 37, 29, 21, 13,  5,
     63, 55, 47, 39, 31, 23, 15,  7,
     56, 48, 40, 32, 24, 16,  8,  0,
     58, 50, 42, 34, 26, 18, 10,  2,
     60, 52, 44, 36, 28, 20, 12,  4,
     62, 54, 46, 38, 30, 22, 14,  6 };

const byte iniperm_compl [64] ={
      7, 39, 15, 47, 23, 55, 31, 63,
      6, 38, 14, 46, 22, 54, 30, 62,
      5, 37, 13, 45, 21, 53, 29, 61,
      4, 36, 12, 44, 20, 52, 28, 60,
      3, 35, 11, 43, 19, 51, 27, 59,
      2, 34, 10, 42, 18, 50, 26, 58,
      1, 33,  9, 41, 17, 49, 25, 57,
      0, 32,  8, 40, 16, 48, 24, 56 
	  };

const byte permi[64] ={
     17,  4, 61,  1, 18, 55, 45, 30,
     40,  2, 27, 29, 36,  8, 37, 53,
     42, 21, 34, 26, 25, 56, 54, 47,
     35, 33, 41, 11, 51, 62, 15, 12,
      7, 16, 49, 32, 22, 39, 19,  5,
     10, 38, 28, 52,  0, 58, 20, 59,
     60,  9, 44, 63, 13, 57,  3, 24,
     23, 48, 31, 14, 50, 43, 46,  6 
	 };

const byte permi_compl[64] ={
     44,  3,  9, 54,  1, 39, 63, 32,
     13, 49, 40, 27, 31, 52, 59, 30,
     33,  0,  4, 38, 46, 17, 36, 56,
     55, 20, 19, 10, 42, 11,  7, 58,
     35, 25, 18, 24, 12, 14, 41, 37,
      8, 26, 16, 61, 50,  6, 62, 23,
     57, 34, 60, 28, 43, 15, 22,  5,
     21, 53, 45, 47, 48,  2, 29, 51 
	 };

MYINT decrypt ;
static byte *shiftp;

byte extract_bit(byteptr str, byte idx)
{
   return (str [idx >> 3] >> (7 - (idx & 7))) & 1;
}


void permute(byteptr str, byteptr res, MYINT bytes, MYINT bits, byteptr table)
{
	MYINT byt, bit;
	byte r;

	for (byt = 0; byt < bytes; byt++)
	{
		r = 0;
		for (bit = 0; bit < bits; bit++)
		{
			r = (r << 1) | extract_bit (str, *table);
			table++;
		}
		*res = r;
		res++;	
	}

	/*for (byt = 0; byt < bytes; byt++)
	{
		r = 0;
		for (bit = 0; bit < bits; bit++)
			r = (r << 1) | extract_bit (str, *table++);
		*res++ = r;
	}*/
}


/*
   shift_28: shift data left one bit, 56 bits in two parts of 28 bits each.
*/
void shift_28(byteptr key)
{
	byte hi_carry, lo_carry;

	if (decrypt)
	{
		hi_carry = (key[3] & 0x10) ? 0x80 : 0;
		lo_carry = (key[6] & 0x01) ? 0x08 : 0;

		key[6] = (key[6] >> 1) | ((key[5] & 0x01) ? 0x80 : 0);
		key[5] = (key[5] >> 1) | ((key[4] & 0x01) ? 0x80 : 0);
		key[4] = (key[4] >> 1) | ((key[3] & 0x01) ? 0x80 : 0);
		key[3] = ((key[3] >> 1) & 0xf7) | lo_carry | ((key [2] & 0x01) ? 0x80 : 0);
		key[2] = (key[2] >> 1) | ((key[1] & 0x01) ? 0x80 : 0);
		key[1] = (key[1] >> 1) | ((key[0] & 0x01) ? 0x80 : 0);
		key[0] = (key[0] >> 1) | hi_carry;
	}
	else
	{
		hi_carry = (key[0] & 0x80) ? 0x10 : 0;
		lo_carry = (key[3] & 0x08) ? 0x01 : 0;

		key[0] = (key[0] << 1) | ((key[1] & 0x80) ? 1 : 0);
		key[1] = (key[1] << 1) | ((key[2] & 0x80) ? 1 : 0);
		key[2] = (key[2] << 1) | ((key[3] & 0x80) ? 1 : 0);
		key[3] = ((key[3] << 1) & 0xee) | hi_carry | ((key [4] & 0x80) ? 1 : 0);
		key[4] = (key[4] << 1) | ((key[5] & 0x80) ? 1 : 0);
		key[5] = (key[5] << 1) | ((key[6] & 0x80) ? 1 : 0);
		key[6] = (key[6] << 1) | lo_carry;
	}
}


void next_key(byteptr key,byteptr keychoice)
{
   if (*shiftp)
      shift_28(key);
   if (*shiftp++ > 1)
      shift_28(key);

   permute (key, keychoice, 8, 6, (byteptr)permkey2);
}


void xor_select(byteptr er, byteptr key, byteptr res)
{
	MYINT i, i0, i1;
	byte temp [8];

	for(i=0; i<8; i++)
      temp[i] = key[i] ^ er[i];

	for(i=0; i<4; i++)
	{
		i0 = i * 2;
		i1 = i0 + 1;
		temp[i] = (seltab[i0][temp[i0]] << 4) | seltab[i1][temp[i1]];
	}

	permute(temp, res, 4, 8, (byteptr)perm32);
}


void add(byteptr a, byteptr b)
{
   MYINT i;

   for (i=0; i<4; i++)
      a[i] ^= b[i];
}


void f_r_k(byteptr r, byteptr k, byteptr res)
{
	byte temp[8];

	permute(r, temp, 8, 6, (byteptr)permefunc);
	xor_select(temp, k, res);
}


/*   main DES module 

    do_decrypt  0 = encrypt  !=0 decrypt
	input  : address of data to be crypted 
	output : address of data crypted
    key    : address of key 
*/
void des_main (MYINT do_decrypt, byteptr input, byteptr output, byteptr key)
{
	byte	temp[8];
	byte	tmpkey[7];
	byte	keychoice[8];
	byte	f[4];

	byteptr x;
	byteptr left;
	byteptr right;

	MYINT		i;


    decrypt = do_decrypt ;  
	shiftp = (byte*)((decrypt) ? decrypt_shifttab : crypt_shifttab);

	permute (input, temp, 8, 8, (byteptr)iniperm);
	permute (key, tmpkey, 7, 8, (byteptr)permkey1);

	left = &temp[0];
	right = &temp[4];

	for (i = 0; i < 16; i++)
	{
		next_key (tmpkey, keychoice);
		f_r_k (right, keychoice, f);
		add (left, f);
		x = right;
		right = left;
		left = x;
	}

	permute (temp, output, 8, 8, (byteptr)iniperm_compl);
	return;
}

short int Encrypt( char *clear_PIN, char *ciphered_PIN )
{
	unsigned char j;
	unsigned char i;
	unsigned char aByte;

	unsigned char nibbled_PIN[8];

	if(strlen(clear_PIN) > 8)
		return -1;

	j = 0;
	for(i = 0; i < strlen(clear_PIN); i++)
	{
		if (!(i%2))
		{
			aByte = clear_PIN[i] - 0x30;
			aByte <<= 4;
		}
		else
		{
			aByte |= clear_PIN[i] - 0x30;
			nibbled_PIN[j++] = aByte;
		}
	}
	if (i%2)
	{
		aByte |= 0xF;
		nibbled_PIN[j++] = aByte;
	}
	for( ; j<8; j++)
		nibbled_PIN[j] = 0xFF;

	des_main(ENCRYPT, nibbled_PIN, (byteptr)ciphered_PIN, key_1);

	if(strlen(clear_PIN) > 8)
		return 0;

	return TRUE;
}

short int Decrypt_f( char *clear_PIN, char *ciphered_PIN )
{
	unsigned char j;
	unsigned char i;
	unsigned char temp;
	unsigned char temp_h;
	unsigned char temp_l;

	unsigned char nibbled_PIN[8];

	if(strlen(ciphered_PIN) < 8)
		return -1;

	des_main(DECRYPT, (byteptr)ciphered_PIN, nibbled_PIN, key_1);

	j = 0;
//	for(i = 0; i < strlen(nibbled_PIN); i++) 00 olunca 0x00 oluyor 
	for(i = 0; i < 8; i++)
	{

		if (nibbled_PIN[i] == 0xFF) break;
		temp = nibbled_PIN[i];
		temp_h = temp & 0xF0;
		temp_l = temp & 0x0F;
		temp_h >>= 4;
		temp_h &= 0x0F;
		
		clear_PIN[j] = temp_h + 0x30;
		j++;

/*		temp = nibbled_PIN[i];
		temp &= 0x0F;
*/
		clear_PIN[j] = temp_l + 0x30;
		j++;
	}
	

	if(j <= 4)
		return 0;

	return TRUE;
}

// Veli 
//
void TDES_CBC(unsigned char *fiDat, int  fiDatLen, unsigned char *fiIV, unsigned char *key, unsigned char *foRes, int  mode)
{
	unsigned char uIVCurrent[8];
	unsigned char uTemp[8];
	unsigned char encData[16];
	int index, i;

	index = 0;
	if (fiIV == NULL)
	memset(uIVCurrent, 0, 8);
	else
	memcpy(uIVCurrent, fiIV, 8);

	while (index < fiDatLen)
	{
		if (mode == 1) // ENCRYPT (parametre)
		{
			  memcpy(uTemp, fiDat + index, 8);
			  if (index > 0)
			  {
					for (i = 0; i < 8; i++)
						  uTemp[i] ^= uIVCurrent[i];
			  }
			  tdes((uchar*)uTemp, key);
			  memcpy(&encData[index], uTemp, 8);
			  memcpy(uIVCurrent, uTemp, 8);
		}
		else
		{
			  // Ayni buffer uzerinde decrypt yapma ihtimaline karsin sakla
			  memcpy(uTemp, fiDat + index, 8);
			  //DES3(uTemp, fiKey, foRes + index, fiMode);
			  if (index > 0)
			  {
					for (i = 0; i < 8; i++)
						  foRes[index + i] ^= uIVCurrent[i];
			  }
			  memcpy(&encData[index], uTemp, 8);
			  memcpy(uIVCurrent, uTemp, 8);
		}

		index += 8;
	}
	memcpy(foRes, encData, fiDatLen);
	return;
}

void XOR(unsigned char *p1, unsigned char *p2, unsigned char *p3)
{
    int i;

    for (i=0;i<8;i++)
        p3[i] = p1[i]^p2[i];
}


unsigned char CalcCheckSum(unsigned char * data, int DataLen)
{
    int i;
    unsigned char CheckSum=0;

    for (i=0;i<DataLen;i++)
        CheckSum = CheckSum^data[i];

    CheckSum = CheckSum^0xA5;
    return CheckSum;
}


void tdes(unsigned char *data,unsigned char *key)
{
    unsigned char temp[8], temp2[8];
    des_main(0, data, temp, key);
    des_main(1, temp, temp2,&key[8]);
    des_main(0, temp2, data,key);
}

void tdes_decrypt(unsigned char *data,unsigned char *key)
{
	unsigned char temp[8], temp2[8];
    des_main(1, data, temp, key);
    des_main(0, temp, temp2,&key[8]);
    des_main(1, temp2, data,key);
}





