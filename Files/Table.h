// Table.h: interface for the CTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLE_H__06566586_FF0D_4A50_B679_0636D8222DC0__INCLUDED_)
#define AFX_TABLE_H__06566586_FF0D_4A50_B679_0636D8222DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"

class CTable  
{
public:
	typedef struct _tagHeader {
		int m_recordSize;
		int m_recordCount;
		int m_version;
	} Header, *HHeader;

private:
	CTable();
public:
	CTable(void* pData);
	virtual ~CTable();
	bool		Open();
	void		Close();
	int			GotoEnd();
	int			GotoBegin();
	int			GotoRec(int recNo, bool read = true);
	inline int	GetRecordCount()	{ return this->m_recordCount;};
	virtual int Append();
	void		Delete();
	void		Update();

	bool		Validate();
	virtual void PrintAll() = 0;

	int			Write(void*pData, int size);
	int			Read(void* pBuffer, int size);

	static int MoveFile(char* pSource, char* pDest);
private:
	int			CalcRecordCount();

protected:
	void*		m_pData;
	char		m_fileName[255];
	int			m_handle;
	int			m_recordSize;
	bool		m_bOpened;
	int			m_currentRecordNo;
	int			m_recordCount;
	Header		m_header;
};

#endif // !defined(AFX_TABLE_H__06566586_FF0D_4A50_B679_0636D8222DC0__INCLUDED_)
