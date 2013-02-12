// CommEngine.cpp: implementation of the CCommEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "CommEngine.h"
#include "..\Util\NumFuncs.h"
#include "..\UI\MessageBox.h"
#include "Engine.h"

//------------------------------------------------------------------------------------------

CCommEngine::CCommEngine():
	m_pEngine((CEngine*)NULL)
{

}

//------------------------------------------------------------------------------------------

CCommEngine::CCommEngine(CEngine* pEng) : 
	m_pEngine(pEng)
{

}

//------------------------------------------------------------------------------------------

CCommEngine::~CCommEngine()
{

}

//------------------------------------------------------------------------------------------

int	CCommEngine::CommInitModule(/*COMM_CONFIG *pstCfg*/)
{
	int		ii, iRet;

	switch(this->m_commConfig.ucCommType) {
		case CT_GPRS:
		case CT_CDMA:
			PRNLINE("CommInitModule():baglanti GPRS");
			for (ii=0; ii<3; ii++) {
				iRet = CommInitGprsCdma();
				if (iRet==0) {
					break;
				}
			}
			return iRet;
		case CT_TCPIP:
			return CommInitLAN();
		case CT_WIFI:
			//return CommInitWifi_Sxx(pstCfg);
		default:
			return 0;
	}
}

//------------------------------------------------------------------------------------------

int	CCommEngine::CommSetCfgParam(/*COMM_CONFIG *pstCfg*/)
{
	int		iLen;
	PRNLINE("CommSetCfgParam");

//	if (pstCfg == NULL) {
//		return ERR_COMM_INV_PARAM;
//	}
// 	if (!ChkIfSupportCommType(this->m_commConfig.ucCommType))
// 	{
// 		return ERR_COMM_INV_TYPE;
// 	}

	switch(this->m_commConfig.ucCommType ) {
		case CT_RS232:
		case CT_DEMO:
			iLen = strlen((char *)this->m_commConfig.stRS232Para.szAttr);
			if (iLen < 10 || iLen > 20 ) {
				return ERR_COMM_INV_PARAM;
			}
		break;
		case CT_MODEM:
			if (this->m_commConfig.stPSTNPara.szTelNo[0]==0 ) {
				return ERR_COMM_INV_PARAM;
			}
			if( this->m_commConfig.stPSTNPara.ucSendMode != CM_ASYNC &&
				this->m_commConfig.stPSTNPara.ucSendMode != CM_SYNC ) {
				return ERR_COMM_INV_PARAM;
			}
		break;
		case CT_TCPIP:
		case CT_WIFI:
			if (!ChkIfValidIp(this->m_commConfig.stTcpIpPara.szLocalIP)) {
				return ERR_COMM_INV_PARAM;
			}
			if (!ChkIfValidIp(this->m_commConfig.stTcpIpPara.szRemoteIP_1) ||
				!ChkIfValidPort(this->m_commConfig.stTcpIpPara.szRemotePort_1)) {
				return ERR_COMM_INV_PARAM;
			}
	    break;
		case CT_CDMA:
		case CT_GPRS:
			PRNLINE("1");

			if( strlen((char *)(this->m_commConfig.stWirlessPara.szAPN)) == 0) {
	PRNLINE("2");
				return ERR_COMM_INV_PARAM;
			}
			if( !ChkIfValidIp(this->m_commConfig.stWirlessPara.szRemoteIP_1) ||
				!ChkIfValidPort(this->m_commConfig.stWirlessPara.szRemotePort_1) )
			{
	PRNLINE("3");
				return ERR_COMM_INV_PARAM;
			}
	PRNLINE("4");
		break;
		default:
			return ERR_COMM_INV_TYPE;
	}

	//? memcpy(&sg_stCurCfg, pstCfg, sizeof(COMM_CONFIG));

	return 0;
}

//------------------------------------------------------------------------------------------

void CCommEngine::CommSwitchType(uchar ucCommType)
{
}

//------------------------------------------------------------------------------------------

