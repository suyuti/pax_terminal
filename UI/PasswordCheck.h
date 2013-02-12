// PasswordCheck.h: interface for the CPasswordCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSWORDCHECK_H__8C59D86E_0A90_4608_9EFB_6C1F08A9B666__INCLUDED_)
#define AFX_PASSWORDCHECK_H__8C59D86E_0A90_4608_9EFB_6C1F08A9B666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPasswordCheck  
{
public:
	CPasswordCheck();
	virtual ~CPasswordCheck();
	typedef enum {
		passVoid,
		passSettle,
		passMerchant,
		passRefund,
		passReport,

		passDeveloper,
	} PassCheckTypes;

	int Check(PassCheckTypes type);
};

#endif // !defined(AFX_PASSWORDCHECK_H__8C59D86E_0A90_4608_9EFB_6C1F08A9B666__INCLUDED_)
