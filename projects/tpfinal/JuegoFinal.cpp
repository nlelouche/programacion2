#pragma once
#include "zakengine/zak.h"
#include "JuegoFinal.h"

#include "Personajes/Roxy/Character_Roxy.h"

#include "Items/Energy/Item_Energy.h"

//-------------------------------------------------------
JuegoFinal::JuegoFinal(void)
{

}
//-------------------------------------------------------
JuegoFinal::~JuegoFinal(void)
{
}
//-------------------------------------------------------
bool JuegoFinal::OnInit()
{
	_clearScreen = true;

	/////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// MAPA /////////////////////////////////////////////
	
	// inicializo el mapa
	if (!m_Mapa.Load("./data/maps/map01.bmp","./data/maps/map01.map",0xFFFFFFFF, 32, 32, false))
		return false;

	// agrega los subindices de colision
	for(unsigned int i=0;i<12;i++)
		m_Mapa.AddColTile(i);

	// setea la posicion inicial del personaje
	m_Mapa.SetCharInitPos(450, -450); //-355

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////// PERSONAJES //////////////////////////////////////////

	// creo al personaje principal
	m_pPersonaje01 = new Character_Roxy();

	// seteo la posicion del personaje en la posicion inicial del mapa
	m_pPersonaje01->SetPos(m_Mapa.GetCharInitPosX(),m_Mapa.GetCharInitPosY());

	// seteo al personaje del jugador para ser accedido por todas las instancias de RPGCharacter
	RPGCharacter::SetPlayerCharacter(m_pPersonaje01);

	// agrego el personaje al mapa
	m_Mapa.AddCharacter(m_pPersonaje01);

	//-----------------------------------------------------------------------------------

	// creo al personaje principal
	m_pPersonaje02 = new Character_Roxy();

	// seteo la posicion del personaje en la posicion inicial del mapa
	m_pPersonaje02->SetPos(m_Mapa.GetCharInitPosX() - 100.0f,m_Mapa.GetCharInitPosY() - 100.0f);

	// agrego el personaje al mapa
	m_Mapa.AddCharacter(m_pPersonaje02);

	//-----------------------------------------------------------------------------------

	// asigno el puntero al personaje del jugador
	m_pJugador = m_pPersonaje01;

	/////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// ITEMS ////////////////////////////////////////////

	RPGItem	*pkItem;

	// creo el item de health
	pkItem = new Item_Energy();

	// seteo la posicion del item
	pkItem->SetPos(m_Mapa.GetCharInitPosX() + 100.0f, m_Mapa.GetCharInitPosY());

	// agrego el item al mapa
	m_Mapa.AddItem(pkItem);

	//-----------------------------------------------------------------------------------
	// creo otro item de health
	pkItem = new Item_Energy();

	// seteo la posicion del item
	pkItem->SetPos(m_Mapa.GetCharInitPosX() - 100.0f, m_Mapa.GetCharInitPosY());

	// agrego el item al mapa
	m_Mapa.AddItem(pkItem);

	/////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// GUI //////////////////////////////////////////////

	m_pInterface = new RPGInterface();
	
	m_pInterface->SetBackground("./data/GUI/background.spr");
	
	m_pInterface->SetItemsBackPos(-400.0f + 256.0f, -300.0f + 32.0f);
	m_pInterface->SetItemsPos(-400.0f - 30.0f, -300.0f + 30.0f);
	m_pInterface->SetItemsOffset(63.0f, 0.0f);

	m_pInterface->SetCharacter(m_pJugador);
	m_pInterface->SetCharacterBarPos(395.0f, -243.0f);
	m_pInterface->SetCharacterBarDim(285.0f, 15.0f);

	//m_pInterface->SetEnemy(m_pPersonaje02);
	m_pInterface->SetEnemyBarPos(253.0f, -270.0f);
	m_pInterface->SetEnemyBarDim(285.0f, 15.0f);

	return true;
}
//-------------------------------------------------------
void JuegoFinal::OnFrame()
{
	// sale del juego
	if(KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);

	// actualizacion del input
	if(KeyDown(DIK_LEFT))
		m_pJugador->Move(270.0f);
	else if(KeyDown(DIK_RIGHT))
		m_pJugador->Move(90.0f);
	else if(KeyDown(DIK_UP))
		m_pJugador->Move(0.0f);
	else if(KeyDown(DIK_DOWN))
		m_pJugador->Move(180.0f);
	else if(KeyDown(DIK_SPACE))
		m_pJugador->Hit();

	if(KeyPressed(DIK_S))
		m_pJugador->SetEnergy(m_pJugador->GetEnergy() + 0.01f);
	else if(KeyPressed(DIK_A))
		m_pJugador->SetEnergy(m_pJugador->GetEnergy() - 0.01f);

	// actualizo el mapa
	m_Mapa.Update((float)_fpsMeter.GetDT(), m_pJugador);

	// actualizo la interface
	m_pInterface->Update((float)_fpsMeter.GetDT());
}
//-------------------------------------------------------
void JuegoFinal::OnDraw()
{
	// dibuja el mapa
	m_Mapa.Draw();

	// dibuja la interface
	m_pInterface->Draw();

	// dibuja los fps
	wstringstream ss;
	ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
	g_renderer.SetFontColor(0xFFFF0000);
	g_renderer.DrawString(ss.str(),10,10,800-20,600-20,ZAK_TEXT_LEFT);
	
}
//-------------------------------------------------------
bool JuegoFinal::OnShutdown()
{
	m_pJugador = NULL;

	delete m_pInterface;
	m_pInterface = NULL;

	delete m_pPersonaje01;
	m_pPersonaje01 = NULL;

	delete m_pPersonaje02;
	m_pPersonaje02 = NULL;
	
	return true;
}
//-------------------------------------------------------
