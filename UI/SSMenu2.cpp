// SSMenu2.cpp: implementation of the CSSMenu2 class.
//
//////////////////////////////////////////////////////////////////////

#include "SSMenu2.h"
#include "MenuItem.h"
//--------------------------------------------------------------------------------------------------

CSSMenu2::CSSMenu2() :
	m_itemCount(0),
	m_position(0),
	m_pParent((IMenu*)NULL)
{
	this->m_pItems = new CSSMenuItem[32];
}

//--------------------------------------------------------------------------------------------------

CSSMenu2::~CSSMenu2()
{
	delete[] this->m_pItems;
}

//--------------------------------------------------------------------------------------------------

IMenu* CSSMenu2::Draw()
{
	uchar key;
	int i = 0;
	int j = 0;
	char tmp[64] = "";
	char choice[4] = "";

	this->m_position = 0;
	TimerSet(TIMER_TEMPORARY,	400);

	int pageCount = this->m_itemCount / 6;
	int pageIndex = 0;
	int maxKey = 0;

	do {
		ScrCls();
		for (i = 0; i < 6; ++i) {
			if (((pageIndex * 6) + i) >= this->m_itemCount) {
				break;
			}
			ScrGotoxy(0, (i) * this->m_pItems[i + this->m_position].GetItemHeight());
			sprintf(tmp, "%d.%s", (i + 1), this->m_pItems[(pageIndex * 6) + i + this->m_position].GetItemText());
			Lcdprintf(tmp);
			maxKey = i + 1 + '0';
		}
				
		ScrGotoxy(5, 6);
		ScrFontSet(1);
		Lcdprintf("SECiM: ");
		Lcdprintf(choice);
		ScrFontSet(0);

		if (kbhit() != 0) {
			DelayMs(200);
			if (!TimerCheck(TIMER_TEMPORARY)) {
				return (IMenu*)NULL;//this->m_pParent;
			}
		}
		else {
			key = getkey();
			TimerSet(TIMER_TEMPORARY, 400);

			if (key <= '0' || key > maxKey) {
				if (key == KEY_DOWN		||
					key == KEY_UP		||
					key == KEY_ENTER	||
					key == KEY_CLEAR	||
					key == KEY_CANCEL	||
					key == KEY_A		||
					key == KEY_B		||
					key == KEY_C		||
					key == KEY_D) {
				}
				else {
					continue;
				}
			}
			else {
				choice[0] = key;
				choice[1] = 0x00;
			}

			switch(key) {
				case KEY_DOWN:
					if (pageIndex >= pageCount) {
					}
					else {
						++pageIndex;
					}
				break;
				case KEY_UP:
					if (pageIndex <= 0) {
					}
					else {
						--pageIndex;
					}
				break;
				case KEY_ENTER:
				{
					int index = (pageIndex * 6) + (choice[0] - '0') - 1;
					if (index < 0 || index > this->m_itemCount) {
						break;
					}
					MenuActionPtr pAction = this->m_pItems[index].GetAction();
					if (pAction != NULL) {
						pAction();
					}
					return this->m_pItems[index].GetNextMenu();
				}
				break;
				case KEY_CLEAR:
					choice[0] = 0x00;
				break;
				case KEY_CANCEL:
					choice[0] = 0x00;
					//if (this->m_pParent == (CSSMenu*)NULL) {
					//	return this;
					//}
					return this->m_pParent;
				break;
				case KEY_A: // Son slip tekrar bas
					islemSonSlipYaz();
				break;
				case KEY_B:
					islemShowToplamRapor();
				break;
				case KEY_C:
				break;
				case KEY_D:
				break;
			} // switch
		}
	} while(true);
	return this;
}

//--------------------------------------------------------------------------------------------------

int CSSMenu2::AddItem(CSSMenuItem* item)
{
	//! boy dinamik artacak

	this->m_pItems[this->m_itemCount++] = *item;
	return this->m_itemCount;
}

//--------------------------------------------------------------------------------------------------

void CSSMenu2::SetParent(IMenu* pMenu)
{
	this->m_pParent = pMenu;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
