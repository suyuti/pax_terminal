// TrnxPuanSorguOnline.cpp: implementation of the CTrnxPuanSorguOnline class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxPuanSorguOnline.h"
#include "..\Engine\Engine.h"

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorguOnline::CTrnxPuanSorguOnline() :
	CTrnxOnline((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_PUANSORGU_LBL, strlen(TRNX_PUANSORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanSorgu;
	//this->m_usesIslemNo = false;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorguOnline::CTrnxPuanSorguOnline(CEngine* pEng) :
	CTrnxOnline(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_PUANSORGU_LBL, strlen(TRNX_PUANSORGU_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxPuanSorgu;
	//this->m_usesIslemNo = false;
}

//--------------------------------------------------------------------------------------------------

CTrnxPuanSorguOnline::~CTrnxPuanSorguOnline()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxPuanSorguOnline::OnBeforeOnline()
{
	int size = 0;
	char tmp[128] = "";
	int ret = 0;
	CCardReader cardReader;

	//this->online.SetSaveAfterConnction(true);
	this->online.SetFinancial(false);
	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	// 2. Kart okunur
	this->m_error = cardReader.ReadCardData();
	if (this->m_error != SUCCESS) {
		this->ShowErrorMessage(cardReader);
		return GENERAL_FAILURE;
	}
	this->SetData(cardReader);
	memcpy(this->m_cardNo, cardReader.GetFanData()->CardNumber, 16);

	return SUCCESS;		
}
/*
//--------------------------------------------------------------------------------------------------

int CTrnxPuanSorguOnline::Do()
{
	CCardReader cardReader;

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	if (cardReader.DoPuanSorgulama() != SUCCESS) {
		this->ShowErrorMessage(cardReader);
		return GENERAL_FAILURE;
	}
	this->SetData(cardReader);

	this->Save();
		
	this->Print();

	this->AfterDone();

	return SUCCESS;
}
*/
//--------------------------------------------------------------------------------------------------

void CTrnxPuanSorguOnline::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";
	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();

	//PrnStr("PUAN          : %d\n", this->m_data.m_lo);

	if (this->m_data.m_responseCode == 0) {
		sprintf(tmp2, "%d", atoi(this->m_pointValue));
		CUIUtils::str2amt(tmp2, this->m_pointValue, strlen(tmp2));
		PrnStr("PUAN        : %10s TL\n", this->m_pointValue);
	}
	else {
		pEng->PrnSetBig();
		PrnStr("     Islem\n  Reddedildi.\n");
		PrnStr("   HATA [%d]\n", this->m_data.m_responseCode);
		PrnStr("\n%s\n", this->m_data.m_responseMsgPrn);
	}
}

int CTrnxPuanSorguOnline::OnApproved()		
{ 	
	int		size		= 0;
	int		ret = -1;
	
	memset(this->m_pointValue, 0x00, sizeof(this->m_pointValue));
	ret = this->online.GetResponseMsgPDS20(this->m_pointValue, &size);
	if(ret != SUCCESS)
		return ret;
		
	return SUCCESS;		
}		
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
