// TrnxRefund.h: interface for the CTrnxRefund class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRNXREFUND_H__37F252D1_2ABD_4968_9BFA_9719819CB89B__INCLUDED_)
#define AFX_TRNXREFUND_H__37F252D1_2ABD_4968_9BFA_9719819CB89B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\globaldef.h"
#include "TrnxBase.h"

class CEngine;
class CTrnxRefund : public CTrnxBase  
{
private:
	CTrnxRefund();
public:
	CTrnxRefund(CEngine*);
	virtual ~CTrnxRefund();

	virtual void	PrintBody();
	virtual int		Do();
	virtual void	Release() { delete this;};

protected:
	virtual int		OnApproved();
	virtual int		OnVoid();
private:	
	unsigned char	m_cardNo[32];
	int				m_refundBalance;		// islem sonunda karta/tan eklenecek/cikartilacak balance degeri
	int				m_refundPoint;			// islem sonunda karta/tan eklenecek/cikartilacak puan degeri
	bool			m_bLoadBalanceToCard;	// balance eklenecekse TRUE
	bool			m_bLoadPointToCard;		// puan eklenecekse TRUE

};

#endif // !defined(AFX_TRNXREFUND_H__37F252D1_2ABD_4968_9BFA_9719819CB89B__INCLUDED_)
