// TrnxBakiyeSorgu.h: interface for the CTrnxBakiyeSorgu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXBAKIYESORGU_H__95B0E9E0_ADF4_413B_B868_B9B5E2CD6357__INCLUDED_)
#define AFX_TRNXBAKIYESORGU_H__95B0E9E0_ADF4_413B_B868_B9B5E2CD6357__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxBakiyeSorgu : public CTrnxBase  
{
private:
	CTrnxBakiyeSorgu();
public:
	CTrnxBakiyeSorgu(CEngine*);
	virtual ~CTrnxBakiyeSorgu();

	virtual void PrintBody();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };
	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXBAKIYESORGU_H__95B0E9E0_ADF4_413B_B868_B9B5E2CD6357__INCLUDED_)
