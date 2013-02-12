#include "des.h"
#include "..\Util\NumFuncs.h"
#include "..\globaldef.h"
#include "crypt.h"

int oldAuthanticateDesfire(unsigned char *Data, int DataLen, unsigned char *commandToSend, int *commandLen)
{
	int SendDataLen = 0;
	int rc=0 ;
	unsigned char sendData[64] = "";
	unsigned char randomB[8] =""; // randomB oluþturmak için
	unsigned char bcdSendCommand[17] ="";
	unsigned char randomA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char Key[] =   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // cbc 24 bytes key string olarak
	
	
    //*** Gelen bcd Data'yý Triple DES ile CBC mode'da þifreleme ***/

	if (DataLen % 8 != 0) // Triple DES ile CBC mode yapmadan önce bu kontrolün yapýlmasý gerekmektedir.
		{
			return 0; // Burada return deðeri olarak "LENGTH ERROR HATASI TANIMLANACAK"
		}
	
	TDES_CBC(Data, DataLen, (unsigned char*)NULL, Key, randomB, DES_MODE_ENC); // 8 byte randomB oluþturuldu.

	//*** bcdOutPut ile 1 kez rotate left iþlemi ile RandomB' oluþturulmasý ***//
	
	RotateStringInPlace((char*)randomB);

	//*** RandomA ve RandomB' concat edilecek ***//
	memcpy(&randomA[8], randomB, sizeof(randomB));

	//*** Gonderilecek komutun basina xAF ekle ***//
	bcdSendCommand[0] = 0xAF;

	//***  new randomA TDES_CBC ile DES_MODE_ENC iþlemi yapýlacak ***//
	TDES_CBC(randomA, sizeof(randomA), (unsigned char*)NULL, Key, &bcdSendCommand[1], DES_MODE_ENC); //new randomA 

	memcpy(commandToSend, bcdSendCommand, sizeof(bcdSendCommand));
	*commandLen = 17;
	
	return TRUE;
}

int AuthanticateDesfire(unsigned char *Data, int DataLen, unsigned char *commandToSend, int *commandLen)
{
	unsigned char		ATRData[33] = "";
	unsigned char		rv=0;
	APDU_SEND			sendData;
	APDU_RESP			cardAnswer;
	
	rv = IccInit(0x02, ATRData);
	IccAutoResp(0x02, 0x00);
	
	memset(&sendData, 0x00, sizeof(APDU_SEND));

	memcpy(sendData.Command, "\x80\x0A\x00\x00", 4);
	sendData.Lc = 0x0A;
	memcpy(sendData.DataIn, "\x00\x00", 2);
	memcpy(&sendData.DataIn[2], Data, 8);
	sendData.Le = 0x0100;

	rv = IccIsoCommand(0x02, &sendData, &cardAnswer);
	if(cardAnswer.SWA == 0x90 && cardAnswer.SWB == 0xAF)
	{
		commandToSend[0] = 0xAF;
		memcpy(&commandToSend[1], cardAnswer.DataOut, cardAnswer.LenOut);
		*commandLen = cardAnswer.LenOut + 1;
		IccClose(0x02);

		return TRUE;
	}

	*commandLen = 0;

	IccClose(0x02);

	return TRUE;
}

