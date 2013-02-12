// Menu.h: interface for the CMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENU_H__785012DB_54F7_4881_A208_560EBDA55B66__INCLUDED_)
#define AFX_MENU_H__785012DB_54F7_4881_A208_560EBDA55B66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <posapi.h>
#include <posapi_all.h>

#include "MenuItem.h"
#include "IMenu.h"

class CSSMenu : public IMenu
{
public:
	CSSMenu();
	virtual ~CSSMenu();

	virtual int		AddItem(CSSMenuItem* item);
	virtual void	SetParent(IMenu*);
	virtual IMenu*	Draw();
	//int AddItem(CSSMenuItem& item);
	//void SetParent(CSSMenu*);
	//virtual CSSMenu* Draw();

private:
	IMenu*			m_pParent;
	CSSMenuItem*	m_pItems;
	int				m_itemCount;
	int				m_position;
};

#endif // !defined(AFX_MENU_H__785012DB_54F7_4881_A208_560EBDA55B66__INCLUDED_)
