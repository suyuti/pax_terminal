// Paramters.cpp: implementation of the CParamters class.
//
//////////////////////////////////////////////////////////////////////

#include "Paramters.h"

//-----------------------------------------------------------------------------------------------------

CParamters::CParamters() :
	CTable((void*)&m_data)
{
	this->m_recordSize = sizeof(CParamters::ParameterRecord);
	sprintf(this->m_fileName, "%s", TABLE_NAME_DEF_PARAMS);
}

//-----------------------------------------------------------------------------------------------------

CParamters::~CParamters()
{

}

//-----------------------------------------------------------------------------------------------------

void CParamters::CreateDefaults()
{
	
	memset(&this->m_data, 0x00, sizeof(ParameterRecord));

	memcpy(this->m_data.m_terminalID		, DEF_TERMINALID		, strlen(DEF_TERMINALID			));
	memcpy(this->m_data.m_merchantID		, DEF_MERCHANTID		, strlen(DEF_MERCHANTID			));
	memcpy(this->m_data.m_serialNo			, DEF_SERIALNO			, strlen(DEF_SERIALNO			));
	memcpy(this->m_data.m_NII				, DEF_NII				, strlen(DEF_NII				));
	memcpy(this->m_data.m_priMedia			, DEF_PRIMEDIA			, strlen(DEF_PRIMEDIA			));
	memcpy(this->m_data.m_secMedia			, DEF_SECMEDIA			, strlen(DEF_SECMEDIA			));
	memcpy(this->m_data.m_subnet			, DEF_SUBNET			, strlen(DEF_SUBNET				));
	memcpy(this->m_data.m_gateway			, DEF_GATEWAY			, strlen(DEF_GATEWAY			));
	memcpy(this->m_data.m_apn				, DEF_APN				, strlen(DEF_APN				));
	memcpy(this->m_data.m_SimPIN			, DEF_SIMPIN			, strlen(DEF_SIMPIN				));
	memcpy(this->m_data.m_TmsIP_1			, DEF_TMSIP_1			, strlen(DEF_TMSIP_1			));
	memcpy(this->m_data.m_TmsPort_1			, DEF_TMSPORT_1			, strlen(DEF_TMSPORT_1			));
	memcpy(this->m_data.m_TmsIP_2			, DEF_TMSIP_2			, strlen(DEF_TMSIP_2			));
	memcpy(this->m_data.m_TmsPort_2			, DEF_TMSPORT_2			, strlen(DEF_TMSPORT_2			));
	memcpy(this->m_data.m_provizyonIP_1		, DEF_PROVIZYONIP_1		, strlen(DEF_PROVIZYONIP_1		));
	memcpy(this->m_data.m_provizyonPort_1	, DEF_PROVIZYONPORT_1	, strlen(DEF_PROVIZYONPORT_1	));
	memcpy(this->m_data.m_provizyonIP_2		, DEF_PROVIZYONIP_2		, strlen(DEF_PROVIZYONIP_2		));
	memcpy(this->m_data.m_provizyonPort_2	, DEF_PROVIZYONPORT_2	, strlen(DEF_PROVIZYONPORT_2	));
	memcpy(this->m_data.m_settleIP_1		, DEF_SETTLEIP_1		, strlen(DEF_SETTLEIP_1			));
	memcpy(this->m_data.m_settlePort_1		, DEF_SETTLEPORT_1		, strlen(DEF_SETTLEPORT_1		));
	memcpy(this->m_data.m_settleIP_2		, DEF_SETTLEIP_2		, strlen(DEF_SETTLEIP_2			));
	memcpy(this->m_data.m_settlePort_2		, DEF_SETTLEPORT_2		, strlen(DEF_SETTLEPORT_2		));
	memcpy(this->m_data.m_tmsPhoneNo_1		, DEF_TMSPHONENO_1		, strlen(DEF_TMSPHONENO_1		));
	memcpy(this->m_data.m_tmsPhoneNo_2		, DEF_TMSPHONENO_2		, strlen(DEF_TMSPHONENO_2		));
	memcpy(this->m_data.m_provizyonPhoneNo_1, DEF_PROVIZYONPHONENO_1, strlen(DEF_PROVIZYONPHONENO_1	));
	memcpy(this->m_data.m_provizyonPhoneNo_2, DEF_PROVIZYONPHONENO_2, strlen(DEF_PROVIZYONPHONENO_2	));
	memcpy(this->m_data.m_settlePhoneNo_1	, DEF_SETTLEPHONENO_1	, strlen(DEF_SETTLEPHONENO_1	));
	memcpy(this->m_data.m_settlePhoneNo_2	, DEF_SETTLEPHONENO_2	, strlen(DEF_SETTLEPHONENO_2	));
	memcpy(this->m_data.m_santalOnCevirme	, DEF_SANTALONCEVIRME	, strlen(DEF_SANTALONCEVIRME	));
	memcpy(this->m_data.m_model				, DEF_MODEL				, strlen(DEF_MODEL				));
	memcpy(this->m_data.m_posVersion		, DEF_POSVERSION		, strlen(DEF_POSVERSION			));
	
	sprintf(this->m_data.m_batch, "%*0d", sizeBatch, 1);
}

//-----------------------------------------------------------------------------------------------------

int CParamters::Append()
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

//-----------------------------------------------------------------------------------------------------

void CParamters::PrintAll() 
{
	PrnInit();

	for (int i = 0; i < this->m_recordCount; ++i) {
		this->GotoRec(i + 1, true);

		PrnStr("TermID: %s\n", this->m_data.m_terminalID);
		PrnStr("M.ID  : %s\n", this->m_data.m_merchantID);
		PrnStr("Model : %s\n", this->m_data.m_model);
	}
	PrnStart();
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
