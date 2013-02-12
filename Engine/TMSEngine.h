// TMSEngine.h: interface for the CTMSEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMSENGINE_H__C2773CB1_9C14_407A_A7CF_1F72F210AFCB__INCLUDED_)
#define AFX_TMSENGINE_H__C2773CB1_9C14_407A_A7CF_1F72F210AFCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"

class CEngine;
class CTMSEngine : public CCommEngine2
{
private:
	CTMSEngine();
public:
	CTMSEngine(CEngine* pEng);
	virtual ~CTMSEngine();

	int DownloadParameters();

	virtual int OnConnect();
	virtual int OnBeforeSend();
	virtual int OnAfterSend();
	virtual int OnAfterRecv();
	virtual int OnAfterProcess();

protected:
	void	MoveNewFiles(); // Indirilen yeni dosyalari eskisi ile degistirir.
	int		ProcessData();

private:
	typedef struct _tagSTTMS8583 {
		uchar	szMsgCode	[LEN_MSG_CODE	+ 2 ];	// message code // 0800
		uchar	sBitMap		[2 * LEN_BITMAP		];	//
		uchar	szProcCode	[LEN_PROC_CODE	+ 2 ];	// proc code	//begin:930000 | cont: 930001 | end: 930002
		uchar	szSTAN		[LEN_STAN		+ 2 ];	// STAN
		//uchar	szLocalTime	[LEN_LOCAL_TIME	+ 2 ];	// time, hhmmss
		//uchar	szLocalDate	[LEN_LOCAL_DATE	+ 2 ];	// date, YYMM
		uchar	szNii		[LEN_NII		+ 2 ];	// NII
		//uchar	szRspCode	[LEN_RSP_CODE	+ 2 ];	// rsp code
		uchar	szTermID	[LEN_TERM_ID	+ 2 ];	// terminal id
		uchar	szMerchantID[LEN_MERCHANT_ID+ 2 ];	// merchant id
		uchar	szF43Data	[LEN_F43		+ 2	];
		//uchar	szSerialNo	[LEN_SERIAL_NO	+ 2 ];
		//uchar	szPosVersion[LEN_POSVERSION	+ 2 ];
		//uchar	szBatchNo	[LEN_BATCHNO	+ 2 ];
		uchar	sField60	[LEN_TMSFIELD60 + 2 ];
		uchar	szField61	[LEN_FIELD61	+ 2 ];
	} STTMS8583;

	typedef struct _tagRecSTTMS8583 {
		uchar	szMsgCode	[LEN_MSG_CODE	+ 2 ];	// message code // 0800
		uchar	sBitMap		[2 * LEN_BITMAP		];	//
		uchar	szProcCode	[LEN_PROC_CODE	+ 2 ];	// proc code	//begin:930000 | cont: 930001 | end: 930002
		uchar	szSTAN		[LEN_STAN		+ 2 ];	// STAN
		//uchar	szLocalTime	[LEN_LOCAL_TIME	+ 2 ];	// time, hhmmss
		//uchar	szLocalDate	[LEN_LOCAL_DATE	+ 2 ];	// date, YYMM
		uchar	szNii		[LEN_NII		+ 2 ];	// NII
		uchar	szRspCode	[LEN_RSP_CODE	+ 2 ];	// rsp code
		uchar	szTermID	[LEN_TERM_ID	+ 2 ];	// terminal id
		uchar	sField60	[LEN_TMSFIELD60 + 2 ];
		uchar	szField61	[LEN_FIELD61	+ 2 ];
	} RecSTTMS8583;

private:
	STTMS8583		m_elements;
	RecSTTMS8583	m_recvElements;
	int				m_packetSeqNum;
	int				m_prevStan;
	bool			m_lastPacket;
};

#endif // !defined(AFX_TMSENGINE_H__C2773CB1_9C14_407A_A7CF_1F72F210AFCB__INCLUDED_)
