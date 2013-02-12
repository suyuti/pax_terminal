// FileSystem.cpp: implementation of the FileSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "FileSystem.h"
#include "..\Files\Batch.h"
#include "..\Files\Paramters.h"
#include "..\Files\Acquier.h"
#include "..\UI\MessageBox.h"
#include "..\Engine\Engine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSystem::CFileSystem() :
	m_pEngine((CEngine*)NULL)
{

}

//---------------------------------------------------------------------------

CFileSystem::CFileSystem(CEngine* pEng) :
	m_pEngine(pEng)
{

}

//---------------------------------------------------------------------------

CFileSystem::~CFileSystem()
{

}

//---------------------------------------------------------------------------

bool CFileSystem::ExistsSysFiles()
{
	if (fexist((char*)TABLE_NAME_DEF_PARAMS) == -1) {

		CParamters pParam;// = new CParamters();
		pParam.CreateDefaults();
		pParam.Append();
		//delete pParam;
		PRNLINE("Paramere olusturuldu\n");
	}

	if ((fexist((char*)TABLE_NAME_BATCH	) == -1)) { 
		// batch dosyasi bos olarak olusturulur.
		int fp = open(TABLE_NAME_BATCH, O_CREATE|O_RDWR);
		close(fp);
		PRNLINE("Batch olusturuldu\n");
	}

	if ((fexist((char*)TABLE_NAME_TERMINAL	) == -1) ||
		(fexist((char*)TABLE_NAME_ACQUIER	) == -1)) {
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------

bool CFileSystem::ValidSysFiles()
{
	return true;
/*	if ((fexist((char *)TABLE_NAME_DEF_PARAMS) < 0) ||
		(filesize((char *)TABLE_NAME_DEF_PARAMS) != sizeof(CParamters::ParameterRecord))) {
		return false;
	}
	//if ((fexist((char *)TABLE_NAME_BATCH)<0) ||
	//	(filesize((char *)TABLE_NAME_BATCH)!=MAX_TRANLOG*sizeof(TRAN_LOG)) )
	//{
	//	return FALSE;
	//}
	return true;
*/
}

void CFileSystem::CreateNew()
{
	remove((char *)TABLE_NAME_DEF_PARAMS);
	remove((char *)TABLE_NAME_BATCH);
	remove((char *)TABLE_NAME_ACQUIER);
	remove((char *)TABLE_NAME_TERMINAL);
	remove((char *)TABLE_NAME_ACQUIER ".tmp");
	remove((char *)TABLE_NAME_TERMINAL ".tmp");

/*	int fp = open(TABLE_NAME_DEF_PARAMS, O_CREATE|O_RDWR);
	close(fp);
	fp = open(TABLE_NAME_BATCH, O_CREATE|O_RDWR);
	close(fp);
	fp = open(TABLE_NAME_ACQUIER, O_CREATE|O_RDWR);
	close(fp);
	fp = open(TABLE_NAME_TERMINAL, O_CREATE|O_RDWR);
	close(fp);
*/
	//!
}

//---------------------------------------------------------------------------
// fix me

bool CFileSystem::CheckFileSystem()
{
	CMessageBox msg("ilklendiriliyor...", MB_SHOW_ONLY);
	msg.Draw();
	if (this->ExistsSysFiles()) {
		PRNLINE("ExistsSysFiles() OK");
		if (this->ValidSysFiles()) {
			PRNLINE("ValidSysFiles() OK");
			this->m_pEngine->SetParametreOK(true);
		}
		else {
			PRNLINE("ValidSysFiles() ERR");
			/*
			this->m_pEngine->GetDefParams()->Delete();
			this->m_pEngine->GetDefParams()->CreateDefaults();
			this->m_pEngine->GetDefParams()->Append();

			this->m_pEngine->GetTerminal()->Delete();
			this->m_pEngine->GetTerminal()->CreateDefault();
			this->m_pEngine->GetTerminal()->Append();
			*/
		}
	}
	else {
		PRNLINE("ExistsSysFiles() ERR");
		msg.SetMessage("Parametre eksik!");
		msg.Draw();

		this->m_pEngine->SetParametreOK(false);
/**/
		CParamters param;
		param.Delete();
		param.CreateDefaults();
		param.Append();

		CBatch* pBatch = new CBatch();
		pBatch->Open();
		pBatch->Close();
		delete pBatch;
/**/
	}

	return true;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
