// TrnxBakiyeYukleme.h: interface for the CTrnxBakiyeYukleme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXBAKIYEYUKLEME_H__F2E3876F_137A_48E1_B632_2CF69474048B__INCLUDED_)
#define AFX_TRNXBAKIYEYUKLEME_H__F2E3876F_137A_48E1_B632_2CF69474048B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"


class CEngine;
class CTrnxBakiyeYukleme : public CTrnxBase  
{
private:
	CTrnxBakiyeYukleme();
public:
	CTrnxBakiyeYukleme(CEngine*);
	virtual ~CTrnxBakiyeYukleme();

	virtual int Do();
	virtual int DoVoid() { return SUCCESS; };
	virtual void Release() { delete this;};
};

#endif // !defined(AFX_TRNXBAKIYEYUKLEME_H__F2E3876F_137A_48E1_B632_2CF69474048B__INCLUDED_)
