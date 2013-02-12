// Terminal.cpp: implementation of the CTerminal class.
//
//////////////////////////////////////////////////////////////////////

#include "Terminal.h"
#include "..\Util\NumFuncs.h"

//--------------------------------------------------------------------------------------

CTerminal::CTerminal() :
	CTable((void*)&m_data)
{
	this->m_recordSize = sizeof(CTerminal::TerminalRecord);
	sprintf(this->m_fileName, "%s", TABLE_NAME_TERMINAL);
}

//--------------------------------------------------------------------------------------

CTerminal::~CTerminal()
{

}

//--------------------------------------------------------------------------------------

void CTerminal::PrintAll()
{
	char tmp[64] = "";

	PrnInit();

	for (int i = 0; i < this->m_recordCount; ++i) {
		this->GotoRec(i + 1, true);

		memcpy(tmp, this->m_data.m_termId, sizeTermId); tmp[sizeTermId] = 0x00;
		PrnStr("TermID: %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchId, sizeMerchId); tmp[sizeMerchId] = 0x00;
		PrnStr("M.ID  : %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchName, sizeMerchName); tmp[sizeMerchName] = 0x00;
		PrnStr("M.Name: %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchAddress1, sizeMerchAddress); tmp[sizeMerchAddress] = 0x00;
		PrnStr("M.Addr: %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchAddress2, sizeMerchAddress); tmp[sizeMerchAddress] = 0x00;
		PrnStr("M.Addr: %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchAddress3, sizeMerchAddress); tmp[sizeMerchAddress] = 0x00;
		PrnStr("M.Addr: %s\n", tmp);

		memcpy(tmp, this->m_data.m_merchAddress4, sizeMerchAddress); tmp[sizeMerchAddress] = 0x00;
		PrnStr("M.Addr: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_mcc, sizeMcc, 0, tmp);
		PrnStr("MCC: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_merchPass, sizeMerchPass, 0, tmp);
		PrnStr("M.Pass: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_voidPass, sizeVoidPass, 0, tmp);
		PrnStr("V.Pass: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_refundPass, sizeRefundPass, 0, tmp);
		PrnStr("R.Pass: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_settlePass, sizeSettlePass, 0, tmp);
		PrnStr("S.Pass: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_reportPass, sizeReportPass, 0, tmp);
		PrnStr("R.Pass: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_termCapabilities, sizeTermCapabilities, 0, tmp);
		PrnStr("T.Caps: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_additionalCapabilities, sizeAdditionalCapabilities, 0, tmp);
		PrnStr("AdCaps: %s\n", tmp);

		memcpy(tmp, this->m_data.m_defCurrencySymbol, sizeDefCurrencySymbol); tmp[sizeDefCurrencySymbol] = 0x00;
		PrnStr("CurSym: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_defCountryCode, sizeDefCountryCode, 0, tmp);
		PrnStr("CntrCd: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_defCurrencyCode, sizeDefCurrencyCode, 0, tmp);
		PrnStr("CurCod: %s\n", tmp);

		//Bcd2Str((unsigned char*)this->m_data.m_EMVTermType, sizeEMVTermType, 0, tmp);
		//PrnStr("EMVTyp: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_trnxAmountLength, sizeTrnxAmountLength, 0, tmp);
		PrnStr("TrAmtL: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_termOnusFloorLimit, sizeTermOnusFloorLimit, 0, tmp);
		PrnStr("OnFlLm: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_termMaxAdviceCount, sizeTermMaxAdviceCount, 0, tmp);
		PrnStr("MaxAdv: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_termAdvicesUploadInterval, sizeTermAdvicesUploadInterval, 0, tmp);
		PrnStr("AdUpIn: %s\n", tmp);

		Bcd2Str((unsigned char*)this->m_data.m_termPostAdviceCount, sizeTermPostAdviceCount, 0, tmp);
		PrnStr("PoAdCo: %s\n", tmp);
	}
	PrnStart();

}

//--------------------------------------------------------------------------------------

void CTerminal::CreateDefault()
{
	memset(&this->m_data, 0x00, sizeof(TerminalRecord));

	strncpy(this->m_data.m_termId		, DEF_TERM_TERMID		, strlen(DEF_TERM_TERMID		));
	strncpy(this->m_data.m_merchId		, DEF_TERM_MERCHID		, strlen(DEF_TERM_MERCHID		));
	strncpy(this->m_data.m_merchName	, DEF_TERM_MERCHNAME	, strlen(DEF_TERM_MERCHNAME		));
	strncpy(this->m_data.m_merchAddress1, DEF_TERM_MERCHADDRESS1, strlen(DEF_TERM_MERCHADDRESS1	));
	strncpy(this->m_data.m_merchAddress2, DEF_TERM_MERCHADDRESS2, strlen(DEF_TERM_MERCHADDRESS2	));
	strncpy(this->m_data.m_merchAddress3, DEF_TERM_MERCHADDRESS3, strlen(DEF_TERM_MERCHADDRESS3	));
	strncpy(this->m_data.m_merchAddress4, DEF_TERM_MERCHADDRESS4, strlen(DEF_TERM_MERCHADDRESS4	));

	Str2Bcd(DEF_TERM_MCC						, strlen(DEF_TERM_MCC						), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_mcc						, CTerminal::sizeMcc						, LEFT_PAD);
	Str2Bcd(DEF_TERM_MERCHPASS					, strlen(DEF_TERM_MERCHPASS					), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_merchPass					, CTerminal::sizeMerchPass					, LEFT_PAD);
	Str2Bcd(DEF_TERM_VOIDPASS					, strlen(DEF_TERM_VOIDPASS					), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_voidPass					, CTerminal::sizeVoidPass					, LEFT_PAD);
	Str2Bcd(DEF_TERM_REFUNDPASS					, strlen(DEF_TERM_REFUNDPASS				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_refundPass					, CTerminal::sizeRefundPass					, LEFT_PAD);
	Str2Bcd(DEF_TERM_SETTLEPASS					, strlen(DEF_TERM_SETTLEPASS				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_settlePass					, CTerminal::sizeSettlePass					, LEFT_PAD);
	Str2Bcd(DEF_TERM_REPORTPASS					, strlen(DEF_TERM_REPORTPASS				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_reportPass					, CTerminal::sizeReportPass					, LEFT_PAD);
	Str2Bcd(DEF_TERM_TERMCAPABILITIES			, strlen(DEF_TERM_TERMCAPABILITIES			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_termCapabilities			, CTerminal::sizeTermCapabilities			, LEFT_PAD);
	Str2Bcd(DEF_TERM_ADDITIONALCAPABILITIES		, strlen(DEF_TERM_ADDITIONALCAPABILITIES	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_additionalCapabilities		, CTerminal::sizeAdditionalCapabilities		, LEFT_PAD);
	Str2Bcd(DEF_TERM_DEFCURRENCYSYMBOL			, strlen(DEF_TERM_DEFCURRENCYSYMBOL			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_defCurrencySymbol			, CTerminal::sizeDefCurrencySymbol			, LEFT_PAD);
	Str2Bcd(DEF_TERM_DEFCOUNTRYCODE				, strlen(DEF_TERM_DEFCOUNTRYCODE			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_defCountryCode				, CTerminal::sizeDefCountryCode				, LEFT_PAD);
	Str2Bcd(DEF_TERM_DEFCURRENCYCODE			, strlen(DEF_TERM_DEFCURRENCYCODE			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_defCurrencyCode			, CTerminal::sizeDefCurrencyCode			, LEFT_PAD);
	//Str2Bcd(DEF_TERM_EMVTERMTYPE				, strlen(DEF_TERM_EMVTERMTYPE				), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_EMVTermType				, CTerminal::sizeEMVTermType				, LEFT_PAD);
	Str2Bcd(DEF_TERM_TRNXAMOUNTLENGTH			, strlen(DEF_TERM_TRNXAMOUNTLENGTH			), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_trnxAmountLength			, CTerminal::sizeTrnxAmountLength			, LEFT_PAD);
	Str2Bcd(DEF_TERM_TERMONUSFLOORLIMIT			, strlen(DEF_TERM_TERMONUSFLOORLIMIT		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_termOnusFloorLimit			, CTerminal::sizeTermOnusFloorLimit			, LEFT_PAD);
	Str2Bcd(DEF_TERM_TERMMAXADVICECOUNT			, strlen(DEF_TERM_TERMMAXADVICECOUNT		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_termMaxAdviceCount			, CTerminal::sizeTermMaxAdviceCount			, LEFT_PAD);
	Str2Bcd(DEF_TERM_TERMADVICESUPLOADINTERVAL	, strlen(DEF_TERM_TERMADVICESUPLOADINTERVAL	), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_termAdvicesUploadInterval	, CTerminal::sizeTermAdvicesUploadInterval	, LEFT_PAD);
	Str2Bcd(DEF_TERM_TERMPOSTADVICECOUNT		, strlen(DEF_TERM_TERMPOSTADVICECOUNT		), LEFT_PAD_ZERO, (unsigned char*)this->m_data.m_termPostAdviceCount		, CTerminal::sizeTermPostAdviceCount		, LEFT_PAD);
}

//--------------------------------------------------------------------------------------

int CTerminal::Append()
{
	if (!this->Open()) {
		return GENERAL_FAILURE;//FILE_NOT_OPENED;
	}
	this->m_currentRecordNo = this->GotoEnd();
	this->Write((void *)&this->m_data, this->m_recordSize);

	this->Close();

	++this->m_currentRecordNo;
	++this->m_recordCount;
	return this->m_currentRecordNo;
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
