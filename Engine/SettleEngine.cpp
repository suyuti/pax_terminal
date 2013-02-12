// SettleEngine.cpp: implementation of the CSettleEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "SettleEngine.h"
#include "..\Engine\Engine.h"
#include "..\Util\NumFuncs.h"
#include "..\UI\MessageBox.h"
#include "..\Files\Batch.h"
#include "..\Files\Paramters.h"
#include "..\Files\SettleReport.h"
#include "..\Util\NumFuncs.h"

//--------------------------------------------------------------------------------

CSettleEngine::CSettleEngine() :
	CCommEngine2((CEngine*)NULL)
{
	this->m_pF63Buffer = (unsigned char*)NULL;
}

//--------------------------------------------------------------------------------

CSettleEngine::CSettleEngine(CEngine* pEng) : 
	CCommEngine2(pEng)
{
	this->m_bBatchUpload	= false;
	this->m_bReconcilation	= false;
	this->m_pF63Buffer = (unsigned char*)NULL;
}

//--------------------------------------------------------------------------------

CSettleEngine::~CSettleEngine()
{
	if (this->m_pF63Buffer != NULL) {
		delete this->m_pF63Buffer;
		this->m_pF63Buffer = (unsigned char*)NULL;
	}
}

//--------------------------------------------------------------------------------

int CSettleEngine::DoSettle()
{
	CMessageBox mb("Günsonu\nyapilacak.\nEmin misiniz?", MB_YES_NO);
	mb.Draw();
	if (mb.GetSelect() != CHOICE_YES) {
		return USER_CANCELLED;
	}

	this->SetHostType(CCommEngine2::htSettlement);
	this->CalcSettle();
	this->m_bBatchUpload			= false;
	this->m_bReconcilation			= false;
	this->m_recNo					= 1;
	this->m_bSettleOK				= false;
	this->m_bBatchUploadCompleted	= false;
	CBatch batch;
	if (batch.Open()) {
		this->m_recCount = batch.GetRecordCount();
		batch.Close();
	}
	return this->SendReceive();
}

//--------------------------------------------------------------------------------
#define F63_BUFFER_SIZE 255
int CSettleEngine::PrepF63()
{
	this->m_pF63Buffer = new unsigned char[F63_BUFFER_SIZE];
	memset(this->m_pF63Buffer, 0x00, F63_BUFFER_SIZE);
	int rec = 0;

	// 30 Sale
	// 31 Cash Load
	// 32 Credit Load
	// 33 Debit Load
	// 34 Poing Usage
	// 35 Refund
#define LEN 2

	//Islem + Void Len = 16 + 2 TagLen = 18, Len BCD olarak 0x18 isteniyor.
	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '0';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN] = 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN] = 0x18;
	Lng2Bcd(this->m_data.m_saleCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_saleTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	Lng2Bcd(this->m_data.m_saleVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_saleVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);

	++rec;
	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '1';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN]	= 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN]	= 0x18;

	Lng2Bcd(this->m_data.m_cashLoadCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_cashLoadTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	Lng2Bcd(this->m_data.m_cashLoadVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_cashLoadVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);
	++rec;

	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '2';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN]	= 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN]	= 0x18;

	Lng2Bcd(this->m_data.m_creditLoadCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_creditLoadTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	Lng2Bcd(this->m_data.m_creditLoadVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_creditLoadVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);
	++rec;

	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '3';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN]	= 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN]	= 0x18;

	Lng2Bcd(this->m_data.m_debitLoadCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_debitLoadTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	Lng2Bcd(this->m_data.m_debitLoadVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_debitLoadVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);
	++rec;

	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '4';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN]	= 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN]	= 0x18;

	Lng2Bcd(this->m_data.m_PointUseCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_PointUseTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	Lng2Bcd(this->m_data.m_PointUseVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_PointUseVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);
	++rec;

	this->m_pF63Buffer[(rec * 20) + LEN]		= '3';
	this->m_pF63Buffer[(rec * 20) + 1 + LEN]	= '5';
	this->m_pF63Buffer[(rec * 20) + 2 + LEN]	= 0x00;
	this->m_pF63Buffer[(rec * 20) + 3 + LEN]	= 0x10;

	Lng2Bcd(this->m_data.m_refundCount,		&this->m_pF63Buffer[(rec * 20) +  2 + LEN + 2], 2);
	Lng2Bcd(this->m_data.m_refundTotal,		&this->m_pF63Buffer[(rec * 20) +  4 + LEN + 2], 6);
	//Lng2Bcd(this->m_data.m_refundVoidCount,	&this->m_pF63Buffer[(rec * 20) + 10 + LEN + 2], 2);
	//Lng2Bcd(this->m_data.m_refundVoidTotal,	&this->m_pF63Buffer[(rec * 20) + 12 + LEN + 2], 6);
	++rec;

	this->m_F63Size = (rec * 20) + LEN;
	if (LEN > 0) {
		Lng2Bcd(this->m_F63Size, this->m_pF63Buffer, LEN);
	}
	return this->m_F63Size;
}

