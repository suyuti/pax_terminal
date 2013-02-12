// ScreenBatchSum.h: interface for the CScreenBatchSum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENBATCHSUM_H__938646F0_2867_4170_A6B6_1A5EFA246887__INCLUDED_)
#define AFX_SCREENBATCHSUM_H__938646F0_2867_4170_A6B6_1A5EFA246887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"

class CSettleEngine;
class CScreenBatchSum : public CScreen  
{
public:
	CScreenBatchSum();
	virtual ~CScreenBatchSum();
	virtual int Draw();
	void Print();
private:
	CSettleEngine* pSettle;
};

#endif // !defined(AFX_SCREENBATCHSUM_H__938646F0_2867_4170_A6B6_1A5EFA246887__INCLUDED_)
