// Batch.h: interface for the CBatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATCH_H__1A709596_F37D_4114_A0AD_03D3735EE79C__INCLUDED_)
#define AFX_BATCH_H__1A709596_F37D_4114_A0AD_03D3735EE79C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"
#include "..\appinfo.h"

#define TABLE_NAME_BATCH	"Batch.txt"

#define STAT_OK				0x0000		// txn accepted
#define STAT_NOSEND			0x0001		// txn not sent to host
#define STAT_ADJ			0x0002		// txn adjusted
#define STAT_REVD			0x0004		// txn reversed (reserved)
#define STAT_VOID			0x0008		// txn voided
#define STAT_CHANGE_APPV	0x0010		// 替换Approval Code, reserved
#define STAT_FLOOR_LIMIT	0x0020		// 交易金额低于Floor Limit
#define STAT_OFFLINE_SEND	0x0040		//
#define STAT_NOT_UPLOAD		0x0080		// 不需要上送(由NOSEND/ADJ判断)


#include "Acquier.h"
#include "..\Trnx\TrnxFactory.h"
class CBatch : public CTable  
{
public:
	CBatch();
	virtual ~CBatch();

	typedef struct _tagTrnxData {
		int						m_orgMTI;
		int						m_trnxType;			// CTrnxFactory::TrnxTypes'daki islem tipleri
		ushort					m_status;
		char					m_deletedFlag;
		char					m_reversalFlag;
		char					m_sentFlag;
		char					m_voidFlag;
		int						m_stan;
		int						m_batch;
		FanStructSum			m_fanData;
		LoyaltyStructSum		m_loyaltyData;
		PrepaidStructSum		m_prepaidData;
		SeasonTicketStructSum	m_seasionTicketData;
		int						m_amount;
		int						m_kazanilanPuan;
		unsigned char			m_acquierID[CAcquier::sizeAcquirerTableId];
		unsigned char			m_dateTime		[7];		// BCD: YY MM DD HH mm SS W. W:1:Monday
		int						m_responseCode;				// BCD: 
		unsigned char			m_RRN			[6];		// BCD
		unsigned char			m_orgRRN		[6];		// BCD
		char					m_responseMsgScr[40 + 1];
		char					m_responseMsgPrn[40 + 1];
	} BatchData, *HBatchData;

	inline void			SetData(HBatchData hData)		{ memcpy(&this->m_data, hData, sizeof(BatchData));			};
	inline HBatchData	GetData()						{ return &this->m_data;										};

	inline bool			IsSent()						{ return (this->m_data.m_sentFlag == 0x01);					};
	inline void			SetSent()						{ this->m_data.m_sentFlag = 0x01;							};
	
	inline bool			IsReversed()					{ return (this->m_data.m_reversalFlag == 0x01);				};
	inline bool			SetReversed()					{ this->m_data.m_reversalFlag = 0x01;						};
	
	inline bool			IsVoided()						{ return (this->m_data.m_voidFlag == 0x01);					};
	inline void			SetVoided()						{ this->m_data.m_voidFlag = 0x01;							};

	inline bool			IsDeleted()						{ return (this->m_data.m_deletedFlag == 0x01);				};
	inline void			SetDeleted()					{ this->m_data.m_deletedFlag = 0x01;						};

	inline CTrnxFactory::TrnxTypes GetTrnxType()		{ return (CTrnxFactory::TrnxTypes)this->m_data.m_trnxType;	};
	inline int			GetAmount()						{ return this->m_data.m_amount;								};
	
	void				GetProcessCode(char*);

	void				SetResponseCode(int respCode);
	inline	int			GetResponseCode()				{return this->m_data.m_responseCode;						};

	virtual int			Append();
	int					FindByStan(int stan, int* pRec);

	virtual void		PrintAll()						{};

private:
	BatchData m_data;
};

#endif // !defined(AFX_BATCH_H__1A709596_F37D_4114_A0AD_03D3735EE79C__INCLUDED_)
