// ScreenTrnxLog.h: interface for the CScreenTrnxLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENTRNXLOG_H__1BD5F405_F1D5_4048_8F62_6F99465119F1__INCLUDED_)
#define AFX_SCREENTRNXLOG_H__1BD5F405_F1D5_4048_8F62_6F99465119F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"
#include "..\globaldef.h"
#include "..\Trnx\TrnxBase.h"

class CScreenTrnxLog : public CScreen  
{
public:
	CScreenTrnxLog();
	virtual ~CScreenTrnxLog();
	virtual int Draw();
	void ShowTrnx(CBatch::HBatchData hTrnx);
};

#endif // !defined(AFX_SCREENTRNXLOG_H__1BD5F405_F1D5_4048_8F62_6F99465119F1__INCLUDED_)
