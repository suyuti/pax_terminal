#include "..\UI\MessageBox.h"
#include "VoidEngine.h"
#include "..\Files\Paramters.h"
#include "..\Files\Batch.h"
#include "..\Engine\Engine.h"
#include "..\Util\NumFuncs.h"
#include "..\Trnx\TrnxFactory.h"


//-----------------------------------------------------------------------------------------

CVoidEngine::CVoidEngine() :
	CCommEngine2((CEngine*)NULL)
{

}

//-----------------------------------------------------------------------------------------

CVoidEngine::CVoidEngine(CEngine* pEng) : 
	CCommEngine2(pEng)
{

}

//-----------------------------------------------------------------------------------------

CVoidEngine::~CVoidEngine()
{

}

//-----------------------------------------------------------------------------------------

int CVoidEngine::DoVoid(int rec)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_recNo		= rec;
	this->m_bReversal	= false;
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int CVoidEngine::DoReversal(int rec)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_recNo		= rec;
	this->m_bReversal	= true;
	return this->SendReceive();
}

//-----------------------------------------------------------------------------------------

int	CVoidEngine::OnBeforeSend()
{
	CCommEngine2::OnBeforeSend();
	
	int		ret;
	char	tmp[255]	= "";
	char	tmp2[255]	= "";
	int		pos			= 0;
	
	// kayit bulunur.
	CBatch batch;// = new CBatch();
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	batch.GotoRec(this->m_recNo, true);
	batch.Close();
	
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
	if (this->m_bReversal) {
		sprintf((char*)this->m_elements.szMsgCode, "0400"); 
	}
	else {
		//sprintf((char*)this->m_elements.szMsgCode, "%04d", hBatch->m_orgMTI); 
		sprintf((char*)this->m_elements.szMsgCode, "0200"); 
	}

	// ----- F2 : PAN
	memcpy(tmp, hBatch->m_fanData.CardNumber, sizeof(hBatch->m_fanData.CardNumber));
	tmp[sizeof(hBatch->m_fanData.CardNumber)] = 0x00;
	sprintf((char*)this->m_elements.szPan, "%s", tmp);
	
	// ----- F3 : Proc Code
	batch.GetProcessCode(tmp);
	tmp[0] = '0';
	tmp[1] = '2';  // Iptal isleminde ProcessCode'un ilk iki byte'i "02" olur.
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

	// ----- F49 : Currency Code
	Bcd2Str((unsigned char*)hTerm->m_defCurrencyCode, CTerminal::sizeDefCurrencyCode, 0, tmp);
	sprintf((char*)this->m_elements.szCurrencyCode, "%s", tmp);


	// ------ Pack
	ret = this->m_8583.Pack(C8583::GetVoidFieldAttrs(), &this->m_elements, this->m_sendBuffer + 16, (unsigned int*)&this->m_sendSize);
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

int	CVoidEngine::OnAfterRecv()
{
	CCommEngine2::OnAfterRecv();
	char tmp[32] = "";
	bool bVoided = false;

/*	char tmp2[2048] = "";
	Bcd2Str((unsigned char*)this->m_recvBuffer, this->m_recvSize, 0, tmp2);
	PRNLINE(tmp2);
*/
	int ret;
	ret = this->m_8583.Unpack(C8583::GetRecvVoidFieldAttrs(), this->m_recvBuffer + 16, this->m_recvSize - 16, &this->m_recvElements);
	if (ret < 0) {
		sprintf(tmp, "Unpack: %d", ret);
		PRNLINE(tmp);
		return UNPACK_ERROR;
	}
	this->m_responseCode	= atoi(this->m_recvElements.szRspCode);

	if (this->m_responseCode != 0) {
		this->OnResponseCodeError(this->m_responseCode);
		//return RESPONSE_CODE_ERROR;
	}
	else {
		sprintf(tmp, "Resp: %02d", this->m_responseCode);
		PRNLINE(tmp);
		bVoided = true;
	}
/*
	// batch kaydi guncellenir	
	CBatch batch;
	if (batch.Open()) {
		batch.GotoRec(this->m_recNo, true);
		batch.SetResponseCode(this->m_responseCode);
		batch.SetSent();
		batch.SetVoided();
		batch.Update();
		batch.Close();
	}
*/
	return SUCCESS;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
