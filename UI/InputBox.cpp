// InputBox.cpp: implementation of the CInputBox class.
//
//////////////////////////////////////////////////////////////////////

#include "InputBox.h"
#include "UIUtils.h"

//--------------------------------------------------------------------------------------------------

CInputBox::CInputBox() : 
	m_size(0),
	m_x(0),
	m_y(0),
	m_inputType(itNumeric)
{
}

//--------------------------------------------------------------------------------------------------

CInputBox::~CInputBox()
{

}

//--------------------------------------------------------------------------------------------------

CInputBox::CInputBox(const char* pLabel, int x, int y, int size, InputTypes type) :
	m_x(x),
	m_y(y),
	m_size(size),
	m_inputType(type)
{
	memset(this->m_label, 0x00, sizeof(this->m_label));
	memset(this->m_buffer, 0x00, sizeof(this->m_buffer));
	strncpy(this->m_label, pLabel, strlen(pLabel));
}

//--------------------------------------------------------------------------------------------------

int CInputBox::Draw()
{
	uchar key, lastKey;
	int pos = 0;
	int retVal = 0;
	static char tmp[255] = "";
	int mapIndex;
	int alphaHit = 0;

	char *pCharMap[] = {
		"QZ.1", "ABC2", "DEF3",
		"GHI4", "JKL5", "MNO6",
		"PRS7", "TUV8", "WXY9",
		",'\" ",",*#0", "###0"
	};


	CScreen::Draw();
	ScrFontSet(1);

	ScrGotoxy(1, 1);
	Lcdprintf(this->m_label);

	ScrGotoxy(m_x, m_y);

	memset(this->m_buffer, 0x00, sizeof(this->m_buffer));
	do {
		key = getkey();
		if (CUIUtils::IsChar(key)) {
			if (pos >= this->m_size) {
				continue;
			}
			this->m_buffer[pos++] = key;
			this->m_buffer[pos] = 0x00;
		}
		if (pos >= sizeof(this->m_buffer)) {
			continue;
		}

		switch (key) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '*':
				lastKey = key;
				break;
			case KEY_ENTER:
				this->m_count = pos;
				retVal = retOK;
				goto EXIT;
			break;
			case KEY_CANCEL:
				retVal = retCancel;
				goto EXIT;
			break;
			case KEY_CLEAR:
				if (pos > 0) {
					this->m_buffer[--pos] = 0x00;
				}
			break;
		}

		CScreen::Clear();
		ScrGotoxy(1, 1);
		Lcdprintf(this->m_label);

		ScrGotoxy(m_x, m_y);
		switch (this->m_inputType) {
			case itPassword:
			{
				memset(tmp, '*', strlen(this->m_buffer));
				tmp[strlen(this->m_buffer)] = 0x00;
			}
			break;
			case itNumeric:
				memcpy(tmp, this->m_buffer, pos);
				tmp[pos] = 0x00;
			break;
			case itAlphaNumeric:
			{
				if (key == KEY_ALPHA) {
					switch(lastKey) {
						case '0': mapIndex = 10;break;
						case '1': mapIndex = 0;	break;
						case '2': mapIndex = 1;	break;
						case '3': mapIndex = 2;	break;
						case '4': mapIndex = 3;	break;
						case '5': mapIndex = 4;	break;
						case '6': mapIndex = 5;	break;
						case '7': mapIndex = 6;	break;
						case '8': mapIndex = 7;	break;
						case '9': mapIndex = 8;	break;
						case '*': mapIndex = 9;	break;
						case '#': mapIndex = 11;break;
					}
					this->m_buffer[pos - 1] = pCharMap[mapIndex][alphaHit];
					if (alphaHit >= 3) {
						alphaHit = 0;
					}
					else {
						++alphaHit;
					}
				}
				else {
					alphaHit = 0;
				}
				memcpy(tmp, this->m_buffer, pos);
				tmp[pos] = 0x00;
			}

			break;
			case itCurrency:
				CUIUtils::str2amt(this->m_buffer, tmp, strlen(this->m_buffer));
				strcat(tmp, " TL");
			break;
		}
		Lcdprintf(tmp);
	} while(true);

EXIT:
	ScrFontSet(0);
	return retVal;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
