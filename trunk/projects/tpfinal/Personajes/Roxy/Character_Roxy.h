#ifndef _CHARACTER_ROXY_H_
#define _CHARACTER_ROXY_H_

#include "../../RPGCharacter.h"

class Character_Roxy : public RPGCharacter
{

protected:

	// propiedades de la IA
	float	m_fCurrentIATime;	// tiempo actual para controlar la IA
	bool	m_bMoveUp;			// dice si el personaje se tiene q mover hacia arriba o hacia abajo

public:

	Character_Roxy();
	~Character_Roxy();

	// sobrecargas de los metodos de RPGCharacter
	virtual void OnActionFinished(char *pszName);
	virtual void Draw();
	virtual void Update(float fTimeBetweenFrames);
	virtual void UpdateIA(float fTimeBetweenFrames);

	// llamado a las acciones
	virtual void Idle();
	virtual void Hit();
	virtual void Move(float fDirection);
};

#endif //_CHARACTER_ROXY_H_