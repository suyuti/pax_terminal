// OnlineEngine.cpp: implementation of the CAdviceEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "AdviceEngine.h"
#include "..\UI\MessageBox.h"
#include "..\Files\Paramters.h"
#include "..\Files\Acquier.h"
#include "..\Engine\Engine.h"
#include "..\Util\NumFuncs.h"
#include "..\Trnx\TrnxFactory.h"

//-----------------------------------------------------------------------------------------

CAdviceEngine::CAdviceEngine() :
	CCommEngine2((CEngine*)NULL)
{
	m_maxAdviceCount = 5;
}

//-----------------------------------------------------------------------------------------

CAdviceEngine::CAdviceEngine(CEngine* pEng) :
	CCommEngine2(pEng)
{
	m_maxAdviceCount = 5;
}

//-----------------------------------------------------------------------------------------

CAdviceEngine::~CAdviceEngine()
{

}
	
//-----------------------------------------------------------------------------------------
// Batch incelenir.
// Gonderilmemis kayit numaralari m_adviceRecords dizisine alinir.
// Daha sonra SendRecv() yapilir.

int CAdviceEngine::SendFirstAdvice(int max)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_maxAdviceCount = max;

	CBatch batch;
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	int recCnt = batch.GetRecordCount();
	this->m_advRecordsCount = 0;
	for (int i = 1; i <= recCnt; ++i) {
		batch.GotoRec(i, true);
		if (batch.GetTrnxType() == CTrnxFactory::trnxIade) {
			continue;
		}
		if (!batch.IsSent()) {
			this->m_adviceRecords[this->m_advRecordsCount++] = i;
		}
		if (this->m_advRecordsCount >= this->m_maxAdviceCount) {
			break;
		}
	}
	batch.Close();

	this->m_sentAdviceCount = 0;
	if (this->m_advRecordsCount == 0) {
		return SUCCESS;
	}

	return this->SendReceive();
}
	
//-----------------------------------------------------------------------------------------

int CAdviceEngine::SendAdvice(int recNo)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	
	this->m_recNo				= recNo;
	this->m_adviceRecords[0]	= recNo;
	this->m_advRecordsCount		= 1;
	this->m_sentAdviceCount		= 0;

	int ret = this->SendReceive();
	if (ret == SUCCESS) {
		PRNLINE("SendAdvice basarili");
		CBatch batch;
		if (batch.Open()) {
			batch.GotoRec(recNo, true);
			batch.SetResponseCode(this->m_responseCode);
			batch.Update();
			batch.Close();
		}
	}
	else {
		PRNLINE("SendAdvice basarisiz");
	}
	return ret;
}

//-----------------------------------------------------------------------------------------

int CAdviceEngine::SendAdvice(CBatch::HBatchData hRec)
{
	this->SetHostType(CCommEngine2::htProvizyon);

	return this->SendReceive();
}

//-----------------------------------------------------------------------------------------

