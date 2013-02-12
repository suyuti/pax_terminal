// MenuItem.h: interface for the CMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUITEM_H__D3119188_4E8C_400E_AD13_5F2F0BDE5DB2__INCLUDED_)
#define AFX_MENUITEM_H__D3119188_4E8C_400E_AD13_5F2F0BDE5DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"

//#define ITEM_HEIGHT				2
#define ITEM_HEIGHT				1
#define DEFAULT_EVENTKEY		0x00

typedef void (*MenuActionPtr)(void);

//class CSSMenu;
class IMenu;
class CSSMenuItem  
{
public:
	CSSMenuItem();
	CSSMenuItem(const char* pItemText, MenuActionPtr fpAction, IMenu* pNextMenu);
	virtual ~CSSMenuItem();
	CSSMenuItem& operator=(const CSSMenuItem& other);


	void			SetValues(const char* pItemText, int eventKey, MenuActionPtr fpAction, IMenu* pNextMenu);

	void			SetItemText(const char* pItemText);
	char*			GetItemText();

	void			SetAction(MenuActionPtr pAction);
	MenuActionPtr	GetAction();

	void			SetNextMenu(IMenu* pNextMenu);
	IMenu*			GetNextMenu();

	inline void		SetItemHeight(int height)	{ this->m_itemHeight = height;	}
	inline int		GetItemHeight()				{ return this->m_itemHeight;	}

	inline	void	SetEventKey(int key)		{ this->m_eventKey = key;		}
	inline	int		GetEventKey()				{ return this->m_eventKey;		}

private:
	char*			m_itemText[32];
	MenuActionPtr	m_fpAction;
	IMenu*			m_pNextMenu;
	int				m_itemHeight;
	int				m_eventKey;
};

#endif // !defined(AFX_MENUITEM_H__D3119188_4E8C_400E_AD13_5F2F0BDE5DB2__INCLUDED_)
