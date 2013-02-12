// TrnxHarcamaIade.h: interface for the CTrnxHarcamaIade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXHARCAMAIADE_H__CD95F4CC_46FC_48C3_9622_57EFD866CE9D__INCLUDED_)
#define AFX_TRNXHARCAMAIADE_H__CD95F4CC_46FC_48C3_9622_57EFD866CE9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CTrnxHarcamaIade : public CTrnxBase  
{
private:
	CTrnxHarcamaIade();
public:
	CTrnxHarcamaIade(CEngine*);
	virtual ~CTrnxHarcamaIade();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };

	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXHARCAMAIADE_H__CD95F4CC_46FC_48C3_9622_57EFD866CE9D__INCLUDED_)
