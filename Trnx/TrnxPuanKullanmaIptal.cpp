// TrnxPuanKullanmaIptal.cpp: implementation of the CTrnxPuanKullanmaIptal class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxPuanKullanmaIptal.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIptal::CTrnxPuanKullanmaIptal() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMAIPTAL_LBL, strlen(TRNX_PUANKULLANMAIPTAL_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanmaIptal;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIptal::CTrnxPuanKullanmaIptal(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMAIPTAL_LBL, strlen(TRNX_PUANKULLANMAIPTAL_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanmaIptal;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanmaIptal::~CTrnxPuanKullanmaIptal()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxPuanKullanmaIptal::Do()
{
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
