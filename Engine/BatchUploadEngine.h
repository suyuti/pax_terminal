// BatchUploadEngine.h: interface for the CBatchUploadEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATCHUPLOADENGINE_H__55220506_5B00_4FCB_80D2_6C4FD5804D1F__INCLUDED_)
#define AFX_BATCHUPLOADENGINE_H__55220506_5B00_4FCB_80D2_6C4FD5804D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommEngine2.h"

class CBatchUploadEngine : public CCommEngine2  
{
public:
	CBatchUploadEngine();
	virtual ~CBatchUploadEngine();

	virtual int DoBatchUpload();

protected:
	virtual int		OnConnect();
	virtual int		OnBeforeSend();
	virtual int		OnAfterRecv();
};

#endif // !defined(AFX_BATCHUPLOADENGINE_H__55220506_5B00_4FCB_80D2_6C4FD5804D1F__INCLUDED_)
