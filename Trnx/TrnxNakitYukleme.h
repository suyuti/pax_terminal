// TrnxNakitYukleme.h: interface for the CTrnxNakitYukleme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXNAKITYUKLEME_H__F095EA05_D094_4DDB_B736_3D49735682EA__INCLUDED_)
#define AFX_TRNXNAKITYUKLEME_H__F095EA05_D094_4DDB_B736_3D49735682EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxOnline.h"


class CTrnxNakitYukleme : public CTrnxOnline
{
private:
	CTrnxNakitYukleme();
public:
	CTrnxNakitYukleme(CEngine*);
	virtual ~CTrnxNakitYukleme();

	virtual void Release() { delete this;};
	virtual void PrintBody();

protected:
	//virtual int		OnApproved();
	virtual int		OnVoid();
};

#endif // !defined(AFX_TRNXNAKITYUKLEME_H__F095EA05_D094_4DDB_B736_3D49735682EA__INCLUDED_)
