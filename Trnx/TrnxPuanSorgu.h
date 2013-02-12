// TrnxPuanSorgu.h: interface for the CTrnxPuanSorgu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
#define AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxPuanSorgu : public CTrnxBase  
{
private:
	CTrnxPuanSorgu();
public:
	CTrnxPuanSorgu(CEngine*);
	virtual ~CTrnxPuanSorgu();

	virtual int Do();
	virtual void Release() { delete this;};

	virtual void PrintBody();
};

#endif // !defined(AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
