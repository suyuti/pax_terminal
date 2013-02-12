// OnlineEngine.h: interface for the CAdviceEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONLINEENGINE_H__6DAC00AF_DCC2_47DE_93C2_110C497C1C46__INCLUDED_)
#define AFX_ONLINEENGINE_H__6DAC00AF_DCC2_47DE_93C2_110C497C1C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"
#include "..\Files\Batch.h"

#define MAX_TRNX_COUNT	2048

class CEngine;
class CAdviceEngine : public CCommEngine2
{
private:
	CAdviceEngine();
public:
	CAdviceEngine(CEngine* pEng);
	virtual ~CAdviceEngine();

	int SendFirstAdvice(int max);					// ilk siradan max adet advice gonderir.
	int SendAdvice(int recNo);						// recNo'daki kaydi advice gonderir.
protected:
	int SendAdvice(CBatch::HBatchData hRec);		// recNo'daki kaydi advice gonderir.

protected:
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();

private:
	typedef struct _tagAdviceData {
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
	} AdviceData;

	typedef struct _tagRecvAdviceData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code // 0230
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3 : proc code
		uchar	szTranAmt		[LEN_TRAN_AMT	+ 2 ];	// F4 : Txn Amount
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11: STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12 : time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13 : date, YYMM
		uchar	szNii			[LEN_NII		+ 2 ];	// F24: NII
		uchar	szRRN			[LEN_RRN		+ 2 ];	// F37: RRN
		uchar	szRspCode		[LEN_RSP_CODE	+ 2 ];	// F39 : rsp code
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41: terminal id
	} RecvAdviceData;

private:
	AdviceData			m_elements;
	RecvAdviceData		m_recvElements;
	
	int					m_maxAdviceCount;					// Gonderilebilecek en fazla adv sayisi
	int					m_sentAdviceCount;					// Gonderilen Advice Sayisi
	int					m_recNo;							// Gonderilmekte olan kayit no
	int					m_adviceRecords[MAX_TRNX_COUNT];	// Gonderilecek adv kayit numaralari
	int					m_advRecordsCount;					// Listeye kac tane kayit girdi.
};

#endif // !defined(AFX_ONLINEENGINE_H__6DAC00AF_DCC2_47DE_93C2_110C497C1C46__INCLUDED_)
