//#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NumFuncs.h"

int power(int a, int b)
{
	int res;
	int i;

	res = 1;
	for (i=0;i<b;i++)
	{
		res = res*a;
	}
	return res;
}


char * ConvUpperCase(char *in_buff,int len, char *out_buff)
{
	int	i;

	for (i=0;i<len;i++)
	{
		if ((in_buff[i] >= 0x61)&&(in_buff[i] <= 0x7A))
			out_buff[i] = in_buff[i] - 0x20;
		else
			out_buff[i] = in_buff[i];
	}

	out_buff[len] = 0;
	return out_buff;
}


unsigned Bin2Lng(unsigned char *buff, unsigned buff_len)
{
	unsigned        Lng,i,j;
	unsigned char   buf[4];									// 4 : The size of Long type.

	if ((buff_len > 4)||(buff_len < 0))
		return (unsigned)-1;

	for (i=0;i<4-buff_len;i++)						// Reset first bytes .
		buf[i]=0;

	for (j=i;j<4;j++)											// Fill last bytes.
		buf[j] = buff[j-i];

	Lng = (buf[0]<<24)|(buf[1]<<16)|(buf[2]<<8)|(buf[3]); // Prep Lng
	return Lng;
}


void Lng2Bin(unsigned int lngValue, unsigned char *buff)
{
	memset(buff, 0, sizeof(int));					// Reset all bytes
	buff[3] = lngValue&0xFF;
	buff[2] = (lngValue>>8)&0xFF;
	buff[1] = (lngValue>>16)&0xFF;
	buff[0] = (lngValue>>24)&0xFF;
}

void Short2Bin(unsigned short int shortValue, unsigned char *buff)
{
	buff[1] = shortValue&0xFF;
	buff[0] = (shortValue>>8)&0xFF;
}

void Bcd2Short(unsigned char *buff, unsigned short int *shortValue)
{
	unsigned short int Temp1;
	unsigned short int Temp2;

	//bu fonksiyon 2 byte'lýk buff'ý short'a çevirir.
	Temp1=buff[0];
	Temp2=Temp1<<8;
	Temp2 = Temp2 + buff[1];
	*shortValue = Temp2;
}

double Bin2Dbl(unsigned char *buff, unsigned buff_len)
{
	double			Dbl;
	int				lnibble;
	int				unibble;
	unsigned		i,j;
	unsigned char	buf[8];

	if ((buff_len > 8)||(buff_len < 0))		// 8 : The size of double type.
		return -1;

	for (i=0;i<8-buff_len;i++)						// Reset first bytes .
		buf[i]=0;

	for (j=i;j<8;j++)											// Fill last bytes.
		buf[j] = buff[j-i];

	unibble = (buf[0]<<56)|(buf[1]<<48)|(buf[2]<<40)|(buf[3]<<32);	// Prep upper nibble
	lnibble =	(buf[4]<<24)|(buf[5]<<16)|(buf[6]<<8)|(buf[7]);				// Prep lower nibble

	Dbl = (double)unibble * power(2,32) + lnibble;	// Pad upper and lower nibbles.

	return Dbl;
}


void  Dbl2Bin(double dblValue, unsigned char *buff)
{
	int				lnibble;			// lower nibble
	int				unibble;			// upper nibble

	memset(buff, 0, sizeof(double));

	lnibble = (int)dblValue;
	unibble = (int)(dblValue / power(2,32));

	buff[7] = lnibble&0xFF;
	buff[6] = (lnibble>>8)&0xFF;
	buff[5] = (lnibble>>16)&0xFF;
	buff[4] = (lnibble>>24)&0xFF;

	buff[3] = unibble&0xFF;
	buff[2] = (unibble>>8)&0xFF;
	buff[1] = (unibble>>16)&0xFF;
	buff[0] = (unibble>>24)&0xFF;

}


char  *Bin2Str(unsigned char *buff, unsigned buff_len, char *str)
{
	unsigned	i;
	double		Dbl;

	if (buff_len > 8)
		return (char*)NULL;

	Dbl = 0;
	for (i=0;i<buff_len;i++)
	{
			Dbl = Dbl+(buff[buff_len-1-i]&0x0F)*power(16,2*i);
			Dbl = Dbl+(buff[buff_len-1-i]>>4)*power(16,2*i+1);
	}

	sprintf(str, "%.0f", Dbl);

	return str;
}

void  itoa(int buff, char* dest, int pow)
{
	sprintf(dest, "%d", buff);
	//PrnInit(); PrnStr("%d %s\n", buff, dest); PrnStart();
}