//--------------------------------------------------------------------------------

int CSettleEngine::BeforeSendForSettle()
{
	int ret;
	char tmp[255] = "";
	int pos = 0;

	this->PrepF63();

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
	sprintf((char*)this->m_elements.szMsgCode, "0500"); 
	
	// ----- F3 : Proc Code
	if (this->m_bReconcilation) {
		sprintf((char*)this->m_elements.szProcCode, "910000");
	}
	else {
		sprintf((char*)this->m_elements.szProcCode, "920000");
	}

	// ----- F11 : STAN
	sprintf((char*)this->m_elements.szSTAN, "%d", params.GetNextStan());

	// ----- F12 : Time
	sprintf((char*)this->m_elements.szLocalTime,	"123456");

	// ----- F13 : Date
	sprintf((char*)this->m_elements.szLocalDate,	"1234");
	
	// ----- F24 : NII
	// acq'dan alacak
	memcpy(this->m_elements.szNii, hParam->m_NII, CParamters::sizeNII);
	this->m_elements.szNii[CParamters::sizeNII] = 0x00;

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

	// ----- F49 : Currency Code
	Bcd2Str((unsigned char*)hTerm->m_defCurrencyCode, CTerminal::sizeDefCurrencyCode, 0, tmp);
	sprintf((char*)this->m_elements.szCurrencyCode, "%s", tmp);

	// ----- F63
	memcpy(this->m_elements.szF63Data, this->m_pF63Buffer, this->m_F63Size);


	// ------ Pack
	ret = this->m_8583.Pack(C8583::GetSettleFieldAttrs(), &this->m_elements, this->m_sendBuffer + 16, (unsigned int*)&this->m_sendSize);
	this->m_sendSize += 16;
	this->m_sendBuffer[7] = 0x01;				// Encrytped flag (0x01 : Not Encrypted, 0x02 : Encrypted)
	memset(&this->m_sendBuffer[8], 0x00, 8);	// Encrypted degilse 0x00 [8], encrypted ise TermID
	this->PrepTPDU();
	this->PrepLen();

//	Gunsonunda gonderilen buffer asagidaki sekilde yazilabilir.
//	PRNBUFFER(this->m_sendBuffer, this->m_sendSize);


	if (ret != SUCCESS) {
		sprintf(tmp, "%d", ret);
		PRNLINE(tmp);
		return ret;
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------

int CSettleEngine::BeforeSendForBatchUpload()
{
	int ret;
	char tmp[255] = "";
	int pos = 0;
	
	// kayit bulunur.
	CBatch batch;
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	batch.GotoRec(this->m_recNo, true);
	batch.Close();

	if (batch.IsDeleted() || batch.IsReversed()) {
		if (this->m_recNo < this->m_recCount) {
			++this->m_recNo;
		}
		return CONTINUE;
	}
	
	CBatch::HBatchData hBatch = batch.GetData();

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
	sprintf((char*)this->m_BUElements.szMsgCode, "0320"); 

	// ----- F2 : PAN
	memcpy(tmp, hBatch->m_fanData.CardNumber, sizeof(hBatch->m_fanData.CardNumber));
	tmp[sizeof(hBatch->m_fanData.CardNumber)] = 0x00;
	sprintf((char*)this->m_BUElements.szPan, "%s", tmp);
	
	// ----- F3 : Proc Code
	sprintf((char*)this->m_BUElements.szProcCode, "000000");

	// ----- F4 : Amount
	sprintf((char*)this->m_BUElements.szTranAmt, "%d", hBatch->m_amount);

	// ----- F11 : STAN
	sprintf((char*)this->m_BUElements.szSTAN, "%d", batch.GetData()->m_stan);

	// ----- F12 : Time
	sprintf((char*)this->m_BUElements.szLocalTime,	"123456");

	// ----- F13 : Date
	sprintf((char*)this->m_BUElements.szLocalDate,	"1234");
	
	// ----- F14 : Expiry Date
	sprintf((char*)this->m_BUElements.szExpDate,		"7890");
	
	// ----- F18 : MCC
	Bcd2Str((unsigned char*)hTerm->m_mcc, CTerminal::sizeMcc, 0, tmp);
	sprintf((char*)this->m_BUElements.szMcc,	"%s", tmp);
		
	// ----- F22 : POS Entry Mode
	//!
	sprintf((char*)this->m_BUElements.szEntryMode,	"0070");

	// ----- F24 : NII
	// acq'dan alacak
	memcpy(this->m_elements.szNii, hParam->m_NII, CParamters::sizeNII);
	this->m_BUElements.szNii[CParamters::sizeNII] = 0x00;

	// ----- F37 : RRN
	sprintf((char*)this->m_BUElements.szRRN,			"98765");


	// ----- F41 : Terminal ID
	memcpy(this->m_BUElements.szTermID, hParam->m_terminalID, CParamters::sizeTerminalID);
	this->m_BUElements.szTermID[CParamters::sizeTerminalID] = 0x00;
	
	// ----- F42 : Merchant ID
	memcpy(this->m_BUElements.szMerchantID, hParam->m_merchantID, CParamters::sizeMerchantID);
	this->m_BUElements.szMerchantID[CParamters::sizeMerchantID] = 0x00;

	// ----- F43
	// Model[4] + Serial[12] + Version[12] + Batch[] : toplam 40. Batch sola dayali string
	memset(this->m_BUElements.szF43Data, ' ', sizeof(this->m_elements.szF43Data));
	memcpy(this->m_BUElements.szF43Data + pos, hParam->m_model,		CParamters::sizeModel		); pos += CParamters::sizeModel;
	memcpy(this->m_BUElements.szF43Data + pos, hParam->m_serialNo,	CParamters::sizeSerialNo	); pos += CParamters::sizeSerialNo;
	memcpy(this->m_BUElements.szF43Data + pos, hParam->m_posVersion,	CParamters::sizePosVersion	); pos += CParamters::sizePosVersion;
	sprintf(tmp, "%d", atoi(hParam->m_batch));
	memcpy(this->m_BUElements.szF43Data + pos, tmp,	strlen(tmp)); pos += strlen(tmp);
	this->m_BUElements.szF43Data[40] = 0x00;

	// ----- F49 : Currency Code
	Bcd2Str((unsigned char*)hTerm->m_defCurrencyCode, CTerminal::sizeDefCurrencyCode, 0, tmp);
	sprintf((char*)this->m_BUElements.szCurrencyCode, "%s", tmp);

	// ------ Pack
	ret = this->m_8583.Pack(C8583::GetAdvFieldAttrs(), &this->m_BUElements, this->m_sendBuffer + 16, (unsigned int*)&this->m_sendSize);
	this->m_sendSize += 16;
	this->m_sendBuffer[7] = 0x01;				// Encrytped flag (0x01 : Not Encrypted, 0x02 : Encrypted)
	memset(&this->m_sendBuffer[8], 0x00, 8);	// Encrypted degilse 0x00 [8], encrypted ise TermID
	this->PrepTPDU();
	this->PrepLen();

	if (ret != SUCCESS) {
		sprintf(tmp, "%d", ret);
		PRNLINE(tmp);
		return ret;
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	CSettleEngine::OnBeforeSend()
{
	int retVal;
	CCommEngine2::OnBeforeSend();
	if (this->m_bBatchUpload) {
		if (this->m_bBatchUploadCompleted) {
			this->m_bReconcilation = true;
			retVal = this->BeforeSendForSettle();
		}
		else {
			retVal = this->BeforeSendForBatchUpload();
		}
	}
	else {
		retVal = this->BeforeSendForSettle();
	}
	return retVal;
}

//--------------------------------------------------------------------------------

int CSettleEngine::AfterRecvBatchUpload()
{
	char tmp[64] = "";
	int ret;
	ret = this->m_8583.Unpack(C8583::GetRecvAdvFieldAttrs(), this->m_recvBuffer + 16, this->m_recvSize - 16, &this->m_recvBUElements);
	if (ret < 0) {
		sprintf(tmp, "Unpack: %d", ret);
		PRNLINE(tmp);
		return UNPACK_ERROR;
	}
	this->m_responseCode	= atoi(this->m_recvBUElements.szRspCode);

	if (this->m_responseCode != 0) {
		this->OnResponseCodeError(this->m_responseCode);
		this->SetContinueSendRecv(false);
		return RESPONSE_CODE_ERROR;
	}
	else {
		sprintf(tmp, "Resp: %02d", this->m_responseCode);
		PRNLINE(tmp);
		if (this->m_recNo >= this->m_recCount) {
			this->m_bBatchUploadCompleted = true;
		}
		else {
			++this->m_recNo;
		}
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------

int CSettleEngine::AfterRecvSettle()
{
	char tmp[32];
	int ret;
	ret = this->m_8583.Unpack(C8583::GetRecvSettleFieldAttrs(), this->m_recvBuffer + 16, this->m_recvSize - 16, &this->m_recvElements);
	if (ret < 0) {
		sprintf(tmp, "Unpack: %d", ret);
		PRNLINE(tmp);
		return UNPACK_ERROR;
	}
	this->m_responseCode = atoi(this->m_recvElements.szRspCode);

	if (this->m_responseCode != 0) {
		PrnStr("%s\n", this->m_recvElements.szRspCode);
		PrnStart();
		this->OnResponseCodeError(this->m_responseCode);
		if (this->m_responseCode == 95 && this->m_bBatchUpload == false) {
			this->m_bBatchUpload = true;
			this->SetContinueSendRecv(true);
			return SUCCESS;
		}
		return RESPONSE_CODE_ERROR;
	}
	else {
		this->m_bSettleOK = true;
		sprintf(tmp, "Resp: %02d", this->m_responseCode);
		PRNLINE(tmp);
		this->SetContinueSendRecv(false);
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	CSettleEngine::OnAfterRecv()
{
	CCommEngine2::OnAfterRecv();

	if (this->m_bBatchUpload) {
		if (this->m_bReconcilation) {
			return this->AfterRecvSettle();
		}
		else {
			return this->AfterRecvBatchUpload();
		}
	}
	else {
		return this->AfterRecvSettle();
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	CSettleEngine::OnAfterProcess()
{	
	remove((char *)TABLE_NAME_BATCH);
	int fp = open(TABLE_NAME_BATCH, O_CREATE|O_RDWR);
	close(fp);

	int currBatch = 0;
	CAcquier acq;
	if (acq.Open()) {
		acq.GotoRec(1, true);
		currBatch = acq.GetBatchNo() + 1;
		acq.SetBatchNo(currBatch);
		acq.Update();
		acq.Close();
	}

	CParamters param;
	if (param.Open()) {
		param.GotoRec(1, true);
		param.SetBatchNo(currBatch);
		param.Update();
		param.Close();
	}

	//todo gunsonundan sonra rapor yazdir.
	CSettleReport pReport;
	pReport.SetData(&this->m_data);
	pReport.Append();
	pReport.PrintAll();

	return SUCCESS;
}

//--------------------------------------------------------------------------------
	
int CSettleEngine::CalcSettle()
{
	PRNLINE("CalcSettle...");
	memset(&this->m_data, 0x00, sizeof(CSettleEngine::SettleData));
	CBatch batch;
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	int recCount = batch.GetRecordCount();
	for (int i = 1; i <= recCount; ++i) {
		batch.GotoRec(i, true);

		if (batch.IsDeleted() || batch.IsReversed()) {
			continue;
		}
		if (batch.GetResponseCode() != 0) {
			continue;
		}

		switch(batch.GetTrnxType()) {
			case CTrnxFactory::trnxHarcama: 
				if (batch.IsVoided()) {
					++this->m_data.m_saleVoidCount;
					this->m_data.m_saleVoidTotal += batch.GetAmount();
				}
				else {
					++this->m_data.m_saleCount;
					this->m_data.m_saleTotal += batch.GetAmount();
				}
			break;
			case CTrnxFactory::trnxBakiyeSorgu: 
			break;
			case CTrnxFactory::trnxNakitYukleme: 
				if (batch.IsVoided()) {
					++this->m_data.m_cashLoadVoidCount;
					this->m_data.m_cashLoadVoidTotal += batch.GetAmount();
				}
				else {
					++this->m_data.m_cashLoadCount;
					this->m_data.m_cashLoadTotal += batch.GetAmount();
				}
			break;
			case CTrnxFactory::trnxKrediKartYukleme:
				if (batch.IsVoided()) {
					++this->m_data.m_creditLoadVoidCount;
					this->m_data.m_creditLoadVoidTotal += batch.GetAmount();
				}
				else {
					++this->m_data.m_creditLoadCount;
					this->m_data.m_creditLoadTotal += batch.GetAmount();
				}
			break;
			case CTrnxFactory::trnxDebitYukleme:
				if (batch.IsVoided()) {
					++this->m_data.m_debitLoadVoidCount;
					this->m_data.m_debitLoadVoidTotal += batch.GetAmount();
				}
				else {
					++this->m_data.m_debitLoadCount;
					this->m_data.m_debitLoadTotal += batch.GetAmount();
				}
			break;
			case CTrnxFactory::trnxPuanKullanma: 
				if (batch.IsVoided()) {
					++this->m_data.m_PointUseVoidCount;
					this->m_data.m_PointUseVoidTotal += batch.GetAmount();
				}
				else {
					++this->m_data.m_PointUseCount;
					this->m_data.m_PointUseTotal += batch.GetAmount();
				}
			break;
			case CTrnxFactory::trnxPuanSorgu: 
			break;
			case CTrnxFactory::trnxKartGuncelle: 
			break;
			case CTrnxFactory::trnxIade:
				++this->m_data.m_refundCount;
				this->m_data.m_refundTotal += batch.GetAmount();
			break;
		}
	}
	batch.Close();
	return SUCCESS;
}

//--------------------------------------------------------------------------------
int	CSettleEngine::PrintSettleReport()
{

	return SUCCESS;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
