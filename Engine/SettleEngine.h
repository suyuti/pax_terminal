// SettleEngine.h: interface for the CSettleEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTLEENGINE_H__ED57CAB7_2CB9_4566_AFA9_5115D755043D__INCLUDED_)
#define AFX_SETTLEENGINE_H__ED57CAB7_2CB9_4566_AFA9_5115D755043D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"

class CEngine;
class CSettleEngine : public CCommEngine2  
{
private:
	CSettleEngine();
public:
	CSettleEngine(CEngine* pEng);
	virtual ~CSettleEngine();
	int DoSettle();
	int CalcSettle();

	typedef struct _tagSettleData {
		int m_saleCount;
		int m_saleTotal;
		int m_saleVoidCount;
		int m_saleVoidTotal;

		int m_cashLoadCount;
		int m_cashLoadTotal;
		int m_cashLoadVoidCount;
		int m_cashLoadVoidTotal;

		int m_debitLoadCount;
		int m_debitLoadTotal;
		int m_debitLoadVoidCount;
		int m_debitLoadVoidTotal;

		int m_creditLoadCount;
		int m_creditLoadTotal;
		int m_creditLoadVoidCount;
		int m_creditLoadVoidTotal;

		int m_PointUseCount;
		int m_PointUseTotal;
		int m_PointUseVoidCount;
		int m_PointUseVoidTotal;

		int m_refundCount;
		int m_refundTotal;
		int m_refundVoidCount;
		int m_refundVoidTotal;
	} SettleData, *HSettleData;

	inline HSettleData GetData() { return &this->m_data;};

protected:
	virtual int		BeforeSendForSettle();
	virtual int		BeforeSendForBatchUpload();
	virtual int		PrepF63();
	virtual int		AfterRecvBatchUpload();
	virtual int		AfterRecvSettle();
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();
	virtual int		OnAfterProcess();

	virtual int		PrintSettleReport();

private:
	typedef struct _tagSettleFieldsData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3 : proc code
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11: STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12: time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13: date, YYMM
		uchar	szNii			[LEN_NII		+ 2 ];	// F24: NII
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41: terminal id
		uchar	szMerchantID	[LEN_MERCHANT_ID+ 2 ];	// F42: merchant id
		uchar	szF43Data		[LEN_F43		+ 2	];	// F43: 
		uchar	szCurrencyCode	[LEN_CURCY_CODE	+ 2	];	// F49: CurrencyCode
		uchar	szF63Data		[LEN_FIELD63	+ 2 ];	// F63: Messages
	} SettleFiledsData;

	typedef struct _tagRecvSettleFieldsData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code // 0230
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3 : proc code
		//uchar	szTranAmt		[LEN_TRAN_AMT	+ 2 ];	// F4 : Txn Amount
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11: STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12 : time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13 : date, YYMM
		uchar	szNii			[LEN_NII		+ 2 ];	// F24: NII
		uchar	szRRN			[LEN_RRN		+ 2 ];	// F37: RRN
		uchar	szRspCode		[LEN_RSP_CODE	+ 2 ];	// F39 : rsp code
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41: terminal id
		uchar	szMerchantID	[LEN_MERCHANT_ID+ 2 ];	// F42: merchant id
		uchar	szF63			[LEN_FIELD63	+ 2 ];	// F63: Messages
	} RecvSettleFiledsData;

	typedef struct _tagBatchUploadData {
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
	} BatchUploadData;

	typedef struct _tagRecvBatchUploadData {
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
	} RecvBatchUploadData;



	BatchUploadData			m_BUElements;
	RecvBatchUploadData		m_recvBUElements;

	SettleFiledsData		m_elements;
	RecvSettleFiledsData	m_recvElements;
	char					m_buff[255];
	SettleData				m_data;
	bool					m_bBatchUpload;
	bool					m_bReconcilation;
	int						m_recNo;					// Batchupload ile gonderilmekte olan kayit no
	int						m_recCount;					// Batchupload ile gonderilecek toplam kayit sayisi (Batch kayýt sayisi)
	bool					m_bSettleOK;				// Gunsonu islemi basarili mi
	bool					m_bBatchUploadCompleted;	// Batch upload ile tum kayitlar gonderildi mi.

	unsigned char*			m_pF63Buffer;
	int						m_F63Size;

};

#endif // !defined(AFX_SETTLEENGINE_H__ED57CAB7_2CB9_4566_AFA9_5115D755043D__INCLUDED_)