unsigned char  *Str2Bin(char *buff, unsigned char *bin, int bin_len, int pad_dir)
{
	unsigned			i,a;
	unsigned			buff_len;
        unsigned char       str_buf[8], str_buf2[8];

	buff_len = strlen(buff);
	memset(bin, 0, buff_len);
	if ((buff_len > 8)||(buff_len < 0))
		return (unsigned char*)NULL;

	/* Gelen String'in hex karþýlýðý bulunur.		*/
	a = atoi(buff);
	sprintf((char *)str_buf2, "%2.2X", a);

        if (strlen((const char*)str_buf2)%2 == 1)
        {
            strcpy((char*)str_buf, (const char*)"0");
            strcat((char*)str_buf, (const char*)str_buf2);
        }
        else
            strcpy((char*)str_buf, (const char*)str_buf2);
	buff_len = strlen((const char*)str_buf);

	for (i=0;i<buff_len;i++)
	{
		if (TEKSAYI(i) == 1)
                {
                    if (pad_dir == LEFT_PAD)
                    {
			if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				bin[i/2] += str_buf[i]-0x37;
			else if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))	// 1..9
				bin[i/2] += str_buf[i]-0x30;
			else
                            return (unsigned char*)NULL;
                    }
                    else
                    {
			if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				bin[bin_len-(strlen((const char*)str_buf)/2)+i/2] += str_buf[i]-0x37;
			else if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))	// 1..9
                        {
				bin[bin_len-(strlen((const char*)str_buf)/2)+i/2] += str_buf[i]-0x30;
                        }
			else
                            return (unsigned char*)NULL;
                    }
		}
		else
		{
                    if (pad_dir == LEFT_PAD)
                    {
			if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				bin[i/2] = (str_buf[i]-0x37)<<4;
			else if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))	// 1..9
				bin[i/2] = (str_buf[i]-0x30)<<4;
			else
                            return (unsigned char*)NULL;
                    }
                    else
                    {
			if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				bin[bin_len-(strlen((const char*)str_buf)/2)+i/2] = (str_buf[i]-0x37)<<4;
                        else if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))	// 1..9
                        {
                            bin[bin_len-(strlen((const char*)str_buf)/2)+i/2] = (str_buf[i]-0x30)<<4;
                        }
			else
                            return (unsigned char*)NULL;
                    }
		}
	}

	return bin;
}




unsigned Bcd2Lng(unsigned char *buff, unsigned buff_len)
{
	unsigned		Lng;
	unsigned		i,j;
	int				FrstNibble;
	int				ScndNibble;

// log(2^32) = 9.5 so the buff_len shouldn't be more than 5
	if ((buff_len > 9)||(buff_len < 0))
		return (unsigned)-1;
// If buff_len = 5, buff[0] shouln't br greater than 3
	if (buff_len == 9)
	{
		if (buff[0] > 0x03)
			return (unsigned)-1;
	}

	Lng = 0;

	for (i=0;i<buff_len;i++)
	{
		j = buff_len-1-i;
		FrstNibble = buff[j]&0x0F;
		ScndNibble = buff[j]>>4;
//		if ((FrstNibble > 0x09)||(ScndNibble > 0x09))
//			return FALSE;
		Lng += (FrstNibble)*power(10,2*i);
		Lng += (ScndNibble)*power(10,2*i+1);
	}

	return Lng;
}


void Lng2Bcd(int lngValue, unsigned char *buff, int len)
{
	unsigned char	str[20];
    int             buff_len,i;
    unsigned char   buf[20];

	sprintf((char *)str, "%d", lngValue);

    buff_len = strlen((const char*)str)/2 + strlen((const char*)str)%2;

	Str2Bcd((char *)str, strlen((char *)str), LEFT_PAD_ZERO, buf, 20, LEFT_PAD);
//	Str2Bcd(str, strlen((char *)str), NO_PAD_ZERO, buf);

    if (len > buff_len)
    {
        for(i=0;i<len-buff_len;i++)
            buff[i] = 0;
        for (i=len-buff_len;i<len;i++)
            buff[i] = buf[i-len+buff_len];
    }
    else
        for (i=0;i<len;i++)
            buff[i] = buf[i];
}


double Bcd2Dbl(unsigned char *buff, unsigned buff_len)
{
	double			Dbl;
	unsigned		i,j;
	int				FrstNibble;
	int				ScndNibble;

	Dbl = 0;

// log(2^65) = 19.5 . So the length of the BCD string shouldn't exceed the 19
	if ((buff_len > 18)||(buff_len < 0))
		return (double)-1;

	for (i=0;i<buff_len;i++)
	{
		j = buff_len-1-i;
		FrstNibble = buff[j]&0x0F;
		ScndNibble = buff[j]>>4;
//		if ((FrstNibble > 0x09)||(ScndNibble > 0x09))
//			return FALSE;
		Dbl += (FrstNibble)*power(10,2*i);
		Dbl += (ScndNibble)*power(10,2*i+1);
	}

	return Dbl;
}


