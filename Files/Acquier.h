// Acquier.h: interface for the CAcquier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACQUIER_H__5F62D8E8_0C75_443C_8DB8_FDF0E3C3D49E__INCLUDED_)
#define AFX_ACQUIER_H__5F62D8E8_0C75_443C_8DB8_FDF0E3C3D49E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

//                                       12345678901234567890
#define DEF_ACQ_ACQUIRERTABLEID			"000000"
#define DEF_ACQ_BATCHNO					"000001"
#define DEF_ACQ_AUTOSETTLETIME			"2359"
#define DEF_ACQ_AUTOSETTLETRYCOUNT		"03"
#define DEF_ACQ_RETRYDIAL				"02"
#define DEF_ACQ_TIMEOUTDIAL				"0010"
#define DEF_ACQ_NII_INIT				"0070"
#define DEF_ACQ_NII_TRNX				"0070"
#define DEF_ACQ_NII_SETTLE				"0070"
#define DEF_ACQ_PRIPHONENUMBER_INIT		"0000005322655137"
#define DEF_ACQ_SECPHONENUMBER_INIT		"0000005322655137"
#define DEF_ACQ_PRIPHONENUMBER_TRNX		"0000005322655137"
#define DEF_ACQ_SECPHONENUMBER_TRNX		"0000005322655137"
#define DEF_ACQ_PRIPHONENUMBER_SETTLE	"0000005322655137"
#define DEF_ACQ_SECPHONENUMBER_SETTLE	"0000005322655137"
#define DEF_ACQ_OPTIONFLAG_1			"00"
#define DEF_ACQ_PRIPORT_INIT			"5001"
#define DEF_ACQ_SECPORT_INIT			"5002"
#define DEF_ACQ_PRIPORT_TRNX			"5001"
#define DEF_ACQ_SECPORT_TRNX			"5002"
#define DEF_ACQ_PRIPORT_SETTLE			"5001"
#define DEF_ACQ_SECPORT_SETTLE			"5002"
#define DEF_ACQ_PRIPORT_PROGRAM			"5001"
#define DEF_ACQ_SECPORT_PROGRAM			"5002"

#define DEF_ACQ_PRIIP_INIT				"    192.168.1.1"
#define DEF_ACQ_SECIP_INIT				"    192.168.1.1"
#define DEF_ACQ_PRIIP_TRNX				"    192.168.1.1"
#define DEF_ACQ_SECIP_TRNX				"    192.168.1.1"
#define DEF_ACQ_PRIIP_SETTLE			"    192.168.1.1"
#define DEF_ACQ_SECIP_SETTLE			"    192.168.1.1"
#define DEF_ACQ_PRIIP_PROGRAM			"    192.168.1.1"
#define DEF_ACQ_SECIP_PROGRAM			"    192.168.1.1"


#define TABLE_NAME_ACQUIER "acquier.txt"

/*
Currenct Batch Number	nP 6	
Auto Settle Time	nP 4	HHMM
Auto Settle Try Count	nP 2	
Retry Dial	nP 2	
Timeout Dial	nP 4	Unit is Second
Init NII	nP 4	
Txn NII	nP 4	
Settle NII	nP 4	
Program NII	nP 4	
Init Primary Phone Number	anP 16	Right Padded (‘F’)
Init Secondary Phone Number	anP 16	Right Padded (‘F’)
Txn Primary Phone Number	anP 16	Right Padded (‘F’)
Txn Secondary Phone Number	anP 16	Right Padded (‘F’)
Settle Primary Phone Number	anP 16	Right Padded (‘F’)
Settle Secondary Phone Number	anP 16	Right Padded (‘F’)
Program Primary Phone Number	anP 16	Right Padded (‘F’)
Program Secondary Phone Number	anP 16	Right Padded (‘F’)
Init Primary IP Address	an 15 	Sample : “192.168.002.010”
Init Primary Port Number	nP 4	
Init Secondary IP Address	an 15	
Init Secondary Port Number	nP 4	
Txn Primary IP Address	an 15 	
Txn Primary Port Number	nP 4	
Txn Secondary IP Address	an 15	
Txn Secondary Port Number	nP 4	
Settle Primary IP Address	an 15 	
Settle Primary Port Number	nP 4	
Settle Secondary IP Address	an 15	
Settle Secondary Port Number	nP 4	
Program Primary IP Address	an 15 	POS program load center IP Address
Program Primary Port Number	nP 4	
Program Secondary IP Address	an 15	
Program Secondary Port Number	nP 4	
Acquirer Option Byte 1	b 8	RFU

*/


class CAcquier : public CTable  
{
public:
	CAcquier();
	virtual ~CAcquier();

