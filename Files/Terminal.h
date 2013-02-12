// Terminal.h: interface for the CTerminal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERMINAL_H__96F5377C_1E7D_431D_8670_D5F2D2A752ED__INCLUDED_)
#define AFX_TERMINAL_H__96F5377C_1E7D_431D_8670_D5F2D2A752ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

/*
Terminal Option Byte 1	b 8	
0x80 : Use Summary Report 
0x40 : Use Detail Report 
0x20 : RFU 
0x10 : Use Report Password
0x08 : Use Settle Password 
0x04 : Use Refund Password
0x02 : Use Void Password
0x01 : Use Merchant Password

Terminal Option Byte 2	b 8	
0x80 : Offline Counter Control
0x40 : Mask Report
0x20 : Contactless Disabled
0x10 : Manual Entry Disabled
0x08 : Pad Disabled 
0x04 : Magnetic Reader Disabled 
0x02 : ICC Disabled 
0x01 : Printer Disabled 

Terminal Option Byte 3	b 8	
0x80 : RFU
0x40 : RFU
0x20 : Try Backup Connection
0x10 : Blacklist Control Enabled
0x08 : Print Contactless Copy 2
0x04 : Print Contactless Copy 1
0x02 : Print Copy 2
0x01 : Print Copy 1

Terminal Option Byte 4	b 8	
0x80 : Sales Allowed 
0x40 : Void Allowed
0x20 : Refund Allowed
0x10 : Balance Load (Cash) Allowed
0x08 : Balance Load (Account) Allowed
0x04 : Balance Load Realization Allowed
0x02 : Balance Inquiry Allowed
0x01 : Balance Refund Allowed

Terminal Option Byte 5	b 8	
0x80 : Give Instruction Allowed
0x40 : Blacklist Load Allowed
0x20 : RFU
0x10 : RFU
0x08 : RFU
0x04 : RFU
0x02 : RFU
0x01 : RFU
*/
//                                           1234567890123456789012345678901234567890       
#define DEF_TERM_TERMID						"00000001"
#define DEF_TERM_MERCHID					"000000000000002"
#define DEF_TERM_MERCHNAME					"<UYE ISYERI>                            "
#define DEF_TERM_MERCHADDRESS1				"<Adres 1>                     </Adres 1>"
#define DEF_TERM_MERCHADDRESS2				"<Adres 2>                     </Adres 2>"
#define DEF_TERM_MERCHADDRESS3				"<Adres 3>                     </Adres 3>"
#define DEF_TERM_MERCHADDRESS4				"<Adres 4>                     </Adres 4>"
#define DEF_TERM_MCC						"1234"
#define DEF_TERM_MERCHPASS					"1111"
#define DEF_TERM_VOIDPASS					"2222"
#define DEF_TERM_REFUNDPASS					"3333"
#define DEF_TERM_SETTLEPASS					"4444"
#define DEF_TERM_REPORTPASS					"5555"
#define DEF_TERM_TERMCAPABILITIES			"E0F0C0"
#define DEF_TERM_ADDITIONALCAPABILITIES		"6000D0A000"
#define DEF_TERM_DEFCURRENCYSYMBOL			" TL"
#define DEF_TERM_DEFCOUNTRYCODE				"0792"
#define DEF_TERM_DEFCURRENCYCODE			"0949"
#define DEF_TERM_EMVTERMTYPE				"22"
#define DEF_TERM_TRNXAMOUNTLENGTH			"07"
#define DEF_TERM_TERMONUSFLOORLIMIT			"000000001000"
#define DEF_TERM_TERMMAXADVICECOUNT			"10"
#define DEF_TERM_TERMADVICESUPLOADINTERVAL	"0020"
#define DEF_TERM_TERMPOSTADVICECOUNT		"12"

#define TABLE_NAME_TERMINAL	"term.txt"


class CTerminal : public CTable  
{
public:
	CTerminal();
	virtual ~CTerminal();

