
//#include "global.h"
#include "SxxCom.h"

/********************** Internal macros declaration ************************/
#define TCPMAXSENDLEN		10240

/********************** Internal structure declaration *********************/

/********************** Internal functions declaration *********************/
static int SxxTcpConnect(char *pszIP, short sPort, int iTimeout);
static uchar SocketCheck(int sk);

/********************** Internal variables declaration *********************/

/********************** external reference declaration *********************/
/******************>>>>>>>>>>>>>Implementations<<<<<<<<<<<<*****************/
#include "CommEngine.h"
//----------------------------------------------------------------------------------------------------

CComm::CComm()
{
}
//----------------------------------------------------------------------------------------------------
CComm::~CComm()
{
}
//----------------------------------------------------------------------------------------------------



#if defined(SXX_IP_MODULE) || defined(SXX_WIRELESS_MODULE)









//----------------------------------------------------------------------------------------------------

// Sxx TCP connection
// Shared by GPRS/CDMA/PPP/LAN/WIFI/...
int CComm::SxxTcpConnect(char *pszIP, short sPort, int iTimeoutSec)
{
	int		iRet;
	struct net_sockaddr stServer_addr;

	// Setup socket
	iRet = NetSocket(NET_AF_INET, NET_SOCK_STREAM, 0);
	if (iRet != 0) {
		return iRet;	
	}
	this->sg_iSocket = iRet;

	// Bind IP
	iRet = SockAddrSet(&stServer_addr, pszIP, sPort);
	if (iRet != 0) {
		return iRet;
	}

	// set connection timeout
	if (iTimeoutSec < 3) {
		iTimeoutSec = 3;
	}
	iRet = Netioctl(this->sg_iSocket, CMD_TO_SET, iTimeoutSec*1000);
	if (iRet != 0) {
		return iRet;
	}

	// Connect to remote IP
	iRet = NetConnect(this->sg_iSocket, &stServer_addr, sizeof(stServer_addr));
	if (iRet != 0) {
		NetCloseSocket(this->sg_iSocket);
	}

	return iRet;
}

//----------------------------------------------------------------------------------------------------

