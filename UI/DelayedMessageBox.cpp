#include "DelayedMessageBox.h"

//--------------------------------------------------------------------------------------------

CDelayedMessageBox::CDelayedMessageBox()
{

}

//--------------------------------------------------------------------------------------------

CDelayedMessageBox::CDelayedMessageBox(char* pMessage, unsigned char mode):
	CMessageBox(pMessage, mode)
{

}

//--------------------------------------------------------------------------------------------

CDelayedMessageBox::CDelayedMessageBox(char* pMessage, int delayTime, bool beeper) :
	CMessageBox(pMessage, MB_ANY_KEY)
{
	this->SetDelayTime(delayTime);
	this->m_bBeeper = beeper;
}

//--------------------------------------------------------------------------------------------
	
CDelayedMessageBox::CDelayedMessageBox(char* pMessage, int delayTime, bool beeper, unsigned char mode) :
	CMessageBox(pMessage, mode)
{
	this->SetDelayTime(delayTime);
	this->m_bBeeper = beeper;
}

//--------------------------------------------------------------------------------------------

CDelayedMessageBox::~CDelayedMessageBox()
{

}

//--------------------------------------------------------------------------------------------
#define TIMER_CLICK			5
#define TIMER_DELAYTIMEOUT	6

int CDelayedMessageBox::Draw()
{
	CScreen::Draw();

	TimerSet(TIMER_CLICK,			50);
	TimerSet(TIMER_DELAYTIMEOUT,	this->m_delayTime);

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
		if (kbhit() == 0) {
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
		}
		else {
			DelayMs(200);
			if (!TimerCheck(TIMER_CLICK)) {
				Beef(1, 100);
				TimerSet(TIMER_CLICK,			50);
			}
			if (!TimerCheck(TIMER_DELAYTIMEOUT)) {
				this->m_choice = CHOICE_NO;
				goto EXIT_TIMEOUT;
			}
		}
	} while(true);

EXIT:
	return SUCCESS;

EXIT_TIMEOUT:
	return USER_TIMEOUT;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
