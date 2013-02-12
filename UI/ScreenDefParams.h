// ScreenDefParams.h: interface for the CScreenDefParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENDEFPARAMS_H__FD7EF2C3_3CAD_4F55_8451_3FB1810971AD__INCLUDED_)
#define AFX_SCREENDEFPARAMS_H__FD7EF2C3_3CAD_4F55_8451_3FB1810971AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"
#include "..\globaldef.h"
#include "..\Files\Paramters.h"

class CScreenDefParams : public CScreen  
{
public:
	CScreenDefParams();
	virtual ~CScreenDefParams();
	virtual int Draw();
	void UpdateItem(int item);
private:
	CParamters m_param;
};

#endif // !defined(AFX_SCREENDEFPARAMS_H__FD7EF2C3_3CAD_4F55_8451_3FB1810971AD__INCLUDED_)
