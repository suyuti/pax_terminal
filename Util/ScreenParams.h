// ScreenParams.h: interface for the CTlv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENPARAMS_H__FAD102EF_8651_42B4_9A3D_129BAF618A2A__INCLUDED_)
#define AFX_SCREENPARAMS_H__FAD102EF_8651_42B4_9A3D_129BAF618A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTlv  
{
public:
	CTlv();
	virtual ~CTlv();

	CTlv* AddTlv(CTlv*);
	int ToString(unsigned char** ppBuff, int* pSize); // aslinda string olusturmaz, bir bellek bloguna yazar.

private:
	unsigned char	m_tag;
	int				m_len;
	unsigned char*	m_pData;

};

#endif // !defined(AFX_SCREENPARAMS_H__FAD102EF_8651_42B4_9A3D_129BAF618A2A__INCLUDED_)
