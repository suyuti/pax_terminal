// Acquier.cpp: implementation of the CAcquier class.
//
//////////////////////////////////////////////////////////////////////

#include "Acquier.h"
#include "..\Util\NumFuncs.h"

//----------------------------------------------------------------------------------

CAcquier::CAcquier() :
	CTable((void*)&m_data)
{
	this->m_recordSize = 221; //sizeof(CAcquier::AcquierRecord); // Alignment dan dolayi oluyor olabilir. Compiler ayarlarina bakilmali. sizeof() 224 veriyor.
	sprintf(this->m_fileName, "%s", TABLE_NAME_ACQUIER);
}

//----------------------------------------------------------------------------------

CAcquier::~CAcquier()
{

}

//----------------------------------------------------------------------------------

void CAcquier::CreateDefault()
{	
	memset(&this->m_data, 0x00, this->m_recordSize/*sizeof(AcquierRecord)*/);
/*
	Str2Bcd(DEF_ACQ_ACQUIRERTABLEID			, strlen(DEF_ACQ_ACQUIRERTABLEID		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_acquirerTableID		, CAcquier::sizeAcquirerTableId			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_BATCHNO					, strlen(DEF_ACQ_BATCHNO				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_batchNo				, CAcquier::sizeBatchNo					, LEFT_PAD);
	Str2Bcd(DEF_ACQ_AUTOSETTLETIME			, strlen(DEF_ACQ_AUTOSETTLETIME			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_autoSettleTime			, CAcquier::sizeAutoSettleTime			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_AUTOSETTLETRYCOUNT		, strlen(DEF_ACQ_AUTOSETTLETRYCOUNT		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_autoSettleTryCount		, CAcquier::sizeAutoSettleTryCount		, LEFT_PAD);
	Str2Bcd(DEF_ACQ_RETRYDIAL				, strlen(DEF_ACQ_RETRYDIAL				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_retryDial				, CAcquier::sizeRetryDial				, LEFT_PAD);
	Str2Bcd(DEF_ACQ_TIMEOUTDIAL				, strlen(DEF_ACQ_TIMEOUTDIAL			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_timeoutDial			, CAcquier::sizeTimeoutDial				, LEFT_PAD);
	Str2Bcd(DEF_ACQ_NII_INIT				, strlen(DEF_ACQ_NII_INIT				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_NII_Init				, CAcquier::sizeNii_Init				, LEFT_PAD);
	Str2Bcd(DEF_ACQ_NII_TRNX				, strlen(DEF_ACQ_NII_TRNX				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_NII_Trnx				, CAcquier::sizeNii_Trnx				, LEFT_PAD);
	Str2Bcd(DEF_ACQ_NII_SETTLE				, strlen(DEF_ACQ_NII_SETTLE				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_NII_Settle				, CAcquier::sizeNii_Settle				, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPHONENUMBER_INIT		, strlen(DEF_ACQ_PRIPHONENUMBER_INIT	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPhoneNumber_Init	, CAcquier::sizePriphonenumber_Init		, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPHONENUMBER_INIT		, strlen(DEF_ACQ_SECPHONENUMBER_INIT	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPhoneNumber_Init	, CAcquier::sizeSecphonenumber_Init		, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPHONENUMBER_TRNX		, strlen(DEF_ACQ_PRIPHONENUMBER_TRNX	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPhoneNumber_Trnx	, CAcquier::sizePriphonenumber_Trnx		, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPHONENUMBER_TRNX		, strlen(DEF_ACQ_SECPHONENUMBER_TRNX	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPhoneNumber_Trnx	, CAcquier::sizeSecphonenumber_Trnx		, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPHONENUMBER_SETTLE	, strlen(DEF_ACQ_PRIPHONENUMBER_SETTLE	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPhoneNumber_Settle	, CAcquier::sizePriphonenumber_Settle	, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPHONENUMBER_SETTLE	, strlen(DEF_ACQ_SECPHONENUMBER_SETTLE	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPhoneNumber_Settle	, CAcquier::sizeSecphonenumber_Settle	, LEFT_PAD);

	Str2Bcd(DEF_ACQ_PRIPORT_INIT			, strlen(DEF_ACQ_PRIPORT_INIT			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPort_Init			, CAcquier::sizePriPort_Init			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPORT_INIT			, strlen(DEF_ACQ_SECPORT_INIT			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPort_Init			, CAcquier::sizeSecPort_Init			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPORT_TRNX			, strlen(DEF_ACQ_PRIPORT_TRNX			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPort_Trnx			, CAcquier::sizePriPort_Trnx			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPORT_TRNX			, strlen(DEF_ACQ_SECPORT_TRNX			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPort_Trnx			, CAcquier::sizeSecPort_Trnx			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPORT_SETTLE			, strlen(DEF_ACQ_PRIPORT_SETTLE			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPort_Settle			, CAcquier::sizePriPort_Settle			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPORT_SETTLE			, strlen(DEF_ACQ_SECPORT_SETTLE			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPort_Settle			, CAcquier::sizeSecPort_Settle			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_PRIPORT_PROGRAM			, strlen(DEF_ACQ_PRIPORT_PROGRAM		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_priPort_Program		, CAcquier::sizePriPort_Program			, LEFT_PAD);
	Str2Bcd(DEF_ACQ_SECPORT_PROGRAM			, strlen(DEF_ACQ_SECPORT_PROGRAM		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_secPort_Program		, CAcquier::sizeSecPort_Program			, LEFT_PAD);

	Str2Bcd(DEF_ACQ_OPTIONFLAG_1			, strlen(DEF_ACQ_OPTIONFLAG_1			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_optionFlag_1			, CAcquier::sizeOptionFlag_1			, LEFT_PAD);

	strncpy(this->m_data.m_priIP_Init		, DEF_ACQ_PRIIP_INIT	, strlen(DEF_ACQ_PRIIP_INIT		));
	strncpy(this->m_data.m_secIP_Init		, DEF_ACQ_SECIP_INIT	, strlen(DEF_ACQ_SECIP_INIT		));
	strncpy(this->m_data.m_priIP_Trnx		, DEF_ACQ_PRIIP_TRNX	, strlen(DEF_ACQ_PRIIP_TRNX		));
	strncpy(this->m_data.m_secIP_Trnx		, DEF_ACQ_SECIP_TRNX	, strlen(DEF_ACQ_SECIP_TRNX		));
	strncpy(this->m_data.m_priIP_Settle		, DEF_ACQ_PRIIP_SETTLE	, strlen(DEF_ACQ_PRIIP_SETTLE	));
	strncpy(this->m_data.m_secIP_Settle		, DEF_ACQ_SECIP_SETTLE	, strlen(DEF_ACQ_SECIP_SETTLE	));
	strncpy(this->m_data.m_priIP_Program	, DEF_ACQ_PRIIP_PROGRAM	, strlen(DEF_ACQ_PRIIP_PROGRAM	));
	strncpy(this->m_data.m_secIP_Program	, DEF_ACQ_SECIP_PROGRAM	, strlen(DEF_ACQ_SECIP_PROGRAM	));
	*/
}

