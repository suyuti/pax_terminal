// RefundEngine.h: interface for the CRefundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REFUNDENGINE_H__2E221722_6554_4CEE_A3A1_5DA1A2E7923D__INCLUDED_)
#define AFX_REFUNDENGINE_H__2E221722_6554_4CEE_A3A1_5DA1A2E7923D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"
#include "..\Files\Batch.h"

class CEngine;
class CTrnxBase;
class CRefundEngine : public CCommEngine2  
{
private:
	CRefundEngine();
public:
	CRefundEngine(CEngine*);
	virtual ~CRefundEngine();

	int DoRefund(CTrnxBase*);
	int DoReversal(CTrnxBase*);

	inline int	GetRefundBalance()		{ return this->m_refundBalance;		};
	inline int	GetRefundPoint()		{ return this->m_refundPoint;		};
	inline bool	IsLoadBalanceToCard()	{ return this->m_bLoadBalanceToCard;};
	inline bool	IsLoadPointToCard()		{ return this->m_bLoadPointToCard;	};


	// bunlar taban sinifa tasinabilir.
	int	GetResponseMsgPrn(char*, int*);
	int	GetResponseMsgScr(char*, int*);



protected:
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();
	virtual int		OnConnect();

	int ParseF63();

private:
	typedef struct _tagRefundData {
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
		uchar	szF62			[LEN_FIELD62	+ 2 ];	// F42 : Merchant id
	} RefundData;

	typedef struct _tagRecvRefundData {
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
		uchar	szF63			[LEN_FIELD63	+ 2 ];	// F42 : Merchant id
	} RecvRefundData;
protected:
	virtual int		PrepF62();

private:
	RefundData			m_elements;
	RecvRefundData		m_recvElements;
	int					m_recNo;				// Gonderilmekte olan kayit no
	bool				m_bReversal;

	unsigned char*		m_pF62Buffer;
	int					m_F62Size;
	CBatch::HBatchData	m_hBatch;
	int					m_refundBalance;
	int					m_refundPoint;
	bool				m_bLoadBalanceToCard;
	bool				m_bLoadPointToCard;
};

#endif // !defined(AFX_REFUNDENGINE_H__2E221722_6554_4CEE_A3A1_5DA1A2E7923D__INCLUDED_)
