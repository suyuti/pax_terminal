// TrnxNakitYukleme.cpp: implementation of the CTrnxNakitYukleme class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxNakitYukleme.h"
#include "..\Engine\Engine.h"
#include "TrnxFactory.h"
#include "..\Engine\OnlineEngine.h"

//--------------------------------------------------------------------------------------------------

CTrnxNakitYukleme::CTrnxNakitYukleme() :
	CTrnxOnline((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_NAKITYUKLEME_LBL, strlen(TRNX_NAKITYUKLEME_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxNakitYukleme;
	sprintf(this->m_inputTypeLabel, "Nk. Yukleme");
}

//--------------------------------------------------------------------------------------------------

CTrnxNakitYukleme::CTrnxNakitYukleme(CEngine* pEng) :
	CTrnxOnline(pEng)
{
	strncpy(this->m_trnxLabel, TRNX_NAKITYUKLEME_LBL, strlen(TRNX_NAKITYUKLEME_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxNakitYukleme;
	sprintf(this->m_inputTypeLabel, "Nk. Yukleme");
}

//--------------------------------------------------------------------------------------------------

CTrnxNakitYukleme::~CTrnxNakitYukleme()
{

}

//--------------------------------------------------------------------------------------------------

void CTrnxNakitYukleme::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	
	sprintf(tmp, "%d", this->m_data.m_amount);
	CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
	if (this->m_data.m_voidFlag == 0x01) {
		PrnStr("iPTAL EDiLEN  : %10s TL\n", tmp2);
	}
	else {
		PrnStr("YUKLEME TUTARI: %10s TL\n", tmp2);
	}
	if (this->m_data.m_reversalFlag == 0x01) {
		pEng->PrnSetBig();
		PrnStr("----- HATA ----\n");
		PrnStr("     Islem\n   basarisiz!\n");
	}
	else {
		if (this->m_data.m_responseCode == 0) {
			Bcd2Str(this->m_data.m_prepaidData.Balance, 6, 0, tmp);
			sprintf(tmp2, "%d", atoi(tmp));
			CUIUtils::str2amt(tmp2, tmp, strlen(tmp2));
			PrnStr("BAKiYE        : %10s TL\n", tmp);
		}
		else {
			pEng->PrnSetBig();
			PrnStr("     Islem\n  Reddedildi.\n");
			PrnStr("   HATA [%d]\n", this->m_data.m_responseCode);
			PrnStr("\n%s\n", this->m_data.m_responseMsgPrn);
		}
	}
}
//--------------------------------------------------------------------------------------------------

int	CTrnxNakitYukleme::OnVoid()
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
	this->m_error = cardReader.DoHarcama(this->m_data.m_amount);
	if (this->m_error != SUCCESS) {
		char tmp[32] = "";
		sprintf(tmp, "DoHarcama(): %d", this->m_error);
		PRNLINE(tmp);
		PRNLINE("INVERSE_OPERATION_ERROR");
		return INVERSE_OPERATION_ERROR;
	}

	this->SetData(cardReader);
	PRNLINE("SetData");
	return SUCCESS;
}

/*
//--------------------------------------------------------------------------------------------------

int CTrnxNakitYukleme::OnApproved()
{
	CCardReader cardReader;
	CMessageBox mb("Kartinizi\nTekrar\nGösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	this->m_error = cardReader.ReadCardData();
	if (this->m_error != SUCCESS) {
		return MAKE_REVERSAL;
	}
	// ayni kart mi kontrolu yapilir.
	if (memcmp(this->m_cardNo, cardReader.GetFanData()->CardNumber, 16) != 0) {
		return MAKE_REVERSAL;
	}
	if (cardReader.DoNakitYukleme(this->m_data.m_amount) != SUCCESS) {
		return MAKE_REVERSAL;
	}
	this->SetData(cardReader);
	return SUCCESS;
}
*/
//--------------------------------------------------------------------------------------------------