int	CCommEngine::CommDial(uchar ucDialMode)
{
	int		iRet;
/*
	switch( sg_stCurCfg.ucCommType )
	{
	case CT_RS232:
		iRet = RS232Dial(ucDialMode);
		break;

	case CT_MODEM:
		iRet = PSTNDial(ucDialMode);
		break;

	case CT_TCPIP:
		iRet = RouteGetDefault();
		if (iRet!=0)
		{
			iRet = RouteSetDefault(0);
		}
		iRet = TcpDial(ucDialMode);
	    break;

#if defined(_P80_) || defined(_P90_) || defined(_S_SERIES_)
	case CT_CDMA:
	case CT_GPRS:
*/
  #ifdef SXX_WIRELESS_MODULE
		iRet = m_comm.SXXWlDial(&this->m_commConfig.stWirlessPara, 60, 3600, (uchar)(ucDialMode==DM_PREDIAL));
  #elif defined(PXX_COMM)
		iRet = WirelessDial(ucDialMode);
  #else
		return 1;
  #endif
/*		break;
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

//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------

int	CCommEngine::CommRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen)
{
	return SUCCESS;
}

//------------------------------------------------------------------------------------------

int	CCommEngine::CommOnHook(uchar bReleaseAll)
{
	return SUCCESS;
}

//------------------------------------------------------------------------------------------

void CCommEngine::CommGetErrMsg(int iErrCode, COMM_ERR_MSG *pstCommErrMsg)
{
}

//------------------------------------------------------------------------------------------
int CCommEngine::CommInitGprsCdma(/*COMM_CONFIG *pstCfg*/)
{
	PRNLINE("CommInitGPRSCdma");
#if defined(_P80_) || defined(_P90_) || defined(_S_SERIES_)
	CommSetCfgParam();

  #ifdef SXX_WIRELESS_MODULE
	return  m_comm.SXXWlInit(&this->m_commConfig.stWirlessPara);
  #elif defined(PXX_COMM)
	return InitWirelessModule(&this->m_commConfig.stWirlessPara);
  #else
	return 1;
  #endif
#else
	return 0;
#endif
}
//------------------------------------------------------------------------------------------
int CCommEngine::CommInitLAN(/*COMM_CONFIG *pstCfg*/)
{
#ifdef SXX_IP_MODULE
	if (this->m_commConfig.stTcpIpPara.ucDhcp)
	{
		return m_comm.SxxDhcpStart(FALSE, 30);		// If already get DHCP in manager or other EDC, no need to re-start.
	}
#endif

	return 0;
}

//------------------------------------------------------------------------------------------

int CCommEngine::ChkIfValidIp(uchar *pszIP)
{
	return ((pszIP[0]!=0) && (ValidIPAddress((char*)pszIP)));
}

//------------------------------------------------------------------------------------------

int CCommEngine::ChkIfValidPort(uchar *pszPort)
{
	return ((pszPort[0]!=0) &&
			(atol((uchar *)pszPort)>0) &&
			(atol((uchar *)pszPort)<65536));
}

//------------------------------------------------------------------------------------------

