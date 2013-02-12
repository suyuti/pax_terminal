// UIUtils.h: interface for the CUIUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIUTILS_H__268EFBE9_AA98_4A5A_9929_ED3506213253__INCLUDED_)
#define AFX_UIUTILS_H__268EFBE9_AA98_4A5A_9929_ED3506213253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"


#define NUM_MAXZHCHARS      16          
#define NUM_MAXCOLS         128         
#define NUM_MAXCOLNO        (NUM_MAXCOLS-1)
#define NUM_MAXLINES        8           
#define NUM_MAXLINENO       (NUM_MAXLINES-1)
#define NUM_MAXZHLINES      4           
#define NUM_MAXCHARS		21

#define DISP_LINE_LEFT		0x80
#define DISP_LINE_RIGHT		0x40
#define DISP_LINE_CENTER	0x20
#define DISP_SCR_CENTER		0x0100
#define DISP_LINE_REVER		0x0200
#define DISP_PART_REVER		0x0400



class CUIUtils  
{
public:
	CUIUtils();
	virtual ~CUIUtils();

	static void		PubDispString(void *pszStr, ushort nPosition);
	static bool		IsChar(uchar ch);
	static int		str2amt(const char *pAmt, char* pDest, int len);
	static char*	strrev(char* pSrc);
	static void		AnimOK(char *pszMsg);
	static void		AnimError(char *pszMsg);
private:
	static void		DispOkSub(uchar ucLogoNo);

};

#endif // !defined(AFX_UIUTILS_H__268EFBE9_AA98_4A5A_9929_ED3506213253__INCLUDED_)
