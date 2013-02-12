#ifndef _GLOBALDEF_H_
#define _GLOBALDEF_H_

//#include <assert.h>
#include <posapi.h>
#include <posapi_all.h>
#include <stdlib.h>
#include <string.h>

//#define OFFLINE_TEST



void AssertDisp(uchar *pszFileName, ulong ulLineNo);
void PrintBuffer(unsigned char* pBuffer, int size);

#define HEX2INT(x) (unsigned int)(x >= '0' && x <= '9' ? x - '0' : x >= 'a' && x <= 'f' ? x - 'a' + 10 : x >= 'A' && x <= 'F' ? x - 'A' + 10 : 0)
extern char g_int2hex[17];
#define INT2HEX(X) g_int2hex[(X)&0xf]

#ifndef NULL
	//#define NULL ((void *) 0)
	#define NULL (0L)
#endif //NULL

#ifndef ASSERT
	//#undef ASSERT

#define ASSERT(expr)                                           \
                if( !(expr) ){                                      \
                    AssertDisp((uchar *)__FILE__, (ulong)(__LINE__));       \
                }
#endif //_ASSERT

//typedef unsigned char uchar;


#define KEY_UP		5
#define KEY_DOWN	6
#define KEY_ENTER	13
#define KEY_CANCEL	27
#define KEY_MENU	20
#define KEY_CLEAR	0x08
#define KEY_ALPHA	0x07
#define KEY_A		0x3b
#define KEY_B		0x3c
#define KEY_C		0x3d
#define KEY_D		0x3e


#define SUCCESS					(    0)
#define CONTINUE				(    1)
#define GENERAL_FAILURE			(-5001)
#define OBJECT_NOT_CREATED		(-5002)
//#define FILE_NOT_OPENED		(-5003)
#define LOGIN_FAILURE			(-5004)
#define UNPACK_ERROR			(-5005)
#define REPRINT_NOT_SUPPORTED	(-5006)
#define RESPONSE_CODE_ERROR		(-5007)
#define PROCESSDATA_ERR			(-5008)
#define LAST_PACKET				(-5009)
#define DEFAULT_PARAMS_NOT_OPEN	(-5010)
#define BATCH_NOT_OPEN			(-5011)
#define ALREADY_SENT			(-5012)
#define TERMINAL_NOT_OPEN		(-5013)
#define PARAMETERS_NOT_EXIST	(-5014)
#define DOES_NOT_NEED_REVERSAL	(-5015)
#define TRNX_NOT_FOUND			(-5016)
#define CARD_NOT_READ			(-5017)
#define CARD_NOT_SAME			(-5018)
#define INVERSE_OPERATION_ERROR	(-5019)
#define TRNX_DOES_NOT_NEED_SEND	(-5020)
#define TRNX_ALREADY_VOIDED		(-5021)
#define PARAMS_FILE_NOT_OPEN	(-5022)
#define ACQUIER_FILE_NOT_OPEN	(-5023)
#define USER_CANCELLED			(-5024)
#define USER_TIMEOUT			(-5025)
#define PASSWORD_NOT_VALID		(-5026)
#define TRNX_DELETED			(-5027)
#define NOT_CONNECTED			(-5028)
#define NOT_NEED_REVERSAL		(-5029)
#define TRNX_NOT_SUCCESS		(-5030)
#define MAKE_REVERSAL			(-5031)

#define TRUE		1
#define FALSE		0

#define _S_SERIES_

#ifdef _S_SERIES_
#define SXX_IP_MODULE			//S80的IP模块通迅方式
#define SXX_WIRELESS_MODULE		//S系列无线模块
#endif
#if defined(SXX_WIRELESS_MODULE) || defined(SXX_IP_MODULE)
//#include "SxxCom.h"
#endif


#define TIMER_TEMPORARY			4       
#define TIMER_AUTO_ADVICE		5       

#define ERR_BASE			0x10000
#define ERR_PINPAD			(ERR_BASE+0x01)
#define ERR_NO_TELNO		(ERR_BASE+0x03)
#define ERR_SWIPECARD		(ERR_BASE+0x05)
#define ERR_USERCANCEL		(ERR_BASE+0x06)
#define ERR_TRAN_FAIL		(ERR_BASE+0x07)
#define ERR_UNSUPPORT_CARD	(ERR_BASE+0x08)
#define ERR_SEL_ACQ			(ERR_BASE+0x09)
#define ERR_HOST_REJ		(ERR_BASE+0x0A)
#define ERR_FILEOPER		(ERR_BASE+99)
// #define ERR_NOT_EMV_CARD	(ERR_BASE+100)
#define ERR_NEED_INSERT		(ERR_BASE+101)
#define ERR_NEED_FALLBACK	(ERR_BASE+102)
#define ERR_NEED_SWIPE		(ERR_BASE+103)
#define ERR_EXIT_APP		(ERR_BASE+990)
#define ERR_NO_DISP			(ERR_BASE+999)


//---------------------------
//  Action Methods

void Method_TermianlID(void);
void Method_MerchantID(void);

void islemIptal(void);
void islemIade(void);
void islemHarcamaHandler(void);
void islemHarcamaIptalHandler(void);
void islemHarcamaIadeHandler(void);
void islemBakiyeSorguHandler(void);
void islemNakitYuklemeHandler(void);
void islemKrediKartYuklemeHandler(void);
void islemBankaKartYuklemeHandler(void);
void islemYuklemeIptalHandler(void);
void islemPuanKullanmaHandler(void);
void islemPuanKullanmaIptalHandler(void);
void islemPuanKullanmaIadeHandler(void);
void islemPuanSorguHandler(void);
void islemKartGuncelleHandler(void);
void islemKayitIzleHandler(void);
void islemTestHandler(void);
void islemTestTemizleHandler(void);
void islemDefaultParameters(void);
void islemParametreYukleHandler(void);
void islemSonSlipYaz();
void islemShowParametreler(void);
void islemShowToplamRapor(void);
void islemGunsonuYap(void);
void islemSonGunsonuYaz(void);

//#define PRNLINE(x)
#define PRN(x)

//#define PRN(x) PrnInit(); PrnStr("%s", x); PrnStart();
#define PRNLINE(x)			PrnInit(); PrnStr("%s\n", x); PrnStart();
#define PRNBUFFER(x, y)		PrintBuffer((x),(y))

#define USER_OPER_TIMEOUT		60
#define TCPMAXSENDLEN			10240


//--------------------------------------------------------------------------
	#define	LEN_MAX_COMM_DATA	10240
//----------------------------------------------------------------------------

#endif //_GLOBALDEF_H_
