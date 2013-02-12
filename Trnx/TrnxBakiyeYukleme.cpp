// TrnxBakiyeYukleme.cpp: implementation of the CTrnxBakiyeYukleme class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxBakiyeYukleme.h"
#include "..\UI\InputBox.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeYukleme::CTrnxBakiyeYukleme() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_BAKIYEYUKLEME_LBL, strlen(TRNX_BAKIYEYUKLEME_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxBakiyeYukleme;
	this->m_bTypeOnline = true;
}

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeYukleme::CTrnxBakiyeYukleme(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_BAKIYEYUKLEME_LBL, strlen(TRNX_BAKIYEYUKLEME_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxBakiyeYukleme;
	this->m_bTypeOnline = true;
}

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeYukleme::~CTrnxBakiyeYukleme()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxBakiyeYukleme::Do()
{

	CInputBox inputTutar("Tutar Giriniz:", 4, 2, 6, CInputBox::itNumeric);
	inputTutar.Draw();

	this->Print();
	
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