//Sxx TCP/IP send data
// Shared by GPRS/CDMA/PPP/LAN/WIFI/...
int CComm::SxxTcpTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec)
{
	int iRet;
	int iSendLen;
	int iSumLen;

	iRet = Netioctl(this->sg_iSocket, CMD_TO_SET, uiTimeOutSec*1000);
	if (iRet < 0) {
		return iRet;
	}

	iSumLen = 0;
	while (1) {
		if (uiDataLen > TCPMAXSENDLEN) {
			iSendLen = TCPMAXSENDLEN;
			uiDataLen = uiDataLen - TCPMAXSENDLEN;
		}
		else {
			iSendLen = uiDataLen;
		}	
		iRet = NetSend(this->sg_iSocket, psTxdData+iSumLen, iSendLen, 0);
		if (iRet < 0) {
			return iRet;
		}
		if (iRet != iSendLen) {
			return -1;
		}
		iSumLen = iSumLen + iSendLen;
		if (iSendLen <= TCPMAXSENDLEN) {
			break;
		}	
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------
//Sxx TCP/IP receive
// Shared by GPRS/CDMA/PPP/LAN/WIFI/...
int CComm::SxxTcpRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen)
{
	int iRet;

	DelayMs(200);

	iRet = 	Netioctl(this->sg_iSocket, CMD_TO_SET, uiTimeOutSec*1000);
	if (iRet < 0) {
		return iRet;
	}

	iRet = NetRecv(this->sg_iSocket, psRxdData, uiExpLen, 0);
	if (iRet < 0) {
		return iRet;
	}
	*puiOutLen = iRet;

	return 0;
}

//----------------------------------------------------------------------------------------------------
//Sxx TCP/IP close socket
// Shared by GPRS/CDMA/PPP/LAN/WIFI/...
int CComm::SxxTcpOnHook(void)
{
	int iRet;

	iRet = NetCloseSocket(this->sg_iSocket);
	if (iRet < 0) {
		return iRet;
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------

uchar CComm::SocketCheck(int sk)
{
	int event;
	if (sk < 0) 
		return RET_TCPCLOSED;
	
	event = Netioctl(sk, CMD_EVENT_GET, 0);
	if(event < 0) {
         NetCloseSocket(sk);
         return RET_TCPCLOSED;
	}	
	
	if(event & (SOCK_EVENT_CONN|SOCK_EVENT_WRITE|SOCK_EVENT_READ)) {
         return RET_TCPOPENED;
	}
	else if(event&(SOCK_EVENT_ERROR)) {
         NetCloseSocket(sk);
         return RET_TCPCLOSED;
	}

	return RET_TCPOPENING;
}

//----------------------------------------------------------------------------------------------------
#endif	 // SXX_WIRELESS_MODULE || SXX_IP_MODULE

#ifdef SXX_IP_MODULE

//----------------------------------------------------------------------------------------------------

int CComm::SxxDhcpStart(uchar ucForceStart, uchar ucTimeOutSec)
{
	int	iRet;

	if (ucForceStart && (DhcpCheck() == 0)) {
		DhcpStop();
	}

	if (ucForceStart || (DhcpCheck() != 0)) {
		iRet = DhcpStart();
		if (iRet < 0) {
			return iRet;
		}

		TimerSet(TIMER_TEMPORARY, (ushort)(ucTimeOutSec*10));
		while (TimerCheck(TIMER_TEMPORARY) != 0) {
			DelayMs(200);
			iRet = DhcpCheck();
			if (iRet == 0) {
				return 0;
			}
		}

		return iRet;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------

int CComm::SxxLANTcpDial(TCPIP_PARA *pstTcpPara)
{
	int		iRet;
	uchar	ucRedoDhcp, ucSecondIP;

	CommOnHook(FALSE);

	if (pstTcpPara->ucDhcp) {
		iRet = SxxDhcpStart(FALSE, 30);
		if (iRet != 0) {	
			return iRet;
		}
	}

	ucRedoDhcp = FALSE;
	ucSecondIP = FALSE;

TAG_RETRY_IP:

	// Connect to remote IP
	if (ucSecondIP) {
		iRet = SxxTcpConnect((char*)pstTcpPara->szRemoteIP_2, (short)atoi(pstTcpPara->szRemotePort_2), 8);
	}
	else {
		iRet = SxxTcpConnect((char*)pstTcpPara->szRemoteIP_1, (short)atoi(pstTcpPara->szRemotePort_1), 8);
	}

	if (iRet!=0) {
		if (!ucSecondIP) {
			if (pstTcpPara->ucDhcp && !ucRedoDhcp) {
				// If fail, suspect the DHCP
				iRet = SxxDhcpStart(FALSE, 10);
				if (iRet!=0) {
					return iRet;
				}
				ucRedoDhcp = TRUE;
				goto TAG_RETRY_IP;
			}

			if (CCommEngine::ChkIfValidIp(pstTcpPara->szRemoteIP_2) && 
				CCommEngine::ChkIfValidPort(pstTcpPara->szRemotePort_2) &&
				(strcmp((char *)(pstTcpPara->szRemoteIP_1), (char *)(pstTcpPara->szRemoteIP_2))!=0)) {
				ucSecondIP = TRUE;
				goto TAG_RETRY_IP;
			}
		}
	}

	return iRet;
}

//----------------------------------------------------------------------------------------------------

#endif	// SXX_IP_MODULE

#ifdef SXX_WIRELESS_MODULE

//----------------------------------------------------------------------------------------------------
int CComm::SXXWlInit(WIRELESS_PARAM *pstWlPara)
{
	int iRet;

	iRet = WlInit(pstWlPara->szSimPin);
	if (iRet == -212)	//模块已初始化
		iRet = 0;

	SXXWlDispSignal();

	return iRet;
}

//----------------------------------------------------------------------------------------------------
int CComm::SXXWlDial(WIRELESS_PARAM *pstWlPara, int iTimeOut, int iAliveInterval, uchar ucPredial)
{
	int		iRet;
	int		iRetryTime;
	uchar	ucSecondIP;

	SXXWlDispSignal();
	
	if (iTimeOut<1) {
		iTimeOut = 1;
	}

	// ********** Pre-dial **********
	if (ucPredial) {
		iRet = WlPppCheck();
		if ((iRet==0) || (iRet==WL_RET_ERR_DIALING) || (iRet==1)) {	// ret=1 means module busy 
			return 0;
		}

		iRet = WlPppLogin(pstWlPara->szAPN, pstWlPara->szUID, pstWlPara->szPwd, 0xFF, 0, iAliveInterval);
		return 0;
	}

	// ********** Full-dial **********

	// ********** Check PPP connection **********
	TimerSet(TIMER_TEMPORARY, (ushort)(iTimeOut*10));
	while (TimerCheck(TIMER_TEMPORARY)!=0) {
		iRet = WlPppCheck();

		if (iRet == 0)
		{
			goto TCPCONNECT;
		}
	}

	// ********** Take PPP dial action **********
	iRetryTime = 3;
	while(iRetryTime--) {
		iRet = WlPppLogin(pstWlPara->szAPN, pstWlPara->szUID, pstWlPara->szPwd, 0xFF, iTimeOut*1000, iAliveInterval);
		if (iRet != 0)
		{
			DelayMs(100);
			continue;
		}

		iRet = WlPppCheck();
		if (iRet == 0)
		{
			break;
		}
	}

	if (iRetryTime <= 0 && iRet != 0) {
		return iRet;
	}

	// ********** Connect IP **********
TCPCONNECT:	
	iRet = SocketCheck(this->sg_iSocket);  //come from R&D, tom
//	ScrPrint(0, 7, ASCII, "tang[SocketCheck(%i)]",iRet); DelayMs(1000);
	if (iRet == RET_TCPOPENED) {
		return 0;
	}

	ucSecondIP = FALSE;

_RETRY_SECOND_IP:
	if (ucSecondIP) {
		iRet = SxxTcpConnect((char*)pstWlPara->szRemoteIP_2, (short)atoi(pstWlPara->szRemotePort_2), 8);
	} 
	else {
		iRet = SxxTcpConnect((char*)pstWlPara->szRemoteIP_1, (short)atoi(pstWlPara->szRemotePort_1), 8);
	}

	if (iRet < 0) {
		if (CCommEngine::ChkIfValidIp(pstWlPara->szRemoteIP_2) && 
			CCommEngine::ChkIfValidPort(pstWlPara->szRemotePort_2) &&
			(strcmp((char *)(pstWlPara->szRemoteIP_1), (char *)(pstWlPara->szRemoteIP_2))!=0)) {
			ucSecondIP = TRUE;
			goto _RETRY_SECOND_IP;
		}

		return iRet;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------

int CComm::SXXWlSend(uchar *psTxdData, ushort usDataLen, ushort uiTimeOutSec)
{
	return SxxTcpTxd(psTxdData, usDataLen, uiTimeOutSec);
}

//----------------------------------------------------------------------------------------------------

int CComm::SXXWlRecv(uchar *psRxdData, ushort usExpLen, ushort uiTimeOutSec, ushort *pusOutLen)
{
	DelayMs(200);
	return SxxTcpRxd(psRxdData, usExpLen, uiTimeOutSec, pusOutLen);
}

//----------------------------------------------------------------------------------------------------

int CComm::SXXWlCloseTcp(void)
{
	int iRet;

	iRet = NetCloseSocket(this->sg_iSocket);
	if (iRet < 0)
	{
		return iRet;
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------

void CComm::SXXWlClosePPP(void)
{
	WlPppLogout(); 
	return;
}

//----------------------------------------------------------------------------------------------------

void CComm::SXXWlDispSignal(void)
{
	uchar	ucRet, ucLevel;
	
	
	ucRet = WlGetSignal(&ucLevel);
	if( ucRet!=RET_OK ) {
		ScrSetIcon(ICON_SIGNAL, CLOSEICON);
		return;
	}
	
	ScrSetIcon(ICON_SIGNAL, (uchar)(5-ucLevel));
}
//----------------------------------------------------------------------------------------------------
int CComm::CommOnHook(uchar bReleaseAll)
{
	int		iRet;
	//!
/*
	switch( sg_stCurCfg.ucCommType )
	{
	case CT_RS232:
		iRet = RS232OnHook(bReleaseAll);
		break;

	case CT_MODEM:
		iRet = PSTNOnHook(bReleaseAll);
		break;

	case CT_TCPIP:
		iRet = TcpOnHook(bReleaseAll);
		break;

#if defined(_P80_) || defined(_P90_) || defined(_S_SERIES_)
	case CT_CDMA:
	case CT_GPRS:

  #ifdef SXX_WIRELESS_MODULE
		iRet = SXXWlCloseTcp();
		if (bReleaseAll)
		{
			SXXWlClosePPP();
		}
  #elif defined(PXX_COMM)
		iRet = WirelessClose(bReleaseAll);
  #else
		return 1;
  #endif
		break;
#endif

//	case CT_WIFI:
//		break;

	case CT_DEMO:
		iRet = 0;
		break;

	default:
		iRet = ERR_COMM_INV_TYPE;
	}
*/
	return iRet;
}

#endif	// SXX_WIRELESS_MODULE

int CComm::RS232OnHook(uchar bReleaseAll)
{
	uchar	ucRet;

//!	ucRet = PortClose(sg_stCurCfg.stRS232Para.ucPortNo);
	if( ucRet==0 )
	{
		return 0;
	}

	return (ERR_COMM_RS232_BASE | ucRet);
}
int CComm::PSTNOnHook(uchar bReleaseAll)
{
#ifndef _P90_
	uchar	ucRet, ucCnt;

	for(ucCnt=0; ucCnt<3; ucCnt++)
	{
		ucRet = OnHook();
		if( ucRet==0 )
		{
			return 0;
		}
		DelayMs(50);
	}

	return (ERR_COMM_MODEM_BASE | ucRet);
#else
	return ERR_COMM_INV_PARAM;
#endif
}

int CComm::TcpOnHook(uchar bReleaseAll)
{
#ifdef SXX_IP_MODULE
	return SxxTcpOnHook();

#elif defined(PXX_COMM)
	TcpClose();
	PortClose(sg_stCurCfg.stTcpIpPara.ucPortNo);
	return 0;

#else
	return 1;

#endif
}
