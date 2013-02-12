// Table.cpp: implementation of the CTable class.
//
//////////////////////////////////////////////////////////////////////

#include "Table.h"

//--------------------------------------------------------------------------------------------------

CTable::CTable() :
	m_pData((void *)NULL),
	m_handle(-1),
	m_bOpened(false),
	m_recordSize(0),
	m_recordCount(0),
	m_currentRecordNo(-1)
{
}

//--------------------------------------------------------------------------------------------------

CTable::CTable(void* pData) :
	m_pData(pData),
	m_handle(-1),
	m_bOpened(false),
	m_recordSize(0),
	m_recordCount(0),
	m_currentRecordNo(-1)
{
}

//--------------------------------------------------------------------------------------------------

CTable::~CTable()
{
	this->Close();
}

//--------------------------------------------------------------------------------------------------

bool CTable::Open()
{
	this->m_handle = open(this->m_fileName, O_CREATE|O_RDWR);
	if (this->m_handle < 0) {
		PRNLINE("dosya acilamadi.");
		this->m_bOpened = false;
		return false;
	}
	this->CalcRecordCount();
	this->m_bOpened = true;
	return true;
}

//--------------------------------------------------------------------------------------------------

void CTable::Delete()
{
	remove(this->m_fileName);
}

//--------------------------------------------------------------------------------------------------

void CTable::Close()
{
	close(this->m_handle);
	this->m_bOpened = false;
	this->m_handle = -1;
}

//--------------------------------------------------------------------------------------------------

int CTable::GotoEnd()
{
	ASSERT(this->m_bOpened);
	ASSERT(this->m_recordSize > 0);

	int rec = (filesize(this->m_fileName) / this->m_recordSize);
	if (seek(this->m_handle, 0, SEEK_END) == 0) {
		this->m_currentRecordNo = rec;
		return this->m_currentRecordNo;
	}
	return (-1);
}

//--------------------------------------------------------------------------------------------------

int CTable::GotoBegin()
{
	ASSERT(this->m_bOpened);
	seek(this->m_handle, 0, SEEK_SET);
	this->m_currentRecordNo = 1;
	return 1;
}

//--------------------------------------------------------------------------------------------------

int CTable::GotoRec(int recNo, bool read)
{
	ASSERT(recNo <= this->m_recordCount);

	int rec = this->m_currentRecordNo;
	if (seek(this->m_handle, ((recNo-1) * this->m_recordSize), SEEK_SET) == 0) {
		if (read) {
			this->Read(this->m_pData, this->m_recordSize);
		}
		this->m_currentRecordNo = recNo;
		return recNo;
	}
	else {
		return (-1);
	}
}

//--------------------------------------------------------------------------------------------------

int CTable::CalcRecordCount()
{
	//ASSERT(this->m_bOpened == true);
	this->m_recordCount = filesize(this->m_fileName) / this->m_recordSize;
	//char tmp[100] = "";
	//sprintf(tmp, "%d / %d\n",filesize(this->m_fileName), this->m_recordSize);
	//PRNLINE(tmp);
	return this->m_recordCount;
}

//--------------------------------------------------------------------------------------------------

int CTable::Write(void* pData, int size)
{
	int		iWriteBytes, iLeftBytes;
	uchar   *psTmp;
	
	ASSERT(this->m_handle >= 0 );
	ASSERT(pData != NULL );
	ASSERT(size >= 0 );
	psTmp      = (uchar *)pData;
	iLeftBytes = size;
	
	while (iLeftBytes > 0) {
		iWriteBytes = write(this->m_handle, psTmp, iLeftBytes);
		if (iWriteBytes <= 0) {
			//PubTRACE2("FWN:%d,%d", iWriteBytes, iLeftBytes);
			//PubTRACE1("errno:%d", errno);
			break;
		}
		iLeftBytes -= iWriteBytes;
		psTmp	   += iWriteBytes;
	}
	
	return (size - iLeftBytes);
}

//--------------------------------------------------------------------------------------------------

int CTable::Read(void* pBuffer, int size)
{
	int		iReadBytes, iLeftBytes;
	uchar	*psTmp;
	
	ASSERT(this->m_handle >= 0 && pBuffer !=NULL && size >= 0);

	psTmp      = (uchar *)pBuffer;
	iLeftBytes = size;
	while (iLeftBytes > 0) {
		iReadBytes = read(this->m_handle, psTmp, iLeftBytes);
		if (iReadBytes <= 0) {
			//PubTRACE1("errno:%d", errno);
			break;
		}
		iLeftBytes -= iReadBytes;
		psTmp	   += iReadBytes;
	}
	
	return (size - iLeftBytes);
}

//--------------------------------------------------------------------------------------------------

void CTable::Update()
{
	this->GotoRec(this->m_currentRecordNo, false);
	this->Write(this->m_pData, this->m_recordSize);
}

//--------------------------------------------------------------------------------------------------

bool CTable::Validate()
{
	return true;
	//int fileSize = filesize(this->m_fileName)
}

//--------------------------------------------------------------------------------------------------

int CTable::Append()
{
	if (!this->Open()) {
		return GENERAL_FAILURE;//FILE_NOT_OPENED;
	}
	this->m_currentRecordNo = this->GotoEnd();
	this->Write((void *)&this->m_pData, this->m_recordSize);

	this->Close();

	++this->m_currentRecordNo;
	++this->m_recordCount;
	return this->m_currentRecordNo;
}

//--------------------------------------------------------------------------------------------------

int CTable::MoveFile(char* pSource, char* pDest)
{
	int fpSource, fpDest;
	long size;
	long moved = 0;
	long remaining = 0;
	unsigned char tmp[512];
	
	remove(pDest);

	size		= filesize(pSource);
	fpSource	= open(pSource, O_RDWR);
	fpDest		= open(pDest, O_CREATE|O_RDWR);
	
	remaining = size; 

	do {
		moved = read(fpSource, tmp, remaining > 512 ? 512 : remaining);
		remaining -= moved;
		write(fpDest, tmp, moved);
		if (remaining <= 0) {
			break;
		}
	} while(true);

	close(fpSource);
	close(fpDest);

	remove(pSource);
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
