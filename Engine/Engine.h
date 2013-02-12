// Engine.h: interface for the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGINE_H__2D97A31D_DD89_4B82_BB23_E2DF201F5904__INCLUDED_)
#define AFX_ENGINE_H__2D97A31D_DD89_4B82_BB23_E2DF201F5904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIEngine.h"
#include "PrinterEngine.h"
#include "..\Trnx\TrnxFactory.h"
#include "..\Trnx\ITrnxBase.h"
#include "..\Files\Paramters.h"
#include "..\Files\Terminal.h"
#include "..\Files\Acquier.h"

class CCommEngine2;
class CEngine  
{
public:
	CEngine();
	virtual ~CEngine();

	int Initialize();
	void DeInitialize();
	void Run();

	void DownloadParameters();


	//------Islemler--------
	int DoBakiyeYukleme();

	int DoHarcama(void);
	int DoHarcamaIptal(void);
	int DoHarcamaIade(void);
	int DoBakiyeSorgu(void);
	int DoNakitYukleme(void);
	int DoKrediKartYukleme(void);
	int DoBankaKartYukleme(void);
	int DoYuklemeIptal(void);
	int DoPuanKullanma(void);
	int DoPuanKullanmaIptal(void);
	int DoPuanKullanmaIade(void);
	int DoPuanSorgu(void);
	int DoKartGuncelle(void);

	int DoVoid();
	int DoRefund();

	int GunsonuYap(void);

	int ShowIslemlerScreen(void);
	int ShowDefaultParameters(void);
	int ShowParametreler(void);
	int ShowToplamlarScreen(void);
	int PrintLastSlip(void);
	int SonGunSonuYaz(void);

	int OnAdviceTime(void);

	//---- Get - Set ----------------
	inline CPrinterEngine*	GetPrinterEng()	{ return this->m_pPrinterEngine;};
	inline CCommEngine2*	GetComm2Eng()	{ return this->m_pCommEng2;		};

	//inline CParamters*		GetDefParams()	{ return this->m_pDefParams;	};
	//inline CTerminal*		GetTerminal()	{ return this->m_pTerminal;		};
	//inline CAcquier*		GetAcquier()	{ return this->m_pAcquier;		};

	inline bool GetParametreOK()			{ return this->m_bParametreOK;	};
	inline void SetParametreOK(bool ok)		{ this->m_bParametreOK = ok;	};
	int CheckStatus(); // Islem yapmadan once yapilacak kontroller


	//------ Test---------
	int TestTemizle();

private:
	CUIEngine*		m_pUIEngine;
	CTrnxFactory*	m_pTrnxFactory;
	CPrinterEngine* m_pPrinterEngine;
	CCommEngine2*	m_pCommEng2;

	//CParamters*		m_pDefParams;
	//CTerminal*		m_pTerminal;
	//CAcquier*		m_pAcquier;
	bool			m_bParametreOK;	// Parametre dosyalari var MI.
};

#endif // !defined(AFX_ENGINE_H__2D97A31D_DD89_4B82_BB23_E2DF201F5904__INCLUDED_)
