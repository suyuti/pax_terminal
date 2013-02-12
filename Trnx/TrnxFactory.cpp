// TrnxFactory.cpp: implementation of the CTrnxFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "TrnxFactory.h"
#include "TrnxBakiyeYukleme.h"
#include "TrnxHarcama.h"
//#include "TrnxHarcamaIptal.h"
//#include "TrnxHarcamaIade.h"
#include "TrnxBakiyeSorgu.h"
#include "TrnxNakitYukleme.h"
#include "TrnxPuanKullanma.h"
//#include "TrnxPuanKullanmaIptal.h"
//#include "TrnxPuanKullanmaIade.h"
#include "TrnxPuanSorgu.h"
#include "TrnxKartGuncelle.h"
#include "TrnxKrediKartYukleme.h"
#include "TrnxDebitYukleme.h"
#include "TrnxRefund.h"
#include "..\Files\Batch.h"

//--------------------------------------------------------------------------------------------------

CTrnxFactory::CTrnxFactory() :
	m_pEngine((CEngine*)NULL)
{

}

//--------------------------------------------------------------------------------------------------

CTrnxFactory::CTrnxFactory(CEngine* pEng) :
	m_pEngine(pEng)
{

}

//--------------------------------------------------------------------------------------------------

CTrnxFactory::~CTrnxFactory()
{

}

//--------------------------------------------------------------------------------------------------

ITrnxBase* CTrnxFactory::CreateTrnx(TrnxTypes type)
{
	ITrnxBase* pTrnx = 0L;

	switch(type) {
		case trnxHarcama: 
			pTrnx = new CTrnxHarcama(this->m_pEngine);
		break;
		//case trnxHarcamaIptal: 
		//	pTrnx = new CTrnxHarcamaIptal(this->m_pEngine);
		//break;
		//case trnxHarcamaIade: 
		//	pTrnx = new CTrnxHarcamaIade(this->m_pEngine);
		//break;
		case trnxBakiyeSorgu: 
			pTrnx = new CTrnxBakiyeSorgu(this->m_pEngine);
		break;
		case trnxNakitYukleme: 
			pTrnx = new CTrnxNakitYukleme(this->m_pEngine);
		break;
		case trnxPuanKullanma: 
			pTrnx = new CTrnxPuanKullanma(this->m_pEngine);
		break;
		//case trnxPuanKullanmaIptal: 
		//	pTrnx = new CTrnxPuanKullanmaIptal(this->m_pEngine);
		//break;
		//case trnxPuanKullanmaIade: 
		//	pTrnx = new CTrnxPuanKullanmaIade(this->m_pEngine);
		//break;
		case trnxPuanSorgu: 
			pTrnx = new CTrnxPuanSorgu(this->m_pEngine);
		break;
		case trnxKartGuncelle: 
			pTrnx = new CTrnxKartGuncelle(this->m_pEngine);
		break;
		case trnxKrediKartYukleme:
			pTrnx = new CTrnxKrediKartYukleme(this->m_pEngine);
		break;
		case trnxDebitYukleme:
			pTrnx = new CTrnxDebitYukleme(this->m_pEngine);
		break;
		case trnxIade:
			pTrnx = new CTrnxRefund(this->m_pEngine);
		break;
	}

	return pTrnx;
}

//--------------------------------------------------------------------------------------------------
// islem kaydindan islemi olusturur.

ITrnxBase* CTrnxFactory::CreateTrnx(CBatch* pBatch)
{
	ITrnxBase* pTrnx = (ITrnxBase*)NULL;
	CBatch::HBatchData pData = pBatch->GetData();

	switch(pData->m_trnxType) {
		case trnxHarcama: 
		{
			pTrnx = new CTrnxHarcama(this->m_pEngine);
			CTrnxHarcama* pTrnxHarcama = (CTrnxHarcama*)pTrnx;
			pTrnxHarcama->SetBatchData(pData);
		}
		break;
		//case trnxHarcamaIptal: 
		//{
		//	pTrnx = new CTrnxHarcamaIptal(this->m_pEngine);
		//	CTrnxHarcamaIptal* pTrnxHarcamaIptal = (CTrnxHarcamaIptal*)pTrnx;
		//	pTrnxHarcamaIptal->SetBatchData(pData);
		//}
		//break;
		//case trnxHarcamaIade: 
		//{
		//	pTrnx = new CTrnxHarcamaIade(this->m_pEngine);
		//	CTrnxHarcamaIade* pTrnxHarcamaIade = (CTrnxHarcamaIade*)pTrnx;
		//	pTrnxHarcamaIade->SetBatchData(pData);
		//}
		break;
		case trnxBakiyeSorgu: 
		{
		}
		break;
		case trnxNakitYukleme: 
		{
			pTrnx = new CTrnxNakitYukleme(this->m_pEngine);
			CTrnxNakitYukleme* pTrnxNakitYukleme = (CTrnxNakitYukleme*)pTrnx;
			pTrnxNakitYukleme->SetBatchData(pData);
		}
		break;
		case trnxPuanKullanma: 
		{
			pTrnx = new CTrnxPuanKullanma(this->m_pEngine);
			CTrnxPuanKullanma* pTrnxPuanKullanma = (CTrnxPuanKullanma*)pTrnx;
			pTrnxPuanKullanma->SetBatchData(pData);
		}
		break;
		//case trnxPuanKullanmaIptal: 
		//{
		//	pTrnx = new CTrnxPuanKullanmaIptal(this->m_pEngine);
		//	CTrnxPuanKullanmaIptal* pTrnxPuanKullanmaIptal = (CTrnxPuanKullanmaIptal*)pTrnx;
		//	pTrnxPuanKullanmaIptal->SetBatchData(pData);
		//}
		//break;
		//case trnxPuanKullanmaIade: 
		//{
		//	pTrnx = new CTrnxPuanKullanmaIade(this->m_pEngine);
		//	CTrnxPuanKullanmaIade* pTrnxPuanKullanmaIade = (CTrnxPuanKullanmaIade*)pTrnx;
		//	pTrnxPuanKullanmaIade->SetBatchData(pData);
		//}
		//break;
		case trnxPuanSorgu: 
		{
		}
		break;
		case trnxKartGuncelle: 
		{
			pTrnx = new CTrnxKartGuncelle(this->m_pEngine);
			CTrnxKartGuncelle* pTrnxKartGuncelle = (CTrnxKartGuncelle*)pTrnx;
			pTrnxKartGuncelle->SetBatchData(pData);
		}
		break;
		case trnxKrediKartYukleme:
		{
			pTrnx = new CTrnxKrediKartYukleme(this->m_pEngine);
			CTrnxKrediKartYukleme* pTrnxKrediKartYukleme = (CTrnxKrediKartYukleme*)pTrnx;
			pTrnxKrediKartYukleme->SetBatchData(pData);
		}
		break;
		case trnxDebitYukleme:
		{
			pTrnx = new CTrnxDebitYukleme(this->m_pEngine);
			CTrnxDebitYukleme* pTrnxDebitYukleme = (CTrnxDebitYukleme*)pTrnx;
			pTrnxDebitYukleme->SetBatchData(pData);
		}
		break;
	}

	return pTrnx;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
