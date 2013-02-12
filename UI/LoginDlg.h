// LoginDlg.h: interface for the CLoginDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINDLG_H__5D654DDD_394A_4F9C_8190_093B15E05032__INCLUDED_)
#define AFX_LOGINDLG_H__5D654DDD_394A_4F9C_8190_093B15E05032__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "Screen.h"

class CLoginDlg : public CScreen  
{
public:
	CLoginDlg();
	virtual ~CLoginDlg();
	
	virtual int Draw();

};

#endif // !defined(AFX_LOGINDLG_H__5D654DDD_394A_4F9C_8190_093B15E05032__INCLUDED_)
