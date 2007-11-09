#ifndef _ACTION_WALK_H_
#define _ACTION_WALK_H_

#include "../../RPGAction.h"

class Action_Walk : public RPGAction
{

protected:

public:

	Action_Walk() : RPGAction()
	{
		// seteo los valores de la accion
		pAnimation = new Animation();
		pAnimation->Load("./data/roxy/walk.ani");	// cargo la animacion
		strcpy(pszName, "Walk");
		fTimeToExecute = 1.0f;
		fTimeToFinish = 100.0f;
	}
	
	~Action_Walk()
	{
		delete pAnimation;
	}

	// sobrecargas de los metodos de RPGAction
	void Execute(RPGCharacter *pCharacter)
	{
		RPGAction::Execute(pCharacter);
	}
};

#endif //_ACTION_WALK_H_