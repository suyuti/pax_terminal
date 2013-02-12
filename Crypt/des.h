
#ifndef _DES_H_
#define _DES_H_

#include "..\globaldef.h"
//#define NULL	0

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef byte *byteptr;
typedef byte MYINT;


void des_main (MYINT do_decrypt, byteptr input, byteptr output, byteptr key);
//void tdes(unsigned char *key, unsigned char *data);
void tdes_decrypt(unsigned char *key, unsigned char *data);
void TDES_CBC(unsigned char *fiDat, int  fiDatLen, unsigned char *fiIV, unsigned char *key, unsigned char *foRes, int  mode);
void tdes_decrypt(uchar *key, uchar *data);
void XOR(uchar *p1, uchar *p2, uchar *p3);
uchar CalcCheckSum(uchar * data, int DataLen);
void tdes(uchar *key, uchar *data);

#endif