int	CAdviceEngine::OnBeforeSend()
{
	CCommEngine2::OnBeforeSend();
	int ret;
	char tmp[255] = "";
	char tmp2[255] = "";
	int pos = 0;
	
	this->m_recNo = this->m_adviceRecords[this->m_sentAdviceCount];

	// kayit bulunur.
	CBatch batch;// = new CBatch();
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	batch.GotoRec(this->m_recNo, true);
	batch.Close();
	
	CBatch::HBatchData hBatch = batch.GetData();
	if (hBatch->m_trnxType == CTrnxFactory::trnxBakiyeSorgu ||
		hBatch->m_trnxType == CTrnxFactory::trnxPuanSorgu) {
		return SUCCESS;
	}

	if (batch.IsSent()) {
		PRNLINE("ALREADY_SENT");
		return ALREADY_SENT;
	}
	if (batch.IsDeleted()) {
		return TRNX_DELETED;
	}

	CParamters params;
	if (!params.Open()) {
		PRNLINE("DEFAULT_PARAMS_NOT_OPEN");
		return DEFAULT_PARAMS_NOT_OPEN;
	}
	params.GotoRec(1, true);
	CParamters::HParameterRecord hParam = params.GetData();
	params.Close();

	CTerminal term;
	if (!term.Open()) {
		PRNLINE("TERMINAL_NOT_OPEN");
		return TERMINAL_NOT_OPEN;
	}
	term.GotoRec(1, true);
	CTerminal::HTerminalRecord hTerm = term.GetData();
	term.Close();

	// ----- MTI
	sprintf((char*)this->m_elements.szMsgCode, "0220"); 

	// ----- F2 : PAN
	memcpy(tmp, hBatch->m_fanData.CardNumber, sizeof(hBatch->m_fanData.CardNumber));
	tmp[sizeof(hBatch->m_fanData.CardNumber)] = 0x00;
	sprintf((char*)this->m_elements.szPan, "%s", tmp);
	
	// ----- F3 : Proc Code
	batch.GetProcessCode(tmp);
	sprintf((char*)this->m_elements.szProcCode, tmp);

	// ----- F4 : Amount
	sprintf((char*)this->m_elements.szTranAmt, "%d", hBatch->m_amount);

	// ----- F11 : STAN
	sprintf((char*)this->m_elements.szSTAN, "%d", batch.GetData()->m_stan);

	// ----- F12 : Time
	memcpy(tmp, hBatch->m_dateTime + 3, 3);
	Bcd2Str((unsigned char*)tmp2, 3, 0, tmp);
	sprintf((char*)this->m_elements.szLocalTime,	tmp);

	// ----- F13 : Date
	memcpy(tmp, hBatch->m_dateTime + 1, 2);
	Bcd2Str((unsigned char*)tmp2, 2, 0, tmp);
	sprintf((char*)this->m_elements.szLocalDate,	tmp);
	
	// ----- F14 : Expiry Date
	memcpy(tmp, hBatch->m_prepaidData.ExpiryDate, 4); tmp[4] = 0x00;
	sprintf((char*)this->m_elements.szExpDate,		tmp);
	
	// ----- F18 : MCC
	Bcd2Str((unsigned char*)hTerm->m_mcc, CTerminal::sizeMcc, 0, tmp);
	sprintf((char*)this->m_elements.szMcc,	"%s", tmp);
		
	// ----- F22 : POS Entry Mode
	//!
	sprintf((char*)this->m_elements.szEntryMode,	"0070");

	// ----- F24 : NII
	// acq'dan alacak
	memcpy(this->m_elements.szNii, hParam->m_NII, CParamters::sizeNII);
	this->m_elements.szNii[CParamters::sizeNII] = 0x00;

	// ----- F37 : RRN
	Bcd2Str((unsigned char*)hBatch->m_RRN, 6, 0, tmp);
	sprintf((char*)this->m_elements.szRRN,	tmp);

	// ----- F41 : Terminal ID
	memcpy(this->m_elements.szTermID, hParam->m_terminalID, CParamters::sizeTerminalID);
	this->m_elements.szTermID[CParamters::sizeTerminalID] = 0x00;
	
	// ----- F42 : Merchant ID
	memcpy(this->m_elements.szMerchantID, hParam->m_merchantID, CParamters::sizeMerchantID);
	this->m_elements.szMerchantID[CParamters::sizeMerchantID] = 0x00;

	// ----- F43
	// Model[4] + Serial[12] + Version[12] + Batch[] : toplam 40. Batch sola dayali string
	memset(this->m_elements.szF43Data, ' ', sizeof(this->m_elements.szF43Data));
	memcpy(this->m_elements.szF43Data + pos, hParam->m_model,		CParamters::sizeModel		); pos += CParamters::sizeModel;
	memcpy(this->m_elements.szF43Data + pos, hParam->m_serialNo,	CParamters::sizeSerialNo	); pos += CParamters::sizeSerialNo;
	memcpy(this->m_elements.szF43Data + pos, hParam->m_posVersion,	CParamters::sizePosVersion	); pos += CParamters::sizePosVersion;
	sprintf(tmp, "%d", atoi(hParam->m_batch));
	memcpy(this->m_elements.szF43Data + pos, tmp,	strlen(tmp)); pos += strlen(tmp);
	this->m_elements.szF43Data[40] = 0x00;
	PRNLINE(this->m_elements.szF43Data);

	// ----- F49 : Currency Code
	Bcd2Str((unsigned char*)hTerm->m_defCurrencyCode, CTerminal::sizeDefCurrencyCode, 0, tmp);
	sprintf((char*)this->m_elements.szCurrencyCode, "%s", tmp);


	// ------ Pack
	ret = this->m_8583.Pack(C8583::GetAdvFieldAttrs(), &this->m_elements, this->m_sendBuffer + 16, (unsigned int*)&this->m_sendSize);
	this->m_sendSize += 16;
	this->m_sendBuffer[7] = 0x01;				// Encrytped flag (0x01 : Not Encrypted, 0x02 : Encrypted)
	memset(&this->m_sendBuffer[8], 0x00, 8);	// Encrypted degilse 0x00 [8], encrypted ise TermID
	this->PrepTPDU();
	this->PrepLen();

/*	static char buff[2048] = "";
	Bcd2Str((unsigned char*)this->m_sendBuffer, this->m_sendSize, 0, buff);
	PRNLINE(buff);
*/

	if (ret != SUCCESS) {
		sprintf(tmp, "%d", ret);
		PRNLINE(tmp);
		return ret;
	}

	return SUCCESS;
}

//-----------------------------------------------------------------------------------------

int	CAdviceEngine::OnAfterRecv()
{
	CCommEngine2::OnAfterRecv();
	char tmp[32] = "";
/*
	char tmp2[2048] = "";
	Bcd2Str((unsigned char*)this->m_recvBuffer, this->m_recvSize, 0, tmp2);
	PRNLINE(tmp2);
*/
	int ret;
	ret = this->m_8583.Unpack(C8583::GetRecvAdvFieldAttrs(), this->m_recvBuffer + 16, this->m_recvSize - 16, &this->m_recvElements);
	if (ret < 0) {
		sprintf(tmp, "Unpack: %d", ret);
		PRNLINE(tmp);
		return UNPACK_ERROR;
	}
	this->m_responseCode	= atoi(this->m_recvElements.szRspCode);

	if (this->m_responseCode != 0) {
		this->OnResponseCodeError(this->m_responseCode);
		return RESPONSE_CODE_ERROR;
	}
	else {
		sprintf(tmp, "Resp: %02d", this->m_responseCode);
		PRNLINE(tmp);
	}

	// batch kaydi guncellenir	
	CBatch batch;
	if (batch.Open()) {
		batch.GotoRec(this->m_recNo, true);
		batch.SetResponseCode(this->m_responseCode);
		batch.SetSent();
		batch.Update();
		batch.Close();
	}

	++this->m_sentAdviceCount;
	if (this->m_sentAdviceCount >= this->m_advRecordsCount) {
		this->SetContinueSendRecv(false);
	}
	else {
		this->SetContinueSendRecv(true);
	}
	return SUCCESS;
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
