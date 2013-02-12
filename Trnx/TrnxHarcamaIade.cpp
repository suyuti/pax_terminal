// TrnxHarcamaIade.cpp: implementation of the CTrnxHarcamaIade class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxHarcamaIade.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIade::CTrnxHarcamaIade() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_HARCAMAIADE_LBL, strlen(TRNX_HARCAMAIADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcamaIade;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIade::CTrnxHarcamaIade(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_HARCAMAIADE_LBL, strlen(TRNX_HARCAMAIADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcamaIade;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcamaIade::~CTrnxHarcamaIade()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxHarcamaIade::Do()
{
	return SUCCESS;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
