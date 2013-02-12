// ScreenParams.cpp: implementation of the CScreenParams class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreenParams.h"
#include "..\Files\Terminal.h"
#include "..\Files\Acquier.h"
#include "..\Files\Paramters.h"

//------------------------------------------------------------------------------

CScreenParams::CScreenParams()
{

}

//------------------------------------------------------------------------------

CScreenParams::~CScreenParams()
{

}

//------------------------------------------------------------------------------

int CScreenParams::Draw()
{
	int i = 0;
	uchar key;

	do {
		CScreen::Clear();
		ScrFontSet(1);
		switch (i) {
			case 0:
				ScrGotoxy(1, 1);
				Lcdprintf("Terminal\n");
			break;
			case 1:
				ScrGotoxy(1, 1);
				Lcdprintf("Acquier\n");
			break;
			case 2:
				ScrGotoxy(1, 1);
				Lcdprintf("Issuier\n");
			break;
		}
		
		ScrFontSet(0);
		ScrGotoxy(1, 7);
		Lcdprintf("[CIKIS]      [YAZ]");
		ScrFontSet(0);

		key = getkey();
		switch(key) {
			case KEY_DOWN:
				if (i >= 2) {
					i = 0;
				}
				else {
					++i;
				}
			break;
			case KEY_UP:
				if (i <= 0) {
					i = 2;
				}
				else {
					--i;
				}
			break;
			case KEY_ENTER:
				this->Print(i);
			break;
			case KEY_CANCEL:
				goto EXIT;
			break;
		}
	} while(true);
EXIT:
	return SUCCESS;
}

//------------------------------------------------------------------------------

void CScreenParams::Print(int item)
{
	switch (item) {
		case 0: 
		{
			CTerminal term;
			if (term.Open()) {
				term.PrintAll();
				term.Close();
			}
		}
		break;
		case 1:
		{
			CAcquier* acq = new CAcquier();
			if (acq->Open()) {
				acq->PrintAll();
				acq->Close();
			}
			else {
				PRNLINE("Dosya acilamadi!...");
			}
			delete acq;
		}
		break;
		case 2:
		break;
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
