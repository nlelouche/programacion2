#ifndef _RPG_ITEM_H_
#define _RPG_ITEM_H_

//---------------------------------------------------------------------------
#include "zakengine/zak.h"
using namespace zak;
//---------------------------------------------------------------------------
class RPGCharacter;
//---------------------------------------------------------------------------

class RPGItem : public Sprite
{
private:

	Sprite	*m_pGUISprite;

public:

	RPGItem();
	virtual ~RPGItem();

	// uses the item
	virtual void Use(RPGCharacter *pCharacter) = 0;

	// devuelve el sprite de la GUI
	Sprite *GetGUISprite();
	// setea el sprite de la GUI
	void SetGUISprite(char *pszFile, float fScale=1.0f);
};


#endif //_RPG_ITEM_H_