uchar CCommEngine::ValidIPAddress(char *pszIPAddr)
{
	int		i;
	char	*p, *q, szBuf[5+1];

	PubTrimStr((uchar *)pszIPAddr);
	if( *pszIPAddr==0 )
	{
		return FALSE;
	}

	p = strchr(pszIPAddr, ' ');
	if( p!=NULL )
	{
		return FALSE;
	}
	if( strlen(pszIPAddr)>15 )
	{
		return FALSE;
	}

	// 1st --- 3rd  part
	for(q=pszIPAddr, i=0; i<3; i++)
	{
		p = strchr(q, '.');
		if( p==NULL || p==q || p-q>3 )
		{
			return FALSE;
		}
		sprintf(szBuf, "%.*s", (int)(p-q), q);
		if( !IsNumStr(szBuf) || atoi(szBuf)>255 )
		{
			return FALSE;
		}
		q = p + 1;
	}

	// final part
	p = strchr((char *)q, '.');
	if( p!=NULL || !IsNumStr(q) || strlen(q)==0 || strlen(q)>3 || atoi(q)>255 )
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------------------------------

// connect to host
int CCommEngine::ConnectHost(void)
{
	int		iRet;

	while (1) {
		iRet = AdjustCommParam();
		if (iRet != 0) {
			if ((this->m_commConfig.ucCommTypeBak != CT_NONE) && 
				(this->m_commConfig.ucCommType != this->m_commConfig.ucCommTypeBak))	{	// switch to next connection
				
				//! this->m_commConfig.ucCommType = glSysParam.stTxnCommCfg.ucCommTypeBak;
				//! CommSwitchType(glSysParam.stTxnCommCfg.ucCommTypeBak);
				//! continue;
			}

			if (iRet != ERR_NO_TELNO) {
				//!DispCommErrMsg(iRet);
				return ERR_NO_DISP;
			}
			return iRet;
		}

		kbflush();
		CMessageBox mb("Araniyor...", MB_SHOW_ONLY);
		mb.Draw();

		iRet = CommDial(DM_DIAL);
		if (iRet == 0) {
			return 0;
		}

		if ((kbhit()==0) && (getkey() == KEYCANCEL)) {
			return ERR_USERCANCEL;
		}

		if ((this->m_commConfig.ucCommTypeBak!=CT_NONE) && (this->m_commConfig.ucCommType!=this->m_commConfig.ucCommTypeBak)) {
			this->m_commConfig.ucCommType = this->m_commConfig.ucCommTypeBak;
			CommSwitchType(this->m_commConfig.ucCommTypeBak);
			continue;
		}

		if( (iRet & MASK_COMM_TYPE)!=ERR_COMM_MODEM_BASE ) {
			//!DispCommErrMsg(iRet);
			return ERR_NO_DISP;
		}
		
		if (AskModemReDial(iRet)) {
			return ERR_USERCANCEL;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------------

int CCommEngine::AdjustCommParam(void)
{
	CParamters::HParameterRecord hParam = this->m_pEngine->GetDefParams()->GetData();

	uchar	szNewTelNo[100+1];

	// 构造拨号电话号码
	if (this->m_commConfig.ucCommType==CT_MODEM) {
/*		if( glProcInfo.stTranLog.ucTranType==LOAD_PARA )
		{
			sprintf((char *)szNewTelNo, "%s.", glSysParam.stEdcInfo.szDownTelNo);
		}
		else if( glProcInfo.stTranLog.ucTranType==SETTLEMENT )
		{
			if( (glCurAcq.stStlPhoneInfo[0].szTelNo[0]!=0) &&
				(glCurAcq.stStlPhoneInfo[1].szTelNo[0]!=0) )
			{	// 都不是空
				sprintf((char *)szNewTelNo, "%s%s;%s%s.",
						glSysParam.stEdcInfo.szPabx, glCurAcq.stStlPhoneInfo[0].szTelNo,
						glSysParam.stEdcInfo.szPabx, glCurAcq.stStlPhoneInfo[1].szTelNo);
			}
			else if( glCurAcq.stStlPhoneInfo[0].szTelNo[0]!=0 )
			{
				sprintf((char *)szNewTelNo, "%s%s.",
						glSysParam.stEdcInfo.szPabx, glCurAcq.stStlPhoneInfo[0].szTelNo);
			}
			else if( glCurAcq.stStlPhoneInfo[1].szTelNo[0]!=0 )
			{
				sprintf((char *)szNewTelNo, "%s%s.",
						glSysParam.stEdcInfo.szPabx, glCurAcq.stStlPhoneInfo[1].szTelNo);
			}
			else
			{
				return ERR_NO_TELNO;
			}
		}
		else
		{
*/
			if (hParam->m_provizyonPhoneNo_1[0] != 0 &&
				hParam->m_provizyonPhoneNo_2[0] != 0) 
																						//if ((glCurAcq.stTxnPhoneInfo[0].szTelNo[0]!=0) &&
																						//(glCurAcq.stTxnPhoneInfo[1].szTelNo[0]!=0) )
			{
				sprintf((char *)szNewTelNo, "%s%s;%s%s.",
						hParam->m_santalOnCevirme, hParam->m_provizyonPhoneNo_1,		//glSysParam.stEdcInfo.szPabx, glCurAcq.stTxnPhoneInfo[0].szTelNo,
						hParam->m_santalOnCevirme, hParam->m_provizyonPhoneNo_2			//glSysParam.stEdcInfo.szPabx, glCurAcq.stTxnPhoneInfo[1].szTelNo
				);
			}
			else if (hParam->m_provizyonPhoneNo_1[0] != 0)
																						//else if( glCurAcq.stTxnPhoneInfo[0].szTelNo[0]!=0 )
			{
				sprintf((char *)szNewTelNo, "%s%s.",
						hParam->m_santalOnCevirme, hParam->m_provizyonPhoneNo_1			//glSysParam.stEdcInfo.szPabx, glCurAcq.stTxnPhoneInfo[0].szTelNo
				);
			}
			else if (hParam->m_provizyonPhoneNo_2[0] != 0)								//else if( glCurAcq.stTxnPhoneInfo[1].szTelNo[0]!=0 )
			{
				sprintf((char *)szNewTelNo, "%s%s.",
						hParam->m_santalOnCevirme, hParam->m_provizyonPhoneNo_2			//glSysParam.stEdcInfo.szPabx, glCurAcq.stTxnPhoneInfo[1].szTelNo
				);
			}
			else {
				return ERR_NO_TELNO;
			}
//		}
		sprintf((char *)this->m_commConfig.stPSTNPara.szTelNo, "%s", szNewTelNo);

		//!if( !CommChkIfSameTelNo(szNewTelNo) ) {
		//	CommOnHook(FALSE);
		//}
	}

	if ((this->m_commConfig.ucCommType==CT_TCPIP) || (this->m_commConfig.ucCommType==CT_WIFI))
	{
		/*if( glProcInfo.stTranLog.ucTranType==LOAD_PARA )
		{
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemoteIP_1, "%.15s", glSysParam.stEdcInfo.stDownIpAddr.szIP);
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemotePort_1, "%.5s", glSysParam.stEdcInfo.stDownIpAddr.szPort);
		}
		else
		{
		*/
			// 使用transaction IP 1,2. 不使用 settle IP
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemoteIP_1,	"%.15s",	hParam->m_provizyonIP_1		); // glCurAcq.TxnTcpIp1);
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemotePort_1,	"%.5s",		hParam->m_provizyonPort_1	); // glCurAcq.TxnTcpPort1);
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemoteIP_2,	"%.15s",	hParam->m_provizyonIP_2		); // glCurAcq.TxnTcpIp2);
			sprintf((char *)this->m_commConfig.stTcpIpPara.szRemotePort_2,	"%.5s",		hParam->m_provizyonPort_2	); // glCurAcq.TxnTcpPort2);
		//}
	}

	// 从ACQUIRER提取目标IP
	if ((this->m_commConfig.ucCommType==CT_GPRS) || (this->m_commConfig.ucCommType==CT_CDMA))
	{
/*		if( glProcInfo.stTranLog.ucTranType==LOAD_PARA )
		{
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemoteIP_1, "%.15s", glSysParam.stEdcInfo.stDownIpAddr.szIP);
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemotePort_1, "%.5s", glSysParam.stEdcInfo.stDownIpAddr.szPort);
		}
		else
		{
*/			// 使用transaction IP 1,2. 不使用 settle IP
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemoteIP_1,		"%.15s",	hParam->m_provizyonIP_1		); //glCurAcq.TxnGPRSIp1);
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemotePort_1,	"%.5s",		hParam->m_provizyonPort_1	); //glCurAcq.TxnGPRSPort1);
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemoteIP_2,		"%.15s",	hParam->m_provizyonIP_2		); //glCurAcq.TxnGPRSIp2);
			sprintf((char *)this->m_commConfig.stWirlessPara.szRemotePort_2,	"%.5s",		hParam->m_provizyonPort_2	); //glCurAcq.TxnGPRSPort2);
