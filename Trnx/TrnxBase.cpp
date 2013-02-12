// TrnxBase.cpp: implementation of the CTrnxBase class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxBase.h"
#include "..\Engine\Engine.h"
#include "..\Engine\AdviceEngine.h"
#include "..\Engine\VoidEngine.h"
#include "..\Files\Batch.h"
#include "..\Files\Acquier.h"
#include "..\UI\UIUtils.h"
#include "..\UI\DelayedMessageBox.h"

//--------------------------------------------------------------------------------------------------

CTrnxBase::CTrnxBase() : 
	m_pEngine((CEngine*)NULL)
{
	m_bTypeOnline = false;
	memset(&this->m_data, 0x00, sizeof(this->m_data));
	memset(this->m_trnxLabel, 0x00, sizeof(this->m_trnxLabel));
	this->m_bSaved = false;
	this->m_usesIslemNo = true;
	this->Clear();
}

//--------------------------------------------------------------------------------------------------

CTrnxBase::CTrnxBase(CEngine* pEng)
{
	m_bTypeOnline = false;
	this->m_pEngine = pEng;
	memset(&this->m_data, 0x00, sizeof(this->m_data));
	memset(this->m_trnxLabel, 0x00, sizeof(this->m_trnxLabel));
	this->m_bSaved		= false;
	this->m_usesIslemNo = true;
	this->Clear();
}

//--------------------------------------------------------------------------------------------------

CTrnxBase::~CTrnxBase()
{

}

//--------------------------------------------------------------------------------------------------

int CTrnxBase::Save()
{
	CBatch batch;
	//CParamters*					pParam		= this->m_pEngine->GetDefParams();
	CAcquier::HAcquierRecord	hAcquier;//	= this->m_pEngine->GetAcquier()->GetData();
	int							batchNo = 0;

	CParamters param;
	if (!param.Open()) {
		this->m_error = PARAMS_FILE_NOT_OPEN;
		return this->m_error;
	}
	param.GotoRec(1, true);
	param.Close();


	CAcquier acq;
	if (!acq.Open()) {
		this->m_error = ACQUIER_FILE_NOT_OPEN;
		return this->m_error;
	}
	acq.GotoRec(1, true);
	batchNo = acq.GetBatchNo();
	hAcquier = acq.GetData();
	acq.Close();


	this->m_data.m_batch = batchNo;//pParam->GetBatchNo();

	if (this->m_bTypeOnline) {
		this->m_data.m_orgMTI = 200;
	}
	else {
		this->m_data.m_orgMTI = 220;
	}


	//---- Date & Time ------
	GetTime(this->m_data.m_dateTime);

	//---- Acquier ----------
	memcpy(this->m_data.m_acquierID, hAcquier->m_acquierTableID, sizeof(this->m_data.m_acquierID));


	this->m_data.m_stan = param.GetNextStan();

	//---- RRN --------------
	this->CalcRRN();

	batch.SetData(&this->m_data);

	if (this->m_data.m_trnxType == CTrnxFactory::trnxBakiyeSorgu ) {
		return SUCCESS; // Bu tip islemler kaydedilmeyecek. SUCCESS donuyor. Normalde fonksiyon kayit numarasini doner.
	}

	int  ret = batch.Append();

	if (ret > 0) {
		param.SetNextStan(this->m_data.m_stan);
		if (param.Open()) {
			param.Update();
			param.Close();
		}
		this->m_bSaved = true;
	}
	return ret;
}

//--------------------------------------------------------------------------------------------------

