// MessageBox.cpp: implementation of the CMessageBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MessageBox.h"

//--------------------------------------------------------------------------------------------------

CMessageBox::CMessageBox()
{
	memset(this->m_message, 0x00, sizeof(this->m_message));
}

//--------------------------------------------------------------------------------------------------

CMessageBox::CMessageBox(char* pMessage, unsigned char mode) :
	m_mode(mode)
{
	memset(this->m_message, 0x00, sizeof(this->m_message));
	sprintf(this->m_message, "%s", pMessage);
}

//--------------------------------------------------------------------------------------------------

CMessageBox::~CMessageBox()
{

}

//--------------------------------------------------------------------------------------------------

int CMessageBox::Draw()
{
	CScreen::Draw();

	ScrFontSet(1);
	ScrGotoxy(1, 1);
	Lcdprintf(this->m_message);
	ScrFontSet(0);

	if (this->m_mode == MB_YES_NO) {
		ScrFontSet(0);
		ScrGotoxy(1, 7);
		Lcdprintf("[HAYIR]      [EVET]");
		ScrFontSet(0);
	}

	if (this->m_mode == MB_SHOW_ONLY) {
		return SUCCESS;
	}

	uchar key;

	do {
		key = getkey();
		switch(this->m_mode) {
			case MB_YES_NO:
				if (key == KEY_ENTER) {
					this->m_choice = CHOICE_YES;
				}
				else if (key == KEY_CANCEL) {
					this->m_choice = CHOICE_NO;
				}
				goto EXIT;
			break;
			case MB_ANY_KEY:
				goto EXIT;
			break;
		}
	} while(true);

EXIT:
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CMessageBox::Format(const char* pBuffer, ...)
{
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
