// UIEngine.cpp: implementation of the CUIEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "UIEngine.h"

//--------------------------------------------------------------------------------------------------

CUIEngine::CUIEngine()
{

}

//--------------------------------------------------------------------------------------------------

CUIEngine::~CUIEngine()
{
	delete this->m_pMenuMain;
	delete this->m_pMenuTrnx;
	delete this->m_pMenuTrnxYukleme;
	delete this->m_pMenuRaporlar;
	delete this->m_pMenuGunsonu;
	delete this->m_pMenuSistem;
	delete this->m_pMenuParametre;
	delete this->m_pMenuIslemler;
	delete this->m_pMenuTrnxPuanIslemleri;

}

//--------------------------------------------------------------------------------------------------

void CUIEngine::Initialize()
{
	/*
		main							: (mainMenu					)
			Islemler					: (mainIslemler				)
				Harcama					: (islemHarcama				)
				Harcama Iptal			: (islemHarcamaIptal		)
				Harcama Iade			: (islemHarcamaIade			)
				Bakiye Sorgulama		: (islemBakiyeSorgu			)
				Nakit Yukleme			: (islemNakitYukleme		)
				Puan Kullanimi			: (islemPuanKullanma		)
				Puan Kullanimi Iptali	: (islemPuanKullanmaIptal	)
				Puan Kullanimi Iadesi	: (islemPuanKullanmaIade	)
				Puan Sorgulama			: (islemPuanSorgu			)
				Kart Guncelleme			: (islemKartGuncelle		)
			Sistem						: (m_sistemMenu				)
				Default					: (m_sistemDefault			)
				Parametre Yukle			: (m_sistemParametreYukle	)
				Kayit					: (m_itemSistemKayitIzle	)
				Test					: (m_itemSistemTest			)

			Islemler
				.....
			Raporlar
				Toplamlar
				Songunsonu
			GunSonu
				Toplamlar
				Gunsonu yap
			Sistem
				Parametre
					Default
					Yazdir
					Yukle
				Islem
					Kayitlar
	
	*/
	this->m_pMenuMain				= new CSSMenu2();
	this->m_pMenuTrnx				= new CSSMenu2();
	this->m_pMenuTrnxYukleme		= new CSSMenu2();
	this->m_pMenuRaporlar			= new CSSMenu2();
	this->m_pMenuGunsonu			= new CSSMenu2();
	this->m_pMenuSistem				= new CSSMenu2();
	this->m_pMenuParametre			= new CSSMenu2();
	this->m_pMenuIslemler			= new CSSMenu2();
	this->m_pMenuTrnxPuanIslemleri	= new CSSMenu2();


	m_itMainTrnx						.SetValues(" iSLEMLER        >",					'0', (MenuActionPtr)NULL,			this->m_pMenuTrnx);
		m_itemTrnxHarcama				.SetValues("Harcama",					'0', islemHarcamaHandler,			this->m_pMenuMain);
		m_itemTrnxBakiyeSorgu			.SetValues("Bakiye Sorgu",				'0', islemBakiyeSorguHandler,		this->m_pMenuMain);
		m_itemTrnxYukleme				.SetValues("Yükleme          >",					'0', (MenuActionPtr)NULL,			this->m_pMenuTrnxYukleme);
			m_itemTrnxYuklemeNakit		.SetValues("Nakit Yükleme",				'0', islemNakitYuklemeHandler,		this->m_pMenuMain);
			m_itemTrnxYuklemeBankaKart	.SetValues("B.Kart Yükleme",			'0', islemBankaKartYuklemeHandler,	this->m_pMenuMain);
			m_itemTrnxYuklemeKrediKart	.SetValues("K.Kart Yükleme",			'0', islemKrediKartYuklemeHandler,	this->m_pMenuMain);
		m_itemTrnxPuanIslemleri			.SetValues("Puan Islemleri   >",			'0', (MenuActionPtr)NULL,			this->m_pMenuTrnxPuanIslemleri);
			m_itemTrnxPuanKullanma		.SetValues("Puan Kullanma",				'0', islemPuanKullanmaHandler,		this->m_pMenuMain);
			m_itemTrnxPuanSorgu			.SetValues("Puan Sorgu",				'0', islemPuanSorguHandler,			this->m_pMenuMain);
		m_itemTrnxKartGuncelle			.SetValues("Kart Güncelle",				'0', islemKartGuncelleHandler,		this->m_pMenuMain);
		m_itemTrnxIptal					.SetValues("Iptal",						'0', islemIptal,					this->m_pMenuMain);
		m_itemTrnxIade					.SetValues("Iade",						'0', islemIade,						this->m_pMenuMain);
/*
	m_itMainTrnx						.SetValues(" iSLEMLER",					'0', (MenuActionPtr)NULL,			this->m_pMenuTrnx);
		m_itemTrnxHarcama				.SetValues("Harcama",					'0', islemHarcamaHandler,			this->m_pMenuMain);
		m_itemTrnxHarcamaIptal			.SetValues("Harcama Iptal",				'0', islemHarcamaIptalHandler,		this->m_pMenuMain);
		m_itemTrnxHarcamaIade			.SetValues("Harcama Iade",				'0', islemHarcamaIadeHandler,		this->m_pMenuMain);
		m_itemTrnxBakiyeSorgu			.SetValues("Bakiye Sorgu",				'0', islemBakiyeSorguHandler,		this->m_pMenuMain);
		m_itemTrnxNakitYukleme			.SetValues("Yükleme",					'0', (MenuActionPtr)NULL,			this->m_pMenuTrnxYukleme);
			m_itemTrnxYuklemeNakit		.SetValues("Nakit Yükleme",				'0', islemNakitYuklemeHandler,		this->m_pMenuMain);
			m_itemTrnxYuklemeBankaKart	.SetValues("B.Kart Yükleme",			'0', islemBankaKartYuklemeHandler,	this->m_pMenuMain);
			m_itemTrnxYuklemeKrediKart	.SetValues("K.Kart Yükleme",			'0', islemKrediKartYuklemeHandler,	this->m_pMenuMain);
			m_itemTrnxYuklemeIptal		.SetValues("Iptal",						'0', islemYuklemeIptalHandler,		this->m_pMenuMain);
		m_itemTrnxPuanKullanma			.SetValues("Puan Kullanma",				'0', islemPuanKullanmaHandler,		this->m_pMenuMain);
		m_itemTrnxPuanKullanmaIptal		.SetValues("Puan Kul. Iptal",			'0', islemPuanKullanmaIptalHandler, this->m_pMenuMain);
		m_itemTrnxPuanKullanmaIade		.SetValues("Puan Kul. Iade",			'0', islemPuanKullanmaIadeHandler,	this->m_pMenuMain);
		m_itemTrnxPuanSorgu				.SetValues("Puan Sorgu",				'0', islemPuanSorguHandler,			this->m_pMenuMain);
		m_itemTrnxKartGuncelle			.SetValues("Kart Güncelle",				'0', islemKartGuncelleHandler,		this->m_pMenuMain);
*/
	m_itMainRaporlar					.SetValues(" RAPORLAR        >",					'0', (MenuActionPtr)NULL,			this->m_pMenuRaporlar);
		m_itRaporToplamlar				.SetValues(" Toplamlar",				'0', islemShowToplamRapor,			this->m_pMenuMain);
		m_itRaporSonGunsonu				.SetValues(" Son Gunsonu",				'0', (MenuActionPtr)islemSonGunsonuYaz,			this->m_pMenuMain);

	m_itMainGunsonu						.SetValues(" GUNSONU         >",					'0', (MenuActionPtr)NULL,			this->m_pMenuGunsonu);
		m_itGunsonuToplamlar			.SetValues(" Toplamlar",				'0', islemShowToplamRapor,			this->m_pMenuMain);
		m_itGunsonuYap					.SetValues(" Gunsonu Yap",				'0', islemGunsonuYap,				this->m_pMenuMain);

	m_itMainSistem						.SetValues(" SiSTEM          >",					'0', (MenuActionPtr)NULL,			this->m_pMenuSistem);
		m_itSistemParametre				.SetValues(" PARAMETRE       >",				'0', (MenuActionPtr)NULL,			this->m_pMenuParametre);
			m_itSistemParametreDefault	.SetValues(" Default Parametreler",		'0', islemDefaultParameters,		this->m_pMenuMain);
			m_itSistemParametreParams	.SetValues(" Yuklenen Parametreler",	'0', islemShowParametreler,			this->m_pMenuMain);
			m_itSistemParametreYukle	.SetValues(" Parametre Yukle",			'0', islemParametreYukleHandler,	this->m_pMenuMain);
		m_itSistemIslemler				.SetValues(" iSLEMLER        >",					'0', (MenuActionPtr)NULL,			this->m_pMenuIslemler);
			m_itSistemIslemlerKayitlar	.SetValues(" Kayitlar",					'0', islemKayitIzleHandler,			this->m_pMenuMain);
			m_itSistemIslemlerTest		.SetValues(" *Test",					'0', islemTestHandler,				this->m_pMenuMain);
			m_itSistemIslemlerTemizle	.SetValues(" *Temizle",					'0', islemTestTemizleHandler,		this->m_pMenuMain);

	m_itMainKartFormatlama				.SetValues(" Kart Formatlama",			'0', (MenuActionPtr)NULL,			this->m_pMenuMain);

	this->m_pMenuMain		->AddItem(&this->m_itMainTrnx					);
	this->m_pMenuMain		->AddItem(&this->m_itMainRaporlar				);
	this->m_pMenuMain		->AddItem(&this->m_itMainGunsonu				);
	this->m_pMenuMain		->AddItem(&this->m_itMainSistem					);
	this->m_pMenuMain		->AddItem(&this->m_itMainKartFormatlama			);

	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxHarcama				);
	//this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxHarcamaIptal			);
	//this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxHarcamaIade			);
	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxBakiyeSorgu			);
	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxYukleme				);

	this->m_pMenuTrnxYukleme->AddItem(&this->m_itemTrnxYuklemeNakit			);
	this->m_pMenuTrnxYukleme->AddItem(&this->m_itemTrnxYuklemeBankaKart		);
	this->m_pMenuTrnxYukleme->AddItem(&this->m_itemTrnxYuklemeKrediKart		);
	//this->m_pMenuTrnxYukleme->AddItem(&this->m_itemTrnxYuklemeIptal			);

	this->m_pMenuTrnx				->AddItem(&this->m_itemTrnxPuanIslemleri		);
	this->m_pMenuTrnxPuanIslemleri	->AddItem(&this->m_itemTrnxPuanKullanma			);
	//this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxPuanKullanmaIptal	);
	//this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxPuanKullanmaIade		);
	this->m_pMenuTrnxPuanIslemleri		->AddItem(&this->m_itemTrnxPuanSorgu			);
	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxKartGuncelle			);
	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxIptal);
	this->m_pMenuTrnx		->AddItem(&this->m_itemTrnxIade);

	this->m_pMenuRaporlar	->AddItem(&this->m_itRaporToplamlar				);
	this->m_pMenuRaporlar	->AddItem(&this->m_itRaporSonGunsonu			);

	this->m_pMenuGunsonu	->AddItem(&this->m_itGunsonuToplamlar			);
	this->m_pMenuGunsonu	->AddItem(&this->m_itGunsonuYap					);

	this->m_pMenuSistem		->AddItem(&this->m_itSistemParametre			);
	this->m_pMenuSistem		->AddItem(&this->m_itSistemIslemler				);

	this->m_pMenuParametre	->AddItem(&this->m_itSistemParametreDefault		);
	this->m_pMenuParametre	->AddItem(&this->m_itSistemParametreParams		);
	this->m_pMenuParametre	->AddItem(&this->m_itSistemParametreYukle		);

	this->m_pMenuIslemler	->AddItem(&this->m_itSistemIslemlerKayitlar		);
	this->m_pMenuIslemler	->AddItem(&this->m_itSistemIslemlerTest			);
	this->m_pMenuIslemler	->AddItem(&this->m_itSistemIslemlerTemizle		);

	ScrFontSet(0);
}

//--------------------------------------------------------------------------------------------------

void CUIEngine::EntryMenu()
{
	
	//CSSMenu2* pActiveMenu = &this->m_pMenuMain;
	IMenu* pActiveMenu = this->m_pMenuMain;

	do {
		pActiveMenu = pActiveMenu->Draw();
		if (pActiveMenu == (CSSMenu*)NULL) {
			break;
		}
	} while (true);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
