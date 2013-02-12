// TrnxBakiyeSorgu.cpp: implementation of the CTrnxBakiyeSorgu class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxBakiyeSorgu.h"
#include "..\Engine\Engine.h"
#include "..\Engine\CardReader.h"

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeSorgu::CTrnxBakiyeSorgu() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_BAKIYESORGU_LBL, strlen(TRNX_BAKIYESORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxBakiyeSorgu;
	this->m_usesIslemNo = false;
}

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeSorgu::CTrnxBakiyeSorgu(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_BAKIYESORGU_LBL, strlen(TRNX_BAKIYESORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxBakiyeSorgu;
	this->m_usesIslemNo = false;
}

//--------------------------------------------------------------------------------------------------

CTrnxBakiyeSorgu::~CTrnxBakiyeSorgu()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxBakiyeSorgu::Do()
{
	CCardReader cardReader;

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);

	mb.Draw();

	if (cardReader.DoBakiyeSorgulama() != SUCCESS) {
		this->SetData(cardReader);
		//this->PrintErrorMessage(cardReader);
		this->ShowErrorMessage(cardReader);
		return GENERAL_FAILURE;
	}

	this->SetData(cardReader);

	this->Save();
		
	this->Print();

	this->AfterDone();

	return SUCCESS;
}
//--------------------------------------------------------------------------------------------------

void CTrnxBakiyeSorgu::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	Bcd2Str(this->m_data.m_prepaidData.Balance, 6, 0, tmp);
	sprintf(tmp2, "%d", atoi(tmp));
	CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
	PrnStr("BAKiYE        : %10s TL\n", tmp);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
