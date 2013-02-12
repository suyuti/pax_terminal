// SSMenu2.h: interface for the CSSMenu2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSMENU2_H__76D734D1_5B87_4FA4_8920_4B6E0EEA3B51__INCLUDED_)
#define AFX_SSMENU2_H__76D734D1_5B87_4FA4_8920_4B6E0EEA3B51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "IMenu.h"

class CSSMenu2 : public IMenu
{
public:
	CSSMenu2();
	virtual ~CSSMenu2();

	virtual int		AddItem(CSSMenuItem* item);
	virtual void	SetParent(IMenu*);
	virtual IMenu*	Draw();
	

private:
	IMenu*			m_pParent;
	CSSMenuItem*	m_pItems;
	int				m_itemCount;
	int				m_position;

};

#endif // !defined(AFX_SSMENU2_H__76D734D1_5B87_4FA4_8920_4B6E0EEA3B51__INCLUDED_)
