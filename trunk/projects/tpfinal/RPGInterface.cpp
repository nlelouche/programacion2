#include "RPGInterface.h"
#include "RPGCharacter.h"
#include "RPGItem.h"

RPGInterface::RPGInterface()
:
m_pBackground(NULL),
m_pkCharacter(NULL),
m_pkEnemy(NULL)
{
	(m_fItemsBackPosX, m_fItemsBackPosY, m_fItemsPosX, 
		m_fItemsPosY, m_fItemsOffsetX, m_fItemsOffsetY) = 0;

	(m_fMainEnergyWidth, m_fMainEnergyHeight,
		m_fEnemyEnergyWidth, m_fEnemyEnergyHeight) = 0;

	m_MainCharEnergy.SetShape(ZAK_SHAPE_QUAD);
	m_MainCharEnergy.SetPos(395.0f, -243.0f);
	m_MainCharEnergy.SetDim(m_fMainEnergyWidth, m_fMainEnergyHeight);	//TO-DO: no harcodear
	m_MainCharEnergy.SetColor(0xFFFF0000);

	m_EnemyEnergy.SetShape(ZAK_SHAPE_QUAD);
	m_EnemyEnergy.SetPos(253.0f, -270.0f);
	m_EnemyEnergy.SetDim(285.0f, 15.0f);	//TO-DO: no harcodear
	m_EnemyEnergy.SetColor(0xFFFF0000);
}
//------------------------------------------------------------------------------------
RPGInterface::~RPGInterface()
{
	delete m_pBackground;
	m_pBackground = NULL;
}
//------------------------------------------------------------------------------------
// actualiza la posicion de los items en la GUI
void RPGInterface::UpdateItemsPosition()
{
	if(!m_pkCharacter)	// esta seteado el puntero al personaje?
		return;			// si no... me voy de la funcion

	for(unsigned int i=0;i<MAX_ITEMS;i++)
	{
		if(m_pkCharacter->GetItem(i))	// el personaje tiene un item en la posicion i?
		{
			Sprite * pkTempSprite = m_pkCharacter->GetItem(i)->GetGUISprite();
			
			pkTempSprite->SetPos(
				m_fItemsPosX + m_fItemsOffsetX * (i + 1),
				m_fItemsPosY + m_fItemsOffsetY // * (i + 1)
			);
		}
	}
}
//------------------------------------------------------------------------------------
// setea el personaje principal
void RPGInterface::SetCharacter(RPGCharacter *pkCharacter)
{
	m_pkCharacter = pkCharacter;
	UpdateItemsPosition();
}
//------------------------------------------------------------------------------------
// setea el enemigo
void RPGInterface::SetEnemy(RPGCharacter *pkEnemy)
{
	m_pkEnemy = pkEnemy;
}
//------------------------------------------------------------------------------------
// setea el sprite de fondo
void RPGInterface::SetBackground(char *pszFile)
{
	delete m_pBackground;
	m_pBackground = new Sprite();
	m_pBackground->LoadIni(pszFile);
}
//------------------------------------------------------------------------------------
// dibuja la interface
void RPGInterface::Draw()
{
	// vuelvo la posicion de pantalla a (0,0) para que no me tome el scroll
	g_renderer.PushMatrix();
	g_renderer.SetViewPosition(0.0f, 0.0f);

	// dibujo el fondo
	m_pBackground->Draw();

	if(m_pkCharacter)
	{
		// dibujo todos los items del personaje
		for(unsigned int i=0;i<MAX_ITEMS;i++)
		{
			if(m_pkCharacter->GetItem(i))	// el personaje tiene un item en la posicion i?
				m_pkCharacter->GetItem(i)->GetGUISprite()->Draw();	// entonces lo dibujo
		}
	}

	if(m_pkCharacter)
		m_MainCharEnergy.Draw();
	
	if(m_pkEnemy)
		m_EnemyEnergy.Draw();

	// vuelvo la posicion de pantalla a "modo scroll"
	g_renderer.PopMatrix();
}
//------------------------------------------------------------------------------------
// actualiza la interface
void RPGInterface::Update(float fTimeBetweenFrames)
{
	m_pBackground->Update(fTimeBetweenFrames);

	UpdateItemsPosition();	// TO-DO: esto se tiene q ir de aca...

	// esta seteado el puntero al personaje?
	if(m_pkCharacter)
	{
		for(int i=0;i<MAX_ITEMS;i++)
		{
			if(m_pkCharacter->GetItem(i))	// el personaje tiene un item en la posicion i?
				m_pkCharacter->GetItem(i)->GetGUISprite()->Update(fTimeBetweenFrames);	// entonces lo actualizo
		}

		// actualiza el uso de los items
		for(unsigned int i=0;i<MAX_ITEMS;i++)
		{
			if(KeyDown(DIK_0))
				m_pkCharacter->UseItem(10);	// TO-DO: harcoded...
			else if(KeyDown(DIK_1 + i))
				m_pkCharacter->UseItem(i);
		}

		// actualiza las barras de energia

		// barra del personaje
	
		// dimension
		m_MainCharEnergy.SetDim(				// TO-DO: magic numbers...
			m_pkCharacter->GetEnergy() * 285.0f / m_pkCharacter->GetMaxEnergy(), 
			15.0f
		);

		// posicion
		m_MainCharEnergy.SetPosX(				// TO-DO: magic numbers...
			397.0f - (285.0f - m_MainCharEnergy.GetWidth() / 2)
		);

		// actualizo el puntero al enemigo con el personaje al cual esta 
		m_pkEnemy = m_pkCharacter->GetCollisionCharacter();
	}

	// barra del personaje
	if(m_pkEnemy)
	{
		// dimension
		m_EnemyEnergy.SetDim(				// TO-DO: magic numbers...
			m_pkEnemy->GetEnergy() * 285.0f / m_pkEnemy->GetMaxEnergy(), 
			15.0f
		);

		// posicion
		m_EnemyEnergy.SetPosX(				// TO-DO: magic numbers...
			397.0f - (285.0f - m_EnemyEnergy.GetWidth() / 2)
		);
	}
}
//------------------------------------------------------------------------------------
// setea la posicion del fondo de los items
void RPGInterface::SetItemsBackPos(float fPosX, float fPosY)
{
	m_fItemsBackPosX = fPosX;
	m_fItemsBackPosY = fPosY;
	m_pBackground->SetPos(fPosX, fPosY);
}
//------------------------------------------------------------------------------------
// setea la posicion de los items
void RPGInterface::SetItemsPos(float fPosX, float fPosY)
{
	m_fItemsPosX = fPosX;
	m_fItemsPosY = fPosY;
	UpdateItemsPosition();
}
//------------------------------------------------------------------------------------
// setea la posicion de los items
void RPGInterface::SetItemsOffset(float fOffsetX, float fOffsetY)
{
	m_fItemsOffsetX = fOffsetX;
	m_fItemsOffsetY = fOffsetY;
	UpdateItemsPosition();
}
//------------------------------------------------------------------------------------
// setea la posicion de la barra de energia del personaje principal
void RPGInterface::SetCharacterBarPos(float fPosX, float fPosY)
{
	
}
//------------------------------------------------------------------------------------
// setea la dimension de la barra de energia del personaje principal
void RPGInterface::SetCharacterBarDim(float fWidth, float fHeight)
{

}
//------------------------------------------------------------------------------------
// setea la posicion de la barra de energia del enemigo actual
void RPGInterface::SetEnemyBarPos(float fPosX, float fPosY)
{

}
//------------------------------------------------------------------------------------
// setea la dimension de la barra de energia del enemigo actual
void RPGInterface::SetEnemyBarDim(float fWidth, float fHeight)
{

}
