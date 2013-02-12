// TrnxOnline.h: interface for the CTrnxOnline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXONLINE_H__CD99D919_AE40_4786_88B6_CB333FDF0586__INCLUDED_)
#define AFX_TRNXONLINE_H__CD99D919_AE40_4786_88B6_CB333FDF0586__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TrnxBase.h"
#include "..\Engine\OnlineEngine.h"

class CEngine;
class CTrnxOnline : public CTrnxBase  
{
public:
	CTrnxOnline();
	CTrnxOnline(CEngine*);
	virtual ~CTrnxOnline();

	virtual int Do();
	virtual int OnBeforeOnline();

	virtual int OnApproved();

protected:
	unsigned char	m_cardNo[32];
	char			m_inputTypeLabel[32]; // Tutar girilirken gosterilecek islem tipi
	COnlineEngine	online;
	int					m_ScriptBalance;
	int					m_ScriptPoint;
	bool				m_bLoadBalanceToCard;
	bool				m_bLoadPointToCard;	
};

#endif // !defined(AFX_TRNXONLINE_H__CD99D919_AE40_4786_88B6_CB333FDF0586__INCLUDED_)
