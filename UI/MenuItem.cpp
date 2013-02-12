// MenuItem.cpp: implementation of the CSSMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#include "MenuItem.h"
#include "..\globaldef.h"
//--------------------------------------------------------------------------------------------------

CSSMenuItem::CSSMenuItem() :
	//m_fpAction((void*)NULL),
	//m_pNextMenu((void*)NULL),
	m_itemHeight(ITEM_HEIGHT),
	m_eventKey(DEFAULT_EVENTKEY)
{
	memset(this->m_itemText, 0x00, sizeof(this->m_itemText));
}

//--------------------------------------------------------------------------------------------------
	
CSSMenuItem::CSSMenuItem(const char* pItemText, MenuActionPtr fpAction, IMenu* pNextMenu) :
	m_fpAction(fpAction),
	m_pNextMenu(pNextMenu),
	m_itemHeight(ITEM_HEIGHT),
	m_eventKey(DEFAULT_EVENTKEY)
{
	strncpy((char*)this->m_itemText, (char*) pItemText, strlen(pItemText));
}

//--------------------------------------------------------------------------------------------------

CSSMenuItem::~CSSMenuItem()
{

}

//--------------------------------------------------------------------------------------------------

CSSMenuItem& CSSMenuItem::operator=(const CSSMenuItem& other)
{
	this->m_fpAction	= other.m_fpAction;
	this->m_pNextMenu	= other.m_pNextMenu;
	strncpy((char*)this->m_itemText, (char*)other.m_itemText, strlen((char*)other.m_itemText));
	this->m_eventKey	= other.m_eventKey;
	this->m_itemHeight	= other.m_itemHeight;

	return *this;
}

//--------------------------------------------------------------------------------------------------

void CSSMenuItem::SetItemText(const char* pItemText)
{
	//ASSERT(pItemText != NULL);

	strncpy((char*)this->m_itemText, pItemText, strlen(pItemText));
}

//--------------------------------------------------------------------------------------------------

char* CSSMenuItem::GetItemText()
{
	return (char*)this->m_itemText;
}

//--------------------------------------------------------------------------------------------------

void CSSMenuItem::SetAction(MenuActionPtr pAction)
{
	//ASSERT(pAction != NULL);

	this->m_fpAction = pAction;
}

//--------------------------------------------------------------------------------------------------

MenuActionPtr CSSMenuItem::GetAction()
{
	return this->m_fpAction;
}

//--------------------------------------------------------------------------------------------------

void CSSMenuItem::SetNextMenu(IMenu* pNextMenu)
{
	ASSERT(pNextMenu != NULL);

	this->m_pNextMenu = pNextMenu;
}

//--------------------------------------------------------------------------------------------------

IMenu* CSSMenuItem::GetNextMenu()
{
	return this->m_pNextMenu;
}

//--------------------------------------------------------------------------------------------------

void CSSMenuItem::SetValues(const char* pItemText, int eventKey, MenuActionPtr fpAction, IMenu* pNextMenu)
{
	this->SetItemText(pItemText);
	this->SetEventKey(eventKey);
	this->SetAction(fpAction);
	this->SetNextMenu(pNextMenu);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
