// ITrnxBase.h: interface for the ITrnxBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITRNXBASE_H__859876F8_5769_4B7E_96DB_5A8D590475A7__INCLUDED_)
#define AFX_ITRNXBASE_H__859876F8_5769_4B7E_96DB_5A8D590475A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ITrnxBase  
{
public:
	virtual void	Release()		= 0;
	virtual int		Do()			= 0;
	virtual void	Print()			= 0;
	virtual int		DoVoid(int rec)	= 0;
	virtual int		OnVoid()		= 0;	// iptal isleminde hosttan onay geldikten sonra trnx'e gore yapilacak islem.
};

#endif // !defined(AFX_ITRNXBASE_H__859876F8_5769_4B7E_96DB_5A8D590475A7__INCLUDED_)
