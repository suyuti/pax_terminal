// Issuer.h: interface for the CIssuer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISSUER_H__FF7A1789_F41E_48D9_ADDF_A1C7AFB059F1__INCLUDED_)
#define AFX_ISSUER_H__FF7A1789_F41E_48D9_ADDF_A1C7AFB059F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

#define TABLE_NAME_ISSUER "issuer.txt"

class CIssuer : public CTable  
{
public:
	CIssuer();
	virtual ~CIssuer();
	virtual int Append();
	virtual void PrintAll();

	typedef enum {
	} IssuerSizes;
	typedef struct _tagIssuerData {
	
	} IssuerData, *HIssuerData;
private:
	IssuerData m_data;
};

#endif // !defined(AFX_ISSUER_H__FF7A1789_F41E_48D9_ADDF_A1C7AFB059F1__INCLUDED_)
