// IdleDlg.h: interface for the CIdleDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDLEDLG_H__49587CED_F898_4A7C_813C_17F42E802C67__INCLUDED_)
#define AFX_IDLEDLG_H__49587CED_F898_4A7C_813C_17F42E802C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "Screen.h"

class CIdleDlg : public CScreen  
{
public:
	CIdleDlg();
	virtual ~CIdleDlg();

	virtual int Draw();
	void SetMessage1(const char*);
	void SetMessage2(const char*);

private:
	char m_idleMessage_1[255];
	char m_idleMessage_2[255];
	static unsigned char ms_pLogo[];

};

#endif // !defined(AFX_IDLEDLG_H__49587CED_F898_4A7C_813C_17F42E802C67__INCLUDED_)
