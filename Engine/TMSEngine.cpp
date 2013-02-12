// TMSEngine.cpp: implementation of the CTMSEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "TMSEngine.h"
#include "..\UI\MessageBox.h"
#include "..\Files\Paramters.h"
#include "..\Engine\Engine.h"
#include "..\Util\NumFuncs.h"


#define GET_PARAM_PROCESSING_CODE_BEGIN "930000"
#define GET_PARAM_PROCESSING_CODE_CONT	"930001"
#define GET_PARAM_PROCESSING_CODE_END	"930002"


//--------------------------------------------------------------------------------

CTMSEngine::CTMSEngine() : 
	CCommEngine2((CEngine*)NULL)
{

}

//--------------------------------------------------------------------------------

CTMSEngine::CTMSEngine(CEngine* pEng) :
	CCommEngine2(pEng)
{

}

//--------------------------------------------------------------------------------

CTMSEngine::~CTMSEngine()
{

}

//--------------------------------------------------------------------------------

int CTMSEngine::DownloadParameters()
{
	this->SetHostType(CCommEngine2::htTMS);
	return this->SendReceive();
}

//--------------------------------------------------------------------------------

int CTMSEngine::OnConnect()
{ 
	remove(TABLE_NAME_TERMINAL ".tmp");
	remove(TABLE_NAME_ACQUIER ".tmp");

	PRNLINE("Baglanti kuruldu.\n");
	this->m_packetSeqNum = 0;
	return SUCCESS; 
}

//--------------------------------------------------------------------------------

int CTMSEngine::OnAfterSend()
{
	return SUCCESS;
}

//--------------------------------------------------------------------------------

int CTMSEngine::OnBeforeSend()
{ 
	CCommEngine2::OnBeforeSend();
	
	CParamters params;
	if (!params.Open()) {
		return DEFAULT_PARAMS_NOT_OPEN;
	}
	params.GotoRec(1, true);
	CParamters::HParameterRecord hParam = params.GetData();
	params.Close();
	//this->m_packetSeqNum = params.GetNextStan();
	//params.SetNextStan(++this->m_packetSeqNum);


	char tmp[1024] = "";
	int ret;
	int pos = 0;

	//--------------------
	sprintf((char*)this->m_elements.szMsgCode, "0800"); 
	//--------------------
	if (this->m_packetSeqNum == 0) {
		sprintf((char*)this->m_elements.szProcCode, GET_PARAM_PROCESSING_CODE_BEGIN);
	}
	else {
		sprintf((char*)this->m_elements.szProcCode, GET_PARAM_PROCESSING_CODE_CONT);
	}
	//--------------------
	sprintf((char*)this->m_elements.szSTAN, "%d", params.GetNextStan());
	//--------------------
	memcpy(this->m_elements.szNii, hParam->m_NII, CParamters::sizeNII);
	this->m_elements.szNii[CParamters::sizeNII] = 0x00;

	//--------------------
	
	memcpy(this->m_elements.szTermID, hParam->m_terminalID, CParamters::sizeTerminalID);
	this->m_elements.szTermID[CParamters::sizeTerminalID] = 0x00;
	
	//--------------------

	memcpy(this->m_elements.szMerchantID, hParam->m_merchantID, CParamters::sizeMerchantID);
	this->m_elements.szMerchantID[CParamters::sizeMerchantID] = 0x00;
	
	//--------------------
	// Model[4] + Serial[12] + Version[12] + Batch[] : toplam 40. Batch sola dayali string
	memset(this->m_elements.szF43Data, ' ', sizeof(this->m_elements.szF43Data));
	memcpy(this->m_elements.szF43Data + pos, hParam->m_model,		CParamters::sizeModel		); pos += CParamters::sizeModel;
	memcpy(this->m_elements.szF43Data + pos, hParam->m_serialNo,	CParamters::sizeSerialNo	); pos += CParamters::sizeSerialNo;
	memcpy(this->m_elements.szF43Data + pos, hParam->m_posVersion,	CParamters::sizePosVersion	); pos += CParamters::sizePosVersion;

	sprintf(tmp, "%d", atoi(hParam->m_batch));
	memcpy(this->m_elements.szF43Data + pos, tmp,	strlen(tmp)); pos += strlen(tmp);

	this->m_elements.szF43Data[40] = 0x00;

	//--------------------
	if (this->m_packetSeqNum > 0) {
		sprintf(tmp, "%0*d", LEN_FIELD61, this->m_prevStan);
		Str2Bcd(tmp, strlen(tmp), LEFT_PAD_ZERO, this->m_elements.szField61, LEN_FIELD61, LEFT_PAD);
	}

	ret = this->m_8583.Pack(C8583::GetTMSFieldAttrs(), &this->m_elements, this->m_sendBuffer + 7, (unsigned int*)&this->m_sendSize);
	this->m_sendSize += 7;

	this->PrepTPDU();
	this->PrepLen();
	
	if (ret != SUCCESS) {
		return ret;
	}
	++this->m_packetSeqNum;
	return SUCCESS;
}

