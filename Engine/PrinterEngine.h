// PrinterEngine.h: interface for the CPrinterEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERENGINE_H__587CF898_DF6E_4B53_A506_FBB23C207013__INCLUDED_)
#define AFX_PRINTERENGINE_H__587CF898_DF6E_4B53_A506_FBB23C207013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"

class CPrinterEngine  
{
public:
	CPrinterEngine();
	virtual ~CPrinterEngine();

	bool Init();
	void Start();

	void PrintLogo();
	
	typedef enum {
		w6	= 6,
		w8	= 8,
		w12 = 12,
		w16 = 16
	} FontWidths;
	
	typedef enum {
		h8	= 8,
		h12 = 12,
		h16 = 16,
		h24 = 24
	} FontHeights;

	static void SetFont(FontWidths width, FontHeights height, bool bold, bool italic);
	//static void SetFont(int ascii, int locale);
	
/*	typedef enum {
		left = 0,
		right,
		center,
	} Alingments;

	typedef enum {
		small,
		normal,
		big,
	} Fonts;

	void Print(char*, Fonts, Alignments);
*/
	void Test();


	enum{
		PRN_6x8=0,
		PRN_8x16,
		PRN_16x16,
		PRN_12x24,
		PRN_24x24,
		PRN_6x12,
		PRN_12x12,
		PRN_NULL=0xFF
	};

public:
	static int GetLogoWidthHeigh(uchar *psData, int *piWidth, int *piHeigh);
	void PrnSetNormal();
	void PrnSetSmall();
	void PrnSetBig();
	void PrnSetBig2();
	int PrnFontSetNew(uchar ucEnType, uchar ucSQType);

	void PrintSettleReport();
	void PrintTotalReport();
	void PrintLastSettleReport();

private:
	static unsigned char ms_pPrnLogo[];
};

#endif // !defined(AFX_PRINTERENGINE_H__587CF898_DF6E_4B53_A506_FBB23C207013__INCLUDED_)
