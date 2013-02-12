// TrnxHarcama.h: interface for the CTrnxHarcama class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXHARCAMA_H__8D054AEB_6F6D_4FA1_AA36_8F887021448F__INCLUDED_)
#define AFX_TRNXHARCAMA_H__8D054AEB_6F6D_4FA1_AA36_8F887021448F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"

class CEngine;
class CTrnxHarcama : public CTrnxBase  
{
private:
	CTrnxHarcama();
public:
	CTrnxHarcama(CEngine*);
	virtual ~CTrnxHarcama();

	virtual void	PrintBody();
	virtual int		Do();
	virtual void	Release() { delete this;};
protected:
	virtual int		OnVoid();

};

#endif // !defined(AFX_TRNXHARCAMA_H__8D054AEB_6F6D_4FA1_AA36_8F887021448F__INCLUDED_)
