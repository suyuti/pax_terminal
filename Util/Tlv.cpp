// Tlv.cpp: implementation of the CTlv class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreenParams.h"
#include "..\Util\NumFuncs.h"

//---------------------------------------------------------------------------

CTlv::CTlv()
{

}

//---------------------------------------------------------------------------

CTlv::~CTlv()
{

}

//---------------------------------------------------------------------------

CTlv* CTlv::AddTlv(CTlv*)
{
	return this;
}

//---------------------------------------------------------------------------

int CTlv::ToString(unsigned char** ppBuff, int* pSize)
{
	*ppBuff = new unsigned char[this->m_len + 3];
	memset(*ppBuff, 0x00, this->m_len + 3);
	(*ppBuff)[0] = this->m_tag;

	Lng2Bcd(this->m_len, (*ppBuff) + 1, 2);
	memcpy((*ppBuff) + 3, this->m_pData, this->m_len);

	return 0;
}

//---------------------------------------------------------------------------
