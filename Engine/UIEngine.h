// UIEngine.h: interface for the CUIEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIENGINE_H__64044F49_91A0_4064_A7FA_0D27DBEEA7E9__INCLUDED_)
#define AFX_UIENGINE_H__64044F49_91A0_4064_A7FA_0D27DBEEA7E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\UI\Menu.h"
#include "..\UI\SSMenu2.h"
#include "..\UI\MenuItem.h"

class CUIEngine  
{
public:
	CUIEngine();
	virtual ~CUIEngine();

	void Initialize();
	void EntryMenu();

private:
	IMenu*	m_pMenuMain;
	IMenu*	m_pMenuTrnx;
	IMenu*	m_pMenuTrnxYukleme;
	IMenu*	m_pMenuTrnxPuanIslemleri;
	IMenu*	m_pMenuRaporlar;
	IMenu*	m_pMenuGunsonu;
	IMenu*	m_pMenuSistem;
	IMenu*	m_pMenuParametre;
	IMenu*	m_pMenuIslemler;

/*
	IMenu*	m_pMenuMain;
	IMenu*	m_pMenuTrnx;
	IMenu*	m_pMenuTrnxYukleme;
	IMenu*	m_pMenuRaporlar;
	IMenu*	m_pMenuGunsonu;
	IMenu*	m_pMenuSistem;
	IMenu*	m_pMenuParametre;
	IMenu*	m_pMenuIslemler;
*/

	CSSMenuItem m_itMainTrnx;
		CSSMenuItem m_itemTrnxHarcama;
		CSSMenuItem m_itemTrnxYukleme;
			CSSMenuItem m_itemTrnxYuklemeNakit;
			CSSMenuItem m_itemTrnxYuklemeBankaKart;
			CSSMenuItem m_itemTrnxYuklemeKrediKart;
		CSSMenuItem m_itemTrnxPuanIslemleri;
			CSSMenuItem m_itemTrnxPuanKullanma;
			CSSMenuItem m_itemTrnxPuanSorgu;
		CSSMenuItem m_itemTrnxBakiyeSorgu;
		CSSMenuItem m_itemTrnxIptal;
		CSSMenuItem m_itemTrnxIade;
		CSSMenuItem m_itemTrnxKartGuncelle;

/*
	CSSMenuItem m_itMainTrnx;
		CSSMenuItem m_itemTrnxHarcama;
		CSSMenuItem m_itemTrnxHarcamaIptal;
		CSSMenuItem m_itemTrnxHarcamaIade;
		CSSMenuItem m_itemTrnxBakiyeSorgu;
		CSSMenuItem m_itemTrnxNakitYukleme;
			CSSMenuItem m_itemTrnxYuklemeNakit;
			CSSMenuItem m_itemTrnxYuklemeBankaKart;
			CSSMenuItem m_itemTrnxYuklemeKrediKart;
			CSSMenuItem m_itemTrnxYuklemeIptal;
		CSSMenuItem m_itemTrnxPuanKullanma;
		CSSMenuItem m_itemTrnxPuanKullanmaIptal;
		CSSMenuItem m_itemTrnxPuanKullanmaIade;
		CSSMenuItem m_itemTrnxPuanSorgu;
		CSSMenuItem m_itemTrnxKartGuncelle;
*/
	CSSMenuItem m_itMainRaporlar;
		CSSMenuItem m_itRaporToplamlar;
		CSSMenuItem m_itRaporSonGunsonu;

	CSSMenuItem m_itMainGunsonu;
		CSSMenuItem m_itGunsonuToplamlar;
		CSSMenuItem m_itGunsonuYap;

	CSSMenuItem m_itMainSistem;
		CSSMenuItem m_itSistemParametre;
			CSSMenuItem m_itSistemParametreDefault;
			CSSMenuItem m_itSistemParametreParams;
			CSSMenuItem m_itSistemParametreYukle;
		CSSMenuItem m_itSistemIslemler;
			CSSMenuItem m_itSistemIslemlerKayitlar;
			CSSMenuItem m_itSistemIslemlerTest;
			CSSMenuItem m_itSistemIslemlerTemizle;
	CSSMenuItem m_itMainKartFormatlama;
};

#endif // !defined(AFX_UIENGINE_H__64044F49_91A0_4064_A7FA_0D27DBEEA7E9__INCLUDED_)
