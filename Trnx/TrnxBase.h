// TrnxBase.h: interface for the CTrnxBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXBASE_H__2508403E_B62C_43B9_A9DB_A54CE0980808__INCLUDED_)
#define AFX_TRNXBASE_H__2508403E_B62C_43B9_A9DB_A54CE0980808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "..\appinfo.h"
#include "ITrnxBase.h"
#include "..\Engine\CardReader.h"
#include "..\UI\InputBox.h"
#include "..\UI\MessageBox.h"
#include "..\Files\Batch.h"
#include "..\Engine\CardReader.h"
#include "..\UI\UIUtils.h"


#define TRNX_HARCAMA_LBL			"Harcama"
#define TRNX_BAKIYESORGU_LBL		"Bakiye Sorgu"
#define TRNX_BAKIYEYUKLEME_LBL		"Bakiye Yukleme"
#define TRNX_KARTGUNCELLE_LBL		"Kart Guncelle"
#define TRNX_NAKITYUKLEME_LBL		"Nakit Yukleme"
#define TRNX_PUANKULLANMA_LBL		"Puan Kullanma"
#define TRNX_PUANSORGU_LBL			"Puan Sorgu"
#define TRNX_DEBIT_YUKLEME			"Banka Karti Yukleme"
#define TRNX_KREDIKART_YUKLEME		"Kredi Karti Yukleme"
#define TRNX_IADE_LBL				"Iade"

class CEngine;
class CTrnxBase : public ITrnxBase
{
private:
	CTrnxBase();
public:
	CTrnxBase(CEngine*);
	virtual ~CTrnxBase();

	virtual int		Update(int recNo);
	virtual int		Save();
	virtual void	Print();
	virtual void	AfterDone();
	virtual int		DoVoid(int rec);
	virtual void	Clear();
	//virtual int		Do() { return SUCCESS; };

	void			SetData(CCardReader& cardReader);
	inline void		SetBatchData(CBatch::HBatchData hData) { memcpy(&this->m_data, hData, sizeof(CBatch::BatchData)); };

	inline void		SetDeleted()				{ this->m_data.m_deletedFlag	= 0x01;					};
	inline void		SetSent()					{ this->m_data.m_sentFlag		= 0x01;					};
	inline void		SetReversal(bool val)		{ this->m_data.m_reversalFlag	= (val ? 0x01 : 0x00);	};
	inline void		SetRecNo(int rec)			{ this->m_recNo					= rec;					};
	inline void		SetResponseCode(int code)	{ this->m_data.m_responseCode	= code;					};
	inline int		GetRecNo()					{ return this->m_recNo;									};
	inline bool		IsSaved()					{ return this->m_bSaved;								};

	void SetResponseMsgPrn(char* pMsg, int size);
	void SetResponseMsgScr(char* pMsg, int size);


protected:
	virtual void	PrintHeader();
	virtual void	PrintBody();
	virtual void	PrintFooter();
	virtual void	PrintErrorMessage(CCardReader& cardReader);
	virtual void	ShowErrorMessage(CCardReader& cardReader);
	virtual int		OnVoid()								{ return SUCCESS;};

	void CalcRRN();

protected:
	bool				m_usesIslemNo;	// STAN tuketir.Bazi islemler kaydedilmez, STAN tuketmez. Sorgulama gibi islemler.
	char				m_trnxLabel[32];
	CEngine*			m_pEngine;
	CBatch::BatchData	m_data;
	int					m_error;
	bool				m_bTypeOnline;  // islem orjinalde online mi gerceklesir.
	bool				m_bVoid;		// iptal islemi demektir. Iptal'in gerceklestigi anlamina gelmez. Sadece islemin turunu belirtir. 
										// Islemin gercekten iptal oldugu m_data.m_voidedFalg'de tutulur.
	int					m_recNo;		// hangi kayit numarasi ile kaydedildi.
	bool				m_bSaved;
};

#endif // !defined(AFX_TRNXBASE_H__2508403E_B62C_43B9_A9DB_A54CE0980808__INCLUDED_)
