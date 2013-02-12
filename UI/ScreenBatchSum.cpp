// ScreenBatchSum.cpp: implementation of the CScreenBatchSum class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreenBatchSum.h"
#include "..\Engine\SettleEngine.h"
#include "..\Engine\Engine.h"
#include "..\Engine\PrinterEngine.h"
#include "..\Files\Terminal.h"

//------------------------------------------------------------------------------

CScreenBatchSum::CScreenBatchSum()
{
	pSettle = new CSettleEngine((CEngine*)NULL);
}

//------------------------------------------------------------------------------

CScreenBatchSum::~CScreenBatchSum()
{
	delete pSettle;
}

//------------------------------------------------------------------------------

int CScreenBatchSum::Draw()
{
	CSettleEngine::HSettleData hSettle;

	if (pSettle->CalcSettle() != SUCCESS) {
		return SUCCESS;
	}
	hSettle = pSettle->GetData();
	CScreen::Clear();

	ScrGotoxy(0, 0);
	Lcdprintf("Harc      : [%d] %d\n", hSettle->m_saleCount,			hSettle->m_saleTotal);
	Lcdprintf("Harc   IPT: [%d] %d\n", hSettle->m_saleVoidCount,		hSettle->m_saleVoidTotal);
	//Lcdprintf("Nk.Yuk.   : [%d] %d\n", hSettle->m_loadBalanceCount,		hSettle->m_loadBalanceTotal);
	//Lcdprintf("Nk.Yuk.IPT: [%d] %d\n", hSettle->m_loadBalanceVoidCount, hSettle->m_loadBalanceVoidTotal);
	Lcdprintf("P.Kul     : [%d] %d\n", hSettle->m_PointUseCount,		hSettle->m_PointUseTotal);
	Lcdprintf("P.Kul  IPT: [%d] %d\n", hSettle->m_PointUseVoidCount,	hSettle->m_PointUseVoidTotal);

	ScrFontSet(0);
	ScrGotoxy(1, 7);
	Lcdprintf("[CIKIS]      [YAZ]");
	ScrFontSet(0);
	
	uchar key;
	do {
		key = getkey();
		switch(key) {
			case KEY_ENTER:
				this->Print();
				break;
			break;
			case KEY_CANCEL:
				goto EXIT;
				break;
			break;
		}
	}
	while(1);
EXIT:

	return SUCCESS;
}

//--------------------------------------------------------------------------------------

void CScreenBatchSum::Print()
{
	char tmp[255] = "";
	CPrinterEngine* pEng = new CPrinterEngine();

	pEng->Init();
	pEng->PrintLogo();
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
	}
	pEng->PrnSetNormal();

	CSettleEngine::HSettleData hSettle;
	hSettle = pSettle->GetData();


	PrnFontSet(6, 0);
	PrnStr("Harcama\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_saleCount, hSettle->m_saleTotal / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n",	hSettle->m_saleVoidCount, hSettle->m_saleVoidTotal / 100.);

	PrnFontSet(6, 0);
	PrnStr("Nakit Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_cashLoadCount, hSettle->m_cashLoadTotal / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n",	hSettle->m_cashLoadVoidCount, hSettle->m_cashLoadVoidTotal / 100.);

	PrnFontSet(6, 0);
	PrnStr("Banka Karti Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_debitLoadCount, hSettle->m_debitLoadTotal / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n",	hSettle->m_debitLoadVoidCount, hSettle->m_debitLoadVoidTotal / 100.);

	PrnFontSet(6, 0);
	PrnStr("Kredi Karti Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_creditLoadCount, hSettle->m_creditLoadTotal/ 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n", hSettle->m_creditLoadVoidCount, hSettle->m_creditLoadVoidTotal / 100.);

	PrnFontSet(6, 0);
	PrnStr("Puan Kullanma\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_PointUseCount, hSettle->m_PointUseTotal / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n", hSettle->m_PointUseVoidCount, hSettle->m_PointUseVoidTotal / 100.);
	
	PrnFontSet(6, 0);
	PrnStr("Iade\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %4d  Toplam: %.02lf TL\n",	hSettle->m_refundCount, hSettle->m_refundTotal / 100.);
	//PrnStr("IPTAL\n");
	//PrnStr("Adet: %4d  Toplam: %.02lf TL\n\n", hSettle->m_PointUseVoidCount, hSettle->m_PointUseVoidTotal / 100.);


	PrnStr("\n\n\n\n\n");
	
	pEng->Start();

	delete pEng;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
