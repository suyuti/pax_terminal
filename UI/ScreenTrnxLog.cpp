// ScreenTrnxLog.cpp: implementation of the CScreenTrnxLog class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreenTrnxLog.h"
#include "..\Files\Batch.h"
#include "MessageBox.h"
#include "UIUtils.h"
#include "..\Trnx\TrnxFactory.h"
#include "..\Trnx\TrnxBase.h"


//-----------------------------------------------------------------------------------------

CScreenTrnxLog::CScreenTrnxLog()
{

}

//-----------------------------------------------------------------------------------------

CScreenTrnxLog::~CScreenTrnxLog()
{

}

//-----------------------------------------------------------------------------------------

int CScreenTrnxLog::Draw()
{
	int count = 0;
	CBatch batch;
	if (!batch.Open()) {
		CMessageBox mb("Batch açýlamadý", MB_ANY_KEY);
		mb.Draw();
		return SUCCESS;
	}
	count = batch.GetRecordCount();
	batch.Close();

	int rec = 1;
	uchar key;
	if (count <= 0) {
		CMessageBox mb("KAYIT YOK", MB_ANY_KEY);
		mb.Draw();
		return SUCCESS;
	}

	while (true) {
		if (!batch.Open()) {
			break;
		}
		batch.GotoRec(rec, true);
		batch.Close();
		this->ShowTrnx(batch.GetData());
		key = getkey();
		switch (key) {
			case KEY_DOWN:
				if (rec < count) {
					++rec;
				}
			break;
			case KEY_UP:
				if (rec > 1) {
					--rec;
				}
			break;
			case KEY_CANCEL:
				goto EXIT;
			break;
		}
	}
EXIT:

	return SUCCESS;
}

//-----------------------------------------------------------------------------------------

void CScreenTrnxLog::ShowTrnx(CBatch::HBatchData hTrnx)
{
	this->Clear();
	
	char tmp[255] = "";
	char tmp2[255] = "";

	switch(hTrnx->m_trnxType) {
		case CTrnxFactory::trnxHarcama: 
			sprintf(tmp, TRNX_HARCAMA_LBL); 
		break;
		case CTrnxFactory::trnxBakiyeSorgu: 
			sprintf(tmp, TRNX_BAKIYESORGU_LBL); 
		break;
		case CTrnxFactory::trnxNakitYukleme: 
			sprintf(tmp, TRNX_NAKITYUKLEME_LBL); 
		break;
		case CTrnxFactory::trnxKrediKartYukleme: 
			sprintf(tmp, TRNX_KREDIKART_YUKLEME); 
		break;
		case CTrnxFactory::trnxDebitYukleme: 
			sprintf(tmp, TRNX_DEBIT_YUKLEME); 
		break;
		case CTrnxFactory::trnxPuanKullanma: 
			sprintf(tmp, TRNX_PUANKULLANMA_LBL); 
		break;
		case CTrnxFactory::trnxPuanSorgu: 
			sprintf(tmp, TRNX_PUANSORGU_LBL); 
		break;
		case CTrnxFactory::trnxKartGuncelle: 
			sprintf(tmp, TRNX_KARTGUNCELLE_LBL); 
		break;
		case CTrnxFactory::trnxIade: 
			sprintf(tmp, TRNX_IADE_LBL); 
		break;
	}
	ScrGotoxy(0, 0);
	//ScrFontSet(1);
	Lcdprintf(tmp);
	//ScrFontSet(0);


	strncpy(tmp, (const char*)hTrnx->m_fanData.CardNumber, sizeof(hTrnx->m_fanData.CardNumber));
	tmp[sizeof(hTrnx->m_fanData.CardNumber)] = 0x00;
	ScrGotoxy(0, 1);
	Lcdprintf(tmp);
	//CUIUtils::PubDispString(tmp, DISP_LINE_LEFT|0);

	sprintf(tmp, "Tutar: %.02lf", ((double)hTrnx->m_amount) / 100.);
	ScrGotoxy(0, 2);
	Lcdprintf(tmp);

	sprintf(tmp, "B+S: %d-%d", hTrnx->m_batch, hTrnx->m_stan);
	ScrGotoxy(0, 3);
	Lcdprintf(tmp);

	//Bcd2Str((unsigned char*)hTrnx->m_responseCode, sizeof(hTrnx->m_responseCode), 0, tmp2);
	sprintf(tmp, "Resp: %02d", hTrnx->m_responseCode);
	ScrGotoxy(0, 4);
	Lcdprintf(tmp);

	sprintf(tmp, "Stat: %s%s%s%s", 
		(hTrnx->m_sentFlag		== 0x01) ? "Sent|"	: "", 
		(hTrnx->m_reversalFlag	== 0x01) ? "RV|"	: "",
		(hTrnx->m_deletedFlag	== 0x01) ? "DL|"	: "",
		(hTrnx->m_voidFlag		== 0x01) ? "VO|"	: "");
	ScrGotoxy(0, 5);
	Lcdprintf(tmp);

	//Bcd2Str(hTrnx->m_orgRRN, 6, 0, tmp2);
	//sprintf(tmp, "OrgRRN: %s", tmp2);
	//ScrGotoxy(0, 6);
	//Lcdprintf(tmp);

}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
