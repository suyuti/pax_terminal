// TrnxKartGuncelle.h: interface for the CTrnxKartGuncelle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXKartGuncelle_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
#define AFX_TRNXKartGuncelle_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxKartGuncelle : public CTrnxBase  
{
private:
	CTrnxKartGuncelle();
public:
	CTrnxKartGuncelle(CEngine*);
	virtual ~CTrnxKartGuncelle();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };
	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXKartGuncelle_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
