// TrnxPuanKullanma.h: interface for the CTrnxPuanKullanma class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXPUANKULLANMA_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
#define AFX_TRNXPUANKULLANMA_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"

#define TRNX_PUANKULLANMA_LBL	"Puan Kullanma"

class CEngine;
class CTrnxPuanKullanma : public CTrnxBase  
{
private:
	CTrnxPuanKullanma();
public:
	CTrnxPuanKullanma(CEngine*);
	virtual ~CTrnxPuanKullanma();

	virtual int Do();
	virtual int DoVoid()	{ return SUCCESS; };
	virtual void Release()	{ delete this;};
	virtual void PrintBody();

};

#endif // !defined(AFX_TRNXPUANKULLANMA_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
