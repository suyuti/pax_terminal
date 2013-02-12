// FileSystem.h: interface for the FileSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESYSTEM_H__D62739B1_C720_4E5C_ADAD_E1DC58E7EED4__INCLUDED_)
#define AFX_FILESYSTEM_H__D62739B1_C720_4E5C_ADAD_E1DC58E7EED4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEngine;
class CFileSystem  
{
private:
	CFileSystem();
public:
	CFileSystem(CEngine* pEng);
	virtual ~CFileSystem();

	bool CheckFileSystem();
	void CreateNew();

private:
	bool ExistsSysFiles();
	bool ValidSysFiles();
private:
	CEngine* m_pEngine;
};

#endif // !defined(AFX_FILESYSTEM_H__D62739B1_C720_4E5C_ADAD_E1DC58E7EED4__INCLUDED_)