//----------------------------------------------------------------------------------

void CAcquier::PrintAll()
{
	char tmp[64] = "";

	PrnInit();

	for (int i = 0; i < this->m_recordCount; ++i) {
		this->GotoRec(i + 1, true);

		Bcd2Str((unsigned char*)this->m_data.m_currentBatch			, sizeCurrentBatch		, 0, tmp); PrnStr("C.Bath: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_autoSettleTime		, sizeAutoSettleTime	, 0, tmp); PrnStr("AuStTi: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_autoSettleTryCount	, sizeAutoSettleTryCount, 0, tmp); PrnStr("AuStTr: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_retryDial			, sizeRetryDial			, 0, tmp); PrnStr("RetDia: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_timeoutDial			, sizeTimeoutDial		, 0, tmp); PrnStr("TioDia: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_initNII				, sizeInitNII			, 0, tmp); PrnStr("IniNII: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_txnNII				, sizeTxnNII			, 0, tmp); PrnStr("TxnNII: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_settleNII			, sizeSettleNII			, 0, tmp); PrnStr("SetNII: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_progNII				, sizeProgNII			, 0, tmp); PrnStr("PrgNII: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_initPriPhone			, sizeInitPriPhone		, 0, tmp); PrnStr("InPho1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_initSecPhone			, sizeInitSecPhone		, 0, tmp); PrnStr("InPho2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_txnPriPhone			, sizeTxnPriPhone		, 0, tmp); PrnStr("TxPho1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_txnSecPhone			, sizeTxnSecPhone		, 0, tmp); PrnStr("TxPho2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_settlePriPhone		, sizeSettlePriPhone	, 0, tmp); PrnStr("StPho1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_settleSecPhone		, sizeSettleSecPhone	, 0, tmp); PrnStr("StPho2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_progPriPhone			, sizeProgPriPhone		, 0, tmp); PrnStr("PrPho1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_progSecPhone			, sizeProgSecPhone		, 0, tmp); PrnStr("PrPho2: %s\n", tmp);

		memcpy(tmp, this->m_data.m_initPriIP 		, sizeInitPriIP 	); tmp[sizeInitPriIP 		] = 0x00; PrnStr("IniIP1: %s\n", tmp);


		Bcd2Str((unsigned char*)this->m_data.m_initPriPort 	, sizeInitPriPort,		0, tmp);						PrnStr("InPrt1: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_initSecIP 	, sizeInitSecIP);		tmp[sizeInitSecIP] = 0x00;		PrnStr("IniIP2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_initSecPort 	, sizeInitSecPort,		0,tmp);							PrnStr("InPrt2: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_txnPriIP 	, sizeTxnPriIP );		tmp[sizeTxnPriIP ] = 0x00;		PrnStr("TxnIP1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_txnPriPort 	, sizeTxnPriPort,		0, tmp);						PrnStr("TxPrt1: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_txnSecIP 	, sizeTxnSecIP );		tmp[sizeTxnSecIP] = 0x00;		PrnStr("TxnIP2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_txnSecPort 	, sizeTxnSecPort,		0, tmp);						PrnStr("TxPrt2: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_settlePriIP 	, sizeSettlePriIP);		tmp[sizeSettlePriIP] = 0x00;	PrnStr("StlIP1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_settlePriPort, sizeSettlePriPort,	0, tmp);						PrnStr("StPrt1: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_settleSecIP 	, sizeSettleSecIP 	);	tmp[sizeSettleSecIP] = 0x00;	PrnStr("StlIP2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_settleSecPort, sizeSettleSecPort,	0, tmp);						PrnStr("StPrt2: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_progPriIP 	, sizeProgPriIP 	);	tmp[sizeProgPriIP ] = 0x00;		PrnStr("PrgIP1: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_progPriPort 	, sizeProgPriPort,		0, tmp);						PrnStr("PrPrt1: %s\n", tmp);
		memcpy(tmp,				this->m_data.m_progSecIP 	, sizeProgSecIP 	);	tmp[sizeProgSecIP]	= 0x00;		PrnStr("PrgIP2: %s\n", tmp);
		Bcd2Str((unsigned char*)this->m_data.m_progSecPort	, sizeProgSecPort,		0, tmp);						PrnStr("PrPrt2: %s\n", tmp);

	}
	PrnStart();

}

//----------------------------------------------------------------------------------
int CAcquier::Append()
{
	if (!this->Open()) {
		return GENERAL_FAILURE;//FILE_NOT_OPENED;
	}
	this->m_currentRecordNo = this->GotoEnd();
	this->Write((void *)&this->m_data, this->m_recordSize);

	this->Close();

	++this->m_currentRecordNo;
	++this->m_recordCount;
	return this->m_currentRecordNo;
}

//----------------------------------------------------------------------------------

int	CAcquier::GetBatchNo()
{
	return (int)Bcd2Lng((unsigned char*)this->m_data.m_currentBatch, sizeCurrentBatch);
}

//----------------------------------------------------------------------------------

void CAcquier::SetBatchNo(int batch)
{
	Lng2Bcd(batch, (unsigned char*)this->m_data.m_currentBatch, sizeCurrentBatch);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