	typedef enum {
		sizeAcquirerTableId		=  3,
		sizeCurrentBatch		=  3,	
		sizeAutoSettleTime		=  2,
		sizeAutoSettleTryCount	=  1,	
		sizeRetryDial			=  1,	
		sizeTimeoutDial			=  2,
		sizeInitNII				=  2,	
		sizeTxnNII				=  2,	
		sizeSettleNII			=  2,	
		sizeProgNII				=  2,	
		sizeInitPriPhone		=  8,
		sizeInitSecPhone		=  8,
		sizeTxnPriPhone			=  8,
		sizeTxnSecPhone			=  8,
		sizeSettlePriPhone		=  8,
		sizeSettleSecPhone		=  8,
		sizeProgPriPhone		=  8,
		sizeProgSecPhone		=  8,
		sizeInitPriIP 			= 15,
		sizeInitPriPort 		=  2,	
		sizeInitSecIP 			= 15,	
		sizeInitSecPort 		=  2,	
		sizeTxnPriIP 			= 15, 	
		sizeTxnPriPort 			=  2,	
		sizeTxnSecIP 			= 15,	
		sizeTxnSecPort 			=  2,	
		sizeSettlePriIP 		= 15, 	
		sizeSettlePriPort 		=  2,	
		sizeSettleSecIP 		= 15,	
		sizeSettleSecPort 		=  2,	
		sizeProgPriIP 			= 15,
		sizeProgPriPort 		=  2,	
		sizeProgSecIP 			= 15,	
		sizeProgSecPort			=  2,	
		sizeAcqOptionByte1		=  1,
	} AcquierSizes;

	typedef struct _tagAcquier {
		char m_acquierTableID		[sizeAcquirerTableId	];
		char m_currentBatch			[sizeCurrentBatch		];// BCD 
		char m_autoSettleTime		[sizeAutoSettleTime		];// BCD 4	HHMM
		char m_autoSettleTryCount	[sizeAutoSettleTryCount	];// BCD 2	
		char m_retryDial			[sizeRetryDial			];// BCD 2	
		char m_timeoutDial			[sizeTimeoutDial		];// BCD 4	Unit is Second
		char m_initNII				[sizeInitNII			];// BCD 4	
		char m_txnNII				[sizeTxnNII				];// BCD 4	
		char m_settleNII			[sizeSettleNII			];// BCD 4	
		char m_progNII				[sizeProgNII			];// BCD 4	
		char m_initPriPhone			[sizeInitPriPhone		];// STR 16	Right Padded (‘F’)
		char m_initSecPhone			[sizeInitSecPhone		];// STR 16	Right Padded (‘F’)
		char m_txnPriPhone			[sizeTxnPriPhone		];// STR 16	Right Padded (‘F’)
		char m_txnSecPhone			[sizeTxnSecPhone		];// STR 16	Right Padded (‘F’)
		char m_settlePriPhone		[sizeSettlePriPhone		];// STR 16	Right Padded (‘F’)
		char m_settleSecPhone		[sizeSettleSecPhone		];// STR 16	Right Padded (‘F’)
		char m_progPriPhone			[sizeProgPriPhone		];// STR 16	Right Padded (‘F’)
		char m_progSecPhone			[sizeProgSecPhone		];// STR 16	Right Padded (‘F’)
		char m_initPriIP 			[sizeInitPriIP 			];// STR 15 	Sample : “192.168.002.010”
		char m_initPriPort 			[sizeInitPriPort 		];// BCD 4	
		char m_initSecIP 			[sizeInitSecIP 			];// STR 15	
		char m_initSecPort 			[sizeInitSecPort 		];// BCD 4	
		char m_txnPriIP 			[sizeTxnPriIP 			];// STR 15 	
		char m_txnPriPort 			[sizeTxnPriPort 		];// BCD 4	
		char m_txnSecIP 			[sizeTxnSecIP 			];// STR 15	
		char m_txnSecPort 			[sizeTxnSecPort 		];// BCD 4	
		char m_settlePriIP 			[sizeSettlePriIP 		];// STR 15 	
		char m_settlePriPort 		[sizeSettlePriPort 		];// BCD 4	
		char m_settleSecIP 			[sizeSettleSecIP 		];// STR 15	
		char m_settleSecPort 		[sizeSettleSecPort 		];// BCD 4	
		char m_progPriIP 			[sizeProgPriIP 			];// STR 15 	POS Prog load center IP 
		char m_progPriPort 			[sizeProgPriPort 		];// BCD 4	
		char m_progSecIP 			[sizeProgSecIP 			];// STR 15	
		char m_progSecPort			[sizeProgSecPort		];// BCD 4	
		char m_acqOptionByte1		[sizeAcqOptionByte1		];// RFU
	} AcquierRecord, *HAcquierRecord;

	inline	HAcquierRecord GetData() { return &this->m_data;};

	int		GetBatchNo();
	void	SetBatchNo(int batch);

	virtual int Append();
	void CreateDefault();
	virtual void PrintAll();
private:
	AcquierRecord m_data;
};

#endif // !defined(AFX_ACQUIER_H__5F62D8E8_0C75_443C_8DB8_FDF0E3C3D49E__INCLUDED_)
