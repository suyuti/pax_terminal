#ifndef _APPINFO_H
#define _APPINFO_H

//temp definitions
#define AUTHENTICATION_TRY_COUNT	3
#define GAIN_POINT_PERCENTAGE		0

//len
#define	LEN_APP_ID					3
#define LEN_FILE_LEN				3
#define LEN_FILE_OFFSET				3
#define LEN_WRITE_DATA_LEN			3
#define LEN_WRITE_DATA				"\x32\x00\x00"

#define	LEN_FILE_FAN				"\xFA\x00\x00"
#define	LEN_FILE_SEASON_TICKET		"\xFA\x00\x00"
#define	LEN_FILE_PREPAID			"\xFA\x00\x00"
#define	LEN_FILE_LOYALTY			"\xFA\x00\x00"
#define	LEN_FILE_TICKET				"\x20\x03\x00" //0x0320 = 800 Byte

#define FILE_OFFSET_0				"\x00\x00\x00"				
#define FILE_OFFSET_1				"\x32\x00\x00"				
#define FILE_OFFSET_2				"\x64\x00\x00"				
#define FILE_OFFSET_3				"\x96\x00\x00"				
#define FILE_OFFSET_4				"\xC8\x00\x00"				

//App IDs
#define APP_ID_FENERBAHCE			"\x19\x07\x60"
#define APP_ID_TICKET				"\x19\x07\x40"

//File IDs
#define FILE_ID_FAN					0x01
#define FILE_ID_SEASON_TICKET		0x02
#define FILE_ID_PREPAID				0x03
#define FILE_ID_LOYALTY				0x04
#define FILE_ID_TICKET				0x01


//Desfire Commands
#define CMD_GET_APP_LIST			"\x6A"
#define LEN_CMD_GET_APP_LIST		1
#define CMD_AUTHENTICATE			"\x0A\x00"
#define LEN_CMD_AUTHENTICATE		2
#define CMD_SELECT_APP				"\x5A"
#define LEN_CMD_SELECT_APP			1
#define CMD_GET_FILE_IDS			"\x6F"
#define LEN_CMD_GET_FILE_IDS		1
#define CMD_READ_FILE_DATA			"\xBD"
#define LEN_CMD_READ_FILE_DATA		1
#define CMD_WRITE_FILE_DATA			"\x3D"
#define LEN_CMD_WRITE_FILE_DATA		1

#define FAIL_READER_INIT			(-5001 )
#define FAIL_CARD_DETECT			(-5002 )
#define FAIL_GET_APPLICATIONS		(-5003 )
#define FAIL_AUTHENTICATION			(-5004 )
#define FAIL_SELECT_APPLICATION		(-5005 )
#define FAIL_GET_FILE_IDS			(-5006 )
#define FAIL_READ_FILE_DATA			(-5007 )
#define FAIL_WRITE_FILE_DATA		(-5008 )
#define FAIL_SEND_RECEIVE			(-5009 )
#define FAIL_INSUFFICENT_BALANCE	(-5010)
#define FAIL_INSUFFICENT_POINTS		(-5011)

//-----------------------------------

typedef struct _FanFile
{
	uchar	CardNumber				[ 16];
    char	Name					[ 20];
    char	SurName					[ 20];           
    uchar	BirthDate				[  4];        
    uchar	FirstCardGivenDate		[  4];
    uchar	TCKN					[ 11];          
    char	Address					[ 50];           
    uchar	MobileNumber			[ 14];        
    uchar	RFU						[111];
} FanStruct, *HFanStruct;

typedef struct _FanFileSum
{
	uchar	CardNumber				[ 16];
    char	Name					[ 20];
    char	SurName					[ 20];           
    uchar	BirthDate				[  4];
    uchar	FirstCardGivenDate		[  4];
    uchar	TCKN					[ 11];          
} FanStructSum, *HFanStructSum;

//-----------------------------------

typedef struct _SeasonTicketFile
{
	uchar	StartDate				[  4];
	uchar	FinishDate				[  4];
	uchar	State					[  1];
	uchar	LastStadiumEntryDate	[  4];
	uchar	Inf						[100]; 
	uchar	RFU						[137];
} SeasonTicketStruct, *HSeasonTicketStruct;

typedef struct _SeasonTicketFileSum
{
	uchar	StartDate				[  4];
	uchar	FinishDate				[  4];
	uchar	State					[  1];
} SeasonTicketStructSum, *HSeasonTicketStructSum;

//-----------------------------------

typedef struct _PrepaidFile
{
	uchar EffectiveDate				[  4];        
    uchar ExpiryDate				[  4];        
    uchar Balance					[  6];
    uchar ProcessCounter			[  2];
    uchar PrepaidState				[  1];     
    uchar StateChangingDate			[  4];       
    uchar LastProcessDate			[  4];        
    uchar LastProcessCost			[  6];        
    uchar LastProcessTerminalId		[  8];
    uchar LastProcessOnlineOffline	[  1];        
    uchar LastProcessCryptogram		[  8];       
    uchar LastProcessRandomNumber	[  8];       
    uchar LastProcessChargeExpense	[  1];  // last process charge/expense        
    uchar LastProcessPlace			[ 20];        
    uchar RFU						[173];
} PrepaidStruct, *HPrepaidStruct;

typedef struct _PrepaidFileSum
{
	uchar EffectiveDate				[  4];        
    uchar ExpiryDate				[  4];        
    uchar Balance					[  6];
} PrepaidStructSum, *HPrepaidStructSum;

//-----------------------------------

typedef struct _LoyaltyFile
{
	uchar ValidationState			[  1];
	uchar SlotCode1					[ 15];
    uchar SlotEffectiveDate1		[  4];
    uchar SlotExpiryDate1			[  4];
    uchar FBPoint1					[  6];
    uchar SlotCode2					[ 15];
    uchar SlotEffectiveDate2		[  4];
    uchar SlotExpiryDate2			[  4];
    uchar FBPoint2					[  6];
    uchar SlotCode3					[ 15];
    uchar SlotEffectiveDate3		[  4];
    uchar SlotExpiryDate3			[  4];
    uchar FBPoint3					[  6];
    uchar SlotCode4					[ 15];
    uchar SlotEffectiveDate4		[  4];
    uchar SlotExpiryDate4			[  4];
    uchar FBPoint4					[  6];
    uchar RFU						[133];
} LoyaltyStruct, *HLoyaltyStruct;

typedef struct _LoyaltyFileSum
{
	uchar ValidationState			[  1];
	uchar SlotCode1					[ 15];
    uchar SlotEffectiveDate1		[  4];
    uchar SlotExpiryDate1			[  4];
    uchar FBPoint1					[  6];
    uchar SlotCode2					[ 15];
    uchar SlotEffectiveDate2		[  4];
    uchar SlotExpiryDate2			[  4];
    uchar FBPoint2					[  6];
    uchar SlotCode3					[ 15];
    uchar SlotEffectiveDate3		[  4];
    uchar SlotExpiryDate3			[  4];
    uchar FBPoint3					[  6];
    uchar SlotCode4					[ 15];
    uchar SlotEffectiveDate4		[  4];
    uchar SlotExpiryDate4			[  4];
    uchar FBPoint4					[  6];
} LoyaltyStructSum, *HLoyaltyStructSum;

//-----------------------------------

#endif
