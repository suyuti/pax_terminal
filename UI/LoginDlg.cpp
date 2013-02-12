// LoginDlg.cpp: implementation of the CLoginDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "LoginDlg.h"
#include "InputBox.h"
#include "MessageBox.h"
#include "UIUtils.h"

//--------------------------------------------------------------------------------------------------

CLoginDlg::CLoginDlg()
{

}

//--------------------------------------------------------------------------------------------------

CLoginDlg::~CLoginDlg()
{

}

//--------------------------------------------------------------------------------------------------

int CLoginDlg:: Draw()
{
	int retVal = LOGIN_FAILURE;
	CScreen::Draw();
	ScrFontSet(1);

	CInputBox inputBox("Kullanici\nsifresi:", 5,5, 4, CInputBox::itPassword);
	//CInputBox inputBox("Kullanici\nsifresi:", 5,5, 4, CInputBox::itAlphaNumeric);
	if (inputBox.Draw() == CInputBox::retOK) {
		if (strncmp(inputBox.GetBuffer(), "0000", 4) == 0) {
			CUIUtils::AnimOK("GiRiS\nBASARILI");
			retVal = SUCCESS;
		}
		else {
			CMessageBox msg("Giris islemi basarisiz!.", MB_ANY_KEY);
			msg.Draw();
			retVal = LOGIN_FAILURE;
		}
	}
	ScrFontSet(0);

	return retVal;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
