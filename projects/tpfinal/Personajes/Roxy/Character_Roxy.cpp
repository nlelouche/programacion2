#include "Character_Roxy.h"

#include "../../RPGAction.h"
#include "../../RPGItem.h"

#include "../../Acciones/Action_Punch.h"
#include "../../Acciones/Action_Walk.h"
#include "../../Acciones/Action_Idle.h"
//------------------------------------------------------------------------------------
Character_Roxy::Character_Roxy()
:
RPGCharacter(),
m_fCurrentIATime(0),
m_bMoveUp(false)
{
	// cargo el sprite del personaje
	LoadIni("./data/roxy/roxy.spr");

	// le seteo la velocidad de movimiento
	SetSpeed(0.1f);

	// accion "Idle" (cuando el personaje no hace nada)
	AddNewAction(new Action_Idle());

	// accion "Punch" (cuando el personaje pega)
	AddNewAction(new Action_Punch());

	// accion "Walk" (cuando el personaje camina)
	AddNewAction(new Action_Walk());

	// se setea por default la accion "Idle"
	Idle();

	// setea los atributos por default
	SetMaxEnergy(100);					// setea la energia actual
	SetEnergy(GetMaxEnergy());			// setea la energia maxima
}
//------------------------------------------------------------------------------------
Character_Roxy::~Character_Roxy()
{

}
//------------------------------------------------------------------------------------
void Character_Roxy::OnActionFinished(char *pszName)
{
	RPGCharacter::OnActionFinished(pszName);

	// pasamos a las acciones correspondientes 
	//		segun si el personaje es el principal o no
	if(m_pkPlayer == this)
	{
		// cuanto termina la accion de golpear, que se quede quieto
		if(strcmp(pszName, "Punch") == 0)
			Idle();
		
		// cuanto termina la accion de caminar, que se quede quieto
		else if(strcmp(pszName, "Walk") == 0)
			Idle();
	}
	// si este personaje no es el principal, entonces actua la inteligencia artificial
	else
	{
	
	}
}
//------------------------------------------------------------------------------------
void Character_Roxy::Draw()
{
	RPGCharacter::Draw();
}
//------------------------------------------------------------------------------------
void Character_Roxy::Update(float fTimeBetweenFrames)
{
	RPGCharacter::Update(fTimeBetweenFrames);
}
//------------------------------------------------------------------------------------
void Character_Roxy::UpdateIA(float fTimeBetweenFrames)
{
	RPGCharacter::UpdateIA(fTimeBetweenFrames);

	m_fCurrentIATime += fTimeBetweenFrames;
	
	if(strcmp(m_pCurrentAction->pszName, "Walk") == 0)
	{
		if(m_fCurrentIATime >= 2000)
		{
			m_fCurrentIATime = 0.0f;
			
			if(m_bMoveUp)
				Move(90.0f);
			else
				Move(270.0f);

			m_bMoveUp = !m_bMoveUp;
		}
	}
	// si el personaje esta quieto, hacer que camine
	else if(strcmp(m_pCurrentAction->pszName, "Idle") == 0)
	{
		Move(270.0f);
		m_bMoveUp = true;
	}
}
//------------------------------------------------------------------------------------

// llamado a las acciones

void Character_Roxy::Idle()
{
	SetMoving(false);
	SetCurrentAction("Idle");
}
void Character_Roxy::Hit()
{
	SetMoving(false);
	SetCurrentAction("Punch");
}
void Character_Roxy::Move(float fDirection)
{
	if(fDirection == 0.0f)
		SetAngleZ(0.0f);
	else if(fDirection == 90.0f)
		SetAngleZ(270.0f);
	else if(fDirection == 180.0f)
		SetAngleZ(180.0f);
	else if(fDirection == 270.0f)
		SetAngleZ(90.0f);

	SetMovDirection(fDirection);
	SetMoving(true);
	SetCurrentAction("Walk");
}