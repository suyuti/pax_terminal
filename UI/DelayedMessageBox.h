// DelayedMessageBox.h: interface for the CDelayedMessageBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAYEDMESSAGEBOX_H__CADE9949_6EB8_4F36_BEF2_F2E9C3F2AB66__INCLUDED_)
#define AFX_DELAYEDMESSAGEBOX_H__CADE9949_6EB8_4F36_BEF2_F2E9C3F2AB66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageBox.h"

class CDelayedMessageBox : public CMessageBox  
{
public:
	CDelayedMessageBox();
	CDelayedMessageBox(char* pMessage, unsigned char mode = MB_ANY_KEY);
	CDelayedMessageBox(char* pMessage, int delayTime, bool beeper);
	CDelayedMessageBox(char* pMessage, int delayTime, bool beeper, unsigned char mode = MB_ANY_KEY);
	virtual ~CDelayedMessageBox();

	virtual int Draw();
	inline void SetBeeper(bool bBeeper) { this->m_bBeeper = bBeeper;		};
	inline void SetDelayTime(int delay) { this->m_delayTime = delay * 1000;	};

private:
	bool	m_bBeeper;
	int		m_delayTime; //ms
};

#endif // !defined(AFX_DELAYEDMESSAGEBOX_H__CADE9949_6EB8_4F36_BEF2_F2E9C3F2AB66__INCLUDED_)
