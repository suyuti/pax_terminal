// TrnxHarcama.cpp: implementation of the CTrnxHarcama class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxHarcama.h"
#include "..\Engine\Engine.h"
#include "..\UI\UIUtils.h"
#include "TrnxFactory.h"

//--------------------------------------------------------------------------------------------------

CTrnxHarcama::CTrnxHarcama() :
	CTrnxBase((CEngine*)NULL)

{
	strncpy(this->m_trnxLabel, TRNX_HARCAMA_LBL, strlen(TRNX_HARCAMA_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcama;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcama::CTrnxHarcama(CEngine* pEng) :
	CTrnxBase(pEng)

{
	strncpy(this->m_trnxLabel, TRNX_HARCAMA_LBL, strlen(TRNX_HARCAMA_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxHarcama;
}

//--------------------------------------------------------------------------------------------------

CTrnxHarcama::~CTrnxHarcama()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxHarcama::Do()
{
	CCardReader cardReader;

	CInputBox inAmount("HARCAMA\nTUTAR:", 5, 5, 6, CInputBox::itCurrency);

	if (inAmount.Draw() != CInputBox::retOK) {
		return GENERAL_FAILURE;
	}
	this->m_data.m_amount =  atoi(inAmount.GetBuffer());
	if (this->m_data.m_amount <= 0) {
		CMessageBox mb("Girilen deger\n yanlis!", MB_ANY_KEY);
		mb.Draw();
		return GENERAL_FAILURE;
	}

	char tmp[64] = "";
	sprintf(tmp, "   Harcama\n%8.02lf TL\nTutar dogru mu?", this->m_data.m_amount / 100.);
	CMessageBox mbOnay(tmp, MB_YES_NO);
	mbOnay.Draw();
	if (mbOnay.GetSelect() == CHOICE_NO) {
		return SUCCESS;
	}

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	if (cardReader.DoHarcama(this->m_data.m_amount) != SUCCESS) {
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

void CTrnxHarcama::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	if (this->m_data.m_voidFlag == 0x01) {
		sprintf(tmp, "%d", this->m_data.m_amount);
		CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
		PrnStr("IPTAL EDiLEN  : %10s TL\n", tmp2);

		Bcd2Str(this->m_data.m_prepaidData.Balance, 6, 0, tmp);
		sprintf(tmp2, "%d", atoi(tmp));
		CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
		PrnStr("YENi BAKiYE   : %10s TL\n", tmp);
	}
	else {
		sprintf(tmp, "%d", this->m_data.m_amount);
		CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
		PrnStr("TUTAR         : %10s TL\n", tmp2);

		Bcd2Str(this->m_data.m_prepaidData.Balance, 6, 0, tmp);
		sprintf(tmp2, "%d", atoi(tmp));
		CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
		PrnStr("BAKiYE        : %10s TL\n", tmp);
		
		sprintf(tmp, "%d", this->m_data.m_kazanilanPuan);
		CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
		PrnStr("KAZANILAN PUAN: %10s TL\n", tmp2);
	}
}

//--------------------------------------------------------------------------------------------------

int	CTrnxHarcama::OnVoid()
{
	CCardReader cardReader;
	PRNLINE("OnVoid");

	this->m_error = cardReader.ReadCardData();
	if (this->m_error != SUCCESS) {
		PRNLINE("CARD_NOT_READ");
		return CARD_NOT_READ;
	}
	
	if (memcmp(this->m_data.m_fanData.CardNumber , cardReader.GetFanData()->CardNumber, 16) != 0) {
		PRNLINE("CARD_NOT_SAME");
		return CARD_NOT_SAME;
	}
	
	// ayni kart mi kontrolu yapilir.
	this->m_error = cardReader.DoNakitYukleme(this->m_data.m_amount);
	if (this->m_error != SUCCESS) {
		char tmp[32] = "";
		sprintf(tmp, "DoNakitYukleme(): %d", this->m_error);
		PRNLINE(tmp);
		PRNLINE("INVERSE_OPERATION_ERROR");
		return INVERSE_OPERATION_ERROR;
	}

	this->SetData(cardReader);
	PRNLINE("SetData");
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
