#ifndef _NUMFUNCS_H__
#define _NUMFUNCS_H__

#define NO_CUT_BYTE					0				// No cut
#define LEFT_CUT_BYTE				1				// Cut one byte from left of the buffer
#define RIGHT_CUT_BYTE			    2				// Cut one byte from right of the buffer
#define PAD_ZERO					LEFT_PAD_ZERO

#define NO_PAD_ZERO					0
#define LEFT_PAD_ZERO					1				// Pad zero to the left of the buffer
#define RIGHT_PAD_ZERO			    		2				// Pad zero to the right of the buffer

#define TEKSAYI(p)					(p%2==1)

#define RIGHT_PAD                   0
#define LEFT_PAD                    1
#define PAD_TYPE					RIGHT_PAD
#define BYTE					unsigned char

#include "..\globaldef.h"

extern "C" {
//unsigned char  *Str2Bin(char *buff, unsigned char *bin);
unsigned		    Bin2Lng(unsigned char *buff, unsigned buff_len);
void                Lng2Bin(unsigned int lngValue, unsigned char *buff);
void				Short2Bin(unsigned short int shortValue, unsigned char *buff);
double				Bin2Dbl(unsigned char *buff, unsigned buff_len);
void                Dbl2Bin(double dblValue, unsigned char *buff);
char				*Bin2Str(unsigned char *buff, unsigned buff_len, char *str);
unsigned			Bcd2Lng(unsigned char *buff, unsigned buff_len);
void                Lng2Bcd(int lngValue, unsigned char *buff, int len);
double				Bcd2Dbl(unsigned char *buff, unsigned buff_len);
void                Dbl2Bcd(double dblValue, unsigned char *buff, int len);
char				*Bcd2Str(unsigned char *buff, unsigned buff_len, int cut_type, char *str);
unsigned char		*Str2Bin(char *, unsigned char *, int , int );
unsigned char		*Str2Bcd(char *str, unsigned str_len, int pad_type, unsigned char *bcd, int bcdlen, int pad_dir);
char				*ConvUpperCase(char *inbuff,int len, char *outbuff);
int					Bin2Bcd(unsigned char *binBuffer,int binBufferLen,unsigned char *bcdBuffer,int bcdBufferLen);
int					Bcd2Bin(unsigned char *bcdBuffer,int bcdBufferLen,unsigned char *binBuffer,int binBufferLen);
void				Bcd2Short(unsigned char *buff, unsigned short int *shortValue);
void				RotateStringInPlace(char buffer[]);
int					hex2int(char c);
void				itoa(int buff, char* dest, int pow);


void PubTrimStr(uchar *pszString);
uchar IsNumStr(char *pszStr);

typedef enum {
	DateType_YYYYMMDD				,
	DateType_DD_MM_YYYY				,
	DateType_MM_YYYY				,
	DateType_DD_MM_YYYY_HH_mm		,
	DateType_DD_MM_YYYY_HH_mm_SS	,
	DateType_MM_SLASH_YY			,
	DateType_YYMM					,
	DateType_YYYYMMDDHHmm			,
	DateType_HHmmSS					,
	DateType_HH_mm_SS				,
	DateType_DDMM					,
	DateType_MMDD					,
	DateType_HHmm					,
	DateType_DD_Name_YYYY			,
	DateType_DD_Name_YYYY__WName	,
} DateTypes;

void date2str(unsigned char* dateBCD, char* pDest, DateTypes type);


};
#endif
