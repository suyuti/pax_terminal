// CommEngine2.cpp: implementation of the CCommEngine2 class.
//
//////////////////////////////////////////////////////////////////////

#include "CommEngine2.h"
#include "Engine.h"
#include "..\Files\Paramters.h"
#include "..\Util\NumFuncs.h"
#include "..\UI\MessageBox.h"

//-----------------------------------------------------------------------------

CCommEngine2::CCommEngine2() : 
	m_pEngine((CEngine*)NULL)
{
	memset(this->m_recvBuffer, 0x00, sizeof(this->m_recvBuffer));
	memset(this->m_sendBuffer, 0x00, sizeof(this->m_sendBuffer));
	
	memset(m_apn,		0x00, sizeof(m_apn));
	memset(m_userID,	0x00, sizeof(m_userID));
	memset(m_password,	0x00, sizeof(m_password));
	memset(m_ip1,		0x00, sizeof(m_ip1));
	memset(m_ip2,		0x00, sizeof(m_ip2));
	m_timeout		= 60;
	m_aliveInternal = 3600;
	m_port1			= 0;
	m_port2			= 0;
	m_socket		= 0;
	m_bConnected	= false;
}

//-----------------------------------------------------------------------------

CCommEngine2::CCommEngine2(CEngine* pEng) : 
	m_pEngine(pEng)
{
	memset(this->m_recvBuffer, 0x00, sizeof(this->m_recvBuffer));
	memset(this->m_sendBuffer, 0x00, sizeof(this->m_sendBuffer));
	memset(m_apn,		0x00, sizeof(m_apn));
	memset(m_userID,	0x00, sizeof(m_userID));
	memset(m_password,	0x00, sizeof(m_password));
	memset(m_ip1,		0x00, sizeof(m_ip1));
	memset(m_ip2,		0x00, sizeof(m_ip2));
	m_timeout		= 60;
	m_aliveInternal = 3600;
	m_port1			= 0;
	m_port2			= 0;
	m_socket		= 0;
	m_bConnected	= false;
}

//-----------------------------------------------------------------------------

CCommEngine2::~CCommEngine2()
{

}

//-----------------------------------------------------------------------------
int CCommEngine2::InitGPRS()
{
	int ret = WlInit((const unsigned char*)this->m_pin);
	//int ret = WlInit((const unsigned char*)"");
	if (ret == -212) {
		ret = 0;
	}
	return ret;
}

//-----------------------------------------------------------------------------

int CCommEngine2::GetSignalLevel()
{
	uchar	ucRet, ucLevel;

	ucRet = WlGetSignal(&ucLevel);
	if( ucRet != RET_OK ) {
		return GENERAL_FAILURE;
	}
	return (int)ucLevel;
}

//-----------------------------------------------------------------------------

int CCommEngine2::SetConfig()
{ 
	CParamters param;
	if (!param.Open()) {
		return PARAMS_FILE_NOT_OPEN;
	}
	param.GotoRec(1, true);
	param.Close();
	CParamters::HParameterRecord hParam = param.GetData();
	
	// apn
	memcpy(this->m_apn, hParam->m_apn, CParamters::sizeApn);
	this->m_apn[CParamters::sizeApn] = 0x00;
	PubTrimStr((uchar*)this->m_apn);

	this->m_timeout			= 60;
	this->m_aliveInternal	= 3600;

	memset(this->m_userID,		0x00, sizeof(this->m_userID		));
	memset(this->m_password,	0x00, sizeof(this->m_password	));
	sprintf(this->m_userID,		"user");
	sprintf(this->m_password,	"password");

	strncpy(this->m_pin, hParam->m_SimPIN, strlen(hParam->m_SimPIN));

	return SUCCESS;
}
	
//-----------------------------------------------------------------------------

