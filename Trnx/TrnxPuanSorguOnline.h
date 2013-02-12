// TrnxPuanSorgu.h: interface for the CTrnxPuanSorguOnline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
#define AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
//#include "TrnxBase.h"
#include "TrnxOnline.h"


class CEngine;
class CTrnxPuanSorguOnline : public CTrnxOnline
{
private:
	CTrnxPuanSorguOnline();
public:
	CTrnxPuanSorguOnline(CEngine*);
	virtual ~CTrnxPuanSorguOnline();

	virtual int DoVoid()			{ return SUCCESS;		};
	virtual void Release()			{ delete this;			};
	virtual int OnBeforeOnline();
	virtual int OnApproved();		

	virtual void PrintBody();

private:
	char m_pointValue[21];
};

#endif // !defined(AFX_TRNXPuanSorgu_H__B326C95A_4107_4509_B0A9_CDC95EC884EE__INCLUDED_)