void  Dbl2Bcd(double dblValue, unsigned char *buff, int len)
{
	unsigned char	str[20];
    int             buff_len,i;
    unsigned char   buf[20];

	sprintf((char *)str, "%0.f", dblValue);
	buff_len = strlen((const char*)str)/2 + strlen((const char*)str)%2;

	Str2Bcd((char *)str, strlen((const char*)str), LEFT_PAD_ZERO, buf,20, LEFT_PAD);
//	Str2Bcd(str, strlen(str), NO_PAD_ZERO, buf); // Deðiþtirildi

    if (len > buff_len)
    {
        for(i=0;i<len-buff_len;i++)
            buff[i] = 0;
        for (i=len-buff_len;i<len;i++)
            buff[i] = buf[i-len+buff_len];
    }
    else
        for (i=0;i<len;i++)
            buff[i] = buf[i];
}


char  *Bcd2Str(unsigned char *buff, unsigned buff_len, int cut_type, char *str)
{
	unsigned        i;
	unsigned char   str_buf[2048];
	int				str_len;

// The length of ASCII string is two times of length of BCD string plus one NULL character
	//str_buf = (unsigned char *)malloc(buff_len*2+1);
//	malloc((char **)&str_buf,buff_len*2+1);
	if (str_buf == NULL)
		return (char*)NULL;

	str_len = buff_len*2;

	for (i=0;i<buff_len;i++)
	{
		sprintf((char *)str_buf+i*2, "%2.2X",buff[i]);
	}

// If the length of string is odd value, right or left pad the string
	if (cut_type == LEFT_CUT_BYTE)
	{
		memcpy(str, str_buf+1, str_len-1);
		str[str_len-1] = 0;
	}
	else if (cut_type == RIGHT_CUT_BYTE)
	{
		memcpy(str, str_buf, str_len-1);
		str[str_len-1] = 0;
	}
	else
	{
		memcpy(str, str_buf, str_len);
		str[str_len] = 0;
	}

	//free((char *)str_buf);
	return str;
}


/*	String bit düzeninde verilmiþ bir buffer'ý BCD bit düzenine çevirir.				*/
/*  str_len deðeri tek sayý verilmiþ ise string'in soluna ve saðýna 0 ekler.		*/
/*	Mesela str = "792" ve PAD_ZERO = LEFT_PAD_ZERO olarak tanýmlanmýþsa					*/
/*  bcd = 07 92, str = "792" ve pad type = LEFT_PAD_ZERO olarak tanýmlanmýþsa		*/
/*  bcd = 79 20 döner. */
/*  Örnek Data = str = "11234567", str_len = 8 ise bcd = 0x11 0x23 0x45 0x67    */
/*  pad_dir : RIGHT_PAD : Saða dayalý */
/*  pad_dir : LEFT_PAD : Sola dayalý */

unsigned char  *Str2Bcd(char *str, unsigned str_len, int pad_type, unsigned char *bcd, int bcdlen, int pad_dir)
{
	unsigned		i,index;
	unsigned char	lnibble;
	unsigned char	unibble = 0x0;
	unsigned char   str_buf[2048];
	unsigned		str_buf_len;


	//str_buf = (unsigned char *)malloc(str_len + str_len%2);
//	malloc((char **)&str_buf,str_len + str_len%2);

	if (TEKSAYI(str_len))
	{
		if (pad_type == LEFT_PAD_ZERO)			// Left Pad
		{
			str_buf[0] = '0';
			memcpy(str_buf+1, str, str_len);
			str_buf_len = str_len +1;
		}
		else if (pad_type == RIGHT_PAD_ZERO)// Right Pad
		{
			memcpy(str_buf, str, str_len);
			str_buf[str_len] = '0';
			str_buf_len = str_len +1;
		}
		else
		{
			memcpy(str_buf, str, str_len);
			str_buf_len = str_len;
		}
	}
	else
	{
		memcpy(str_buf, str, str_len);
		str_buf_len = str_len;
	}

	memset(bcd, 0, bcdlen);
	if (pad_dir == RIGHT_PAD)
		index = bcdlen-(str_len+1)/2;
	else
		index=0;

	for (i=0;i<str_buf_len;i++)
	{
		if (TEKSAYI(i) == 0)
		{
			if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))							// 0..9
				unibble = str_buf[i]-0x30;															// upper nibble of byte
			else if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				unibble = str_buf[i]-0x37;
			else
			{
			//	free((char *)str_buf);
				return (unsigned char*)NULL;
			}
	        bcd[index+i/2] = unibble;
		}
		else
		{
			if ((str_buf[i]>= 0x30)&&(str_buf[i]<= 0x39))							// 0..9
				lnibble = str_buf[i]-0x30;															// lower nibble of byte
			else if ((str_buf[i]>= 0x41)&&(str_buf[i]<= 0x46))				// A..F
				lnibble = str_buf[i]-0x37;
			else
			{
//				free((char *)str_buf);
				return (unsigned char *)NULL;
			}
			bcd[index+i/2] = (unibble << 4)|(lnibble);
		}
	}
	//free((char *)str_buf);
	return bcd;
}

