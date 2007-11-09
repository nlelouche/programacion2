#include "RPGMap.h"
#include "RPGCharacter.h"
#include "RPGItem.h"

//--------------------------------------------------------------------------------
// constructor
RPGMap::RPGMap()
:
Map(),
_fCharInitPosX(0),
_fCharInitPosY(0),
m_uiCharactersCount(0),
m_uiItemsCount(0),
m_uiColTilesCount(0)
{
	// inicializo los valores
	SetPos(0,0);

	for(unsigned int i=0;i<m_uiCharactersCount;i++)
		m_kCharacters[i] = NULL;

	for(unsigned int i=0;i<m_uiItemsCount;i++)
		m_kItems[i] = NULL;
}
//--------------------------------------------------------------------------------
// posicion inicial del personaje
void RPGMap::SetCharInitPos(float fPosX, float fPosY)
{
	_fCharInitPosX = fPosX;
	_fCharInitPosY = fPosY;
}
//--------------------------------------------------------------------------------
float RPGMap::GetCharInitPosX()
{
	return _fCharInitPosX;
}
//--------------------------------------------------------------------------------
float RPGMap::GetCharInitPosY()
{
	return _fCharInitPosY;
}
//--------------------------------------------------------------------------------
// agrega un personaje al mapa
void RPGMap::AddCharacter(RPGCharacter *pkCharacter)
{
	// inserto el nuevo personaje en la lista
	if(m_uiCharactersCount < MAX_CHARACTERS)
	{
		m_kCharacters[m_uiCharactersCount] = pkCharacter;
		m_uiCharactersCount++;
	}
}
//--------------------------------------------------------------------------------
// borra un personaje del mapa
void RPGMap::RemoveCharacter(RPGCharacter *pkCharacter)
{
	for(unsigned int i=0;i<m_uiCharactersCount;i++)
	{
		if(m_kCharacters[i] == pkCharacter)
		{
			m_uiCharactersCount--;
			m_kCharacters[i] = NULL;
			m_kCharacters[i] = m_kCharacters[m_uiCharactersCount];
		}
	}
}
//--------------------------------------------------------------------------------
// agrega un item al mapa
void RPGMap::AddItem(RPGItem *pkItem)
{
	// inserto el nuevo item en la lista
	if(m_uiItemsCount < MAX_ITEMS)
	{
		m_kItems[m_uiItemsCount] = pkItem;
		m_uiItemsCount++;
	}
}
//--------------------------------------------------------------------------------
// borra un item del mapa
void RPGMap::RemoveItem(RPGItem *pkItem)
{
	for(unsigned int i=0;i<m_uiItemsCount;i++)
	{
		if(m_kItems[i] == pkItem)
		{
			m_uiItemsCount--;
			m_kItems[i] = NULL;
			m_kItems[i] = m_kItems[m_uiItemsCount];
		}
	}
}
//--------------------------------------------------------------------------------
// dibuja el mapa y los elementos insertados
void RPGMap::Draw()
{
	DisableAlphaBlend();
	Map::Draw();
	EnableAlphaBlend();

	for(unsigned int i=0;i<m_uiCharactersCount;i++)
		m_kCharacters[i]->Draw();

	for(unsigned int i=0;i<m_uiItemsCount;i++)
		m_kItems[i]->Draw();
}
//--------------------------------------------------------------------------------
// actualiza el estado del mapa y de los elementos insertados
void RPGMap::Update(float fTimeBetweenFrames, RPGCharacter *pkPlayer)
{
	// actualizo del scroll del mapa
	UpdateScroll(pkPlayer->GetPosX(), pkPlayer->GetPosY());

	// actualizo cada uno de los personajes del mapa
	for(unsigned int i=0;i<m_uiCharactersCount;i++)
	{
		m_kCharacters[i]->Update(fTimeBetweenFrames);
		
		if(IsCharacterColliding(m_kCharacters[i]))
			m_kCharacters[i]->SetToPreviousPosition();
	}

	// actualizo cada uno de los items del mapa
	for(unsigned int i=0;i<m_uiItemsCount;i++)
		m_kItems[i]->Update(fTimeBetweenFrames);

	// chequeo la colision del personaje contra todos los items
	for(unsigned int i=0;i<m_uiItemsCount;i++)
	{
		if(pkPlayer->CheckCollision(m_kItems[i]))	// si colisiona....
		{
			pkPlayer->AddItem(m_kItems[i]);	// le agrega el item al personaje
			RemoveItem(m_kItems[i]);		// saca el item del mapa
		}
	}

	// chequeo la colision de cada personaje contra todos personajes
	for(unsigned int i=0;i<m_uiCharactersCount;i++)
	{
		m_kCharacters[i]->SetCollisionCharacter(NULL);
		for(unsigned int j=i+1;j<m_uiCharactersCount;j++)
		{
			if(m_kCharacters[i]->CheckCollision(m_kCharacters[j]))	// si colisiona....
			{
				m_kCharacters[i]->SetCollisionCharacter(m_kCharacters[j]);
				m_kCharacters[j]->SetCollisionCharacter(m_kCharacters[i]);
			}
		}
	}
}
//--------------------------------------------------------------------------------
// actualizacion del scroll del mapa en base a la posicion del personaje
void RPGMap::UpdateScroll(float fPosCharX, float fPosCharY)
{
	g_renderer.SetViewPosition(fPosCharX,fPosCharY);
	return;

	// calculo la cantidad de tiles q entran en el ancho de la pantalla
	unsigned int uiTilesX = 
		(unsigned int)(g_renderer.GetViewPortWidth() / GetTileWidth());
	
	// calculo la cantidad de tiles q entran en el alto de la pantalla
	unsigned int uiTilesY = 
		(unsigned int)(g_renderer.GetViewPortHeight() / GetTileHeight());

	// calculo las mitades de la pantalla para no dejar q la camara se mueva mas alla
	float fMapAbsPosX = (float)(g_renderer.GetViewPortWidth() / 2);
	float fMapAbsPosY = (float)(g_renderer.GetViewPortHeight() / 2);

	// en estas variables va a quedar la posicion final de la camara
	float fFinalMapPosX;
	float fFinalMapPosY;

	// chequeo que el personaje no este muy cerca de la esquina superior izquierda
	if(fPosCharX > fMapAbsPosX)
		// si no pasa, entonces la posicion de la camara es igual a la del personaje
		fFinalMapPosX = fPosCharX;
	else
	{
		// si pasa, TO-DO: no me acuerdo q mierda hace esto... =o)
		if(fPosCharX > (GetTileWidth() * GetMapWidth()) - fMapAbsPosX)
			fFinalMapPosX = (GetTileWidth() * GetMapWidth()) - fMapAbsPosX;
		else
			fFinalMapPosX = fMapAbsPosX;
	}

	if(fPosCharY < -fMapAbsPosY)
		fFinalMapPosY = fPosCharY;
	else
		fFinalMapPosY = -fMapAbsPosY;

	// seteo la posicion final de la camara
	g_renderer.SetViewPosition(fFinalMapPosX,fFinalMapPosY);
}
//------------------------------------------------------------------------------------
// agrega el indice de un tile colisionable
void RPGMap::AddColTile(int iTileID)
{
	// si el tile ya esta agregado, entonces salgo de la funcion
	if(SearchColTileID(iTileID))
		return;

	// inserto el nuevo personaje en la lista
	if(m_uiColTilesCount < MAX_COL_TILES)
	{
		m_piColTiles[m_uiColTilesCount] = iTileID;
		m_uiColTilesCount++;
	}
}
//------------------------------------------------------------------------------------
// se fija si un determinado personaje esta chocando contra alguna pared
bool RPGMap::IsCharacterColliding(RPGCharacter *pkCharacter)
{
	// calculo la posicion absoluta de cada uno de los limites del personaje
	float fLeft		= pkCharacter->GetPosX() - pkCharacter->GetWidth() / 2;
	float fRight	= pkCharacter->GetPosX() + pkCharacter->GetWidth() / 2;
	float fTop		= pkCharacter->GetPosY() - pkCharacter->GetHeight() / 2;
	float fBottom	= pkCharacter->GetPosY() + pkCharacter->GetHeight() / 2;

	// por cada uno de los tiles colisionables
	for(unsigned int i=0;i<m_uiColTilesCount;i++)
	{
		// pruebo con el tile de arriba a la izq
		int iTempTileID = GetTileFromWorldCoords(fLeft, fTop);

		if(SearchColTileID(iTempTileID)) return true;

		// pruebo con el tile de arriba a la derecha
		iTempTileID = GetTileFromWorldCoords(fLeft, fBottom);

		if(SearchColTileID(iTempTileID)) return true;

		// pruebo con el tile de abajo a la izq
		iTempTileID = GetTileFromWorldCoords(fRight, fTop);

		if(SearchColTileID(iTempTileID)) return true;

		// pruebo con el tile de abajo a la derecha
		iTempTileID = GetTileFromWorldCoords(fRight, fBottom);

		if(SearchColTileID(iTempTileID)) return true;
	}

	 return false;
}
//------------------------------------------------------------------------------------
// se fija si un ID determinado es colisionable o no
bool RPGMap::SearchColTileID(int uiTileID)
{
	for(unsigned int i=0;i<m_uiColTilesCount;i++)
	{
		// si lo encuentra...
		if(m_piColTiles[i] == uiTileID)
			return true;
	}
	// si no lo encuentra, devuelve falso
	return false;
}