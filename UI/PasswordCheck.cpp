#include "PasswordCheck.h"
#include "..\Files\Terminal.h"
#include "..\UI\MessageBox.h"
#include "..\UI\InputBox.h"
#include "..\Util\NumFuncs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPasswordCheck::CPasswordCheck()
{

}

CPasswordCheck::~CPasswordCheck()
{

}

int CPasswordCheck::Check(PassCheckTypes type)
{
	char caption[32]	= "";
	char passTmp[8]		= "";
	char passTmpUser[8] = "";

	CTerminal term;
	CTerminal::HTerminalRecord hTerm;
	if (!term.Open()) {
		return TERMINAL_NOT_OPEN;
	}
	term.GotoRec(1, true);
	term.Close();
	hTerm = term.GetData();
	
	switch (type) {
		case passVoid:
			sprintf(caption, "IPTAL Sifresi?");
			Bcd2Str((unsigned char*)hTerm->m_voidPass, CTerminal::sizeVoidPass, 0, passTmp);
		break;
		case passSettle:
			sprintf(caption, "Gunsnu Sifresi?");
			Bcd2Str((unsigned char*)hTerm->m_settlePass, CTerminal::sizeSettlePass, 0, passTmp);
		break;
		case passMerchant:
			sprintf(caption, "Kulln Sifresi?");
			Bcd2Str((unsigned char*)hTerm->m_merchPass, CTerminal::sizeMerchPass, 0, passTmp);
		break;
		case passRefund:
			sprintf(caption, "Iade Sifresi?");
			Bcd2Str((unsigned char*)hTerm->m_refundPass, CTerminal::sizeRefundPass, 0, passTmp);
		break;
		case passReport:
			sprintf(caption, "Rapor Sifresi?");
			Bcd2Str((unsigned char*)hTerm->m_reportPass, CTerminal::sizeReportPass, 0, passTmp);
		break;
		case passDeveloper:
			sprintf(caption, "Sifre ?");
			sprintf(passTmp, "4291");
		break;
	}


	CInputBox inPass(caption, 5, 5, 4, CInputBox::itPassword);
	if (inPass.Draw() != CInputBox::retOK) {
		return USER_CANCELLED;
	}
	strncpy(passTmpUser, inPass.GetBuffer(), strlen(inPass.GetBuffer()));

	if (strncmp(passTmp, passTmpUser, strlen(passTmp)) != 0) {
		CMessageBox mb("Sifre gecersiz!", MB_ANY_KEY);
		mb.Draw();
		return PASSWORD_NOT_VALID;
	}
	return SUCCESS;
}