int Bin2Bcd(unsigned char *binBuffer,int binBufferLen,unsigned char *bcdBuffer,int bcdBufferLen)
{
	char strBuffer[500]="";	

	Bin2Str(binBuffer,binBufferLen,strBuffer);
	Str2Bcd(strBuffer,strlen(strBuffer),0,bcdBuffer,bcdBufferLen,LEFT_PAD_ZERO);
	return 1;
}

int Bcd2Bin(unsigned char *bcdBuffer,int bcdBufferLen,unsigned char *binBuffer,int binBufferLen)
{
	char strBuffer[512]="";	

	Bcd2Str(bcdBuffer,bcdBufferLen,0,strBuffer);
	Str2Bin(strBuffer,binBuffer,binBufferLen,0);
	return 1;
}


void RotateStringInPlace(char buffer[])
{ 

	// Get the length of the string.
	char tmp;
	int len=strlen(buffer);
	if(len==0){
		return;
	}

	// Save the first character, it's going to be overwritten. 

	tmp= buffer[0];

	// Slide the rest of the string over by one position.

	memmove(&buffer[0], &buffer[1], len-1);

	// Put the character we saved from the front of the string in place.

	buffer[len-1]=tmp;
	return;
} 

void PubTrimStr(uchar *pszString)
{
#define ISSPACE(ch) ( ((ch) == ' ')  || ((ch) == '\t') || \
	((ch) == '\n') || ((ch) == '\r') )
	
    uchar *p, *q;
	
    if( !pszString || !*pszString )
    {
        return;
    }
	
    p = &pszString[strlen((char*)pszString) - 1];
    while(( p > pszString) && ISSPACE(*p) )
    {
        *p-- = 0;
    }
    if( (p == pszString) && ISSPACE(*p) )  *p = 0;
	
    for(p = pszString; *p && ISSPACE(*p); p++);
    if( p != pszString )
    {
        q = pszString;
        while( *p )   *q++ = *p++;
        *q = 0;
    }
#undef ISSPACE
}

uchar IsNumStr(char *pszStr)
{
	if( pszStr==NULL || *pszStr==0 )
	{
		return FALSE;
	}

	while( *pszStr )
	{
		if( !isdigit(*pszStr++) )
		{
			return FALSE;
		}
	}

	return TRUE;
}

void date2str(unsigned char* dateBCD, char* pDest, DateTypes type)
{
	// dateBCD: YYMMDDHHmmSSW

	char tmp[32] = "";
	
	Bcd2Str(dateBCD, 7, 0, tmp);

	switch (type) {
		case DateType_YYYYMMDD				: 
		break;
		case DateType_DD_MM_YYYY			: 
		break;
		case DateType_MM_YYYY				: 
		break;
		case DateType_DD_MM_YYYY_HH_mm		: 
		break;
		case DateType_DD_MM_YYYY_HH_mm_SS	: 
			pDest[ 0] = tmp[4];
			pDest[ 1] = tmp[5];
			pDest[ 2] = '.';
			pDest[ 3] = tmp[2];
			pDest[ 4] = tmp[3];
			pDest[ 5] = '.';
			pDest[ 6] = '2';
			pDest[ 7] = '0';
			pDest[ 8] = tmp[0];
			pDest[ 9] = tmp[1];
			pDest[10] = ' ';
			pDest[11] = tmp[6];
			pDest[12] = tmp[7];
			pDest[13] = ':';
			pDest[14] = tmp[8];
			pDest[15] = tmp[9];
			pDest[16] = ':';
			pDest[17] = tmp[10];
			pDest[18] = tmp[11];
			pDest[19] = 0x00;
		break;
		case DateType_MM_SLASH_YY			: 
		break;
		case DateType_YYMM					: 
		break;
		case DateType_YYYYMMDDHHmm			: 
		break;
		case DateType_HHmmSS				: 
		break;
		case DateType_HH_mm_SS				: 
		break;
		case DateType_DDMM					: 
		break;
		case DateType_MMDD					: 
		break;
		case DateType_HHmm					: 
		break;
		case DateType_DD_Name_YYYY			: 
		break;
		case DateType_DD_Name_YYYY__WName	: 
		break;
	}
}

int hex2int(char c)
{
  if(c >= '0' && c <= '9')
    return c - '0';
  if(c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  if(c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  return -1;
}
