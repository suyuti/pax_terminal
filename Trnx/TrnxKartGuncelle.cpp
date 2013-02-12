// TrnxKartGuncelle.cpp: implementation of the CTrnxKartGuncelle class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxKartGuncelle.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxKartGuncelle::CTrnxKartGuncelle() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_KARTGUNCELLE_LBL, strlen(TRNX_KARTGUNCELLE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxKartGuncelle;
	this->m_bTypeOnline = true;
}

//--------------------------------------------------------------------------------------------------

CTrnxKartGuncelle::CTrnxKartGuncelle(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_KARTGUNCELLE_LBL, strlen(TRNX_KARTGUNCELLE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxKartGuncelle;
	this->m_bTypeOnline = true;
}

//--------------------------------------------------------------------------------------------------

CTrnxKartGuncelle::~CTrnxKartGuncelle()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxKartGuncelle::Do()
{
	this->Print();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
