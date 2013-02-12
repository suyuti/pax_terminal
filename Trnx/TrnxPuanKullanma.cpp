// TrnxPuanKullanma.cpp: implementation of the CTrnxPuanKullanma class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxPuanKullanma.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanma::CTrnxPuanKullanma() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMA_LBL, strlen(TRNX_PUANKULLANMA_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanma;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanma::CTrnxPuanKullanma(CEngine* pEng) :
	CTrnxBase(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_PUANKULLANMA_LBL, strlen(TRNX_PUANKULLANMA_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanKullanma;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanKullanma::~CTrnxPuanKullanma()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxPuanKullanma::Do()
{
	CCardReader cardReader;

	CInputBox inAmount("P.HARCAMA\nTUTAR:", 5, 5, 6, CInputBox::itCurrency);

	if (inAmount.Draw() != CInputBox::retOK) {
		return GENERAL_FAILURE;
	}
	this->m_data.m_amount =  atoi(inAmount.GetBuffer());

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	if (cardReader.DoPuanKullanma(this->m_data.m_amount) != SUCCESS) {
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

void CTrnxPuanKullanma::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	sprintf(tmp, "%d", this->m_data.m_amount);
	CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
	PrnStr("KULLANILAN PUAN : %7s TL\n", tmp2);

	//Bcd2Str(this->m_data.m_loyaltyData.FBPoint1, 6, 0, tmp);
	//sprintf(tmp2, "%d", atoi(tmp));
	//CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
	//PrnStr("KALAN PUAN      : %10s TL\n", tmp);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
