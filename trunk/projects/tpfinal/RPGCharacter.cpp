#include "RPGCharacter.h"
#include "RPGAction.h"
#include "RPGItem.h"

//----------------------------------------------------------------------
RPGCharacter* RPGCharacter::m_pkPlayer = NULL;
//----------------------------------------------------------------------
RPGCharacter::RPGCharacter()
:	// inicializo todos los valores
Sprite(),
m_pCurrentAction(NULL),
m_fCurrentActionTime(0.0f),
m_pLastAction(NULL),
m_uiActionsCount(0),
m_uiItemsCount(0),
m_pkColliding(NULL)
{
	for(unsigned int i=0;i<MAX_ITEMS;i++)
		m_kItems[i] = NULL;

	for(unsigned int i=0; i<MAX_ACTIONS;i++)
		m_kActions[i] = NULL;
}
//----------------------------------------------------------------------
RPGCharacter::~RPGCharacter()
{
	// borro todas las acciones
	for(unsigned int i=0; i<m_uiActionsCount;i++)
	{
		delete m_kActions[i];
		m_kActions[i] = NULL;
	}

	// borro todos los items
	for(unsigned int i=0; i<m_uiItemsCount;i++)
	{
		delete m_kItems[i];
		m_kItems[i] = NULL;
	}
}
//----------------------------------------------------------------------
// le agrega una nueva accion al personaje
void RPGCharacter::AddNewAction(
								char *pszName, Animation *pAnimation, 
								float fTimeToExecute, float fTimeToFinish
)
{
	// creo la nueva accion
	RPGAction *pActionToInsert = new RPGAction();
	
	// chequeo que el nombre sea mas corto que el maximo permitido
	if(strlen(pszName) < MAX_ACTION_NAME - 1)
		strcpy(pActionToInsert->pszName, pszName);			// copio el nombre
	else
		strcpy(pActionToInsert->pszName, "LONG NAME");	// copio un texto de error

	// le seteo los parametros a la nueva accion
	pActionToInsert->pAnimation = pAnimation;
	pActionToInsert->fTimeToExecute = fTimeToExecute;
	pActionToInsert->fTimeToFinish = fTimeToFinish;

	// inserto la nueva accion en la lista
	if(m_uiActionsCount < MAX_ACTIONS)
	{
		m_kActions[m_uiActionsCount] = pActionToInsert;
		m_uiActionsCount++;
	}
}
//----------------------------------------------------------------------
void RPGCharacter::AddNewAction(RPGAction* pkAction)
{
	// inserto la nueva accion en la lista
	if(m_uiActionsCount < MAX_ACTIONS)
	{
		m_kActions[m_uiActionsCount] = pkAction;
		m_uiActionsCount++;
	}
}
//----------------------------------------------------------------------
// setea el personaje del jugador para ser accedido por todas las instancias de RPGCharacter
void RPGCharacter::SetPlayerCharacter(RPGCharacter* pkPlayer)
{
	m_pkPlayer = pkPlayer;
}
//----------------------------------------------------------------------
RPGCharacter* RPGCharacter::GetPlayerCharacter()
{
	return m_pkPlayer;
}
//----------------------------------------------------------------------
// setea el personaje con el cual esta colisionando
void RPGCharacter::SetCollisionCharacter(RPGCharacter* pkColliding)
{
	m_pkColliding = pkColliding;
}
//----------------------------------------------------------------------
RPGCharacter* RPGCharacter::GetCollisionCharacter()
{
	return m_pkColliding;
}
//----------------------------------------------------------------------
// agrega un item al inventario
void RPGCharacter::AddItem(RPGItem *pkItemToInsert)
{
	// me fijo si tengo lugar en la lista
	if(m_uiItemsCount < MAX_ITEMS)
	{
		// inserto el nuevo item en la lista
		m_kItems[m_uiItemsCount] = pkItemToInsert;
		m_uiItemsCount++;
	}
}
//----------------------------------------------------------------------
// devuelve el valor de un item
RPGItem *RPGCharacter::GetItem(unsigned int uiIndex)
{
	// si el indice en invalido, retorno NULL
	if(uiIndex >= MAX_ITEMS)
		return NULL;
	else
		return m_kItems[uiIndex];

}
//----------------------------------------------------------------------
bool RPGCharacter::SetCurrentAction(char *pszActionName)
{
	// busco una accion con el nombre pasado como parametro

	for(unsigned int i=0; i<m_uiActionsCount;i++)
	{
		if(strcmp(m_kActions[i]->pszName, pszActionName) == 0)
		{
			// si la encuentro...
			
			// si la accion encontrada es la actual, entonces no la 
			//	seteo porque ya esta seteada
			if(m_kActions[i] == m_pCurrentAction)
				return false;

			// seteo la nueva accion
			m_pCurrentAction = m_kActions[i];
			m_pLastAction = m_pCurrentAction;

			// reseteo los contadores
			m_fCurrentActionTime = 0.0f;
			m_WasActionExecuted = false;

			// seteo la animacion actual
 			SetAnimation(m_pCurrentAction->pAnimation);

			// devuelvo verdadero
			return true;
		}
	}
	// si no la encuentro devuelvo false
	return false;
}
//----------------------------------------------------------------------
void RPGCharacter::OnActionFinished(char *pszName)
{
}
//----------------------------------------------------------------------
void RPGCharacter::Draw()
{
	Sprite::Draw();
}
//----------------------------------------------------------------------
void RPGCharacter::Update(float fTimeBetweenFrames)
{
	Sprite::Update(fTimeBetweenFrames);

	// si el personaje tiene una accion actual
	m_fCurrentActionTime += fTimeBetweenFrames;

	// si el tiempo actual es mayor q el tiempo para ejecutar la accion, la ejecuto
	if(m_fCurrentActionTime >= m_pCurrentAction->fTimeToExecute && !m_WasActionExecuted)
	{
		m_pCurrentAction->Execute(this);
		m_WasActionExecuted = true;
	}

	// si el tiempo actual es mayor q el tiempo a q dura la accion, la termino
	if(m_pCurrentAction->fTimeToFinish != 0 && m_fCurrentActionTime >= m_pCurrentAction->fTimeToFinish)
		OnActionFinished(m_pCurrentAction->pszName);

	// si este personaje no es el principal, entonces actua la inteligencia artificial
	if(m_pkPlayer != this)
		UpdateIA(fTimeBetweenFrames);
}
//----------------------------------------------------------------------
// actualiza la IA de ese personaje
void RPGCharacter::UpdateIA(float fTimeBetweenFrames)
{
	
}
//----------------------------------------------------------------------
// acciones genericas
void RPGCharacter::Idle() {}
void RPGCharacter::Hit() {}
void RPGCharacter::Move(float fDirection) {}

