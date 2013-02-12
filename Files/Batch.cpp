// Batch.cpp: implementation of the CBatch class.
//
//////////////////////////////////////////////////////////////////////

#include "Batch.h"
#include "..\Util\NumFuncs.h"
#include "..\Trnx\TrnxFactory.h"

//--------------------------------------------------------------------------------------------------

CBatch::CBatch() :
	CTable((void*)&m_data)
{
	this->m_recordSize = sizeof(CBatch::BatchData);
	sprintf(this->m_fileName, "%s", TABLE_NAME_BATCH);
}

//--------------------------------------------------------------------------------------------------

CBatch::~CBatch()
{
}

//--------------------------------------------------------------------------------------------------

int CBatch::Append()
{
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

//--------------------------------------------------------------------------------------------------

void CBatch::SetResponseCode(int respCode)
{
	this->m_data.m_responseCode = respCode;
	//Lng2Bcd(respCode, (unsigned char *)this->m_data.m_responseCode, 1);
}

//--------------------------------------------------------------------------------------------------

void CBatch::GetProcessCode(char* pDest)
{
	switch(this->m_data.m_trnxType) {
		case CTrnxFactory::trnxHarcama: 
		{
			sprintf(pDest, PRCOCODE_HARCAMA);
		}
		break;
		case CTrnxFactory::trnxBakiyeSorgu: 
		{
			sprintf(pDest, PRCOCODE_BAKIYESORGU);
		}
		break;
		case CTrnxFactory::trnxKrediKartYukleme: 
		{
			sprintf(pDest, PRCOCODE_KREDIKART_YUKLEME);
		}
		break;
		case CTrnxFactory::trnxDebitYukleme: 
		{
			sprintf(pDest, PRCOCODE_BANKAKART_YUKLEME);
		}
		break;
		case CTrnxFactory::trnxNakitYukleme: 
		{
			sprintf(pDest, PRCOCODE_NAKIT_YUKLEME);
		}
		break;
		case CTrnxFactory::trnxPuanKullanma: 
		{
			sprintf(pDest, PRCOCODE_PUANKULLANMA);
		}
		break;
		case CTrnxFactory::trnxPuanSorgu: 
		{
			sprintf(pDest, PRCOCODE_PUANSORGU);
		}
		break;
		case CTrnxFactory::trnxKartGuncelle: 
		{
			sprintf(pDest, PRCOCODE_KARTGUNCELLE);
		}
		break;
		case CTrnxFactory::trnxIade: 
		{
			sprintf(pDest, PRCOCODE_IADE);
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
int CBatch::FindByStan(int stan, int* pRec)
{
	int retVal = TRNX_NOT_FOUND;
	if (!this->Open()) {
		return BATCH_NOT_OPEN; 
	}
	for (int i = 1; i <= this->m_recordCount; ++i) {
		this->GotoRec(i, true);
		if (this->m_data.m_stan == stan) {
			*pRec = i;
			retVal = SUCCESS;
			break;
		}
	}
	this->Close();
	return retVal;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
