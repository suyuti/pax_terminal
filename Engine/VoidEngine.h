// VoidEngine.h: interface for the CVoidEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOIDENGINE_H__8D8A4ECC_28A6_40A2_AB88_AEBBBC24BC4A__INCLUDED_)
#define AFX_VOIDENGINE_H__8D8A4ECC_28A6_40A2_AB88_AEBBBC24BC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"

class CEngine;
class CVoidEngine : public CCommEngine2  
{
private:
	CVoidEngine();
public:
	CVoidEngine(CEngine*);
	virtual ~CVoidEngine();

	int			DoVoid(int rec);
	int			DoReversal(int rec);

protected:
	
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();

private:
	typedef struct _tagVoidData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szPan			[LEN_PAN		+ 2 ];	// F2 : PAN
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3 : proc code
		uchar	szTranAmt		[LEN_TRAN_AMT	+ 2 ];	// F4 : Txn Amount
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11: STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12: time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13: date, YYMM
		uchar	szExpDate		[LEN_EXP_DATE	+ 2 ];	// F14: Expiry, YYMM
		uchar	szMcc			[LEN_MCC		+ 2 ];	// F18: MCC
		uchar	szEntryMode		[LEN_ENTRY_MODE	+ 2 ];	// F22: POS Entry Mode
		uchar	szNii			[LEN_NII		+ 2 ];	// F24: NII
		uchar	szRRN			[LEN_RRN		+ 2 ];	// F37: RRN
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41: terminal id
		uchar	szMerchantID	[LEN_MERCHANT_ID+ 2 ];	// F42: merchant id
		uchar	szF43Data		[LEN_F43		+ 2	];	// F43: 
		uchar	szCurrencyCode	[LEN_CURCY_CODE	+ 2	];	// F49: CurrencyCode
	} VoidData;

	typedef struct _tagRecvVoidData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code // 0230
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3  : proc code
		uchar	szTranAmt		[LEN_TRAN_AMT	+ 2 ];	// F4  : Txn Amount
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11 : STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12 : time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13 : date, YYMM
		uchar	szNii			[LEN_NII		+ 2 ];	// F24 : NII
		uchar	szRRN			[LEN_RRN		+ 2 ];	// F37 : RRN
		uchar	szAuthCode		[LEN_AUTH_CODE	+ 2 ];	// F38 : Auth Code
		uchar	szRspCode		[LEN_RSP_CODE	+ 2 ];	// F39 : rsp code
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41 : terminal id
		uchar	szMerchID		[LEN_MERCHANT_ID+ 2 ];	// F42 : Merchant id
		uchar	szF63Data		[LEN_FIELD63	+ 2 ];	// F42 : Merchant id
	} RecvVoidData;
private:
	VoidData			m_elements;
	RecvVoidData		m_recvElements;

	int					m_recNo;				// Gonderilmekte olan kayit no
	bool				m_bReversal;

};

#endif // !defined(AFX_VOIDENGINE_H__8D8A4ECC_28A6_40A2_AB88_AEBBBC24BC4A__INCLUDED_)
