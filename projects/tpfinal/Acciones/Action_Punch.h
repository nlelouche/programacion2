#ifndef _ACTION_PUNCH_H_
#define _ACTION_PUNCH_H_

#include "../../RPGAction.h"

class Action_Punch : public RPGAction
{

protected:

public:

	Action_Punch() : RPGAction()
	{
		// seteo los valores de la accion
		pAnimation = new Animation();
		pAnimation->Load("./data/roxy/punch.ani");	// cargo la animacion
		strcpy(pszName, "Punch");
		fTimeToExecute = 150.0f;
		fTimeToFinish = 300.0f;
	}
	
	~Action_Punch()
	{
		delete pAnimation;
	}

	// sobrecargas de los metodos de RPGAction
	void Execute(RPGCharacter *pCharacter)
	{
		RPGAction::Execute(pCharacter);

		RPGCharacter *pkChar = pCharacter->GetCollisionCharacter();
		// ejecuta la accion solo si esta colisionando con algun personaje
		if(pkChar)
			pkChar->SetEnergy(pkChar->GetEnergy() - 10);
	}
};

#endif //_ACTION_PUNCH_H_