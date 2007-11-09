#ifndef _ACTION_IDLE_H_
#define _ACTION_IDLE_H_

#include "../../RPGAction.h"

class Action_Idle : public RPGAction
{

protected:

public:

	Action_Idle() : RPGAction()
	{
		// seteo los valores de la accion
		pAnimation = new Animation();
		pAnimation->Load("./data/roxy/idle.ani");	// cargo la animacion
		strcpy(pszName, "Idle");
		fTimeToExecute = 1.0f;
		fTimeToFinish = 0.0f;
	}
	
	~Action_Idle()
	{
		delete pAnimation;
	}

	// sobrecargas de los metodos de RPGAction
	void Execute(RPGCharacter *pCharacter)
	{
		RPGAction::Execute(pCharacter);
	}
};

#endif //_ACTION_IDLE_H_