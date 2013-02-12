/****************************************************************************
NAME
	SxxCom.h - 无线模块封装函数

DESCRIPTION

REFERENCE

MODIFICATION SHEET:
	MODIFIED   (YYYY.MM.DD)

****************************************************************************/

#ifndef _SWIRELESS_H
#define _SWIRELESS_H

#ifndef uchar
#define uchar   unsigned char
#endif
#ifndef uint
#define uint    unsigned int
#endif
#ifndef ushort
#define ushort  unsigned short
#endif
#ifndef ulong
#define ulong   unsigned long
#endif

#ifndef TRUE
	#define TRUE	1
	#define FALSE	0
#endif

#include "..\globaldef.h"

class CComm {

public:
	CComm();
	virtual ~CComm();

	int SxxTcpConnect(char *pszIP, short sPort, int iTimeoutSec);

	int SxxTcpTxd(uchar *psTxdData, ushort uiDataLen, ushort uiTimeOutSec);
	int SxxTcpRxd(uchar *psRxdData, ushort uiExpLen, ushort uiTimeOutSec, ushort *puiOutLen);
	int SxxTcpOnHook(void);
	int SxxDhcpStart(uchar ucForceStart, uchar ucTimeOutSec);
	int SxxLANTcpDial(TCPIP_PARA *pstTcpPara);
	int SXXWlInit(WIRELESS_PARAM *pstWlPara);
	int SXXWlDial(WIRELESS_PARAM *pstWlPara, int iTimeOut, int iAliveInterval, uchar ucPredial);
	int SXXWlSend(uchar *psTxdData, ushort usDataLen, ushort usTimeOut);
	int SXXWlRecv(uchar *psRxdData, ushort usExpLen, ushort usTimeOut, ushort *pusOutLen);
	int SXXWlCloseTcp(void);
	void SXXWlClosePPP(void);
	void SXXWlDispSignal(void);
	uchar SocketCheck(int sk);
	int		CommOnHook(uchar bReleaseAll);
	int RS232OnHook(uchar bReleaseAll);
	int PSTNOnHook(uchar bReleaseAll);
	int TcpOnHook(uchar bReleaseAll);



private:
	int sg_iSocket;
};

#endif