	typedef enum {
		sizeTableId						= 3,
		sizeTermId						= 8,
		sizeMerchId						= 15,
		sizeMerchName					= 40,
		sizeMerchAddress				= 40,
		sizeMcc							= 2,
		sizeMerchPass					= 2,
		sizeVoidPass					= 2,
		sizeRefundPass					= 2,
		sizeSettlePass					= 2,
		sizeReportPass					= 2,
		sizeTermCapabilities			= 3,
		sizeAdditionalCapabilities		= 5,
		sizeDefCurrencySymbol			= 3,
		sizeDefCountryCode				= 2,
		sizeDefCurrencyCode				= 2,
		sizeEMVTermType					= 1,
		sizeTrnxAmountLength			= 1,
		sizeTermOnusFloorLimit			= 6,
		sizeTermMaxAdviceCount			= 1,
		sizeTermAdvicesUploadInterval	= 2,
		sizeTermPostAdviceCount			= 1,
		sizeTermOptionByte				= 8,
	} TerminalSizes;

	typedef struct _tagTerminal {
		char m_tableId					[sizeTableId					];	// BCD	nP 6	
		char m_termId					[sizeTermId						];	// STR	an 8	
		char m_merchId					[sizeMerchId					];	// STR	an 15 	
		char m_merchName				[sizeMerchName					];	// STR	an 40	
		char m_merchAddress1			[sizeMerchAddress				];	// STR	Line - 1	an 40	Ticket header line : 1
		char m_merchAddress2			[sizeMerchAddress				];	// STR	Line - 2	an 40	Ticket header line : 2
		char m_merchAddress3			[sizeMerchAddress				];	// STR	Line - 2	an 40	Ticket header line : 2
		char m_merchAddress4			[sizeMerchAddress				];	// STR	Line - 2	an 40	Ticket header line : 2
		char m_mcc						[sizeMcc						];	// BCD	nP 4	
		char m_merchPass				[sizeMerchPass					];	// BCD	nP 4	
		char m_voidPass					[sizeVoidPass					];	// BCD	nP 4	
		char m_refundPass				[sizeRefundPass					];	// BCD	nP 4	
		char m_settlePass				[sizeSettlePass					];	// BCD	nP 4	
		char m_reportPass				[sizeReportPass					];	// BCD	nP 4	
		char m_termCapabilities			[sizeTermCapabilities			];	// BCD	anP 6	Default : \xE0\xF0\xC0
		char m_additionalCapabilities	[sizeAdditionalCapabilities		];	// BCD	anP 10	Default : \x60\x00\xD0\xA0\x00
		char m_defCurrencySymbol		[sizeDefCurrencySymbol			];	// BCD	an 3 	Default : “ TL”
		char m_defCountryCode			[sizeDefCountryCode				];	// BCD	nP 4	Default : \x07\x92
		char m_defCurrencyCode			[sizeDefCurrencyCode			];	// BCD	nP 4	Default \x09\x49
		//char m_EMVTermType				[sizeEMVTermType				];	// BCD	nP 2	Default : \x22
		char m_trnxAmountLength			[sizeTrnxAmountLength			];	// BCD	nP 2	Default : \x07
		char m_termOnusFloorLimit		[sizeTermOnusFloorLimit			];	// BCD	nP 12	12.34 TL = \x00\x00\x00\x00\x12\x34 
		char m_termMaxAdviceCount		[sizeTermMaxAdviceCount			];	// BCD	nP 2	Max. threshold value to send advice
		char m_termAdvicesUploadInterval[sizeTermAdvicesUploadInterval	];	// BCD	nP 4	Interval unit is minute
		char m_termPostAdviceCount		[sizeTermPostAdviceCount		];	// BCD	nP 2	Send advice count after online trnx
		char m_termOptionByte			[sizeTermOptionByte				];	// BIN	1	b 8	0x80 : Use Summary Report 
	} TerminalRecord, *HTerminalRecord;

	inline	HTerminalRecord GetData() { return &this->m_data;};

	virtual int Append();
	virtual void PrintAll();
	void CreateDefault();

private:
	TerminalRecord m_data;

};

#endif // !defined(AFX_TERMINAL_H__96F5377C_1E7D_431D_8670_D5F2D2A752ED__INCLUDED_)