void RPGCharacter::UseItem(unsigned int uiIndex)
{
	if(uiIndex >= MAX_ITEMS) 
		return;

	if(m_kItems[uiIndex])
	{
		m_kItems[uiIndex]->Use(this);
		m_kItems[uiIndex] = NULL;
		m_uiItemsCount--;
	}
}
//----------------------------------------------------------------------
// chequea colision contra un Entity2D (solamente cajas...)
bool RPGCharacter::CheckCollision(Sprite *pkSprite)
{
	// calculo las posiciones de las cajas
	float fColPosX01, fColPosY01;
	float fColPosX02, fColPosY02;

	GetCollisionPos(fColPosX01, fColPosY01);
	pkSprite->GetCollisionPos(fColPosX02, fColPosY02);

	// calculo las extensiones de las cajas
	float fExtX01 = (GetWidth() * GetScaleX()) * 0.5f;
	float fExtY01 = (GetHeight() * GetScaleY()) * 0.5f;
	float fExtX02 = (pkSprite->GetWidth() * pkSprite->GetScaleX()) * 0.5f;
	float fExtY02 = (pkSprite->GetHeight() * pkSprite->GetScaleY()) * 0.5f;

	// calculo la colision
	float fTempX = (pkSprite->GetPosX() + fColPosX02) - (GetPosX() + fColPosX01);
	float fTempY = (pkSprite->GetPosY() + fColPosY02) - (GetPosY() + fColPosY01);

	return (fabs(fTempX) <= (fExtX01 + fExtX02)) && 
			(fabs(fTempY) <= (fExtY01 + fExtY02));
}
//----------------------------------------------------------------------
// acceso a atributos

// devuelve la cantidad actual de energia
float RPGCharacter::GetEnergy()
{
	return m_fEnergy;
}

// setea la cantidad actual de energia
void RPGCharacter::SetEnergy(float fEnergy)
{
	m_fEnergy = fEnergy;
}

// devuelve la cantidad maxima de energia
float RPGCharacter::GetMaxEnergy()
{
	return m_fMaxEnergy;
}

// setea la cantidad maxima de energia
void RPGCharacter::SetMaxEnergy(float fMaxEnergy)
{
	m_fMaxEnergy = fMaxEnergy;
}