int CTrnxBase::Update(int recNo)
{
	CBatch batch;

	batch.SetData(&this->m_data);
	if (!batch.Open()) {
		return BATCH_NOT_OPEN;
	}
	char tmp[128] = "";
	sprintf(tmp, "trnxUpdate.%d", recNo);
	PRNLINE(tmp);
	batch.GotoRec(recNo, false);
	batch.Update();//.Append()
	batch.Close();

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::Print()
{
	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	pEng->Init();

	this->PrintHeader();
	this->PrintBody();
	this->PrintFooter();

	pEng->Start();
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::PrintHeader()
{
	char tmp[255] = "";
	char tmp2[255] = "";
	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	pEng->PrintLogo();

	// Merchant
	CTerminal term;
	CTerminal::HTerminalRecord hTerm;
	if (term.Open()) {
		term.GotoRec(1, true);
		hTerm = term.GetData();
		term.Close();

		pEng->PrnSetNormal();
		memcpy(tmp, hTerm->m_merchName, sizeof(hTerm->m_merchName));
		tmp[sizeof(hTerm->m_merchName)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");

		pEng->PrnSetSmall();
		memcpy(tmp, hTerm->m_merchAddress1, sizeof(hTerm->m_merchAddress1));
		tmp[sizeof(hTerm->m_merchAddress1)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");

		memcpy(tmp, hTerm->m_merchAddress2, sizeof(hTerm->m_merchAddress2));
		tmp[sizeof(hTerm->m_merchAddress2)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");

		memcpy(tmp, hTerm->m_merchAddress3, sizeof(hTerm->m_merchAddress3));
		tmp[sizeof(hTerm->m_merchAddress3)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");

		memcpy(tmp, hTerm->m_merchAddress4, sizeof(hTerm->m_merchAddress4));
		tmp[sizeof(hTerm->m_merchAddress4)] = 0x00;
		PrnStr(tmp);
		PrnStr("\n");
	}
	pEng->PrnSetBig();
	if (strlen(this->m_trnxLabel) < 19) {
		PrnStr("%*s%s\n\n", (19 - strlen(this->m_trnxLabel)) / 2, " ", this->m_trnxLabel);
	}
	else {
		PrnStr("%s\n\n", this->m_trnxLabel);
	}

	if (this->m_bVoid) {
		PrnStr("     iPTAL\n");
	}

	if (this->m_usesIslemNo) {
		// Batch - Stan
		pEng->PrnSetSmall();
		PrnStr("Batch No                   Islem No\n");
		pEng->PrnSetNormal();
		PrnStr("%06d            %06d\n", this->m_data.m_batch, this->m_data.m_stan);
	}
	// DateTime
	pEng->PrnSetSmall();
	PrnStr("Tarih / Zaman\n");
	pEng->PrnSetNormal();
	date2str(this->m_data.m_dateTime, tmp, DateType_DD_MM_YYYY_HH_mm_SS);
	PrnStr("%s\n", tmp);

	if (this->m_usesIslemNo) {
		// Belge Referans No
		pEng->PrnSetSmall();
		PrnStr("Belge Referans No\n");
		pEng->PrnSetNormal();
		Bcd2Str(this->m_data.m_RRN, 6, 0, tmp);
		PrnStr("%s\n", tmp);
	}
	// Card No
	pEng->PrnSetSmall();
	PrnStr("Kart No\n");
	PrnFontSet(6, 0);
	memset(tmp, 0x00, sizeof(tmp));
	strncpy(tmp, (const char*)this->m_data.m_fanData.CardNumber, sizeof(this->m_data.m_fanData.CardNumber));
	PrnStr("%*s%s\n", (22 - strlen(tmp)) / 2, " ", tmp);

	// Name
	pEng->PrnSetSmall();
	PrnStr("Kart sahibi\n");
	pEng->PrnSetNormal();
	memset(tmp, 0x00, sizeof(tmp));
	strncpy(tmp, this->m_data.m_fanData.Name, sizeof(this->m_data.m_fanData.Name));
	PubTrimStr((unsigned char*)tmp);
	PrnStr("%s ", tmp);
	// Surname
	memset(tmp, 0x00, sizeof(tmp));
	strncpy(tmp, this->m_data.m_fanData.SurName, sizeof(this->m_data.m_fanData.SurName));
	PubTrimStr((unsigned char*)tmp);
	PrnStr("%s\n", tmp);

	PrnStr("\n\n");
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::PrintBody()
{
	// Her trnx kendisi implemente eder.
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::PrintFooter()
{
	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	if (this->m_error != SUCCESS) {
		pEng->PrnSetBig2();
		switch(this->m_error) {
			case CARD_NOT_READ:
				PrnStr("Kart okunamadi!\n");
			break;
			case CARD_NOT_SAME:
				PrnStr("Farkli kart !\n");
			break;
			case INVERSE_OPERATION_ERROR:
				PrnStr("Ters islem yapilamadi!\n");
			break;
			/*
			case ....
			*/
		}
	} 
	else {
		if (this->m_data.m_voidFlag == 0x00 && this->m_bVoid) {
			pEng->PrnSetBig2();
			PrnStr("\n      iPTAL\n   BASARISIZ.\n");
		}
	}
	pEng->PrnSetNormal();
	PrnStr("-----------------------------\n\n\n\n\n");
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::AfterDone()
{

	if (this->m_error == SUCCESS) {
		CUIUtils::AnimOK("iSLEM BASARILI");
	}
	else {
		CUIUtils::AnimError("BASARISIZ.");
	}
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::SetData(CCardReader& cardReader)
{
	HFanStruct			hFan	= cardReader.GetFanData();
	HLoyaltyStruct		hLoyalty= cardReader.GetLoyaltyData();
	HPrepaidStruct		hPrep	= cardReader.GetPrepaidData();
	HSeasonTicketStruct	hSeason	= cardReader.GetSeasonTicketData();

	memcpy(&this->m_data.m_fanData.CardNumber,				hFan->CardNumber			,	sizeof(hFan->CardNumber				));
	memcpy(&this->m_data.m_fanData.Name,					hFan->Name					,	sizeof(hFan->Name					));
	memcpy(&this->m_data.m_fanData.SurName,					hFan->SurName				,	sizeof(hFan->SurName				));
	memcpy(&this->m_data.m_fanData.BirthDate,				hFan->BirthDate				,	sizeof(hFan->BirthDate				));
	memcpy(&this->m_data.m_fanData.FirstCardGivenDate,		hFan->BirthDate				,	sizeof(hFan->BirthDate				));
	memcpy(&this->m_data.m_fanData.TCKN,					hFan->TCKN					,	sizeof(hFan->TCKN					));

	memcpy(&this->m_data.m_loyaltyData.FBPoint1	,			hLoyalty->FBPoint1			,	sizeof(hLoyalty->FBPoint1			));
	memcpy(&this->m_data.m_loyaltyData.FBPoint2,			hLoyalty->FBPoint2			,	sizeof(hLoyalty->FBPoint2			));
	memcpy(&this->m_data.m_loyaltyData.FBPoint3,			hLoyalty->FBPoint3			,	sizeof(hLoyalty->FBPoint3			));
	memcpy(&this->m_data.m_loyaltyData.FBPoint4,			hLoyalty->FBPoint4			,	sizeof(hLoyalty->FBPoint4			));
	memcpy(&this->m_data.m_loyaltyData.SlotCode1,			hLoyalty->SlotCode1			,	sizeof(hLoyalty->SlotCode1			));
	memcpy(&this->m_data.m_loyaltyData.SlotCode2,			hLoyalty->SlotCode2			,	sizeof(hLoyalty->SlotCode2			));
	memcpy(&this->m_data.m_loyaltyData.SlotCode3,			hLoyalty->SlotCode3			,	sizeof(hLoyalty->SlotCode3			));
	memcpy(&this->m_data.m_loyaltyData.SlotCode4,			hLoyalty->SlotCode4			,	sizeof(hLoyalty->SlotCode4			));
	memcpy(&this->m_data.m_loyaltyData.SlotEffectiveDate1,	hLoyalty->SlotEffectiveDate1,	sizeof(hLoyalty->SlotEffectiveDate1	));
	memcpy(&this->m_data.m_loyaltyData.SlotEffectiveDate2,	hLoyalty->SlotEffectiveDate2,	sizeof(hLoyalty->SlotEffectiveDate2	));
	memcpy(&this->m_data.m_loyaltyData.SlotEffectiveDate3,	hLoyalty->SlotEffectiveDate3,	sizeof(hLoyalty->SlotEffectiveDate3	));
	memcpy(&this->m_data.m_loyaltyData.SlotEffectiveDate4,	hLoyalty->SlotEffectiveDate4,	sizeof(hLoyalty->SlotEffectiveDate4	));
	memcpy(&this->m_data.m_loyaltyData.SlotExpiryDate1,		hLoyalty->SlotExpiryDate1	,	sizeof(hLoyalty->SlotExpiryDate1	));
	memcpy(&this->m_data.m_loyaltyData.SlotExpiryDate2,		hLoyalty->SlotExpiryDate2	,	sizeof(hLoyalty->SlotExpiryDate2	));
	memcpy(&this->m_data.m_loyaltyData.SlotExpiryDate3,		hLoyalty->SlotExpiryDate3	,	sizeof(hLoyalty->SlotExpiryDate3	));
	memcpy(&this->m_data.m_loyaltyData.SlotExpiryDate4,		hLoyalty->SlotExpiryDate4	,	sizeof(hLoyalty->SlotExpiryDate4	));
	memcpy(&this->m_data.m_loyaltyData.ValidationState,		hLoyalty->ValidationState	,	sizeof(hLoyalty->ValidationState	));
		
	memcpy(&this->m_data.m_prepaidData.Balance,				hPrep->Balance				,	sizeof(hPrep->Balance				));
	memcpy(&this->m_data.m_prepaidData.EffectiveDate,		hPrep->EffectiveDate		,	sizeof(hPrep->EffectiveDate			));
	memcpy(&this->m_data.m_prepaidData.ExpiryDate,			hPrep->ExpiryDate			,	sizeof(hPrep->ExpiryDate			));

	// Season Ticketin tamami
	//!
	//memcpy(&this->m_data.m_seasionTicketData,		hSeason,			sizeof(SeasonTicketStruct));
	
	this->m_data.m_kazanilanPuan = cardReader.GetGainedPoint();
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::PrintErrorMessage(CCardReader& cardReader)
{
	CPrinterEngine* pEng = this->m_pEngine->GetPrinterEng();
	pEng->Init();

	this->PrintHeader();
	pEng->PrnSetBig2();
	PrnStr("      HATA:\n\n");
	PrnStr("%s\n", cardReader.GetLastErrorMsg());
	this->PrintFooter();

	pEng->Start();
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::ShowErrorMessage(CCardReader& cardReader)
{
	CMessageBox mb(cardReader.GetLastErrorMsg(), MB_ANY_KEY);
	mb.Draw();
}

//--------------------------------------------------------------------------------------------------

int CTrnxBase::DoVoid(int rec) 
{ 
//	int stan = 0;
//	int rec = 0;
	int ret;

	this->m_bVoid = true;
/*
	CInputBox inStan("iSLEM NO\nGiriniz:", 5, 5, 6, CInputBox::itNumeric);

	if (inStan.Draw() != CInputBox::retOK) {
		return GENERAL_FAILURE;
	}

	stan = atoi(inStan.GetBuffer());

	CBatch batch;
	ret = batch.FindByStan(stan, &rec);
	if (ret != SUCCESS) {
		CMessageBox mb("Islem\nBulunamadi!", MB_ANY_KEY);
		mb.Draw();
		return ret;
	}

	if (batch.IsVoided()) {
		CMessageBox mb("Islem\niptal edilmis!", MB_ANY_KEY);
		mb.Draw();
		return TRNX_ALREADY_VOIDED;
	}
*/
//	this->SetBatchData(batch.GetData());

	if (this->m_data.m_sentFlag == 0x00) {
		CMessageBox mb("Islem gonderiliyor.", MB_SHOW_ONLY);
		mb.Draw();
		char tmp[32] = "";
		sprintf(tmp, "islem gonderiliyor. rec: %d", rec);
		PRNLINE(tmp);
		CAdviceEngine adv(this->m_pEngine);
		ret = adv.SendAdvice(rec);
		if (ret != SUCCESS) {
			return ret;
		}
	}
	// Kart okutulmali mi?

	//CDelayedMessageBox mb("Kartinizi.\ngösteriniz.", 4, true, MB_SHOW_ONLY);
	Beef(7, 200);
	Beef(4, 100);
	CMessageBox mb("Kartinizi\ngösteriniz.", MB_SHOW_ONLY);
	mb.Draw();

	CVoidEngine voidEng(this->m_pEngine);
	if (voidEng.DoVoid(rec) == SUCCESS) {
		PRNLINE("cevap geldi");
			
		this->m_data.m_responseCode = voidEng.GetResponseCode();
		this->m_data.m_sentFlag		= 0x01;
		this->m_data.m_reversalFlag = 0x00;
		
		if (voidEng.GetResponseCode() == 0) {
		//		5. Cevap onaysa karta ..... yapilir.
			PRNLINE("onay");
			mb.Draw();

			this->m_error = this->OnVoid();
			if (this->m_error != SUCCESS) {
				this->m_data.m_reversalFlag = 0x01;
				goto REVERSAL;
			}
			this->m_data.m_voidFlag		= 0x01;
			this->Update(rec);
			PRNLINE("update yapildi.");
		}
		else {
			PRNLINE("void red");
			this->m_data.m_voidFlag		= 0x00;
		}
		goto PRINT;
	}

REVERSAL:
	PRNLINE("Void Reversal yapilir.");
	if (voidEng.DoReversal(rec) == SUCCESS) {
		this->m_data.m_deletedFlag	= 0x01;
		this->Update(rec);
		PRNLINE("VO RV update yapildi!");
	}
PRINT:
	this->Print();
/*
EXIT:
	this->AfterDone();
*/
	return SUCCESS; 
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::CalcRRN()
{
	// TerminalNo[5] + 3
	// Stan
	// Rand
	char	tmp[13] = "";
	int		pos		= 0;

	CTerminal term;
	CTerminal::HTerminalRecord hTerm;
	if (term.Open()) {
		term.GotoRec(1 ,true);
		hTerm = term.GetData();
		term.Close();
	}
	strncpy(tmp + pos, hTerm->m_termId + 5, 3); pos += 3;

	sprintf(tmp + pos, "%06d", this->m_data.m_stan); pos += 6;

	int rnd = rand() % 999;
	sprintf(tmp + pos, "%03d", rnd); pos += 3;

	// eskisi tasinir
	//memcpy(this->m_data.m_orgRRN, this->m_data.m_RRN, sizeof(this->m_data.m_RRN));

	// yenisi hesaplanir.
	Str2Bcd(tmp, strlen(tmp), LEFT_PAD_ZERO, this->m_data.m_RRN, sizeof(this->m_data.m_RRN), LEFT_PAD);

	PRNLINE(tmp);
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::Clear()
{
	memset(&this->m_data, 0x00, sizeof(CBatch::BatchData));
	this->m_bTypeOnline = false;
	this->m_bVoid		= false;
	this->m_error		= SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::SetResponseMsgPrn(char* pMsg, int size)
{
	if (size <= sizeof(this->m_data.m_responseMsgPrn)) {
		strncpy(this->m_data.m_responseMsgPrn, pMsg, size);
	}
}

//--------------------------------------------------------------------------------------------------

void CTrnxBase::SetResponseMsgScr(char* pMsg, int size)
{
	if (size <= sizeof(this->m_data.m_responseMsgScr)) {
		strncpy(this->m_data.m_responseMsgScr, pMsg, size);
	}
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