//		}
	}

	return CommSetCfgParam();
}
//------------------------------------------------------------------------------------------
int CCommEngine::AskModemReDial(int iRet)
{
	uchar	ucKey;
/*
	if( iRet==ERR_COMM_MODEM_OCCUPIED || iRet==ERR_COMM_MODEM_NO_LINE ||
		iRet==ERR_COMM_MODEM_NO_LINE_2 )
	{
		DispCommErrMsg(iRet);
	}
	else if( iRet==ERR_COMM_MODEM_LINE || iRet==ERR_COMM_MODEM_NO_ACK ||
			 iRet==ERR_COMM_MODEM_LINE_BUSY )
	{
		DispResult(iRet);
		ScrClrLine(2, 7);
		PubDispString(_T("RE DIAL ?    "), 4|DISP_LINE_LEFT);
	}
	else
	{
		PubBeepErr();
		ScrClrLine(2, 7);
		PubDispString(_T("DIAL FAIL,RETRY?"), 4|DISP_LINE_LEFT);
		ScrPrint(114, 7, ASCII, "%02X", (uchar)(iRet & MASK_ERR_CODE));
	}
	ucKey = PubWaitKey(USER_OPER_TIMEOUT/2);
	if( ucKey==KEYCANCEL || ucKey==NOKEY )
	{
		return ERR_USERCANCEL;
	}
*/
	return 0;
}
//------------------------------------------------------------------------------------------

