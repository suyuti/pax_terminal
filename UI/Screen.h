// Screen.h: interface for the CScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREEN_H__FD262297_F388_49BF_AC08_95694B02162A__INCLUDED_)
#define AFX_SCREEN_H__FD262297_F388_49BF_AC08_95694B02162A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <posapi.h>
#include <posapi_all.h>

class CScreen  
{
public:
	CScreen();
	virtual ~CScreen();
	virtual int Draw();
	virtual void DrawLogo(unsigned char* pLogo);
	virtual void Clear();
};

#endif // !defined(AFX_SCREEN_H__FD262297_F388_49BF_AC08_95694B02162A__INCLUDED_)
