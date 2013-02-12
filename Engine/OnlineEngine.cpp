// OnlineEngine.cpp: implementation of the COnlineEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "OnlineEngine.h"
#include "..\Engine\Engine.h"
#include "..\Util\NumFuncs.h"
#include "..\UI\MessageBox.h"
#include "..\Files\Paramters.h"
#include "..\Files\Acquier.h"
#include "..\Files\Batch.h"
#include "..\Trnx\TrnxBase.h"

//--------------------------------------------------------------------------------

COnlineEngine::COnlineEngine() :
	CCommEngine2((CEngine*)NULL)
{
	this->m_bSaveAfterConnection = true;
	this->m_pTrnx = (CTrnxBase*)NULL;
	this->m_bFinancial = true;
}

//--------------------------------------------------------------------------------

COnlineEngine::COnlineEngine(CEngine* pEng) :
	CCommEngine2(pEng)
{
	this->m_bSaveAfterConnection = true;
	this->m_pTrnx = (CTrnxBase*)NULL;
	this->m_bFinancial = true;
}

//--------------------------------------------------------------------------------

COnlineEngine::~COnlineEngine()
{

}

//--------------------------------------------------------------------------------

int COnlineEngine::DoOnline(CTrnxBase* pTrnx)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_bReversal				= false;
	this->m_bSaveAfterConnection	= true;
	this->m_pTrnx					= pTrnx;
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int COnlineEngine::DoReversal(CTrnxBase* pTrnx)
{
//	if (pTrnx->IsSaved()) {
//		return NOT_NEED_REVERSAL;
//	}
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_bReversal				= true;
	this->m_pTrnx					= pTrnx;
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int COnlineEngine::DoOnline(int rec)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_recNo					= rec;
	this->m_bReversal				= false;
	this->m_bSaveAfterConnection	= false;
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int COnlineEngine::DoReversal(int rec)
{
	this->SetHostType(CCommEngine2::htProvizyon);
	this->m_recNo					= rec;
	this->m_bReversal				= true;
	this->m_bSaveAfterConnection	= false;
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int	COnlineEngine::OnConnect()
{
	if (this->m_bSaveAfterConnection && !this->m_bReversal) {
		PRNLINE("Baglanti kuruldu. Kayit yapilir.");
		//this->m_pTrnx->SetSent();
		this->m_pTrnx->SetReversal(true);
		this->m_recNo = this->m_pTrnx->Save();
		this->m_pTrnx->SetRecNo(this->m_recNo);
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	COnlineEngine::OnBeforeSend()
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

	if (batch.IsSent()) {
		PRNLINE("ALREADY_SENT");
		return ALREADY_SENT;
	}
	if (this->m_bReversal && !batch.IsReversed()) {
			return DOES_NOT_NEED_REVERSAL;
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
	if (this->m_bReversal) {
		sprintf((char*)this->m_elements.szMsgCode, "0400"); 
	}
	else if(this->m_bFinancial){
		sprintf((char*)this->m_elements.szMsgCode, "0200"); 
	}
	else {
		sprintf((char*)this->m_elements.szMsgCode, "0100"); 
	}

	// ----- F2 : PAN
	memcpy(tmp, hBatch->m_fanData.CardNumber, sizeof(hBatch->m_fanData.CardNumber));
	tmp[sizeof(hBatch->m_fanData.CardNumber)] = 0x00;
	sprintf((char*)this->m_elements.szPan, "%s", tmp);
	
	// ----- F3 : Proc Code
	batch.GetProcessCode((char*)this->m_elements.szProcCode);

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
	//memcpy(this->m_elements.szCurrencyCode, hTerm->m_defCurrencyCode, CTerminal::sizeDefCurrencyCode);


	// ------ Pack
	ret = this->m_8583.Pack(C8583::GetOnlineFieldAttrs(), &this->m_elements, this->m_sendBuffer + 16, (unsigned int*)&this->m_sendSize);
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

int	COnlineEngine::OnAfterRecv()
{
	CCommEngine2::OnAfterRecv();

	char tmp[32] = "";

	int ret;
	ret = this->m_8583.Unpack(C8583::GetRecvOnlineFieldAttrs(), this->m_recvBuffer + 16, this->m_recvSize - 16, &this->m_recvElements);
	if (ret < 0) {
		sprintf(tmp, "Unpack: %d", ret);
		PRNLINE(tmp);
		return UNPACK_ERROR;
	}

	//PRNBUFFER(this->m_recvElements.szF63, 100);


	this->m_responseCode	= atoi(this->m_recvElements.szRspCode);
	// F39 Host response "00" onay degil mi.
	if (this->m_responseCode != 0) {
		this->OnResponseCodeError(this->m_responseCode);
	}
	else {
		sprintf(tmp, "Resp: %02d", this->m_responseCode);
		PRNLINE(tmp);
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	COnlineEngine::OnAfterProcess()
{
/*	if (this->m_bReversal) {
		this->m_pTrnx->SetDeleted();
		this->m_pTrnx->SetReversal(true);
	}
	else {
		this->m_pTrnx->SetReversal(false);
		this->m_pTrnx->SetResponseCode(this->GetResponseCode());
	}
	this->m_pTrnx->SetSent();
	this->m_pTrnx->Update(this->m_pTrnx->GetRecNo());
*/
	return SUCCESS;
}

//--------------------------------------------------------------------------------



int	COnlineEngine::GetResponseMsgPrn(char* pBuffer, int* pSize)
{
	int f63size = 0;
	char tmp[255] = "";
	int blockSize = 0;
	int pos = 0;

	f63size = Bin2Lng(this->m_recvElements.szF63, 2);


	if (f63size <= 0) {
		*pSize = 0;
		pBuffer[0] = 0x00;
		return SUCCESS;
	}

	pos += 2;

	do {
		Bcd2Str(this->m_recvElements.szF63 + pos, 2, 0, tmp);
		blockSize = atoi(tmp);

		if (blockSize <= 0) {
			break;
		}

		pos += 2;

		tmp[0] = this->m_recvElements.szF63[pos + 0];
		tmp[1] = this->m_recvElements.szF63[pos + 1];
		tmp[2] = 0x00;

		pos += 2;

		if (strncmp(tmp, "54", 2) == 0) {
			strncpy(pBuffer, (const char*)this->m_recvElements.szF63 + pos, blockSize - 2);
			*pSize = blockSize - 2;
			//PRNLINE(pBuffer);
			break;
		}
		pos += (blockSize - 2);

		if (pos >= f63size) {
			break;
		}
	} while(true);


	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	COnlineEngine::GetResponseMsgScr(char* pBuffer, int* pSize)
{
	int f63size = 0;
	char tmp[255] = "";
	int blockSize = 0;
	int pos = 0;

	f63size = Bin2Lng(this->m_recvElements.szF63, 2);


	if (f63size <= 0) {
		*pSize = 0;
		pBuffer[0] = 0x00;
		return SUCCESS;
	}

	pos += 2;

	do {
		Bcd2Str(this->m_recvElements.szF63 + pos, 2, 0, tmp);
		blockSize = atoi(tmp);

		if (blockSize <= 0) {
			break;
		}

		pos += 2;

		tmp[0] = this->m_recvElements.szF63[pos + 0];
		tmp[1] = this->m_recvElements.szF63[pos + 1];
		tmp[2] = 0x00;

		pos += 2;

		if (strncmp(tmp, "53", 2) == 0) {
			strncpy(pBuffer, (const char*)this->m_recvElements.szF63 + pos, blockSize - 2);
			*pSize = blockSize - 2;
			break;
		}
		pos += (blockSize - 2);
		if (pos >= f63size) {
			break;
		}
	} while(true);


	return SUCCESS;
}

//--------------------------------------------------------------------------------

int	COnlineEngine::GetResponseMsgPDS20(char* pBuffer, int* pSize)
{
	int f63size = 0;
	char tmp[255] = "";
	int blockSize = 0;
	int pos = 0;

	f63size = Bin2Lng(this->m_recvElements.szF63, 2);


	if (f63size <= 0) {
		*pSize = 0;
		pBuffer[0] = 0x00;
		return SUCCESS;
	}

	pos += 2;

	do {
		Bcd2Str(this->m_recvElements.szF63 + pos, 2, 0, tmp);
		blockSize = atoi(tmp);

		if (blockSize <= 0) {
			break;
		}

		pos += 2;

		tmp[0] = this->m_recvElements.szF63[pos + 0];
		tmp[1] = this->m_recvElements.szF63[pos + 1];
		tmp[2] = 0x00;

		pos += 2;

		if (strncmp(tmp, "20", 2) == 0) {
			strncpy(pBuffer, (const char*)this->m_recvElements.szF63 + pos, blockSize - 2);
			*pSize = blockSize - 2;
			break;
		}
		pos += (blockSize - 2);
		if (pos >= f63size) {
			break;
		}
	} while(true);


	return SUCCESS;
}

//-------------------------------------------------------------------------------------------------------
//PDS 61 : 1 byte bcd [0: - ][1 : + ] balance eklenecek veya azaltýlacak
//PDS 62 : 6 byte bcd balance tutar
//PDS 63 : 1 byte bcd [0: - ][1 : + ] point eklenecek veya azaltýlacak
//PDS 64 : 6 byte bcd point tutar

int COnlineEngine::ParseF63()
{
	int		f63size		= 0;
	char	tmp[255]	= "";
	int		blockSize	= 0;
	int		pos			= 0;

	f63size = Bin2Lng(this->m_recvElements.szF63, 2);


	if (f63size <= 0) {
		return SUCCESS;
	}

	pos += 2;

	do {
		Bcd2Str(this->m_recvElements.szF63 + pos, 2, 0, tmp);
		blockSize = atoi(tmp);

		if (blockSize <= 0) {
			break;
		}
		blockSize -= 2;

		pos += 2;

		tmp[0] = this->m_recvElements.szF63[pos + 0];
		tmp[1] = this->m_recvElements.szF63[pos + 1];
		tmp[2] = 0x00;

		pos += 2;

		if (strncmp(tmp, "61", 2) == 0) {
			this->m_bLoadBalanceToCard = (this->m_recvElements.szF63[pos] == 0x01);
		}
		else if (strncmp(tmp, "62", 2) == 0) {
			PRNLINE("62");
			PRNBUFFER((unsigned char*)this->m_recvElements.szF63 + pos, blockSize);
			this->m_ScriptBalance = Bcd2Lng((unsigned char*)this->m_recvElements.szF63 + pos, blockSize);

		}
		else if (strncmp(tmp, "63", 2) == 0) {
			this->m_bLoadPointToCard = (this->m_recvElements.szF63[pos] == 0x01);
		}
		else if (strncmp(tmp, "64", 2) == 0) {
			this->m_ScriptPoint = Bcd2Lng((unsigned char*)this->m_recvElements.szF63 + pos, blockSize);
		}
		else {
			break;
		}
		pos += blockSize;

		if (pos >= f63size) {
			break;
		}
	} while(true);


	return SUCCESS;
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
