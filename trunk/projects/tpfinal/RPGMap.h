#ifndef _RPG_MAP_H_
#define _RPG_MAP_H_

//---------------------------------------------------------------------------
#include "zakengine/zak.h"
using namespace zak;
//---------------------------------------------------------------------------
#define MAX_CHARACTERS	10	//TO-DO: Pasar al config
#define MAX_ITEMS		10	//TO-DO: Pasar al config
#define MAX_COL_TILES	50	//TO-DO: Pasar al config
//---------------------------------------------------------------------------
class RPGCharacter;
class RPGItem;
//---------------------------------------------------------------------------

class RPGMap : public Map
{
private:

	float	_fCharInitPosX;
	float	_fCharInitPosY;

	// personajes dentro del mapa
	RPGCharacter	*m_kCharacters[MAX_CHARACTERS];	// array de personajes
	unsigned int	m_uiCharactersCount;			// cantidad actual de personajes

	// items dentro del mapa
	RPGItem			*m_kItems[MAX_ITEMS];			// array de items
	unsigned int	m_uiItemsCount;					// cantidad actual de items

	// tipos de tiles que son colisionables
	int				m_piColTiles[MAX_COL_TILES];	// array de indices a los tiles colisionables
	unsigned int	m_uiColTilesCount;				// cantidad actual de tiles colisionables

	// se fija si un ID determinado es colisionable o no
	bool SearchColTileID(int uiTileID);

public:

	// constructor
	RPGMap();

	// posicion inicial del personaje
	void SetCharInitPos(float fPosX, float fPosY);
	float GetCharInitPosX();
	float GetCharInitPosY();

	// agrega un personaje al mapa
	void AddCharacter(RPGCharacter *pkCharacter);

	// borra un personaje del mapa
	void RemoveCharacter(RPGCharacter *pkCharacter);

	// agrega un item al mapa
	void AddItem(RPGItem *pkItem);

	// borra un item del mapa
	void RemoveItem(RPGItem *pkItem);	

	// dibuja el mapa y los elementos insertados
	virtual void Draw();

	// actualiza el estado del mapa y de los elementos insertados
	void Update(float fTimeBetweenFrames, RPGCharacter *pkPlayer);

	// actualizacion del scroll del mapa en base a la posicion del personaje
	void UpdateScroll(float fPosCharX, float fPosCharY);

	// agrega el indice de un tile colisionable
	void AddColTile(int iTileID);

	// se fija si un determinado personaje esta chocando contra alguna pared
	bool IsCharacterColliding(RPGCharacter *pkCharacter);
};

#endif //_RPG_MAP_H_