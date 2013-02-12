// DebitYukleme.h: interface for the CDebitYukleme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBITYUKLEME_H__AA331FD0_0C4C_49C3_B638_D1668084E0FF__INCLUDED_)
#define AFX_DEBITYUKLEME_H__AA331FD0_0C4C_49C3_B638_D1668084E0FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxOnline.h"

class CEngine;
class CTrnxDebitYukleme : public CTrnxOnline
{
private:
	CTrnxDebitYukleme();
public:
	CTrnxDebitYukleme(CEngine*);
	virtual ~CTrnxDebitYukleme();

	virtual void	PrintBody();
	//virtual int		Do();
	virtual void	Release() { delete this;};
protected:
	//virtual int		OnApproved();
	virtual int		OnVoid();
};

#endif // !defined(AFX_DEBITYUKLEME_H__AA331FD0_0C4C_49C3_B638_D1668084E0FF__INCLUDED_)
