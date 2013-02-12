// TrnxPuanKullanmaIade.cpp: implementation of the CTrnxPuanKullanmaIade class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxPuanKullanmaIade.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIade::CTrnxPuanKullanmaIade() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMAIADE_LBL, strlen(TRNX_PUANKULLANMAIADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanmaIade;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIade::CTrnxPuanKullanmaIade(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMAIADE_LBL, strlen(TRNX_PUANKULLANMAIADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanmaIade;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIade::~CTrnxPuanKullanmaIade()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxPuanKullanmaIade::Do()
{
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
