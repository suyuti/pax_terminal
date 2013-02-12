// Issuer.cpp: implementation of the CIssuer class.
//
//////////////////////////////////////////////////////////////////////

#include "Issuer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIssuer::CIssuer() :
	CTable((void*)&m_data)
{
	this->m_recordSize = sizeof(CIssuer::IssuerData);
	sprintf(this->m_fileName, "%s", TABLE_NAME_ISSUER);
}

CIssuer::~CIssuer()
{

}

int CIssuer::Append()
{
	return SUCCESS;
}

void CIssuer::PrintAll()
{
}
