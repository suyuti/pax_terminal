// CommEngine.h: interface for the CCommEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMENGINE_H__9E5CAA65_0304_47B0_9B23_A65379847DC1__INCLUDED_)
#define AFX_COMMENGINE_H__9E5CAA65_0304_47B0_9B23_A65379847DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "SxxCom.h"


class CEngine;
class CCommEngine  
{
private:
	CCommEngine();
public:
	CCommEngine(CEngine* pEng);
	virtual ~CCommEngine();

	int SendRecv();

	//--------------------------------------------------------------------

	int		CommInitModule(/*COMM_CONFIG *pstCfg*/);
	int		CommSetCfgParam(/*COMM_CONFIG *pstCfg*/);
	void	CommSwitchType(uchar ucCommType);
	int		CommDial(uchar ucDialMode);
	int		CommRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen);
	int		CommOnHook(uchar bReleaseAll);
	void	CommGetErrMsg(int iErrCode, COMM_ERR_MSG *pstCommErrMsg);

	int		CommInitGprsCdma(/*COMM_CONFIG *pstCfg*/);
	int		CommInitLAN(/*COMM_CONFIG *pstCfg*/);

	//---- GET - SET -----------------------------------------------------
	inline HCOMM_CONFIG GetCommConfig() { return &this->m_commConfig;};
	inline void SetMedia(uchar media) {this->m_commConfig.ucCommType = media;};
	void SetParameters();


	static int		ChkIfValidIp(uchar *pszIP);
	static int		ChkIfValidPort(uchar *pszPort);
	static uchar	ValidIPAddress(char *pszIPAddr);

private:
	int ConnectHost();
	int AdjustCommParam(void);
	int AskModemReDial(int iRet);
	int CommTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec);
	int TcpTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec);
	int TcpRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen);
	int SXXWlSend(uchar *psTxdData, ushort usDataLen, ushort uiTimeOutSec);
	int SXXWlRecv(uchar *psRxdData, ushort usExpLen, ushort uiTimeOutSec, ushort *pusOutLen);

	int SendPacket();
	int RecvPacket();


	
private:
	CEngine* m_pEngine;
	COMM_CONFIG m_commConfig;
	CComm		m_comm;
	COMM_DATA	m_sendData;
	COMM_DATA	m_recvData;
};

#endif // !defined(AFX_COMMENGINE_H__9E5CAA65_0304_47B0_9B23_A65379847DC1__INCLUDED_)
