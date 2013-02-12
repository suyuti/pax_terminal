// ScreenDefParams.cpp: implementation of the CScreenDefParams class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreenDefParams.h"
#include "InputBox.h"
#include "..\Files\Acquier.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScreenDefParams::CScreenDefParams()
{

}

//----------------------------------------------------------------------------------------

CScreenDefParams::~CScreenDefParams()
{

}

//----------------------------------------------------------------------------------------

int CScreenDefParams::Draw()
{
	CScreen::Clear();
	int i = 0;
	uchar key;
	char tmp[64] = "";
	CParamters::HParameterRecord hRec;

	if (!this->m_param.Open()) {
		goto EXIT;
	}
	this->m_param.GotoRec(1);
	this->m_param.Close();
	hRec = this->m_param.GetData();

	do {
		CScreen::Clear();
		switch (i) {
			case 0: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Terminal ID\n");
				memcpy(tmp, hRec->m_terminalID, CParamters::sizeTerminalID);
				tmp[CParamters::sizeTerminalID] = 0x00;
				//ScrGotoxy(1, 2);
				Lcdprintf(tmp);
			}
			break;
			case 1: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Merchant ID\n");
				memcpy(tmp, hRec->m_merchantID, CParamters::sizeMerchantID);
				tmp[CParamters::sizeMerchantID] = 0x00;
				//ScrGotoxy(1, 2);
				Lcdprintf(tmp);
			}
			break;
			case 2: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Serial No:\n");
				memcpy(tmp, hRec->m_serialNo, CParamters::sizeSerialNo);
				tmp[CParamters::sizeSerialNo] = 0x00;
				////ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 3: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("NII\n");
				memcpy(tmp, hRec->m_NII, CParamters::sizeNII);
				tmp[CParamters::sizeNII] = 0x00;
				////ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 4: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Pri.Media\n");
				memcpy(tmp, hRec->m_priMedia, CParamters::sizeMedia);
				tmp[CParamters::sizeMedia] = 0x00;
				////ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 5: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sec.Media\n");
				memcpy(tmp, hRec->m_secMedia, CParamters::sizeMedia);
				tmp[CParamters::sizeMedia] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 6: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Subnet\n");
				memcpy(tmp, hRec->m_subnet, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 7: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Gateway\n");
				memcpy(tmp, hRec->m_gateway, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 8: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("APN\n");
				memcpy(tmp, hRec->m_apn, CParamters::sizeApn);
				tmp[CParamters::sizeApn] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 9: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("PIN\n");
				memcpy(tmp, hRec->m_SimPIN, CParamters::sizePIN);
				tmp[CParamters::sizePIN] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 10: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMS Pri. IP\n");
				memcpy(tmp, hRec->m_TmsIP_1, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 11: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMS Pri. Port\n");
				memcpy(tmp, hRec->m_TmsPort_1, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 12: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMS Sec. IP\n");
				memcpy(tmp, hRec->m_TmsIP_2, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 13: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMS Sec. Port\n");
				memcpy(tmp, hRec->m_TmsPort_2, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 14: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Pri.IP\n");
				memcpy(tmp, hRec->m_provizyonIP_1, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 15: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Pri.Port\n");
				memcpy(tmp, hRec->m_provizyonPort_1, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 16: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Sec.IP\n");
				memcpy(tmp, hRec->m_provizyonIP_2, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 17: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Sec.Port\n");
				memcpy(tmp, hRec->m_provizyonPort_2, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 18: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Pri.IP\n");
				memcpy(tmp, hRec->m_settleIP_1, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 19: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Pri.Port\n");
				memcpy(tmp, hRec->m_settlePort_1, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 20: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Sec.IP\n");
				memcpy(tmp, hRec->m_settleIP_2, CParamters::sizeIP);
				tmp[CParamters::sizeIP] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 21: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Sec.Port\n");
				memcpy(tmp, hRec->m_settlePort_2, CParamters::sizePort);
				tmp[CParamters::sizePort] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 22: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMP Pri. Phone\n");
				memcpy(tmp, hRec->m_tmsPhoneNo_1, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 23: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("TMS Sec.Phone\n");
				memcpy(tmp, hRec->m_tmsPhoneNo_2, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 24: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Pri.Phone\n");
				memcpy(tmp, hRec->m_provizyonPhoneNo_1, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 25: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Prov.Sec.Phone\n");
				memcpy(tmp, hRec->m_provizyonPhoneNo_2, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 26: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Pri.Phone\n");
				memcpy(tmp, hRec->m_settlePhoneNo_1, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 27: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Sett.Sec.Phone\n");
				memcpy(tmp, hRec->m_settlePhoneNo_2, CParamters::sizePhoneNo);
				tmp[CParamters::sizePhoneNo] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 28: 
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Pre\n");
				memcpy(tmp, hRec->m_santalOnCevirme, CParamters::sizeOnCevirme);
				tmp[CParamters::sizeOnCevirme] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 29:
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Last STAN\n");
				memcpy(tmp, hRec->m_stan, CParamters::sizeSTAN);
				tmp[CParamters::sizeSTAN] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 30:
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Batch\n");
				memcpy(tmp, hRec->m_batch, CParamters::sizeBatch);
				tmp[CParamters::sizeBatch] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
			case 31:
			{
				ScrGotoxy(1, 1);
				Lcdprintf("Version\n");
				memcpy(tmp, hRec->m_posVersion, CParamters::sizePosVersion);
				tmp[CParamters::sizePosVersion] = 0x00;
				//ScrGotoxy(2, 1);
				Lcdprintf(tmp);
			}
			break;
		}
		key = getkey();
		switch(key) {
			case KEY_DOWN:
				if (i >= 31) {
					i = 0;
				}
				else {
					++i;
				}
			break;
			case KEY_UP:
				if (i <= 0) {
					i = 31;
				}
				else {
					--i;
				}
			break;
			case KEY_ENTER:
				this->UpdateItem(i);
			break;
			case KEY_CANCEL:
				goto EXIT;
			break;
		}
	} while(true);
EXIT:
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
void CScreenDefParams::UpdateItem(int item)
{
	bool update = false;
	CParamters::HParameterRecord hRec = this->m_param.GetData();

	switch(item) {
		case 0: 
		{
			CInputBox inp("Terminal ID:", 3, 3, CParamters::sizeTerminalID, CInputBox::itAlphaNumeric);
			if (inp.Draw() == CInputBox::retOK) {
				update = true;
				memset(hRec->m_terminalID, 0x00, CParamters::sizeTerminalID);
				memcpy(hRec->m_terminalID, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 1: 
		{ 
			CInputBox inp("Merchant ID:", 3, 3, CParamters::sizeMerchantID, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK) {
				update = true;
				memset(hRec->m_merchantID, 0x00, CParamters::sizeMerchantID);
				memcpy(hRec->m_merchantID, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 2: 
		{ 
			CInputBox inp("Serial No:", 3,3, CParamters::sizeSerialNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK) {
				update = true;
				memset(hRec->m_serialNo, 0x00, CParamters::sizeSerialNo);
				memcpy(hRec->m_serialNo, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 3: 
		{ 
			CInputBox inp("NII:", 3,3, CParamters::sizeNII, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK) {
				update = true;
				memset(hRec->m_NII, 0x00, CParamters::sizeNII);
				memcpy(hRec->m_NII, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 4: 
		{ 
			CInputBox inp("Pri.Media:", 3,3, CParamters::sizeMedia, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK) {
				update = true;
				memset(hRec->m_priMedia, 0x00, CParamters::sizeMedia);
				memcpy(hRec->m_priMedia, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 5: 
		{ 
			CInputBox inp("Sec.Media:", 3,3, CParamters::sizeMedia, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_secMedia, 0x00, CParamters::sizeMedia);
				memcpy(hRec->m_secMedia, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 6: 
		{ 
			CInputBox inp("Subnet:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_subnet, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_subnet, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 7: 
		{ 
			CInputBox inp("Gateway:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_gateway, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_gateway, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 8: 
		{ 
			CInputBox inp("APN:", 3,3, CParamters::sizeApn, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_apn, 0x00, CParamters::sizeApn);
				memcpy(hRec->m_apn, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 9: 
		{ 
			CInputBox inp("PIN:", 3,3, CParamters::sizePIN, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_SimPIN, 0x00, CParamters::sizePIN);
				memcpy(hRec->m_SimPIN, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 10:
		{ 
			CInputBox inp("TMS Pri. IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_TmsIP_1, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_TmsIP_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 11: 
		{ 
			CInputBox inp("TMS Pri. Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ) {
				update = true;
				memset(hRec->m_TmsPort_1, 0x00, CParamters::sizePort);
				memcpy(hRec->m_TmsPort_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 12: 
		{ 
			CInputBox inp("TMS Sec. IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_TmsIP_2, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_TmsIP_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 13: 
		{ 
			CInputBox inp("TMS Sec. Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_TmsPort_2, 0x00, CParamters::sizePort);
				memcpy(hRec->m_TmsPort_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 14: 
		{ 
			CInputBox inp("Prov.Pri.IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonIP_1, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_provizyonIP_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 15: 
		{ 
			CInputBox inp("Prov.Pri.Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonPort_1, 0x00, CParamters::sizePort);
				memcpy(hRec->m_provizyonPort_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 16: 
		{ 
			CInputBox inp("Prov.Sec.IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonIP_2, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_provizyonIP_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 17: 
		{ 
			CInputBox inp("Prov.Sec.Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonPort_2, 0x00, CParamters::sizePort);
				memcpy(hRec->m_provizyonPort_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 18: 
		{ 
			CInputBox inp("Sett.Pri.IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settleIP_1, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_settleIP_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 19: 
		{ 
			CInputBox inp("Sett.Pri.Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settlePort_1, 0x00, CParamters::sizePort);
				memcpy(hRec->m_settlePort_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 20: 
		{ 
			CInputBox inp("Sett.Sec.IP:", 3,3, CParamters::sizeIP, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settleIP_2, 0x00, CParamters::sizeIP);
				memcpy(hRec->m_settleIP_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 21: 
		{ 
			CInputBox inp("Sett.Sec.Port:", 3,3, CParamters::sizePort, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settlePort_2, 0x00, CParamters::sizePort);
				memcpy(hRec->m_settlePort_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 22: 
		{ 
			CInputBox inp("TMP Pri. Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_tmsPhoneNo_1, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_tmsPhoneNo_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 23: 
		{ 
			CInputBox inp("TMS Sec.Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_tmsPhoneNo_2, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_tmsPhoneNo_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 24: 
		{ 
			CInputBox inp("Prov.Pri.Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonPhoneNo_1, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_provizyonPhoneNo_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 25: 
		{ 
			CInputBox inp("Prov.Sec.Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_provizyonPhoneNo_2, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_provizyonPhoneNo_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 26: 
		{ 
			CInputBox inp("Sett.Pri.Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settlePhoneNo_1, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_settlePhoneNo_1, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 27: 
		{ 
			CInputBox inp("Sett.Sec.Phone:", 3,3, CParamters::sizePhoneNo, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_settlePhoneNo_2, 0x00, CParamters::sizePhoneNo);
				memcpy(hRec->m_settlePhoneNo_2, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 28: 
		{ 
			CInputBox inp("Pre:", 3,3, CParamters::sizeOnCevirme, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_santalOnCevirme, 0x00, CParamters::sizeOnCevirme);
				memcpy(hRec->m_santalOnCevirme, inp.GetBuffer(), inp.GetSize());
			}
		}
		break;
		case 30: //! kaldirilacak
		{ 
			CInputBox inp("Batch:", 3,3, CParamters::sizeBatch, CInputBox::itAlphaNumeric); 
			if (inp.Draw() == CInputBox::retOK ){
				update = true;
				memset(hRec->m_batch, 0x00, CParamters::sizeBatch);
				memcpy(hRec->m_batch, inp.GetBuffer(), inp.GetSize());

				CAcquier acq;
				if (acq.Open()) 
				{
					acq.GotoRec(1, true);
					acq.SetBatchNo(atoi(hRec->m_batch));
					acq.Update();
					acq.Close();
				}
	
				
			}
		}
		break;
		default:
			update = false;
		break;
	}

	if (update) {
		if (!this->m_param.Open()) {
			goto EXIT;
		}
		this->m_param.GotoRec(1, false);
		this->m_param.Update();
		this->m_param.Close();
	}
	return;
EXIT:
	PRNLINE("Parametre Update icin acilamadi!");
	return;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
