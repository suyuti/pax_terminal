// CommEngine2.h: interface for the CCommEngine2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMENGINE2_H__2E0C4875_40BE_4F05_A50E_31B80CD5C41D__INCLUDED_)
#define AFX_COMMENGINE2_H__2E0C4875_40BE_4F05_A50E_31B80CD5C41D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_BUFFER	1024

#include "..\globaldef.h"
#include "..\8583\8583.h"

class CEngine;
class CTrnxBase;
class CCommEngine2  
{
public:
	typedef enum {
		htTMS = 0,
		htProvizyon,
		htSettlement,
	} HostTypes;
private:
	CCommEngine2();
public:
	CCommEngine2(CEngine* pEng);
	virtual ~CCommEngine2();

	int				InitGPRS();
	int				GetSignalLevel();

	int				SetConfig();
	int				SetHostType(HostTypes);

	inline bool		GetSaveAfterConnction()				{ return this->m_bSaveAfterConnection;	};
	inline void		SetSaveAfterConnction(bool save)	{this->m_bSaveAfterConnection = save;	};


	virtual int		SendReceive();

	inline bool		IsConnected()						{ return this->m_bConnected;			};

	inline bool		GetContinueSendRecv()				{ return this->m_bContinueSendRecv;		};
	inline void		SetContinueSendRecv(bool cont)		{ this->m_bContinueSendRecv = cont;		};

	inline int		GetResponseCode()					{ return this->m_responseCode;			};
	
	inline bool		IsUserCancelled()					{ return this->m_bUserCancelled;		};

	int				Connect();

protected:
	int				Disconnect();
	int				SendPacket();
	int				RecvPacket();
	
	virtual int		PrepTPDU();
	virtual int		PrepLen();

	uchar			SocketCheck(int sk);
	int				TcpConnect(char *pszIP, short sPort, int iTimeoutSec);

	static int		ChkIfValidIp(char *pszIP);
	static int		ChkIfValidPort(int port);
	static uchar	ValidIPAddress(char *pszIPAddr);

	//-- Events -----
	typedef enum {
		errConnect = 0,
		errSend,
		errRecv,
		errDisconnect,
	} ErrorSources;

	virtual int		OnError(ErrorSources source, int err);
	virtual int		OnBeforeConnect();
	virtual int		OnConnect();
	virtual int		OnBeforeSend();
	virtual int		OnAfterSend();
	virtual int		OnBeforeRecv();
	virtual int		OnAfterRecv();
	virtual int		OnBeforeProcess();
	virtual int		OnAfterProcess();
	virtual int		OnResponseCodeError(int err);

protected:
	unsigned char	m_sendBuffer[MAX_BUFFER];
	unsigned char	m_recvBuffer[MAX_BUFFER];
	int				m_sendSize;
	int				m_recvSize;
	CEngine*		m_pEngine;
	int				m_responseCode;
	C8583			m_8583;
	bool			m_bSaveAfterConnection; // true: baglanti basarili olduktan sonra kayit yapilir. Yoksa baglanti kurulamadiginda gereksiz RV kayitlar olusur. 
	CTrnxBase*		m_pTrnx;
private:
	int		m_timeout;
	int		m_aliveInternal;
	char	m_apn		[32];
	char	m_userID	[32];
	char	m_password	[32];
	char	m_ip1		[16];
	int		m_port1;
	char	m_ip2		[16];
	int		m_port2;
	int		m_socket;
	bool	m_bConnected;
	bool	m_bContinueSendRecv;
	bool	m_bUserCancelled;
	char	m_pin		[4 + 1];
};

#endif // !defined(AFX_COMMENGINE2_H__2E0C4875_40BE_4F05_A50E_31B80CD5C41D__INCLUDED_)
