// MessageBox.h: interface for the CMessageBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEBOX_H__7932334A_53D6_45D6_9F86_70B10A1552DD__INCLUDED_)
#define AFX_MESSAGEBOX_H__7932334A_53D6_45D6_9F86_70B10A1552DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "Screen.h"

#define MB_SHOW_ONLY	0x01
#define MB_ANY_KEY		0x02
#define MB_YES_NO		0x04

#define CHOICE_YES			1
#define CHOICE_NO			2

class CMessageBox : public CScreen  
{
public:
	CMessageBox();
	CMessageBox(char* pMessage, unsigned char mode = MB_ANY_KEY);
	virtual ~CMessageBox();
	inline void SetMessage(const char* pMsg) { strncpy(this->m_message, pMsg, strlen(pMsg)); this->m_message[strlen(pMsg)] = 0x00;};

	virtual int Draw();
	int Format(const char*, ...);
	inline int GetSelect() { return this->m_choice;};

protected:
	char			m_message[255];
	unsigned char	m_mode;
	int				m_choice;
};

#endif // !defined(AFX_MESSAGEBOX_H__7932334A_53D6_45D6_9F86_70B10A1552DD__INCLUDED_)