int CCommEngine2::SetHostType(HostTypes type)
{
	CParamters param;
	if (!param.Open()) {
		return PARAMS_FILE_NOT_OPEN;
	}
	param.GotoRec(1, true);
	param.Close();
	CParamters::HParameterRecord hParam = param.GetData();
	char tmp[64] = "";

	switch(type) {
		case htTMS:
			memcpy(this->m_ip1, hParam->m_TmsIP_1, CParamters::sizeIP);
			this->m_ip1[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip1);

			memcpy(tmp, hParam->m_TmsPort_1, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port1 = atoi(tmp);

			memcpy(this->m_ip2, hParam->m_TmsIP_2, CParamters::sizeIP);
			this->m_ip2[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip2);

			memcpy(tmp, hParam->m_TmsPort_2, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port2 = atoi(tmp);
		break;
		case htProvizyon:
			memcpy(this->m_ip1, hParam->m_provizyonIP_1, CParamters::sizeIP);
			this->m_ip1[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip1);

			memcpy(tmp, hParam->m_provizyonPort_1, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port1 = atoi(tmp);

			memcpy(this->m_ip2, hParam->m_provizyonIP_2, CParamters::sizeIP);
			this->m_ip1[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip2);

			memcpy(tmp, hParam->m_provizyonPort_2, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port2 = atoi(tmp);
		break;
		case htSettlement:
			memcpy(this->m_ip1, hParam->m_settleIP_1, CParamters::sizeIP);
			this->m_ip1[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip1);

			memcpy(tmp, hParam->m_settlePort_1, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port1 = atoi(tmp);

			memcpy(this->m_ip1, hParam->m_settleIP_2, CParamters::sizeIP);
			this->m_ip2[CParamters::sizeIP] = 0x00;
			PubTrimStr((uchar*)this->m_ip2);

			memcpy(tmp, hParam->m_settlePort_2, CParamters::sizePort);
			tmp[CParamters::sizePort] = 0x00;
			this->m_port2 = atoi(tmp);
		break;
	}
	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::Connect()
{ 
	int		ret;
	int		retryTime = 0;
	bool	bSecondIP = false;

	this->m_timeout = 1;
	this->m_bConnected = false;

	// ---------- Check PPP connection ------------
	TimerSet(TIMER_TEMPORARY, (ushort)(this->m_timeout * 10));
	while (TimerCheck(TIMER_TEMPORARY)!=0) {
		ret = WlPppCheck();

		if (kbhit() == 0) {
			if (getkey() == KEY_CANCEL) {
				this->m_bUserCancelled = true;
				return USER_CANCELLED;
			}
		}

		if (ret == 0) {
			goto TCPCONNECT;
		}
	}
	// ----------- Take PPP dial action -------------
	retryTime = 3;
	while (retryTime--) {
		if (kbhit() == 0) {
			if (getkey() == KEY_CANCEL) {
				this->m_bUserCancelled = true;
				return USER_CANCELLED;
			}
		}
		ret = WlPppLogin((uchar*)"internet", (uchar*)NULL, (uchar*)NULL, 0xFF, /*this->m_timeout*/ 60 * 1000, this->m_aliveInternal);
		//ret = WlPppLogin((uchar*)"internet", (uchar*)NULL, (uchar*)NULL, 0xFF, /*this->m_timeout*/ 60 * 1000, this->m_aliveInternal);
		if (ret != 0) {
			DelayMs(100);
			continue;
		}

		ret = WlPppCheck();
		if (ret == 0) {
			break;
		}
	}
	if (retryTime <= 0 && ret != 0) {
		return NOT_CONNECTED;
		//return ret;
	}

TCPCONNECT:	
	ret = this->SocketCheck(this->m_socket);  //come from R&D, tom
	if (ret == RET_TCPOPENED) {
		return 0;
	}

	bSecondIP = FALSE;

_RETRY_SECOND_IP:
	if (bSecondIP) {
		ScrGotoxy(0,3);
		Lcdprintf("%s:%d", this->m_ip2, this->m_port2);
		ret = this->TcpConnect(this->m_ip2, this->m_port2, 8);
	} 
	else {
		ScrGotoxy(0,3);
		Lcdprintf("%s:%d", this->m_ip1, this->m_port1);
		ret = this->TcpConnect(this->m_ip1, this->m_port1, 8);
	}

	if (ret < 0) {
		if (ChkIfValidIp(this->m_ip2) && ChkIfValidPort(this->m_port2) &&
			(strcmp((char *)(this->m_ip1), (char *)(this->m_ip2)) != 0)) {
			bSecondIP = true;
			goto _RETRY_SECOND_IP;
		}

		ScrGotoxy(0,4);
		Lcdprintf("Baglanti basarisiz!");
			
		this->m_bConnected = false;

		return ret;
	}
	this->m_bConnected = true;
	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::Disconnect()
{
	int ret;

	ret = NetCloseSocket(this->m_socket);
	if (ret < 0) {
		return ret;
	}
	this->m_bConnected = false;
	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::SendReceive()
{ 
	int ret;
	char tmp[128] = "";
	
	this->m_bUserCancelled = false;

	this->SetContinueSendRecv(false);

	CMessageBox mb("Araniyor...", MB_SHOW_ONLY);
	mb.Draw();

	this->OnBeforeConnect();

	ret = this->Connect();
	if (ret != SUCCESS) {
PRNLINE("baglanamadi");
		this->OnError(errConnect, ret);
		goto EXIT;
	}
PRNLINE("Baglandi");

	this->OnConnect();

	ret = this->OnBeforeProcess();
	if (ret != SUCCESS) {
PRNLINE("OnbeforeProcess basarisiz");
		goto DISCONNECT;
	}
	
	do {
		if (kbhit() == 0) {
			if (getkey() == KEY_CANCEL) {
PRNLINE("Kullanici iptal etti.");
				this->m_bUserCancelled = true;
				ret = USER_CANCELLED;
				break;
			}
		}

		//----------------------- 

PRNLINE("OnBeforeSend");
		ret = this->OnBeforeSend();
		if (ret == CONTINUE) {
PRNLINE("continue");
			continue;
		}
		else if (ret != SUCCESS) {
PRNLINE("disconnect");
			goto DISCONNECT;
		}

		//----------------------- 

PRNLINE("send");
		ret = this->SendPacket();
		if (ret != SUCCESS) {
PRNLINE("send error");
			this->OnError(errSend, ret);
			goto DISCONNECT;
		}

		//----------------------- 

PRNLINE("OnAfterSend");
		this->OnAfterSend();

		//----------------------- 

		this->OnBeforeRecv();

		//----------------------- 

PRNLINE("Recv");
		ret = this->RecvPacket();
		if (ret != SUCCESS) {
PRNLINE("Recv Error");
			this->OnError(errRecv, ret);
			goto DISCONNECT;
		}

		//----------------------- 

PRNLINE("OnAfterRecv");
		ret = this->OnAfterRecv();
		if (ret == CONTINUE) {
PRNLINE("continue");
			continue;
		}
		else if (ret != SUCCESS) {
PRNLINE("disconnect");
			goto DISCONNECT;
		}
	
		//----------------------- 

		if (!this->GetContinueSendRecv()) {
PRNLINE("senRecv bitir.");
			break;
		}
	} while(true);

PRNLINE("OnAfterProcess Begin");
	this->OnAfterProcess();
PRNLINE("OnAfterProcess");
	ret = SUCCESS;

DISCONNECT:
PRNLINE("baglanti kesilir.");
	this->Disconnect();
	//ret = this->Disconnect();
	//if (ret != SUCCESS) {
	//	this->OnError(errDisconnect, ret);
	//	goto EXIT;
	//}
	return ret;

	//return SUCCESS;

EXIT:
	sprintf(tmp, "SendRecv: %d", ret);
	PRNLINE(tmp);
	return ret;
}

//-----------------------------------------------------------------------------

int CCommEngine2::SendPacket()
{
	int ret;
	int iSendLen;
	int iSumLen;
	
	ret = Netioctl(this->m_socket, CMD_TO_SET, USER_OPER_TIMEOUT * 1000);
	if (ret < 0) {
		PRNLINE("NETIOCTL ERROR");
		return ret;
	}

	iSumLen = 0;
	while (1) {
		if (this->m_sendSize > TCPMAXSENDLEN) {
			iSendLen = TCPMAXSENDLEN;
			this->m_sendSize = this->m_sendSize - TCPMAXSENDLEN;
		}
		else {
			iSendLen = this->m_sendSize;
		}	
		ret = NetSend(this->m_socket, this->m_sendBuffer + iSumLen, iSendLen, 0);
		if (ret < 0) {
			PRNLINE("NETSEND ERROR");
			return ret;
		}
		if (ret != iSendLen) {
			return -1;
		}
		iSumLen = iSumLen + iSendLen;
		if (iSendLen <= TCPMAXSENDLEN) {
			break;
		}	
	}
	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::RecvPacket()
{ 
	int ret;

	DelayMs(200);

	ret = 	Netioctl(this->m_socket, CMD_TO_SET, USER_OPER_TIMEOUT * 1000);
	if (ret < 0) {
		return ret;
	}

	ret = NetRecv(this->m_socket, this->m_recvBuffer, LEN_MAX_COMM_DATA, 0);
	if (ret < 0) {
		return ret;
	}
	this->m_recvSize = ret;

	return SUCCESS;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//#define OFFLINE_TEST
//-----------------------------------------------------------------------------
uchar CCommEngine2::SocketCheck(int sk)
{
	int event;
	if (sk < 0) {
		return RET_TCPCLOSED;
	}
	
	event = Netioctl(sk, CMD_EVENT_GET, 0);
	if (event < 0) {
         NetCloseSocket(sk);
         return RET_TCPCLOSED;
	}	
	
	if(event & (SOCK_EVENT_CONN|SOCK_EVENT_WRITE|SOCK_EVENT_READ)) {
         return RET_TCPOPENED;
	}
	else if(event & (SOCK_EVENT_ERROR)) {
         NetCloseSocket(sk);
         return RET_TCPCLOSED;
	}

	return RET_TCPOPENING;
}

//-----------------------------------------------------------------------------

int CCommEngine2::TcpConnect(char *pszIP, short sPort, int iTimeoutSec)
{
	int					iRet;
	struct net_sockaddr stServer_addr;

	// Setup socket
	iRet = NetSocket(NET_AF_INET, NET_SOCK_STREAM, 0);
	if (iRet != 0) {
		return iRet;	
	}
	this->m_socket = iRet;

	// Bind IP
	iRet = SockAddrSet(&stServer_addr, pszIP, sPort);
	if (iRet != 0) {
		return iRet;
	}

	// set connection timeout
	if (iTimeoutSec < 3) {
		iTimeoutSec = 3;
	}
	iRet = Netioctl(this->m_socket, CMD_TO_SET, iTimeoutSec * 1000);
	if (iRet != 0) {
		return iRet;
	}

	// Connect to remote IP
	iRet = NetConnect(this->m_socket, &stServer_addr, sizeof(stServer_addr));
	if (iRet != 0) {
		NetCloseSocket(this->m_socket);
	}

	return iRet;
}

//-----------------------------------------------------------------------------

int CCommEngine2::ChkIfValidIp(char *pszIP)
{
	return ((pszIP[0]!=0) && (ValidIPAddress(pszIP)));
}

//-----------------------------------------------------------------------------

int CCommEngine2::ChkIfValidPort(int port)
{
	return ((port > 0) && (port) < 65536);
}

//-----------------------------------------------------------------------------

uchar CCommEngine2::ValidIPAddress(char *pszIPAddr)
{
	int		i;
	char	*p, *q, szBuf[5+1];

	PubTrimStr((uchar *)pszIPAddr);
	if (*pszIPAddr == 0) {
		return FALSE;
	}

	p = strchr(pszIPAddr, ' ');
	if (p != NULL) {
		return FALSE;
	}
	if (strlen(pszIPAddr) > 15) {
		return FALSE;
	}

	// 1st --- 3rd  part
	for (q = pszIPAddr, i = 0; i < 3; ++i) {
		p = strchr(q, '.');
		if (p == NULL || p == q || p - q > 3) {
			return FALSE;
		}
		sprintf(szBuf, "%.*s", (int)(p-q), q);
		if (!IsNumStr(szBuf) || atoi(szBuf) > 255) {
			return FALSE;
		}
		q = p + 1;
	}

	// final part
	p = strchr((char *)q, '.');
	if (p != NULL || !IsNumStr(q) || strlen(q) == 0 || strlen(q) > 3 || atoi(q) > 255 ) {
		return FALSE;
	}

	return TRUE;
}
//-----------------------------------------------------------------------------

int CCommEngine2::PrepTPDU()
{
	// 60 [00 00] 00 01: [NII]
	//!
	this->m_sendBuffer[2] = 0x60;
	this->m_sendBuffer[3] = 0x00;
	this->m_sendBuffer[4] = 0x70;
	this->m_sendBuffer[5] = 0x00;
	this->m_sendBuffer[6] = 0x01;

	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::PrepLen()
{
	// 60 [00 00] 00 01: [NII]
	char tmp[10] = "";
	sprintf(tmp, "%04X", this->m_sendSize - 2);
	Str2Bcd(tmp, strlen(tmp), LEFT_PAD_ZERO, this->m_sendBuffer, 2, LEFT_PAD);

	return SUCCESS;
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnError(ErrorSources source, int err)
{ 
	char tmp[64] = "";
	switch(source) {
		case errConnect:
			sprintf(tmp, "err[Connect][%d]", err);
		break;
		case errSend:
			sprintf(tmp, "err[Send][%d]", err);
		break;
		case errRecv:
			sprintf(tmp, "err[Recv][%d]", err);
		break;
		case errDisconnect:
			sprintf(tmp, "err[Disconnect][%d]", err);
		break;
	}
	PRNLINE(tmp);
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnBeforeConnect()
{ 
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnConnect()
{
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnBeforeSend()
{ 
	memset(this->m_sendBuffer, 0x00, sizeof(this->m_sendBuffer));
	this->m_sendSize = 0;
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnAfterSend()
{ 
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnBeforeRecv()
{ 
	memset(this->m_recvBuffer, 0x00, sizeof(this->m_recvBuffer));
	this->m_recvSize = 0;
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnAfterRecv()
{ 
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnBeforeProcess()
{ 
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int CCommEngine2::OnAfterProcess()
{ 
	return SUCCESS; 
}

//-----------------------------------------------------------------------------

int	CCommEngine2::OnResponseCodeError(int err)
{
	char tmp[8] = "";

	sprintf(tmp, "RespCode: %02d\n", err);
	PRNLINE(tmp);

	return SUCCESS;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