int CCommEngine::SendRecv()
{
	int ret = 0;
	
	this->SendPacket();
	this->RecvPacket();

	return SUCCESS;
}

//------------------------------------------------------------------------------------------

int CCommEngine::SendPacket()
{
	int ret;
	ret = this->ConnectHost();
	if (ret != SUCCESS) {
		return ret;
	}

	ret = CommTxd(this->m_sendData.sContent, this->m_sendData.uiLength, USER_OPER_TIMEOUT);	// 不能用 no timeout

	return SUCCESS;
}

//------------------------------------------------------------------------------------------

int CCommEngine::RecvPacket()
{
	return SUCCESS;
}

//------------------------------------------------------------------------------------------
// send data for all kinds of communication.
int CCommEngine::CommTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec)
{
	int		iRet;

	if( psTxdData==NULL )
	{
		return ERR_COMM_INV_PARAM;
	}

/*	switch( sg_stCurCfg.ucCommType )
	{
	case CT_RS232:
		//!iRet = RS232Txd(psTxdData, uiDataLen);
		break;

	case CT_MODEM:
		//!iRet = PSTNTxd(psTxdData, uiDataLen, uiTimeOutSec);
		break;

	case CT_TCPIP:
		iRet = TcpTxd(psTxdData, uiDataLen, uiTimeOutSec);
		break;

#if defined(_P80_) || defined(_P90_) || defined(_S_SERIES_)
	case CT_CDMA:
	case CT_GPRS:
*/
  #ifdef SXX_WIRELESS_MODULE
		iRet = SXXWlSend(psTxdData, uiDataLen, uiTimeOutSec);
  #elif defined(PXX_COMM)
		iRet = WirelessTxd(psTxdData, uiDataLen, uiTimeOutSec);
  #else
		return 1;
  #endif
		/*
		break;
#endif
		
//	case CT_WIFI:
//		break;

	case CT_DEMO:
		iRet = 0;
//#ifdef _WIN32
//		if (!ChkTerm(_TERMINAL_S90_))
//		{
//			iRet = RS232Txd(psTxdData, uiDataLen);
//			iRet = 0;
//		}
//#endif
		break;

	default:
		iRet = ERR_COMM_INV_TYPE;
	}
*/
	return iRet;
}

//------------------------------------------------------------------------------------------

