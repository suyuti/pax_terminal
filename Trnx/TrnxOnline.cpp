// TrnxOnline.cpp: implementation of the CTrnxOnline class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxOnline.h"
#include "..\Engine\OnlineEngine.h"
#include "..\Engine\Engine.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrnxOnline::CTrnxOnline() :
	CTrnxBase((CEngine*)NULL)
{
	this->m_bTypeOnline = true;
	this->online = COnlineEngine(this->m_pEngine);
}

CTrnxOnline::CTrnxOnline(CEngine* pEng) :
	CTrnxBase(pEng)
{
	this->m_bTypeOnline = true;
	this->online = COnlineEngine(this->m_pEngine);
}

CTrnxOnline::~CTrnxOnline()
{
}

int CTrnxOnline::Do()
{
	int size = 0;
	char tmp[128] = "";
	//unsigned char cardNo[32] = "";
	int ret = 0;
	// 1. tutar girilir.
	// 2. Kart okunur
	// 3. Rev kaydi yapilir.
	// 4. Online sorulur
	//		Cevap gelirse
	//		5. Cevap onaysa karta nakit yukleme yapilir.
	//		6. Cevap Redse karta nakit yukleme yapilmaz
	//		7. Rev kaldirilir, kayit update yapilir.
	//		Cevap gelmezse
	//		8. islem sonlanir. Kayit Rev kalir.
	
	ret = this->OnBeforeOnline();
	if (ret != SUCCESS) {
				goto EXIT_ERROR;
			}

	// 4. Online sorulur	
	ret = this->online.DoOnline(this);
	if (ret == SUCCESS) {
		if (this->online.GetResponseCode() == 0) {
			this->m_ScriptBalance		= online.GetScriptBalance();
			this->m_ScriptPoint			= online.GetScriptPoint();
			this->m_bLoadBalanceToCard	= online.IsLoadBalanceToCard();
			this->m_bLoadPointToCard	= online.IsLoadPointToCard();
			ret = this->OnApproved();
			if (ret != SUCCESS) {
				goto REVERSAL;
			}
		}
		this->online.GetResponseMsgPrn(this->m_data.m_responseMsgPrn, &size);
		this->online.GetResponseMsgScr(this->m_data.m_responseMsgScr, &size);
		this->SetResponseCode(online.GetResponseCode());
		this->SetReversal(false);
		this->SetSent();
		this->Update(this->m_recNo);
		goto PRINT;
	}
	else if (ret == NOT_CONNECTED) {
		CMessageBox mb("Baglanti\nkurulamadi!", MB_ANY_KEY);
		mb.Draw();
		goto EXIT_ERROR;
	}

REVERSAL:
	ret = this->online.DoReversal(this);
	if (ret == SUCCESS) {
		this->SetResponseCode(online.GetResponseCode());
		this->SetDeleted();
		this->SetReversal(true);
		this->SetSent();
		this->Update(this->m_recNo);
		goto PRINT;
	}
		
PRINT:
	this->Print();
	this->AfterDone();
	return SUCCESS;

EXIT_ERROR:
	//CUIUtils::AnimError("Islem\nBasarisiz.");
	return TRNX_NOT_SUCCESS;
}

int CTrnxOnline::OnBeforeOnline()
{
	int size = 0;
	char tmp[128] = "";
	//unsigned char cardNo[32] = "";
	int ret = 0;
	// 1. tutar girilir.
	// 2. Kart okunur
	// 3. Rev kaydi yapilir.
	// 4. Online sorulur
	//		Cevap gelirse
	//		5. Cevap onaysa karta nakit yukleme yapilir.
	//		6. Cevap Redse karta nakit yukleme yapilmaz
	//		7. Rev kaldirilir, kayit update yapilir.
	//		Cevap gelmezse
	//		8. islem sonlanir. Kayit Rev kalir.

	CCardReader cardReader;

	// 1. Tutar girilir.
	sprintf(tmp, "%s\nTUTAR:", this->m_inputTypeLabel);
	CInputBox inAmount(tmp, 5, 5, 6, CInputBox::itCurrency);

	if (inAmount.Draw() != CInputBox::retOK) {
		return GENERAL_FAILURE;
	}
	this->m_data.m_amount =  atoi(inAmount.GetBuffer());

	if (this->m_data.m_amount <= 0) {
		CMessageBox mb("Girilen deger\n yanlis!", MB_ANY_KEY);
		mb.Draw();
		return GENERAL_FAILURE;
	}

	sprintf(tmp, "   Yukleme\n%8.02lf TL\nTutar dogru mu?", this->m_data.m_amount / 100.);
	CMessageBox mbOnay(tmp, MB_YES_NO);
	mbOnay.Draw();
	if (mbOnay.GetSelect() == CHOICE_NO) {
		return SUCCESS;
	}

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

//--------------------------------------------------------------------------------------------------

int CTrnxOnline::OnApproved()
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

	if (this->m_bLoadBalanceToCard) {
		if (this->m_ScriptBalance > 0) {
			if (cardReader.DoNakitYukleme(this->m_ScriptBalance) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}
	else {
		if (this->m_ScriptBalance > 0) {
			if (cardReader.DoHarcama(this->m_ScriptBalance) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}

	if (this->m_bLoadPointToCard) {
		if (this->m_ScriptPoint > 0) {
			if (cardReader.DoPuanKullanmaIptal(this->m_ScriptPoint) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}
	else {
		if (this->m_ScriptPoint > 0) {
			if (cardReader.DoPuanKullanma(this->m_ScriptPoint) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}

	this->SetData(cardReader);
	return SUCCESS;
}