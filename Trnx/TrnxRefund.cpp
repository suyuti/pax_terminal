#include "TrnxRefund.h"
#include "..\Engine\Engine.h"
#include "..\Engine\RefundEngine.h"
#include "..\UI\UIUtils.h"
#include "TrnxFactory.h"

//---------------------------------------------------------------------------------------------------------

CTrnxRefund::CTrnxRefund() :
	CTrnxBase((CEngine*)NULL)
{
	strncpy(this->m_trnxLabel, TRNX_IADE_LBL, strlen(TRNX_IADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxIade;
	this->m_refundBalance		= 0;
	this->m_refundPoint			= 0;
	this->m_bLoadBalanceToCard	= false;
	this->m_bLoadPointToCard	= false;
}

//---------------------------------------------------------------------------------------------------------

CTrnxRefund::CTrnxRefund(CEngine* pEng) :
	CTrnxBase(pEng)

{
	strncpy(this->m_trnxLabel, TRNX_IADE_LBL, strlen(TRNX_IADE_LBL));
	this->m_data.m_trnxType = CTrnxFactory::trnxIade;
	this->m_refundBalance		= 0;
	this->m_refundPoint			= 0;
	this->m_bLoadBalanceToCard	= false;
	this->m_bLoadPointToCard	= false;
}

//---------------------------------------------------------------------------------------------------------

CTrnxRefund::~CTrnxRefund()
{
}

//---------------------------------------------------------------------------------------------------------

int	CTrnxRefund::OnVoid()
{
	CMessageBox mb("Iade Iptal edilemez!", MB_ANY_KEY);
	mb.Draw();
	return SUCCESS;
}

//---------------------------------------------------------------------------------------------------------

int CTrnxRefund::Do()
{
	int size = 0;
	int ret;
	CCardReader cardReader;

	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	this->m_error = cardReader.ReadCardData();
	if (this->m_error != SUCCESS) {
		this->ShowErrorMessage(cardReader);
		return GENERAL_FAILURE;
	}

	//------------------

	CInputBox inRRN("Belge No\nGiriniz:", 5, 5, 12,CInputBox::itNumeric);
	if (inRRN.Draw() != CInputBox::retOK) {
		return USER_CANCELLED;
	}
	Str2Bcd(inRRN.GetBuffer(), strlen(inRRN.GetBuffer()), LEFT_PAD_ZERO,	this->m_data.m_orgRRN, sizeof(this->m_data.m_orgRRN), LEFT_PAD);

	char ttt[100] = "";
	Bcd2Str((unsigned char*)this->m_data.m_orgRRN, 6, 0, ttt);
	PRNLINE(ttt);

	//------------------
	
	CInputBox inAmount("Tutar\nGiriniz:", 5, 5, 12,CInputBox::itCurrency);
	if (inAmount.Draw() != CInputBox::retOK) {
		return USER_CANCELLED;
	}

	this->m_data.m_amount = atoi(inAmount.GetBuffer());

	this->SetData(cardReader);
	memcpy(this->m_cardNo, cardReader.GetFanData()->CardNumber, 16);

	CRefundEngine refundEng(this->m_pEngine);
	ret = refundEng.DoRefund(this);
	if (ret == SUCCESS) {
		if (refundEng.GetResponseCode() == 0) {
			this->m_refundBalance		= refundEng.GetRefundBalance();
			this->m_refundPoint			= refundEng.GetRefundPoint();
			this->m_bLoadBalanceToCard	= refundEng.IsLoadBalanceToCard();
			this->m_bLoadPointToCard	= refundEng.IsLoadPointToCard();
			ret = this->OnApproved();
			if (ret != SUCCESS) {
				goto REVERSAL;
			}
		}
		refundEng.GetResponseMsgPrn(this->m_data.m_responseMsgPrn, &size);
		refundEng.GetResponseMsgScr(this->m_data.m_responseMsgScr, &size);
		this->SetResponseCode(refundEng.GetResponseCode());
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
	ret = refundEng.DoReversal(this);
	if (ret == SUCCESS) {
		this->SetResponseCode(refundEng.GetResponseCode());
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

//---------------------------------------------------------------------------------------------------------

void CTrnxRefund::PrintBody()
{
	char tmp[100] = "";
	char tmp2[100] = "";

	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	
	sprintf(tmp, "%d", this->m_data.m_amount);
	CUIUtils::str2amt(tmp, tmp2, strlen(tmp));
	
	PrnStr("IADE EDiLEN  : %10s TL\n", tmp2);

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

//---------------------------------------------------------------------------------------------------------

int CTrnxRefund::OnApproved()
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


	if (this->m_bLoadBalanceToCard) {
		if (this->m_refundBalance > 0) {
			if (cardReader.DoNakitYukleme(this->m_refundBalance) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}
	else {
		if (this->m_refundBalance > 0) {
			if (cardReader.DoHarcama(this->m_refundBalance) != SUCCESS) {
				return MAKE_REVERSAL;
			}
		}
	}

	if (this->m_bLoadPointToCard) {
		if (this->m_refundPoint > 0) {
		}
	}
	else {
		if (this->m_refundPoint > 0) {
		}
	}

	this->SetData(cardReader);
	return SUCCESS;
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
