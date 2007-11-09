#ifndef _RPG_INTERFACE_H_
#define _RPG_INTERFACE_H_

//---------------------------------------------------------------------------
#include "RPGMap.h"
using namespace zak;
//---------------------------------------------------------------------------
class RPGCharacter;
//---------------------------------------------------------------------------

class RPGInterface
{
private:

	// sprite de fondo
	Sprite	*m_pBackground;

	// posicion del fondo de los items
	float	m_fItemsBackPosX, m_fItemsBackPosY;

	// posicion inicial de dibujo de los items
	float	m_fItemsPosX, m_fItemsPosY;

	// variacion de posicion por item
	float	m_fItemsOffsetX, m_fItemsOffsetY;

	// puntero al personaje principal
	RPGCharacter *m_pkCharacter;

	// puntero al enemigo
	RPGCharacter *m_pkEnemy;

	// actualiza la posicion de los items en la GUI
	void UpdateItemsPosition();

	// barra de energia del personaje principal
	Shape	m_MainCharEnergy;

	// posicion de la barra de energia del personaje principal
	float	m_fMainEnergyPosX, m_fMainEnergyPosY;

	// dimension de la barra de energia del personaje principal
	float	m_fMainEnergyWidth, m_fMainEnergyHeight;

	// barra de energia del enemigo actual
	Shape	m_EnemyEnergy;

	// posicion de la barra de energia del enemigo actual
	float	m_fEnemyEnergyPosX, m_fEnemyEnergyPosY;

	// dimension de la barra de energia del enemigo actual
	float	m_fEnemyEnergyWidth, m_fEnemyEnergyHeight;

public:

	RPGInterface();
	~RPGInterface();

	// setea el personaje principal
	void SetCharacter(RPGCharacter *pkCharacter);

	// setea el enemigo
	void SetEnemy(RPGCharacter *pkEnemy);

	// setea el sprite de fondo
	void SetBackground(char *pszFile);

	// dibuja la interface
	void Draw();

	// actualiza la interface
	void Update(float fTimeBetweenFrames);

	// setea la posicion del fondo de los items
	void SetItemsBackPos(float fPosX, float fPosY);

	// setea la posicion de los items
	void SetItemsPos(float fPosX, float fPosY);

	// setea la posicion de los items
	void SetItemsOffset(float fOffsetX, float fOffsetY);

	// setea la posicion de la barra de energia del personaje principal
	void SetCharacterBarPos(float fPosX, float fPosY);

	// setea la dimension de la barra de energia del personaje principal
	void SetCharacterBarDim(float fWidth, float fHeight);

	// setea la posicion de la barra de energia del enemigo actual
	void SetEnemyBarPos(float fPosX, float fPosY);

	// setea la dimension de la barra de energia del enemigo actual
	void SetEnemyBarDim(float fWidth, float fHeight);

};

#endif //_RPG_INTERFACE_H_