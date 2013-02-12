// Menu.cpp: implementation of the CSSMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "Menu.h"
#include <posapi.h>
#include <posapi_all.h>

//--------------------------------------------------------------------------------------------------

CSSMenu::CSSMenu() :
	m_itemCount(0),
	m_position(0),
	m_pParent((IMenu*)NULL)
{
	this->m_pItems = new CSSMenuItem[32];
}

//--------------------------------------------------------------------------------------------------

CSSMenu::~CSSMenu()
{
	delete[] this->m_pItems;
}

//--------------------------------------------------------------------------------------------------

IMenu* CSSMenu::Draw()
{
	uchar key;
	int i = 0;
	int j = 0;

	this->m_position = 0;
	TimerSet(TIMER_TEMPORARY, 100);

	do {
		ScrCls();
		for (i = 0; (i < this->m_itemCount) && (i < 4); ++i) {
			ScrGotoxy(0, (i) * this->m_pItems[i + this->m_position].GetItemHeight());
			Lcdprintf(this->m_pItems[i + this->m_position].GetItemText());
		}

		ScrDrawRect(0, (j * (8*ITEM_HEIGHT)), 120, (j * (8*ITEM_HEIGHT)) + (8*ITEM_HEIGHT));
		//key = getkey();

		if (kbhit() != 0) {
			DelayMs(100);
			if (!TimerCheck(TIMER_TEMPORARY)) {
				return (CSSMenu*)NULL;//this->m_pParent;
			}
		}
		else {
			key = getkey();
			TimerSet(TIMER_TEMPORARY, 100);
			//for (i = 0; i < this->m_itemCount; ++i) {
			//	if (key == this->m_pItems[i].GetEventKey()) {
			//		return this->m_pItems[i].GetNextMenu();
			//	}
			//}

			switch(key) {
				case KEY_DOWN:
					if (j < 3 && j < (this->m_itemCount - 1)) {
						++j;
					}
					else {
						if (this->m_position + j < this->m_itemCount - 1) {
							++this->m_position;
						}
					}
				break;
				case KEY_UP:
					if (j > 0) {
						--j;
					}
					else {
						if (this->m_position > 0) {
							--this->m_position;
						}
					}
				break;
				case KEY_ENTER:
				{
					MenuActionPtr pAction = this->m_pItems[this->m_position + j].GetAction();
					if (pAction != NULL) {
						pAction();
					}
					return this->m_pItems[this->m_position + j].GetNextMenu();
				}
				break;
				case KEY_CANCEL:
					//if (this->m_pParent == (CSSMenu*)NULL) {
					//	return this;
					//}
					return this->m_pParent;
				break;
				case KEY_A: // Son slip tekrar bas
					islemSonSlipYaz();
				break;
				case KEY_B:
				break;
				case KEY_C:
				break;
				case KEY_D:
				break;
			}
		}
	} while(true);
//EXIT:

//	key = getkey();
//	for (i = 0; i < this->m_itemCount; ++i) {
//		if (key == this->m_pItems[i].GetEventKey()) {
//			return this->m_pItems[i].GetNextMenu();
//		}
//	}
	return this;
}

//--------------------------------------------------------------------------------------------------

int CSSMenu::AddItem(CSSMenuItem* item)
{
	//! boy dinamik artacak

	this->m_pItems[this->m_itemCount++] = *item;
	return this->m_itemCount;
}

//--------------------------------------------------------------------------------------------------

void CSSMenu::SetParent(IMenu* pMenu)
{
	this->m_pParent = pMenu;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
