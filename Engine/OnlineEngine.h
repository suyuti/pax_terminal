// OnlineEngine.h: interface for the COnlineEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONLINEENGINE_H__EBD6F978_6FCF_4CC4_8D1B_D509A6BC3537__INCLUDED_)
#define AFX_ONLINEENGINE_H__EBD6F978_6FCF_4CC4_8D1B_D509A6BC3537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"

class CEngine;
class COnlineEngine : public CCommEngine2
{
//private:
	
public:
	COnlineEngine();
	COnlineEngine(CEngine* pEng);
	virtual ~COnlineEngine();
	
	int			DoOnline(CTrnxBase*); // islemi dosya kaydindan yapmaz. Kayit baglanti kurulup mesaj gonderildikten sonra RV olarak olusturulur.
	int			DoReversal(CTrnxBase*);
	int			DoOnline(int rec);
	int			DoReversal(int rec);
	void		SetFinancial(bool financial)	{this->m_bFinancial = financial;};
	bool		GetFinancial(void)				{return this->m_bFinancial;};
	inline int	GetScriptBalance()				{ return this->m_ScriptBalance;	};
	inline int	GetScriptPoint()				{ return this->m_ScriptPoint;		};
	inline bool	IsLoadBalanceToCard()			{ return this->m_bLoadBalanceToCard;};
	inline bool	IsLoadPointToCard()				{ return this->m_bLoadPointToCard;	};			

	// bunlar taban sinifa tasinabilir.
	int	GetResponseMsgPrn(char*, int*);
	int	GetResponseMsgScr(char*, int*);
	int GetResponseMsgPDS20(char*, int*);

protected:
	virtual int		OnConnect();
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();
	virtual int		OnAfterProcess();
	virtual int		ParseF63();

private:
	typedef struct _tagOnlineData {
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
	} OnlineData;

	typedef struct _tagRecvOnlineData {
		uchar	szMsgCode		[LEN_MSG_CODE	+ 2 ];	// message code // 0230
		uchar	sBitMap			[2 * LEN_BITMAP		];	//
		uchar	szProcCode		[LEN_PROC_CODE	+ 2 ];	// F3 : proc code
		uchar	szTranAmt		[LEN_TRAN_AMT	+ 2 ];	// F4 : Txn Amount
		uchar	szSTAN			[LEN_STAN		+ 2 ];	// F11: STAN
		uchar	szLocalTime		[LEN_LOCAL_TIME	+ 2 ];	// F12 : time, hhmmss
		uchar	szLocalDate		[LEN_LOCAL_DATE	+ 2 ];	// F13 : date, YYMM
		uchar	szNii			[LEN_NII		+ 2 ];	// F24: NII
		uchar	szRRN			[LEN_RRN		+ 2 ];	// F37: RRN
		uchar	szAUTHCODE		[LEN_AUTH_CODE	+ 2 ];	// F38: Auth Code
		uchar	szRspCode		[LEN_RSP_CODE	+ 2 ];	// F39 : rsp code
		uchar	szTermID		[LEN_TERM_ID	+ 2 ];	// F41: terminal id
		uchar	szMerchantID	[LEN_MERCHANT_ID+ 2 ];	// F42: merchant id
		uchar	szF63			[LEN_FIELD63	+ 2 ];	// F63: Messages
	} RecvOnlineData;

private:
	OnlineData			m_elements;
	RecvOnlineData		m_recvElements;
		
	int					m_recNo;				// Gonderilmekte olan kayit no
	bool				m_bReversal;
	bool				m_bFinancial;

	int					m_ScriptBalance;
	int					m_ScriptPoint;
	bool				m_bLoadBalanceToCard;
	bool				m_bLoadPointToCard;
};

#endif // !defined(AFX_ONLINEENGINE_H__EBD6F978_6FCF_4CC4_8D1B_D509A6BC3537__INCLUDED_)
