// InputBox.h: interface for the CInputBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTBOX_H__7BF8DCD7_CA74_4125_A504_DDDE82073762__INCLUDED_)
#define AFX_INPUTBOX_H__7BF8DCD7_CA74_4125_A504_DDDE82073762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "Screen.h"

class CInputBox : CScreen
{
public:
	typedef enum {
		itNumeric = 0,
		itAlphaNumeric,
		itPassword,
		itCurrency,
		itIP,
	} InputTypes;

	typedef enum {
		retOK = 0,
		retCancel,
		retTimeout,
	} ReturnTypes;

protected:
	CInputBox();
public:
	CInputBox(const char* pLabel, int x, int y, int size, InputTypes type);
	virtual ~CInputBox();


	virtual int Draw();
	inline char* GetBuffer()	{ return this->m_buffer;	};
	inline int GetSize()		{ return this->m_count;		};

private:
	char		m_label[64];
	char		m_buffer[255];
	int			m_size;
	InputTypes	m_inputType;
	int			m_x;
	int			m_y;
	int			m_count;
};

#endif // !defined(AFX_INPUTBOX_H__7BF8DCD7_CA74_4125_A504_DDDE82073762__INCLUDED_)
