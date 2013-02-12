// CardReader.cpp: implementation of the CCardReader class.
//
//////////////////////////////////////////////////////////////////////

#include "CardReader.h"

#define TEST_CARDNO "123456789123456"



//--------------------------------------------------------------------------------------------------

CCardReader::CCardReader() :
	m_cardWaitTime(3000),
	m_error(SUCCESS)
{
	this->Clear();
}

//--------------------------------------------------------------------------------------------------

CCardReader::~CCardReader()
{

}

//--------------------------------------------------------------------------------------------------

void CCardReader::Clear()
{
	this->m_gainedPoints	= 0;
	this->m_error			= SUCCESS;

	memset(&this->m_fanData,			0x00, sizeof(FanStruct			));
	memset(&this->m_prepaidData,		0x00, sizeof(PrepaidStruct		));
	memset(&this->m_loyaltyData,		0x00, sizeof(LoyaltyStruct		));
	memset(&this->m_seasonTicketData,	0x00, sizeof(SeasonTicketStruct	));
}

//--------------------------------------------------------------------------------------------------

int CCardReader::Initialize()
{
	uchar result;
	
	this->Clear();

	result = PiccOpen();
	
	if(result != 0x00)
		return FAIL_READER_INIT;

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::Close()
{
	PiccClose();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderDetectCard()
{
	int		DetectResult			= -1;
	uchar	CardType		[ 2]	= "";
	uchar	CardSerialNumber[20]	= "";
	uchar	CardID			[20]	= "";
	uchar	ResponseData	[30]	= "";
	ushort  currentDelayTime		= 0;
	uchar	key;

	DetectResult = PiccDetect(0x00, CardType, CardSerialNumber, CardID, ResponseData);
	while (DetectResult != 0x00) {
		DelayMs(10);
		currentDelayTime += 10;
		
		if (kbhit() == 0) {
			key = getkey();
			if (key == KEY_CANCEL) {
				this->m_error = USER_CANCELLED;
				return this->m_error;
			}
		}

		if(currentDelayTime >= this->m_cardWaitTime)
			return FAIL_CARD_DETECT;	
		
		DetectResult = PiccDetect(0x00, CardType, CardSerialNumber, CardID, ResponseData);
	}
	Beef(1, 100);

	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderGetApplications(uchar* CardApplications, int* LenCardApplications)
{
	int		recvLen			= 0;
	int		sendLen			= 0;
	//int		returnResult	= FALSE;
	uchar	recvData[50]	= "";
	int		index			= 0;

	this->m_error = SendReceiveCommand((unsigned char*)CMD_GET_APP_LIST, LEN_CMD_GET_APP_LIST, recvData, &recvLen);

	if(this->m_error != SUCCESS) {
		this->m_error = FAIL_GET_APPLICATIONS;
		return FAIL_GET_APPLICATIONS;
	}
	
	memcpy(CardApplications, recvData, recvLen);
	*LenCardApplications = recvLen;
	
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::AuthenticateCard()
{
	int recvLen = 0;
	int sendLen = 0;
	//int returnResult = FALSE;
	uchar recvData[100] = "";
	int index = 0;
	int tryCount = 0;

	this->m_error = SendReceiveCommand((unsigned char*)CMD_AUTHENTICATE, LEN_CMD_AUTHENTICATE, recvData, &recvLen);
	
	
	while(this->m_error != SUCCESS)
	{
		tryCount ++;

		if(tryCount >= AUTHENTICATION_TRY_COUNT) {
			this->m_error = FAIL_AUTHENTICATION;
			return FAIL_AUTHENTICATION;
		}

		recvLen = 0;
		memset(recvData, 0x00, sizeof(recvData));
		this->m_error = SendReceiveCommand((unsigned char*)CMD_AUTHENTICATE, LEN_CMD_AUTHENTICATE, recvData, &recvLen);
	}

	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::SelectCardApplication(uchar* ApplicationID)
{
	int recvLen = 0;
	int sendLen = 0;
	//int returnResult = FALSE;
	uchar recvData[100] = "";
	uchar sendCmd[4] = "";
	int index = 0;
	int cmdLen = 0;

	memcpy(sendCmd, CMD_SELECT_APP, LEN_CMD_SELECT_APP);
	cmdLen += LEN_CMD_SELECT_APP;
	memcpy(&sendCmd[cmdLen], ApplicationID, 3);
	cmdLen += LEN_APP_ID;

	this->m_error = SendReceiveCommand(sendCmd, cmdLen, recvData, &recvLen);
	
	if(this->m_error != SUCCESS) {
		this->m_error = FAIL_SELECT_APPLICATION;
		return FAIL_SELECT_APPLICATION;
	}
	
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderGetFileIDs(uchar* FileIDs)
{
	int recvLen = 0;
	int sendLen = 0;
	//int returnResult = FALSE;
	uchar recvData[90] = "";
	int index = 0;

	this->m_error = SendReceiveCommand((unsigned char*)CMD_GET_FILE_IDS, LEN_CMD_GET_FILE_IDS, recvData, &recvLen);
	
	if(this->m_error != SUCCESS) {
		this->m_error = FAIL_GET_FILE_IDS;
		return FAIL_GET_FILE_IDS;
	}
	
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderGetFileData(uchar FileID, uchar* FileLen, uchar* CardData, int* CardDataLen)
{
	int recvLen = 0;
	int sendLen = 0;
	//int returnResult = FALSE;
	uchar recvData[500] = "";
	char sRecvData[1001] = "";
	int index = 0;
	int PrintInitResult = -1;
	uchar sendCmd[8] = "";
	int cmdLen = 0;

	memcpy(sendCmd, CMD_READ_FILE_DATA, LEN_CMD_READ_FILE_DATA);
	cmdLen += LEN_CMD_READ_FILE_DATA;

	sendCmd[cmdLen] = FileID;
	cmdLen += 1;

	memcpy(&sendCmd[cmdLen], FILE_OFFSET_0, LEN_FILE_OFFSET);
	cmdLen += LEN_FILE_OFFSET;

	memcpy(&sendCmd[cmdLen], FileLen, LEN_FILE_LEN);
	cmdLen += LEN_FILE_LEN;

	this->m_error = SendReceiveCommand(sendCmd, cmdLen, recvData, &recvLen);

	if(this->m_error != SUCCESS) {
		this->m_error = FAIL_READ_FILE_DATA;
		return FAIL_READ_FILE_DATA;
	}
	
	memcpy(CardData, recvData, recvLen);
	*CardDataLen = recvLen;

	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderWriteFileData(uchar FileID, uchar* CardData, uchar* FileOffset, int DataLen)
{
	int recvLen = 0;
	int sendLen = 0;
	//int returnResult = FALSE;
	uchar recvData[500] = "";
	char sRecvData[1001] = "";
	int cmdLen = 0;
	uchar sendCmd[300] = "";
	
	memcpy(sendCmd, CMD_WRITE_FILE_DATA, LEN_CMD_WRITE_FILE_DATA);
	cmdLen += LEN_CMD_WRITE_FILE_DATA;
	
	sendCmd[cmdLen] = FileID;
	cmdLen += 1;
	
	memcpy(&sendCmd[cmdLen], FileOffset, LEN_FILE_OFFSET);
	cmdLen += LEN_FILE_OFFSET;

	memcpy(&sendCmd[cmdLen], LEN_WRITE_DATA, LEN_WRITE_DATA_LEN);
	cmdLen += LEN_WRITE_DATA_LEN;

	memcpy(&sendCmd[cmdLen], CardData, DataLen);
	cmdLen += DataLen;

	this->m_error = SendReceiveCommand(sendCmd, cmdLen, recvData, &recvLen);
	
	if(this->m_error != SUCCESS) {
		this->m_error = FAIL_WRITE_FILE_DATA;
		return FAIL_WRITE_FILE_DATA;
	}
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::SendReceiveCommand(uchar* SendCommand, int SendLen, uchar* RecvCommand, int* RecvDataLen)
{
	//int	CommandResult = -1;	
	int PrintInitResult = -1;
	
	char sResponseData[255] = "";
	char sSendData[513] = "";
	uchar recvData[513] = "";
	int recvLen = -1;
	uchar tempSendCmd[255] = "";
	char stempSendData[513] = "";
	int sTempSendLen = 0;

	*RecvDataLen = 0;

	this->m_error = PiccCmdExchange(SendLen, SendCommand, (unsigned int*)&recvLen, recvData);
	if(this->m_error != 0x00) {
		this->m_error = FAIL_SEND_RECEIVE;
		return FAIL_SEND_RECEIVE;
	}

	this->m_error = SUCCESS;// = TRUE;
/*
	Bcd2Str(SendCommand, SendLen, 0, sSendData);
	Bcd2Str(recvData, recvLen, 0, sResponseData);

	PrintInitResult = PrnInit();

	if (PrintInitResult != 0x00) 
	{
		return FAIL_SEND_RECEIVE;
	}

	PrnStr("Send Command : %s\n", sSendData);
	PrnStr("Command Result : %d\n", CommandResult);
	PrnStr("Response : %s\n", sResponseData);

	PrnStart();
*/	
	memcpy(RecvCommand, &recvData[1], recvLen - 1);
	*RecvDataLen += recvLen -1;

	if(recvData[0] == RV_SUCCESS)
	{
		return SUCCESS;
	}
	else if(recvData[0] == RV_MORE_DATA)
	{	
		//Authenticate mesaji ise hesaplama yapilmasi gerekiyor.
		if(SendCommand[0] == 0x0A)
		{
			AuthanticateDesfire(&recvData[1], recvLen -1, tempSendCmd, &sTempSendLen);
			memset(recvData, 0x00, sizeof(recvData));
			this->m_error = SendReceiveCommand(tempSendCmd, sTempSendLen, recvData, &recvLen);
			return this->m_error;
		}
		else
		{
			memset(recvData, 0x00, sizeof(recvData));
			
			this->m_error = SendReceiveCommand((unsigned char*)"\xAF", 1, recvData, &recvLen);

			memcpy(&RecvCommand[*RecvDataLen], recvData, recvLen);
			*RecvDataLen += recvLen;
			
			return this->m_error;
		}			
	}
	else
	{
		this->m_error = FAIL_SEND_RECEIVE;
		return FAIL_SEND_RECEIVE;
	}
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderFillFanApp()
{
	int			recvLen = 0;
	//int			result = -1;
	uchar		recvData[500] = "";

/*	this->m_error = this->Initialize();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = CardReaderDetectCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
	
	this->m_error = SelectCardApplication((unsigned char*)APP_ID_FENERBAHCE);
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = AuthenticateCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
*/

	this->m_error = CardReaderGetFileData(FILE_ID_FAN, (unsigned char*)LEN_FILE_FAN, recvData, &recvLen);
	if(this->m_error != SUCCESS)
		return this->m_error;

	memcpy(&this->m_fanData, recvData, recvLen);

	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderFillSeasonTicketApp()
{
	int			recvLen = 0;
	//int			result = -1;
	uchar		recvData[500] = "";

/*
	this->m_error = this->Initialize();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = CardReaderDetectCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
	
	this->m_error = SelectCardApplication((unsigned char*)APP_ID_FENERBAHCE);
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = AuthenticateCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
*/

	this->m_error = CardReaderGetFileData(FILE_ID_SEASON_TICKET, (unsigned char*)LEN_FILE_SEASON_TICKET, recvData, &recvLen);
	if(this->m_error != SUCCESS)
		return this->m_error;

	memcpy(&this->m_seasonTicketData, recvData, recvLen);
	
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderFillPrepaidApp()
{
	int			recvLen = 0;
	//int			result = -1;
	uchar		recvData[500] = "";
/*
	this->m_error = this->Initialize();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = CardReaderDetectCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
	
	this->m_error = SelectCardApplication((unsigned char*)APP_ID_FENERBAHCE);
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = AuthenticateCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
*/

	this->m_error = CardReaderGetFileData(FILE_ID_PREPAID, (unsigned char*)LEN_FILE_PREPAID, recvData, &recvLen);
	if(this->m_error != SUCCESS)
		return this->m_error;

	memcpy(&this->m_prepaidData, recvData, recvLen);
	
	this->m_error = SUCCESS;
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::CardReaderFillLoyaltyApp()
{
	int			recvLen = 0;
	//int			result = -1;
	uchar		recvData[500] = "";

/*	this->m_error = this->Initialize();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = CardReaderDetectCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
	
	this->m_error = SelectCardApplication((unsigned char*)APP_ID_FENERBAHCE);
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = AuthenticateCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
*/

	this->m_error = CardReaderGetFileData(FILE_ID_LOYALTY, (unsigned char*)LEN_FILE_LOYALTY, recvData, &recvLen);
	if(this->m_error != SUCCESS)
		return this->m_error;

	memcpy(&this->m_loyaltyData, recvData, recvLen);
	
	this->m_error = SUCCESS;	
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::PostOperation()
{
	if (this->m_error == SUCCESS) {
		Beef(4, 100);
		Beef(1, 100);
	}
	else {
		Beef(1, 100);
		Beef(4, 100);
		Beef(1, 100);
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::PreOperation()
{
	this->m_error = this->Initialize();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = CardReaderDetectCard();
	if(this->m_error != SUCCESS)
		return this->m_error;
	
	this->m_error = SelectCardApplication((unsigned char*)APP_ID_FENERBAHCE);
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = AuthenticateCard();
	if(this->m_error != SUCCESS)
		return this->m_error;

	this->m_error = SUCCESS;
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoHarcama(int Amount)
{
#if 0
	char tmp[32] = "";
	memcpy(this->m_fanData.CardNumber, TEST_CARDNO, strlen(TEST_CARDNO));
	sprintf(tmp, "%d", (Amount * GAIN_POINT_PERCENTAGE) / 100);
	//Str2Bcd(tmp, strlen(tmp), LEFT_PAD_ZERO, this->m_prepaidData.Balance, sizeof(this->m_prepaidData.Balance), RIGHT_PAD);
	return SUCCESS;
#else
	//int result;
	int Balance;
	int FBPoint;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	Balance = Bcd2Lng(this->m_prepaidData.Balance, 6);
	FBPoint = Bcd2Lng(this->m_loyaltyData.FBPoint1, 6);

	if(Balance < Amount) {
		this->m_error = FAIL_INSUFFICENT_BALANCE;
		goto EXIT;
	}

	Balance = Balance - Amount;
	FBPoint = FBPoint + ((Amount * GAIN_POINT_PERCENTAGE) / 100);

	Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
	Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_PREPAID, (unsigned char*)&this->m_prepaidData, (unsigned char*)FILE_OFFSET_0, 50);
	if(this->m_error != SUCCESS)
	{
		Balance = Balance + Amount;
		Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);

		FBPoint = FBPoint - ((Amount * GAIN_POINT_PERCENTAGE) / 100);
		Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

		goto EXIT;
	}

	this->m_error = CardReaderWriteFileData(FILE_ID_LOYALTY, (unsigned char*)&this->m_loyaltyData, (unsigned char*)FILE_OFFSET_0, 50);
	if(this->m_error != SUCCESS)
	{
		FBPoint = FBPoint - ((Amount * GAIN_POINT_PERCENTAGE) / 100);
		Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

		this->m_error = SUCCESS;
		goto EXIT;
	}

	this->m_gainedPoints = ((Amount * GAIN_POINT_PERCENTAGE) / 100);

	this->m_error = SUCCESS;
EXIT:
	this->PostOperation();
	return this->m_error;
#endif
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoHarcamaIptal(int Amount)
{
	//int result;
	int Balance;
	int FBPoint;
	int OrigFBPoint;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	Balance = Bcd2Lng(this->m_prepaidData.Balance, 6);
	OrigFBPoint = Bcd2Lng(this->m_loyaltyData.FBPoint1, 6);

	Balance = Balance + Amount;
	FBPoint = OrigFBPoint - ((Amount * GAIN_POINT_PERCENTAGE) / 100);
	if(FBPoint < 0)
		FBPoint = 0;
	
	Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
	Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_PREPAID, (unsigned char*)&this->m_prepaidData, (unsigned char*)FILE_OFFSET_0, 50);
	if (this->m_error != SUCCESS) {
		Balance = Balance - Amount;
		Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
		Lng2Bcd(OrigFBPoint, this->m_loyaltyData.FBPoint1, 6);

		goto EXIT;
	}

	this->m_error = CardReaderWriteFileData(FILE_ID_LOYALTY, (unsigned char*)&this->m_loyaltyData, (unsigned char*)FILE_OFFSET_0, 50);
	if (this->m_error != SUCCESS) {
		Lng2Bcd(OrigFBPoint, this->m_loyaltyData.FBPoint1, 6);

		this->m_error = SUCCESS;
	}

	this->m_error = SUCCESS;
EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoHarcamaIade(int Amount)
{
	int Balance;
	int FBPoint;
	int OrigFBPoint;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	Balance = Bcd2Lng(this->m_prepaidData.Balance, 6);
	OrigFBPoint = Bcd2Lng(this->m_loyaltyData.FBPoint1, 6);

	Balance = Balance + Amount;
	FBPoint = OrigFBPoint - ((Amount * GAIN_POINT_PERCENTAGE) / 100);
	if(FBPoint < 0)
		FBPoint = 0;
	
	Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
	Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_PREPAID, (unsigned char*)&this->m_prepaidData, (unsigned char*)FILE_OFFSET_0, 50);
	if(this->m_error != SUCCESS)
	{
		Balance = Balance - Amount;
		Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
		Lng2Bcd(OrigFBPoint, this->m_loyaltyData.FBPoint1, 6);

		goto EXIT;
	}

	this->m_error = CardReaderWriteFileData(FILE_ID_LOYALTY, (unsigned char*)&this->m_loyaltyData, (unsigned char*)FILE_OFFSET_0, 50);
	if(this->m_error != SUCCESS)
	{
		Lng2Bcd(OrigFBPoint, this->m_loyaltyData.FBPoint1, 6);
//!
		this->m_error = SUCCESS;
	}

	this->m_error = SUCCESS;
EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoNakitYukleme(int Amount)
{
	int Balance;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	Balance = Bcd2Lng(this->m_prepaidData.Balance, 6);

	Balance = Balance + Amount;

	Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_PREPAID, (unsigned char*)&this->m_prepaidData, (unsigned char*)FILE_OFFSET_0, 50);
	if(this->m_error != SUCCESS) {
		Balance = Balance - Amount;
		Lng2Bcd(Balance, this->m_prepaidData.Balance, 6);
		goto EXIT;
	}

	this->m_error = SUCCESS;
EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoBakiyeSorgulama()
{
	
	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = SUCCESS;

EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoPuanKullanma(int Amount)
{
	int FBPoint;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	FBPoint = Bcd2Lng(this->m_loyaltyData.FBPoint1, 6);

	if(FBPoint < Amount) {
		this->m_error = FAIL_INSUFFICENT_POINTS;
		goto EXIT;
	}

	FBPoint = FBPoint - Amount;

	Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_LOYALTY, (unsigned char*)&this->m_loyaltyData, (unsigned char*)FILE_OFFSET_0, 50);
	if (this->m_error != SUCCESS) {
		FBPoint = FBPoint + Amount;
		Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);
		goto EXIT;
	}

	this->m_error = SUCCESS;

EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoPuanSorgulama()
{
	
	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if(this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = SUCCESS;

EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoPuanKullanmaIptal(int Amount)
{
	int FBPoint;

	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	FBPoint = Bcd2Lng(this->m_loyaltyData.FBPoint1, 6);

	FBPoint = FBPoint + Amount;

	Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);

	this->m_error = CardReaderWriteFileData(FILE_ID_LOYALTY, (unsigned char*)&this->m_loyaltyData, (unsigned char*)FILE_OFFSET_0, 50);
	if (this->m_error != SUCCESS) {
		FBPoint = FBPoint - Amount;
		Lng2Bcd(FBPoint, this->m_loyaltyData.FBPoint1, 6);
		goto EXIT;
	}

	this->m_error = SUCCESS;

EXIT:
	this->PostOperation();
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

int CCardReader::DoPuanKullanmaIade(int Amount)
{

	this->m_error = DoPuanKullanmaIptal(Amount);
	return this->m_error;
}

//--------------------------------------------------------------------------------------------------

char* CCardReader::GetLastErrorMsg()
{
	static char tmp[64] = "";

	switch (this->m_error) {
		case FAIL_GET_APPLICATIONS:		return "Get App Error!";		break;
		case FAIL_AUTHENTICATION:		return "Authenticate\nError!";	break;
		case FAIL_SELECT_APPLICATION:	return "Kart\nFormatlanmamis!";	break;
		case FAIL_GET_FILE_IDS:			return "Get File ID Error!";	break;
		case FAIL_READ_FILE_DATA:		return "Read Error!";			break;
		case FAIL_WRITE_FILE_DATA:		return "Write Error!";			break;
		case FAIL_SEND_RECEIVE:			return "Send-Recevie Error!";	break;
		case FAIL_INSUFFICENT_BALANCE:	return "Yetersiz\nBakiye";		break;
		case FAIL_INSUFFICENT_POINTS:	return "Yetersiz\nPuan";		break;
		case USER_CANCELLED:			return "Kullanici Iptal etti.";	break;
		case FAIL_CARD_DETECT:			return "Kart okunamadi!";		break;
		default:
			sprintf(tmp, "%d", this->m_error);
			return tmp; //! local
		break;
	}
	return "";
}

//--------------------------------------------------------------------------------------------------

int CCardReader::ReadCardData()
{
	this->m_error = this->PreOperation();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillFanApp();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillPrepaidApp();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}

	this->m_error = CardReaderFillLoyaltyApp();
	if (this->m_error != SUCCESS) {
		goto EXIT;
	}
	this->m_error = SUCCESS;

EXIT:
	this->PostOperation();
	return this->m_error;
}
