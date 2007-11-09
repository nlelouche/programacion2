#ifndef _RPG_ACTION_H_
#define _RPG_ACTION_H_

//---------------------------------------------------------------------------
#include "RPGMap.h"
using namespace zak;
//---------------------------------------------------------------------------
#define MAX_ACTION_NAME	256
//---------------------------------------------------------------------------

class RPGAction
{
public:

	char			pszName[MAX_ACTION_NAME];
	Animation		*pAnimation;
	float			fTimeToExecute;
	float			fTimeToFinish;

	// constructor
	RPGAction();

	// ejecuta la accion
	virtual void Execute(RPGCharacter *pCharacter);
};

#endif //_RPG_ACTION_H_