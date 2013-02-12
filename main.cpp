#include <posapi.h>
#include <posapi_all.h>

#include "Engine/Engine.h"
#include "UI\MessageBox.h"

CEngine g_engine;
char g_int2hex[17] = "0123456789abcdef";

//---------------------------------------------------------------

void Method_TermianlID(void)
{
	g_engine.DoBakiyeYukleme();
	getkey();
}

//---------------------------------------------------------------

void Method_MerchantID(void)
{
	ScrCls();
	ScrGotoxy(0, 0);
	Lcdprintf("Merchant ID ");
	getkey();
}

//---------------------------------------------------------------

void islemIptal(void)
{
	g_engine.DoVoid();
}

//---------------------------------------------------------------

void islemIade(void)
{
	g_engine.DoRefund();
}

//---------------------------------------------------------------

void islemHarcamaHandler(void)
{
	g_engine.DoHarcama();
}

//---------------------------------------------------------------

void islemHarcamaIptalHandler(void)
{
	g_engine.DoHarcamaIptal();
}

//---------------------------------------------------------------

void islemHarcamaIadeHandler(void)
{
	g_engine.DoHarcamaIade();
}

//---------------------------------------------------------------

void islemBakiyeSorguHandler(void)
{
	g_engine.DoBakiyeSorgu();
}

//---------------------------------------------------------------

void islemNakitYuklemeHandler(void)
{
	g_engine.DoNakitYukleme();
}

//---------------------------------------------------------------

void islemKrediKartYuklemeHandler(void)
{
	g_engine.DoKrediKartYukleme();
}

//---------------------------------------------------------------

void islemYuklemeIptalHandler(void)
{
	g_engine.DoKrediKartYukleme();
}

//---------------------------------------------------------------

void islemBankaKartYuklemeHandler(void)
{
	g_engine.DoBankaKartYukleme();
}

//---------------------------------------------------------------

void islemPuanKullanmaHandler(void)
{
	g_engine.DoPuanKullanma();
}

//---------------------------------------------------------------

void islemPuanKullanmaIptalHandler(void)
{
	g_engine.DoPuanKullanmaIptal();
}

//---------------------------------------------------------------

void islemPuanKullanmaIadeHandler(void)
{
	g_engine.DoPuanKullanmaIade();
}

//---------------------------------------------------------------

void islemPuanSorguHandler(void)
{
	g_engine.DoPuanSorgu();
}

//---------------------------------------------------------------

void islemKartGuncelleHandler(void)
{
	g_engine.DoKartGuncelle();
}

//---------------------------------------------------------------

void islemShowToplamRapor(void)
{
	g_engine.ShowToplamlarScreen();
}

//---------------------------------------------------------------

void islemGunsonuYap(void)
{
	g_engine.GunsonuYap();
}

//---------------------------------------------------------------

void islemKayitIzleHandler(void)
{
	g_engine.ShowIslemlerScreen();
}

//---------------------------------------------------------------

void islemTestHandler(void)
{
	g_engine.OnAdviceTime();
}

//---------------------------------------------------------------

void islemTestTemizleHandler(void)
{
	g_engine.TestTemizle();
}

//---------------------------------------------------------------

void islemDefaultParameters(void)
{
	g_engine.ShowDefaultParameters();
}

//---------------------------------------------------------------

void islemShowParametreler(void)
{
	g_engine.ShowParametreler();
}

//---------------------------------------------------------------

void islemParametreYukleHandler(void)
{
	g_engine.DownloadParameters();
}

//---------------------------------------------------------------

void islemSonSlipYaz()
{
	g_engine.PrintLastSlip();
}

//---------------------------------------------------------------

void islemSonGunsonuYaz()
{
	g_engine.SonGunSonuYaz();
}


//---------------------------------------------------------------

void AssertDisp(uchar *pszFileName, ulong ulLineNo)
{
	char tmp[255] = "";
	sprintf(tmp, "%s:%d", pszFileName, ulLineNo);
	CMessageBox msg(tmp, MB_ANY_KEY);
	msg.Draw();
}

//---------------------------------------------------------------


void PrintBuffer(unsigned char* pBuffer, int size)
{
	PrnInit(); 
	for (int i = 0; i < size; ++i) {
		PrnStr("%02X ", pBuffer[i]);
	}
	PrnStr("\n"); 
	PrnStart();
}










//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------






const APPINFO AppInfo={
	"FB",
	"FB",
	"1.0",
	"SmarSoft-RedTeam",
	"FB",
	"",
	0,
	0,
	0,
	""
};


int event_main(ST_EVENT_MSG *msg)
{
	SystemInit();
    return 0;
}


int main(void)
{
	uchar key;
	SystemInit();
	g_engine.Initialize();
	g_engine.Run();
	key = getkey();
	g_engine.DeInitialize();

	return 0;
}
