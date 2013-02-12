// TrnxHarcamaIptal.cpp: implementation of the CTrnxHarcamaIptal class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxHarcamaIptal.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIptal::CTrnxHarcamaIptal() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_HARCAMAIPTAL_LBL, strlen(TRNX_HARCAMAIPTAL_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcamaIptal;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIptal::CTrnxHarcamaIptal(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_HARCAMAIPTAL_LBL, strlen(TRNX_HARCAMAIPTAL_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcamaIptal;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIptal::~CTrnxHarcamaIptal()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxHarcamaIptal::Do()
{
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
