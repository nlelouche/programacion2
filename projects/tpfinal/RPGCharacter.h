#ifndef _RPG_CHARACTER_H_
#define _RPG_CHARACTER_H_

//---------------------------------------------------------------------------
#include "RPGMap.h"
using namespace zak;
//---------------------------------------------------------------------------
#define MAX_ACTIONS	10	//TO-DO: Pasar al config
#define MAX_ITEMS	10	//TO-DO: Pasar al config
//---------------------------------------------------------------------------
class RPGAction;
class RPGItem;
//---------------------------------------------------------------------------

class RPGCharacter : public Sprite
{

protected:

	// propiedades generales
	static RPGCharacter*	m_pkPlayer;			// puntero al personaje del jugador
	RPGCharacter*			m_pkColliding;		// puntero al personaje con el cual se esta colisionando
	
	// acciones
	RPGAction*		m_kActions[MAX_ACTIONS];	// array de acciones
	RPGAction*		m_pCurrentAction;			// puntero a la accion actual
	unsigned int	m_uiActionsCount;			// cantidad actual de acciones
	float			m_fCurrentActionTime;		// tiempo actual de la accion
	RPGAction*		m_pLastAction;				// puntero a la accion del frame anterior
	bool			m_WasActionExecuted;		// indica si la accion ya fue ejecutada

	// items
	RPGItem*		m_kItems[MAX_ITEMS];		// array de items
	unsigned int	m_uiItemsCount;				// cantidad actual de items

	// atributos
	float			m_fEnergy;					// cantidad actual de energia
	float			m_fMaxEnergy;				// cantidad maxima de energia

public:

	RPGCharacter();
	virtual ~RPGCharacter();

	// le agrega una nueva accion al personaje
	void AddNewAction(
			char *pszName, Animation *pAnimation, 
			float fTimeToExecute, float fTimeToFinish
	);

	void AddNewAction(RPGAction* pkAction);

	// setea el personaje del jugador para ser accedido por todas las instancias de RPGCharacter
	static void SetPlayerCharacter(RPGCharacter* pkPlayer);
	static RPGCharacter* GetPlayerCharacter();

	// setea el personaje con el cual esta colisionando
	void SetCollisionCharacter(RPGCharacter* pkColliding);
	RPGCharacter* GetCollisionCharacter();

	// setea la accion actual del personaje
	bool SetCurrentAction(char *pszActionName);

	// metodo llamado cuando se termina una accion
	virtual void OnActionFinished(char *pszName);

	// agrega un item al inventario
	void AddItem(RPGItem *pkItemToInsert);

	// devuelve el valor de un item
	RPGItem *GetItem(unsigned int uiIndex);

	// sobrecargas de los metodos de Entity2D
	virtual void Draw();
	virtual void Update(float fTimeBetweenFrames);

	// actualiza la IA del personaje
	virtual void UpdateIA(float fTimeBetweenFrames);

	// acciones genericas
	virtual void Idle();
	virtual void Hit();
	virtual void Move(float fDirection);
	void UseItem(unsigned int uiIndex);

	// chequea colision contra un Entity2D (solamente cajas...)
	bool CheckCollision(Sprite *pkSprite);

	//-----------------------------------------------------------
	// acceso a atributos

	float GetEnergy();						// devuelve la cantidad actual de energia
	void SetEnergy(float fEnergy);			// setea la cantidad actual de energia

	float GetMaxEnergy();					// devuelve la cantidad maxima de energia
	void SetMaxEnergy(float fMaxEnergy);	// setea la cantidad maxima de energia
};

#endif //_RPG_CHARACTER_H_