#ifndef _IMENU_H_
#define _IMENU_H_

class CSSMenuItem;
class IMenu 
{
public:
	virtual int		AddItem(CSSMenuItem* item)	= 0;
	virtual void	SetParent(IMenu*)			= 0;
	virtual IMenu*	Draw()						= 0;
};

#endif //_IMENU_H_
