#ifndef _ITEM_ENERGY_H_
#define _ITEM_ENERGY_H_

//---------------------------------------------------------------------------
#include "../../RPGItem.h"
//---------------------------------------------------------------------------

class Item_Energy : public RPGItem
{
private:

public:

	Item_Energy()
	{
		// cargo el sprite del personaje
		LoadIni("./data/items/energy.spr");
		SetGUISprite("./data/items/energy.spr", 3.0f);
	}

	void Use(RPGCharacter *pCharacter)
	{
		int a = 0;
	}
};


#endif //_ITEM_ENERGY_H_