int CCommEngine::TcpTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec)
{
#ifdef SXX_IP_MODULE
	return m_comm.SxxTcpTxd(psTxdData, uiDataLen, uiTimeOutSec);

#else
	PortReset(sg_stCurCfg.stTcpIpPara.ucPortNo);

	switch( sg_ucTcpVer ) {
	case TCPIP_V8:
		while( uiDataLen-->0 )
		{
			if( *psTxdData=='\\'  )
			{
				if( PortSend(sg_stCurCfg.stTcpIpPara.ucPortNo, '\\') )
				{
					return ERR_COMM_TCPIP_TXD;
				}
			}
			if( PortSend(sg_stCurCfg.stTcpIpPara.ucPortNo, *psTxdData++) )
			{
				return ERR_COMM_TCPIP_TXD;
			}
		}

		// 去掉SendCommand（此函数中又调用了一次PortReset函数），改用直接发送结束符
		if( PortSend(sg_stCurCfg.stTcpIpPara.ucPortNo, '\\') )
		{			
			return ERR_COMM_TCPIP_TXD;
		}
		
		if( PortSend(sg_stCurCfg.stTcpIpPara.ucPortNo, '\x1C') )
		{			
			return ERR_COMM_TCPIP_TXD;
		}
		//end

		break;

	case TCPIP_V7:
	default:
		while( uiDataLen-->0 )
		{
			if( PortSend(sg_stCurCfg.stTcpIpPara.ucPortNo, *psTxdData++) )
			{
				return ERR_COMM_TCPIP_TXD;
			}
		}
		break;
	}

	return 0;
#endif
}

// 接收数据 非S80 TCP/IP 方式
// receive data, for Pxx
int CCommEngine::TcpRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen)
{
#ifdef SXX_IP_MODULE
	return m_comm.SxxTcpRxd(psRxdData, uiExpLen, uiTimeOutSec, puiOutLen);

#else
	uchar	ucRet;
	ushort	uiLength;
	ulong	ulTemp;

	ulTemp   = 0;
	uiLength = 0;
	TimerSet(TIMER_TEMPORARY, 10);
	while( uiLength<uiExpLen )
	{
		if( TimerCheck(TIMER_TEMPORARY)==0 )
		{
			if( uiTimeOutSec==0 )
			{
				if( uiLength>0 )		// 已经读取了数据
				{
					break;
				}
				return ERR_COMM_TIMEOUT;
			}
			uiTimeOutSec--;
			if( sg_stCurCfg.pfUpdWaitUI!=NULL )
			{
				(*sg_stCurCfg.pfUpdWaitUI)(uiTimeOutSec);
			}
			TimerSet(TIMER_TEMPORARY, 10);
		}

		ucRet = PortRecv(sg_stCurCfg.stTcpIpPara.ucPortNo, psRxdData, (ushort)ulTemp);
		if( ucRet==0 )
		{
			ulTemp = 80;				// timeout between chars!!!
			psRxdData++;
			uiLength++;
		}
		else if( ucRet==0xFF )
		{
			if( uiLength>0 )		// 已经读取了数据
			{
				break;
			}
		}
		else
		{
			return ERR_COMM_COMERR;
		}
	}
	if( puiOutLen!=NULL )
	{
		*puiOutLen = uiLength;
	}

	return 0;
#endif
}
//------------------------------------------------------------------------------------------
int CCommEngine::SXXWlSend(uchar *psTxdData, ushort usDataLen, ushort uiTimeOutSec)
{
	return m_comm.SxxTcpTxd(psTxdData, usDataLen, uiTimeOutSec);
}
//------------------------------------------------------------------------------------------
int CCommEngine::SXXWlRecv(uchar *psRxdData, ushort usExpLen, ushort uiTimeOutSec, ushort *pusOutLen)
{
	DelayMs(200);
	return m_comm.SxxTcpRxd(psRxdData, usExpLen, uiTimeOutSec, pusOutLen);
}
//------------------------------------------------------------------------------------------

void CCommEngine::SetParameters()
{
	CParamters::HParameterRecord hParam = this->m_pEngine->GetDefParams()->GetData();

	memcpy(this->m_commConfig.stWirlessPara.szAPN, hParam->m_apn, CParamters::sizeApn);
	this->m_commConfig.stWirlessPara.szAPN[CParamters::sizeApn] = 0x00;
	PRNLINE(this->m_commConfig.stWirlessPara.szAPN);
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
