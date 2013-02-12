// TrnxPuanKullanmaIptal.h: interface for the CTrnxPuanKullanmaIptal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXPuanKullanmaIptal_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
#define AFX_TRNXPuanKullanmaIptal_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxPuanKullanmaIptal : public CTrnxBase  
{
private:
	CTrnxPuanKullanmaIptal();
public:
	CTrnxPuanKullanmaIptal(CEngine*);
	virtual ~CTrnxPuanKullanmaIptal();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };
	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXPuanKullanmaIptal_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