//--------------------------------------------------------------------------------

int CTMSEngine::OnAfterRecv()
{ 
	int ret;
	char tmp[100] = "";
	

	ret = this->m_8583.Unpack(C8583::GetRecvTMSFieldAttrs(), this->m_recvBuffer + 7, this->m_recvSize - 7, &this->m_recvElements);
	if (ret < 0) {
		return UNPACK_ERROR;
	}

	this->m_lastPacket = false;
	if (strncmp((char*)this->m_recvElements.szProcCode, GET_PARAM_PROCESSING_CODE_END, strlen(GET_PARAM_PROCESSING_CODE_END)) == 0) {
		this->m_lastPacket = true;
	}

	this->m_responseCode	= atoi(this->m_recvElements.szRspCode);
	Bcd2Str(this->m_recvElements.szField61 + 2, LEN_FIELD61, 0, tmp);
	this->m_prevStan		= atoi(tmp);

	// F39 Host response "00" onay degil mi.
	if (this->m_responseCode != 0) {
		this->OnResponseCodeError(this->m_responseCode);
		return RESPONSE_CODE_ERROR;
	}

	// F60'da alinan tablo datasi islenir.
	this->ProcessData();

	// Gelecek olan baska paket var mi
	if (!this->m_lastPacket) {
		PRNLINE("son paket degil\n");
		this->SetContinueSendRecv(true);
	}
	else {
		PRNLINE("son paket!\n");
		this->SetContinueSendRecv(false);
	}

	// Parametre updae edilir. STAN no ilerledi.
	CParamters params;
	if (!params.Open()) {
		return DEFAULT_PARAMS_NOT_OPEN;
	}
	params.GotoRec(1, true);
	params.SetNextStan(this->m_prevStan);
	params.Update();
	params.Close();


	return SUCCESS; 
}

//--------------------------------------------------------------------------------

