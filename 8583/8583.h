// 8583.h: interface for the C8583 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_8583_H__39CBB89C_0A1D_4633_A8E1_FD943DCDEC6E__INCLUDED_)
#define AFX_8583_H__39CBB89C_0A1D_4633_A8E1_FD943DCDEC6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"


#define	LEN_MSG_CODE			  4
#define	LEN_BITMAP				  8
#define	LEN_PAN					 19
#define	LEN_PROC_CODE			  6
#define	LEN_TRAN_AMT			 12
#define	LEN_FRN_AMT				 12
#define	LEN_DCC_RATE			  8
#define	LEN_STAN				  6
#define	LEN_LOCAL_TIME		 	  6
#define	LEN_LOCAL_DATE			  4
#define	LEN_EXP_DATE			  4
#define	LEN_SETTLE_DATE			  4
#define	LEN_ENTRY_MODE			  4
#define	LEN_PAN_SEQ_NO			  3
#define	LEN_MCC					  4
//#define	LEN_NII					  3
#define	LEN_NII					  4
#define	LEN_COND_CODE			  2
#define	LEN_TRACK2				 37
#define	LEN_TRACK3				104
#define	LEN_RRN					 12
#define	LEN_AUTH_CODE			  6
#define	LEN_RSP_CODE			  2
#define	LEN_TERM_ID				  8
#define	LEN_MERCHANT_ID			 15
#define	LEN_ADDL_RSP			  2
#define	LEN_TRACK1				 76
#define	LEN_FIELD48				100
#define	LEN_CURCY_CODE			  4
//#define	LEN_CURCY_CODE			  2
#define	LEN_PIN_DATA			  8
#define	LEN_EXT_AMOUNT			 12
#define	LEN_ICC_DATA			260
#define	LEN_ICC_DATA2			110
#define	LEN_FIELD60				 22
#define	LEN_TMSFIELD60			600
//#define	LEN_FIELD61			 30
#define	LEN_FIELD61				 3
#define	LEN_INVOICE_NO			  6
#define LEN_FIELD62             100
#define	LEN_FIELD63				800
//#define	LEN_FIELD63				200
#define LEN_MAC					  8


#define LEN_MODEL				  4
#define LEN_SERIAL_NO			 12
#define LEN_POSVERSION			 12
#define LEN_BATCHNO				  3
#define LEN_F43					 40

#define  ERR_UNPACK_LEN		  -1000

#define Attr_a					  0
#define Attr_b					  1
#define Attr_n					  2
#define Attr_z					  3
#define Attr_UnUsed				  4
#define Attr_Over				  5

#define Attr_var1				  0
#define Attr_var2				  1
#define Attr_fix				  2

typedef struct _tagFIELD_ATTR
{
   uchar	eElementAttr;
   uchar	eLengthAttr;
   uint		uiLength;
} FIELD_ATTR;


class C8583  
{
public:
	C8583();
	virtual ~C8583();

	int Pack(FIELD_ATTR *pDataAttr, void *pSt8583, uchar *pusOut, uint *puiOutLen);
	int Unpack(FIELD_ATTR *pDataAttr, uchar *pusIn, uint uiInLen, void *pSt8583);

	inline static FIELD_ATTR* GetTMSFieldAttrs()		{ return ms_TMSFieldDef;		};
	inline static FIELD_ATTR* GetRecvTMSFieldAttrs()	{ return ms_recTMSFieldDef;		};
	//inline static FIELD_ATTR* GetTrnxFieldAttrs()		{ return ms_fieldDef;			};
	//inline static FIELD_ATTR* GetRecvTrnxFieldAttrs()	{ return ms_recFieldDef;		};

	inline static FIELD_ATTR* GetAdvFieldAttrs()		{ return ms_advFieldDef;		};
	inline static FIELD_ATTR* GetRecvAdvFieldAttrs()	{ return ms_recAdvFieldDef;		};

	inline static FIELD_ATTR* GetOnlineFieldAttrs()		{ return ms_OnlineFieldDef;		};
	inline static FIELD_ATTR* GetRecvOnlineFieldAttrs()	{ return ms_recOnlineFieldDef;	};

	inline static FIELD_ATTR* GetSettleFieldAttrs()		{ return ms_settleFieldDef;		};
	inline static FIELD_ATTR* GetRecvSettleFieldAttrs()	{ return ms_recSettleFieldDef;	};

	inline static FIELD_ATTR* GetVoidFieldAttrs()		{ return ms_voidFieldDef;		};
	inline static FIELD_ATTR* GetRecvVoidFieldAttrs()	{ return ms_recVoidFieldDef;	};

	inline static FIELD_ATTR* GetRefundFieldAttrs()		{ return ms_refundFieldDef;		};
	inline static FIELD_ATTR* GetRecvRefundFieldAttrs()	{ return ms_recRefundFieldDef;	};

private:
	int UnPackElement(FIELD_ATTR *pAttr, uchar *pusIn, uchar *pusOut, uint *puiInLen);
	int PackElement(FIELD_ATTR *pAttr, uchar *pusIn, uchar *pusOut, uint *puiOutLen);

private:
	static FIELD_ATTR ms_TMSFieldDef		[];
	static FIELD_ATTR ms_recTMSFieldDef		[];
	static FIELD_ATTR ms_fieldDef			[];
	static FIELD_ATTR ms_recFieldDef		[];
	static FIELD_ATTR ms_advFieldDef		[];
	static FIELD_ATTR ms_recAdvFieldDef		[];
	static FIELD_ATTR ms_OnlineFieldDef		[];
	static FIELD_ATTR ms_recOnlineFieldDef	[];
	static FIELD_ATTR ms_settleFieldDef		[];
	static FIELD_ATTR ms_recSettleFieldDef	[];
	static FIELD_ATTR ms_voidFieldDef		[];
	static FIELD_ATTR ms_recVoidFieldDef	[];
	static FIELD_ATTR ms_refundFieldDef		[];
	static FIELD_ATTR ms_recRefundFieldDef	[];
};

#endif // !defined(AFX_8583_H__39CBB89C_0A1D_4633_A8E1_FD943DCDEC6E__INCLUDED_)
