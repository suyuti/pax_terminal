// CardReader.h: interface for the CCardReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARDREADER_H__32F6A297_2419_42E6_8AD2_28BFB19AFDC4__INCLUDED_)
#define AFX_CARDREADER_H__32F6A297_2419_42E6_8AD2_28BFB19AFDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "..\appinfo.h"
#include "..\Util\NumFuncs.h"
#include "..\Crypt\crypt.h"


#define RV_SUCCESS			0x00
#define	RV_MORE_DATA		0xAF
#define RV_FAIL				0x96


class CCardReader  
{
public:
	CCardReader();
	virtual ~CCardReader();

	int Initialize();
	int Close();
	void Clear();
public:
	int ReadCardData();
	int DoHarcama(int Amount);
	int DoHarcamaIptal(int Amount);
	int DoHarcamaIade(int Amount);
	int DoNakitYukleme(int Amount);
	int DoBakiyeSorgulama();
	int DoPuanKullanma(int Amount);
	int DoPuanSorgulama();
	int DoPuanKullanmaIptal(int Amount);
	int DoPuanKullanmaIade(int Amount);

	inline HFanStruct			GetFanData()			{ return &this->m_fanData;			};
	inline HPrepaidStruct		GetPrepaidData()		{ return &this->m_prepaidData;		};
	inline HLoyaltyStruct		GetLoyaltyData()		{ return &this->m_loyaltyData;		};
	inline HSeasonTicketStruct	GetSeasonTicketData()	{ return &this->m_seasonTicketData;	};
	inline int					GetGainedPoint()		{ return this->m_gainedPoints;		};

	inline void					SetCardWaitTime(int ms) { this->m_cardWaitTime = ms;		};

	char* GetLastErrorMsg();

protected:
	int CardReaderDetectCard();
	int CardReaderGetApplications(uchar* CardApplications, int* LenCardApplications);
	int AuthenticateCard();
	int SelectCardApplication(uchar* ApplicationID);
	int CardReaderGetFileIDs(uchar* FileIDs);
	int CardReaderGetFileData(uchar FileID, uchar* FileLen, uchar* CardData, int* CardDataLen);
	int CardReaderWriteFileData(uchar FileID, uchar* CardData, uchar* FileOffset, int DataLen);
	int SendReceiveCommand(uchar* SendCommand, int SendLen, uchar* RecvCommand, int* RecvLen);
	int CardReaderFillFanApp();
	int CardReaderFillSeasonTicketApp();
	int CardReaderFillPrepaidApp();
	int CardReaderFillLoyaltyApp();

	int PreOperation(); // init, detect, select ve auth yapar.
	int PostOperation();


private:
	int					m_cardWaitTime;	// Karti bekleme suresi. Detect icin
	int					m_gainedPoints; // Kazanilan puan
	FanStruct			m_fanData;
	PrepaidStruct		m_prepaidData;
	LoyaltyStruct		m_loyaltyData;
	SeasonTicketStruct	m_seasonTicketData;
	int					m_error;
};

#endif // !defined(AFX_CARDREADER_H__32F6A297_2419_42E6_8AD2_28BFB19AFDC4__INCLUDED_)
