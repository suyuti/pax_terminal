// Engine.cpp: implementation of the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "..\UI\LoginDlg.h"
#include "..\UI\IdleDlg.h"
#include "..\UI\MessageBox.h"
#include "..\UI\ScreenTrnxLog.h"
#include "..\UI\ScreenDefParams.h"
#include "..\UI\ScreenParams.h"
#include "..\UI\ScreenBatchSum.h"
#include "..\UI\PasswordCheck.h"
#include "FileSystem.h"
#include "CommEngine2.h"
#include "TmsEngine.h"
#include "AdviceEngine.h"
#include "SettleEngine.h"
#include "..\Files\SettleReport.h"

//--------------------------------------------------------------------------------------------------

CEngine::CEngine() :
	m_pTrnxFactory((CTrnxFactory*)NULL),
	m_pUIEngine((CUIEngine*)NULL),
	m_pPrinterEngine((CPrinterEngine*)NULL)
{

}

//--------------------------------------------------------------------------------------------------

CEngine::~CEngine()
{

}

//--------------------------------------------------------------------------------------------------

int CEngine::Initialize()
{
	char tmp[64] = "";
	int gprsSignalLevel = 0;

	kbmute(0);

	CParamters::HParameterRecord hParam;

	this->m_pUIEngine = new CUIEngine();

	this->m_pUIEngine->Initialize();

	this->m_pTrnxFactory = new CTrnxFactory(this);

	this->m_pPrinterEngine	= new CPrinterEngine();
	this->m_pCommEng2		= new CCommEngine2(this);

	//this->m_pDefParams		= new CParamters();
	//this->m_pTerminal		= new CTerminal();
	//this->m_pAcquier		= new CAcquier();

	//this->m_pPrinterEngine->Test();

	//---------------------------------------
	// Dosyalar kontrol edilir.
	CFileSystem fSys(this);
	//fSys.CreateNew();
	fSys.CheckFileSystem();

	//---------------------------------------
	// Default parametreler okunur.
	//if (!this->m_pDefParams->Open()) {
	//	goto EXIT;
	//}
	//this->m_pDefParams->GotoRec(1, true);
	//this->m_pDefParams->Close();
	CParamters param;
	if (!param.Open()) {
		return PARAMS_FILE_NOT_OPEN;
	}
	param.GotoRec(1, true);
	param.Close();
	hParam = param.GetData();



	//---------------------------------------
	// Birincil baglanti turu kontrol edilir.
	// GPRS ise, initialize edilir.
	
	memcpy(tmp, hParam->m_priMedia, CParamters::sizeMedia); tmp[CParamters::sizeMedia] = 0x00;
	PRNLINE(tmp);
	if (strncmp(tmp, DEF_PRIMEDIA, CParamters::sizeMedia) == 0) {
		// GPRS ilklendirme
		PRNLINE("GPRS ilklendirme");
		CMessageBox m("GPRS\nkuruluyor.", MB_SHOW_ONLY);
		m.Draw();
		this->m_pCommEng2->SetConfig();
		if (this->m_pCommEng2->InitGPRS() == SUCCESS) {
			gprsSignalLevel = this->m_pCommEng2->GetSignalLevel();
			ScrSetIcon(ICON_SIGNAL, (uchar)(5 - gprsSignalLevel));
		}
		else {
			CMessageBox mb("GPRS kurulamadi!", MB_ANY_KEY);
			mb.Draw();
		}
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void CEngine::DeInitialize()
{
	if (this->m_pUIEngine != NULL) {
		delete this->m_pUIEngine;
		//this->m_pUIEngine = NULL;
	}
	
	if (this->m_pTrnxFactory != NULL) {
		delete this->m_pTrnxFactory;
		//this->m_pTrnxFactory = NULL;
	}

	if (this->m_pPrinterEngine != NULL) {
		delete this->m_pPrinterEngine;
	}
	if (this->m_pCommEng2 != NULL) {
		delete this->m_pCommEng2;
	}
/*	if (this->m_pDefParams != NULL) {
		delete this->m_pDefParams;
	}
	if (this->m_pTerminal!= NULL) {
		delete this->m_pTerminal;
	}
	if (this->m_pAcquier!= NULL) {
		delete this->m_pAcquier;
	}
	*/
}

//--------------------------------------------------------------------------------------------------

void CEngine::Run()
{
	CLoginDlg login;
	do {
		if (login.Draw() != SUCCESS) {
			continue;
		}
		CIdleDlg idle;
		idle.SetMessage1("   FENERBAHÇE\n      SPOR\n     KULÜBÜ");
		idle.SetMessage2("sayfa 2");
		
		do {
			idle.Draw();
			this->m_pUIEngine->EntryMenu();
		} while(true);
	} while(true);

}

//--------------------------------------------------------------------------------------------------

int CEngine::DoBakiyeYukleme()
{
/*	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}

	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxBakiyeYukleme);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
*/
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoHarcama(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxHarcama);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoVoid()
{
	int ret = this->CheckStatus();
	int stan;
	int rec;
	char passTmp	[5] = "";
	char passTmpUser[5] = "";

	if (ret != SUCCESS) {
		return ret;
	}

	//------------------

	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passVoid);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	//------------------

	CInputBox inStan("iSLEM NO\nGiriniz:", 5, 5, 6, CInputBox::itNumeric);

	if (inStan.Draw() != CInputBox::retOK) {
		return USER_CANCELLED;
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

	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(&batch);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->DoVoid(rec);
	pTrnx->Release();

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoRefund()
{
	int ret = this->CheckStatus();

	if (ret != SUCCESS) {
		return ret;
	}
	
	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passRefund);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	//------------------
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxIade);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();


	//CTrnxBase trnx;
	//trnx.DoVoid();

	//ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxHarcama);
	//if (pTrnx == (ITrnxBase*)NULL) {
	//	return OBJECT_NOT_CREATED;
	//}
	//pTrnx->DoVoid();
	//pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoHarcamaIptal(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxHarcama);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	//pTrnx->DoVoid();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoHarcamaIade(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	//ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxHarcamaIade);
	//if (pTrnx == (ITrnxBase*)NULL) {
	//	return OBJECT_NOT_CREATED;
	//}
	//pTrnx->Do();
	//pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoBakiyeSorgu(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxBakiyeSorgu);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoNakitYukleme(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxNakitYukleme);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoKrediKartYukleme(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxKrediKartYukleme);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoBankaKartYukleme(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxDebitYukleme);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoYuklemeIptal(void)
{
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxNakitYukleme); // her yuklemenin iptali ayni oldugu icin sadece biri uzerinden yapilabilir.
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	//pTrnx->DoVoid();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoPuanKullanma(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxPuanKullanma);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoPuanKullanmaIptal(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxPuanKullanma);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	//pTrnx->DoVoid();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoPuanKullanmaIade(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	//ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxPuanKullanmaIade);
	//if (pTrnx == (ITrnxBase*)NULL) {
	//	return OBJECT_NOT_CREATED;
	//}
	//pTrnx->Do();
	//pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoPuanSorgu(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxPuanSorgu);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::DoKartGuncelle(void) 
{ 
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(CTrnxFactory::trnxKartGuncelle);
	if (pTrnx == (ITrnxBase*)NULL) {
		return OBJECT_NOT_CREATED;
	}
	pTrnx->Do();
	pTrnx->Release();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::ShowIslemlerScreen(void)
{
	CScreenTrnxLog log;
	log.Draw();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::ShowToplamlarScreen(void)
{
	int ret;

	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passReport);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	CScreenBatchSum sum;
	sum.Draw();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::ShowParametreler(void)
{
	CScreenParams params;
	params.Draw();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
	
int CEngine::ShowDefaultParameters(void)
{
	CScreenDefParams def;
	def.Draw();
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void CEngine::DownloadParameters()
{
	int batchCount = 0;
	CBatch batch;
	if (batch.Open()) {
		batchCount = batch.GetRecordCount();
		batch.Close();
	}
	if (batchCount > 0) {
		CMessageBox mb("Gunsonu\nYapmalisiniz!", MB_ANY_KEY);
		mb.Draw();
		return;
	}

	CTMSEngine* pTms = new CTMSEngine(this);
	pTms->DownloadParameters();
	delete pTms;
}

//--------------------------------------------------------------------------------------------------

int CEngine::PrintLastSlip()
{
	int retVal = this->CheckStatus();

	if (retVal != SUCCESS) {
		return retVal;
	}
	CMessageBox mb("Son islem\nyazdiriliyor.", MB_SHOW_ONLY);
	mb.Draw();
	CBatch* pBatch = new CBatch();
	if (!pBatch->Open()) {
		return GENERAL_FAILURE;
	}
	int recCount = pBatch->GetRecordCount();
	pBatch->GotoRec(recCount, true);
	pBatch->Close();

	ITrnxBase* pTrnx = this->m_pTrnxFactory->CreateTrnx(pBatch);
	if (pTrnx == (ITrnxBase*)NULL) {
		delete pBatch;
		return REPRINT_NOT_SUPPORTED;
	}
	pTrnx->Print();

	delete pTrnx;
	delete pBatch;

	CUIUtils::AnimOK("YAZDIRMA\nBASARILI\n");

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::TestTemizle()
{
	int ret;
	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passDeveloper);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	remove((char *)TABLE_NAME_BATCH);
	int fp = open(TABLE_NAME_BATCH, O_CREATE|O_RDWR);
	close(fp);
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::OnAdviceTime(void)
{
	CAdviceEngine adv(this);
	adv.SendFirstAdvice(3);
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

int CEngine::CheckStatus()
{
	int retVal = SUCCESS;
	CMessageBox mb("", MB_ANY_KEY);

	if (!this->GetParametreOK()) {
		mb.SetMessage("Parametre\nyuklemelisiniz!");
		retVal = PARAMETERS_NOT_EXIST;
		goto EXIT;
	}
	
	//....

	return retVal;
EXIT:
	mb.Draw();
	return retVal;
}

//--------------------------------------------------------------------------------------------------

int CEngine::GunsonuYap(void)
{
	int ret;

	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passSettle);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	CAdviceEngine adv(this);
	ret = adv.SendFirstAdvice(MAX_TRNX_COUNT);
	if (ret != SUCCESS) {
		CMessageBox mb("Tum kayitlar\ngonderilemedi!", MB_ANY_KEY);
		mb.Draw();
		return ret;
	}

	CSettleEngine settle(this);
	if (settle.DoSettle() == SUCCESS) {
		//CTMSEngine tms(this);
		//tms.DownloadParameters();
	}
	return SUCCESS;
}

int CEngine::SonGunSonuYaz(void)
{
	int ret;

	CPasswordCheck* pwd = new CPasswordCheck();
	ret = pwd->Check(CPasswordCheck::passReport);
	if (ret != SUCCESS) {
		delete pwd;
		return ret;
	}
	delete pwd;

	CSettleReport settleReport;
	ret = settleReport.Open();
	if (ret) 
	{
		settleReport.GotoRec(1, true);
		settleReport.PrintAll();
		settleReport.Close();
	}
	else
	{
		return ret;
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
