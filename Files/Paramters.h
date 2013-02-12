// Paramters.h: interface for the CParamters class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMTERS_H__A7DF9976_ED17_4535_8BF7_636ECA7B8AAB__INCLUDED_)
#define AFX_PARAMTERS_H__A7DF9976_ED17_4535_8BF7_636ECA7B8AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"



//                               1234567890123456
#define DEF_TERMINALID			"90000001"
#define DEF_MERCHANTID			"000000000000005"
#define DEF_SERIALNO			"       12345"
#define DEF_NII					"  70"
#define DEF_PRIMEDIA			"    GPRS"
#define DEF_SECMEDIA			"    DIAL"
#define DEF_SUBNET				"255.255.255.255"
#define DEF_GATEWAY				"        0.0.0.0"
#define DEF_APN					"       INTERNET"
#define DEF_SIMPIN				"0000"
#define DEF_TMSIP_1				"81.214.254.125"
#define DEF_TMSPORT_1			"5100"
#define DEF_TMSIP_2				"81.214.254.125"
#define DEF_TMSPORT_2			"5100"
#define DEF_PROVIZYONIP_1		"81.214.254.125"
#define DEF_PROVIZYONPORT_1		"5101"
#define DEF_PROVIZYONIP_2		"81.214.254.125"
#define DEF_PROVIZYONPORT_2		"5101"
#define DEF_SETTLEIP_1			"81.214.254.125"
#define DEF_SETTLEPORT_1		"5101"
#define DEF_SETTLEIP_2			"81.214.254.125"
#define DEF_SETTLEPORT_2		"5101"
#define DEF_TMSPHONENO_1		" "
#define DEF_TMSPHONENO_2		" "
#define DEF_PROVIZYONPHONENO_1	" "
#define DEF_PROVIZYONPHONENO_2	" "
#define DEF_SETTLEPHONENO_1		" "
#define DEF_SETTLEPHONENO_2		" "
#define DEF_SANTALONCEVIRME		" "
#define DEF_MODEL				"S90 "
#define DEF_POSVERSION			"000000000001"

#define TABLE_NAME_DEF_PARAMS "defParams.txt"


class CParamters : public CTable  
{
public:
	CParamters();
	virtual ~CParamters();

	typedef enum {
		sizeTerminalID	=  8,
		sizeMerchantID	= 15,
		sizeModel		=  4,
		sizeSerialNo	= 12,
		sizeNII			=  4,
		sizeMedia		=  8,
		sizeIP			= 15,
		sizePort		=  5,
		sizeApn			= 16,
		sizePIN			=  4,
		sizePhoneNo		= 11,
		sizeOnCevirme	=  5,
		sizePosVersion	= 12,
		sizeSTAN		=  6,
		sizeBatch		=  6,
	} ParameterSizes;

	typedef struct _tagParameterRec {
		char m_terminalID			[sizeTerminalID	+ 1];
		char m_merchantID			[sizeMerchantID	+ 1];
		char m_model				[sizeModel		+ 1];
		char m_serialNo				[sizeSerialNo	+ 1];
		char m_NII					[sizeNII		+ 1];
		char m_priMedia				[sizeMedia		+ 1];
		char m_secMedia				[sizeMedia		+ 1];
		char m_subnet				[sizeIP			+ 1];
		char m_gateway				[sizeIP			+ 1];
		char m_apn					[sizeApn		+ 1];
		char m_SimPIN				[sizePIN		+ 1];
		char m_TmsIP_1				[sizeIP			+ 1];
		char m_TmsPort_1			[sizePort		+ 1];
		char m_TmsIP_2				[sizeIP			+ 1];
		char m_TmsPort_2			[sizePort		+ 1];
		char m_provizyonIP_1		[sizeIP			+ 1];
		char m_provizyonPort_1		[sizePort		+ 1];
		char m_provizyonIP_2		[sizeIP			+ 1];
		char m_provizyonPort_2		[sizePort		+ 1];
		char m_settleIP_1			[sizeIP			+ 1];
		char m_settlePort_1			[sizePort		+ 1];
		char m_settleIP_2			[sizeIP			+ 1];
		char m_settlePort_2			[sizePort		+ 1];
		char m_tmsPhoneNo_1			[sizePhoneNo	+ 1];
		char m_tmsPhoneNo_2			[sizePhoneNo	+ 1];
		char m_provizyonPhoneNo_1	[sizePhoneNo	+ 1];
		char m_provizyonPhoneNo_2	[sizePhoneNo	+ 1];
		char m_settlePhoneNo_1		[sizePhoneNo	+ 1];
		char m_settlePhoneNo_2		[sizePhoneNo	+ 1];
		char m_santalOnCevirme		[sizeOnCevirme	+ 1];
		char m_posVersion			[sizePosVersion	+ 1];
		char m_stan					[sizeSTAN		+ 1];
		char m_batch				[sizeBatch		+ 1];
	} ParameterRecord, *HParameterRecord;


	void	CreateDefaults();
	inline	HParameterRecord GetData() { return &this->m_data;};
	
	virtual int Append();

	inline int	GetNextStan()			{ return atoi(this->m_data.m_stan) + 1;						};
	inline void SetNextStan(int stan)	{ sprintf(this->m_data.m_stan, "%0*d", sizeSTAN, stan);		};

	inline int	GetBatchNo()			{ return atoi(this->m_data.m_batch);						};
	inline void SetBatchNo(int batch)	{ sprintf(this->m_data.m_batch, "%0*d", sizeBatch, batch);	};

	virtual void PrintAll();
private:
	ParameterRecord m_data;
};

#endif // !defined(AFX_PARAMTERS_H__A7DF9976_ED17_4535_8BF7_636ECA7B8AAB__INCLUDED_)
