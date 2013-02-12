// KrediKartYukleme.h: interface for the CKrediKartYukleme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KREDIKARTYUKLEME_H__02A98F77_6AF5_41D7_9F5D_B0B847A7FF40__INCLUDED_)
#define AFX_KREDIKARTYUKLEME_H__02A98F77_6AF5_41D7_9F5D_B0B847A7FF40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxOnline.h"

class CEngine;
class CTrnxKrediKartYukleme : public CTrnxOnline 
{
private:
	CTrnxKrediKartYukleme();
public:
	CTrnxKrediKartYukleme(CEngine*);
	virtual ~CTrnxKrediKartYukleme();

	virtual void	PrintBody();
	virtual void	Release() { delete this;};
protected:
	//virtual int		OnApproved();
	virtual int		OnVoid();
};

#endif // !defined(AFX_KREDIKARTYUKLEME_H__02A98F77_6AF5_41D7_9F5D_B0B847A7FF40__INCLUDED_)
