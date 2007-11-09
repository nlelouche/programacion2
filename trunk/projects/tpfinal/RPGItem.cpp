#include "RPGItem.h"

//---------------------------------------------------------------------------
RPGItem::RPGItem()
:
m_pGUISprite(NULL)
{

}
//---------------------------------------------------------------------------
RPGItem::~RPGItem()
{
	delete m_pGUISprite;
}
//---------------------------------------------------------------------------
void RPGItem::Use(RPGCharacter *pCharacter)
{

}
//---------------------------------------------------------------------------
// devuelve el sprite de la GUI
Sprite *RPGItem::GetGUISprite()
{
	return m_pGUISprite;
}
//---------------------------------------------------------------------------
// setea el sprite de la GUI
void RPGItem::SetGUISprite(char *pszFile, float fScale)
{
	delete m_pGUISprite;
	m_pGUISprite = new Sprite();
	m_pGUISprite->LoadIni(pszFile);
	m_pGUISprite->SetScale(fScale);
}
//---------------------------------------------------------------------------