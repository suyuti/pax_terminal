#include "..\Engine\SettleEngine.h"
#include "..\Engine\PrinterEngine.h"
#include "SettleReport.h"
#include "..\Util\NumFuncs.h"
#include "Terminal.h"
#include "..\globaldef.h"
#include <stdlib.h>
#include "Acquier.h"


CSettleReport::CSettleReport() :
	CTable((void*)&m_data)
{
	memset(&this->m_data, 0, sizeof(this->m_data));
	this->m_recordSize = sizeof(CSettleReport::SettleReportData);
	sprintf(this->m_fileName, "%s", TABLE_NAME_SETTLE_REPORT);
}

CSettleReport::CSettleReport(CSettleEngine::HSettleData settleData):
	CTable((void*)&m_data)
{
	memset(&this->m_data, 0, sizeof(this->m_data));
	this->m_recordSize = sizeof(CSettleReport::SettleReportData);
	sprintf(this->m_fileName, "%s", TABLE_NAME_SETTLE_REPORT);

	SetData(settleData);	
}

CSettleReport::~CSettleReport()
{

}

void CSettleReport::SetData(CSettleEngine::HSettleData settleData)
{
	uchar DateTime[7] = "";

	itoa(settleData->m_saleCount, this->m_data.m_saleCount, 10);
	itoa(settleData->m_saleTotal, this->m_data.m_saleTotal, 10);
	itoa(settleData->m_saleVoidCount, this->m_data.m_saleVoidCount, 10);
	itoa(settleData->m_saleVoidTotal, this->m_data.m_saleVoidTotal, 10);

	itoa(settleData->m_cashLoadCount, this->m_data.m_cashLoadCount, 10);
	itoa(settleData->m_cashLoadTotal, this->m_data.m_cashLoadTotal, 10);
	itoa(settleData->m_cashLoadVoidCount, this->m_data.m_cashLoadVoidCount, 10);
	itoa(settleData->m_cashLoadVoidTotal, this->m_data.m_cashLoadVoidTotal, 10);

	itoa(settleData->m_debitLoadCount, this->m_data.m_debitLoadCount, 10);
	itoa(settleData->m_debitLoadTotal, this->m_data.m_debitLoadTotal, 10);
	itoa(settleData->m_debitLoadVoidCount, this->m_data.m_debitLoadVoidCount, 10);
	itoa(settleData->m_debitLoadVoidTotal, this->m_data.m_debitLoadVoidTotal, 10);

	itoa(settleData->m_creditLoadCount, this->m_data.m_creditLoadCount, 10);
	itoa(settleData->m_creditLoadTotal, this->m_data.m_creditLoadTotal, 10);
	itoa(settleData->m_creditLoadVoidCount, this->m_data.m_creditLoadVoidCount, 10);
	itoa(settleData->m_creditLoadVoidTotal, this->m_data.m_creditLoadVoidTotal, 10);
	
	itoa(settleData->m_PointUseCount, this->m_data.m_PocharUseCount, 10);
	itoa(settleData->m_PointUseTotal, this->m_data.m_PocharUseTotal, 10);
	itoa(settleData->m_PointUseVoidCount, this->m_data.m_PocharUseVoidCount, 10);
	itoa(settleData->m_PointUseVoidTotal, this->m_data.m_PocharUseVoidTotal, 10);
	
	itoa(settleData->m_refundCount, this->m_data.m_refundCount, 10);
	itoa(settleData->m_refundTotal, this->m_data.m_refundTotal, 10);
	itoa(settleData->m_refundVoidCount, this->m_data.m_refundVoidCount, 10);
	itoa(settleData->m_refundVoidTotal, this->m_data.m_refundVoidTotal, 10);
	
	GetTime(this->m_data.m_settleDate);	
}

int CSettleReport::Append()
{
	// gunsonu raporu sadece bir tane kaydedilir. Eskisi silinir.
	this->Delete();

	if (!this->Open()) {
		return GENERAL_FAILURE;//FILE_NOT_OPENED;
	}

	this->m_currentRecordNo = this->GotoEnd();
	this->Write((void *)&this->m_data, this->m_recordSize);

	this->Close();

	++this->m_currentRecordNo;
	++this->m_recordCount;
	return this->m_currentRecordNo;
}

void CSettleReport::PrintAll()
{
	char tmp[255] = "";
	char dateTime[20] = "";
	CPrinterEngine* pEng = new CPrinterEngine();

	pEng->Init();
	pEng->PrintLogo();

	// Merchant
	CTerminal term;
	CTerminal::HTerminalRecord hTerm;
	CAcquier acq;
	int currBatch = 0;

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
	PrnStr("%*s%s\n\n", (19 - strlen("GUN SONU")) / 2, " ", "GUN SONU");
	

	if (acq.Open()) 
	{
		acq.GotoRec(1, true);
		currBatch = acq.GetBatchNo();
		acq.Close();

		// Batch - Stan
		pEng->PrnSetSmall();
		PrnStr("Batch No\n");
		pEng->PrnSetNormal();
		PrnStr("%d\n", currBatch);
	}
	
	// DateTime
	pEng->PrnSetSmall();
	PrnStr("Tarih / Zaman\n");
	pEng->PrnSetNormal();
	date2str(this->m_data.m_settleDate, dateTime, DateType_DD_MM_YYYY_HH_mm_SS);
	PrnStr("%s\n", dateTime);

/*
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

*/  
	pEng->PrnSetNormal();

	PrnFontSet(6, 0);
	PrnStr("Harcama\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_saleCount, atoi(this->m_data.m_saleTotal) / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n",	this->m_data.m_saleVoidCount, atoi(this->m_data.m_saleVoidTotal) / 100.);

	PrnFontSet(6, 0);
	PrnStr("Nakit Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_cashLoadCount, atoi(this->m_data.m_cashLoadTotal) / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n",	this->m_data.m_cashLoadVoidCount, atoi(this->m_data.m_cashLoadVoidTotal) / 100.);

	PrnFontSet(6, 0);
	PrnStr("Banka Karti Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_debitLoadCount, atoi(this->m_data.m_debitLoadTotal) / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n",	this->m_data.m_debitLoadVoidCount, atoi(this->m_data.m_debitLoadVoidTotal) / 100.);

	PrnFontSet(6, 0);
	PrnStr("Kredi Karti Yukleme\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_creditLoadCount, atoi(this->m_data.m_creditLoadTotal)/ 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n", this->m_data.m_creditLoadVoidCount, atoi(this->m_data.m_creditLoadVoidTotal) / 100.);

	PrnFontSet(6, 0);
	PrnStr("Puan Kullanma\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_PocharUseCount, atoi(this->m_data.m_PocharUseTotal) / 100.);
	PrnStr("IPTAL\n");
	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n", this->m_data.m_PocharUseVoidCount, atoi(this->m_data.m_PocharUseVoidTotal) / 100.);

	PrnFontSet(6, 0);
	PrnStr("Iade\n");
	pEng->PrnSetNormal();
	PrnStr("Adet: %s  Toplam: %.02lf TL\n",	this->m_data.m_refundCount, atoi(this->m_data.m_refundTotal) / 100.);
//	PrnStr("IPTAL\n");
//	PrnStr("Adet: %s  Toplam: %.02lf TL\n\n", this->m_data.m_PocharUseVoidCount, atoi(this->m_data.m_PocharUseVoidTotal) / 100.);

	PrnStr("\n\n\n\n\n");
	
	pEng->Start();

	delete pEng;
}