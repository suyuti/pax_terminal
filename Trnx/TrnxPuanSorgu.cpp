// TrnxPuanSorgu.cpp: implementation of the CTrnxPuanSorgu class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxPuanSorgu.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorgu::CTrnxPuanSorgu() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_PUANSORGU_LBL, strlen(TRNX_PUANSORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanSorgu;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorgu::CTrnxPuanSorgu(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_PUANSORGU_LBL, strlen(TRNX_PUANSORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanSorgu;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorgu::~CTrnxPuanSorgu()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxPuanSorgu::Do()
{
	CCardReader cardReader;

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	if (cardReader.DoPuanSorgulama() != SUCCESS) {
		return GENERAL_FAILURE;
	}
	this->SetData(cardReader);

	this->Save();
		
	this->Print();

	this->AfterDone();

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void CTrnxPuanSorgu::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	//PrnStr("PUAN          : %d\n", this->m_data.m_lo);

	Bcd2Str(this->m_data.m_loyaltyData.FBPoint1, 6, 0, tmp);
	sprintf(tmp2, "%d", atoi(tmp));
	CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
	PrnStr("PUAN        : %10s TL\n", tmp);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
