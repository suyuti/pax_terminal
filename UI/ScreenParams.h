// ScreenParams.h: interface for the CScreenParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENPARAMS_H__28479066_3D3D_4CD4_BB25_5344BD4B1FA3__INCLUDED_)
#define AFX_SCREENPARAMS_H__28479066_3D3D_4CD4_BB25_5344BD4B1FA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"
#include "..\globaldef.h"

class CScreenParams : public CScreen  
{
public:
	CScreenParams();
	virtual ~CScreenParams();
	virtual int Draw();
	void Print(int item);
};

#endif // !defined(AFX_SCREENPARAMS_H__28479066_3D3D_4CD4_BB25_5344BD4B1FA3__INCLUDED_)
