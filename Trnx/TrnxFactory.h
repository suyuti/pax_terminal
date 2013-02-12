// TrnxFactory.h: interface for the CTrnxFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXFACTORY_H__1DA22CDF_5F4D_4EAC_BEC7_B3012182D955__INCLUDED_)
#define AFX_TRNXFACTORY_H__1DA22CDF_5F4D_4EAC_BEC7_B3012182D955__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PRCOCODE_HARCAMA			"000000"
#define PRCOCODE_BAKIYESORGU		""
#define PRCOCODE_NAKIT_YUKLEME		"007000"
#define PRCOCODE_BANKAKART_YUKLEME	"007010"
#define PRCOCODE_KREDIKART_YUKLEME	"007020"
#define PRCOCODE_PUANKULLANMA		"001000"
#define PRCOCODE_PUANSORGU			"203800"
#define PRCOCODE_KARTGUNCELLE		""
#define PRCOCODE_IADE				"002000"



class ITrnxBase;
class CEngine;
class CBatch;
class CTrnxFactory  
{
private:
	CTrnxFactory();
public:
	CTrnxFactory(CEngine*);
	virtual ~CTrnxFactory();

	typedef enum {
		//trnxBakiyeYukleme = 0,
		//trnxSatis = 0,
		trnxHarcama = 0,
		//trnxHarcamaIptal,
		//trnxHarcamaIade,
		trnxBakiyeSorgu,
		trnxNakitYukleme,
		trnxPuanKullanma,
		//trnxPuanKullanmaIptal,
		//trnxPuanKullanmaIade,
		trnxPuanSorgu,
		trnxKartGuncelle,
		trnxKrediKartYukleme,
		trnxDebitYukleme,
		trnxIade,
	} TrnxTypes;

	ITrnxBase* CreateTrnx(TrnxTypes type);
	ITrnxBase* CreateTrnx(CBatch* pBatch);
private:
	CEngine* m_pEngine;
};

#endif // !defined(AFX_TRNXFACTORY_H__1DA22CDF_5F4D_4EAC_BEC7_B3012182D955__INCLUDED_)