int CTMSEngine::OnAfterProcess()
{ 
	char tmp[255] = "";
	this->MoveNewFiles();

	// Acq'dan batch no Params'a alinir.
	CAcquier acq;
	CParamters param;

	CAcquier::HAcquierRecord hAcq;
	CParamters::HParameterRecord hParam;

	if (acq.Open()) {
		if (param.Open()) {
			param.GotoRec(1, true);
			acq.GotoRec(1, true);

			hAcq	= acq.GetData();
			hParam	= param.GetData();

			Bcd2Str((unsigned char*)hAcq->m_currentBatch, CAcquier::sizeCurrentBatch, 0, hParam->m_batch);

			param.Update();

			param.Close();
		}
		acq.Close();
	}

	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	pEng->PrintLogo();
	CTerminal term;
	CTerminal::HTerminalRecord hTerm;
	if (term.Open()) {
		term.GotoRec(1, true);
		hTerm = term.GetData();
		term.Close();

		pEng->PrnSetNormal();
		memcpy(tmp, hTerm->m_merchName, sizeof(hTerm->m_merchName));
		tmp[sizeof(hTerm->m_merchName)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");
	}
	PrnStr("Parametre Indirildi.\n\n");
	pEng->PrnSetNormal();
	PrnStr("-----------------------------\n\n\n\n\n");

	return SUCCESS; 
}

//--------------------------------------------------------------------------------











































//#define OFFLINE_TEST
/*
int CTMSEngine::SendReceive()
{
	int ret;
	char tmp[128] = "";
	bool bUserCancelled = false;


	CMessageBox mb("Araniyor...", MB_SHOW_ONLY);
	mb.Draw();



#ifndef OFFLINE_TEST
	ret = this->Connect();
	if (ret != SUCCESS) {
		mb.SetMessage("Basarisiz!");
		mb.Draw();
		goto EXIT;
	}
#endif

	mb.SetMessage("Aliniyor...");
	mb.Draw();
	this->m_packetSeqNum	= 0;
	this->m_lastPacket		= false;
	do {
		ret = this->BeforeSend();
		if (ret != SUCCESS) {
			goto EXIT;
		}
#ifndef OFFLINE_TEST
		ret = this->SendPacket();
		if (ret != SUCCESS) {
			goto EXIT;
		}

		ret = this->RecvPacket();
		if (ret != SUCCESS) {
			goto EXIT;
		}
#endif

		ret = this->AfterRecv();
		if (ret != SUCCESS) {
			goto EXIT;
		}
		if (this->m_responseCode != 0) {
			break;
		}
		
		this->ProcessData();

		if (kbhit() == 0) {
			if (getkey() == KEY_CANCEL) {
				bUserCancelled = true;
				break;
			}
		}

		if (this->m_lastPacket) {
			break;
		}
#ifndef OFFLINE_TEST
	} while(1);
#else
	} while(false);
#endif

#ifndef OFFLINE_TEST
	ret = this->Disconnect();
	if (ret != SUCCESS) {
		goto EXIT;
	}
#endif

	if (!bUserCancelled) {
		this->MoveNewFiles();
	}

	return SUCCESS;

EXIT:
	if (this->IsConnected()) {
		this->Disconnect();
	}
	sprintf(tmp, "SendRecv: %d", ret);
	PRNLINE(tmp);
	return ret;
}
*/
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

int CTMSEngine::ProcessData()
{
	int tableType;
	int size = 0;
	int fp;
	int fileExist = 0;
	char tmp[8] = "";
	static char buff[2048] = "";

	// Table Type	[1]
	// Table Len	[2] : n (BCD)
	// Table ID		[3]
	// <Data>		[n]

	tableType = (int)this->m_recvElements.sField60[2];
	memcpy(tmp, &this->m_recvElements.sField60[3], 2);
	tmp[3] = 0x00;

	size = Bcd2Lng((unsigned char*)tmp, 2);
	
	switch(tableType) {
		case 0x01: // Terminal
			if (fexist(TABLE_NAME_TERMINAL ".tmp") != -1) {
				fp = open(TABLE_NAME_TERMINAL ".tmp", O_RDWR);
			}
			else {
				fp = open(TABLE_NAME_TERMINAL ".tmp", O_CREATE|O_RDWR);
			}
		break;
		case 0x02: // Acquier
			if (fexist(TABLE_NAME_ACQUIER ".tmp") != -1) {
				fp = open(TABLE_NAME_ACQUIER ".tmp", O_RDWR);
			}
			else {
				fp = open(TABLE_NAME_ACQUIER ".tmp", O_CREATE|O_RDWR);
			}
		break;
		case 0x03: // Issuer
		break;
		case 0x04:
		break;
		default:
		break;
	}
	seek(fp, 0, SEEK_END);

	//memset(buff, 0x00, sizeof(buff));
	//Bcd2Str(&this->m_recvElements.sField60[5], size, 0, buff);
	//PRNLINE(buff);

	//sprintf(buff, "size: %d\n", size);
	//PRNLINE(buff);
	
	write(fp, &this->m_recvElements.sField60[5], size);

	close(fp);

	return SUCCESS;
}

//--------------------------------------------------------------------------------

void CTMSEngine::MoveNewFiles()
{
	CTable::MoveFile(TABLE_NAME_TERMINAL ".tmp",	TABLE_NAME_TERMINAL);
	CTable::MoveFile(TABLE_NAME_ACQUIER ".tmp",		TABLE_NAME_ACQUIER);
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
