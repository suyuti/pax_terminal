// TrnxHarcamaIptal.h: interface for the CTrnxHarcamaIptal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXHARCAMAIPTAL_H__5BD5202D_527F_4635_ADCE_B8A2F1D9DB80__INCLUDED_)
#define AFX_TRNXHARCAMAIPTAL_H__5BD5202D_527F_4635_ADCE_B8A2F1D9DB80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxHarcamaIptal : public CTrnxBase  
{
private:
	CTrnxHarcamaIptal();
public:
	CTrnxHarcamaIptal(CEngine*);
	virtual ~CTrnxHarcamaIptal();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };
	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXHARCAMAIPTAL_H__5BD5202D_527F_4635_ADCE_B8A2F1D9DB80__INCLUDED_)
