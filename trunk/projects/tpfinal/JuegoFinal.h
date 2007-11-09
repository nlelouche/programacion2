#pragma once
#include "zakengine/zak.h"

#include "RPGMap.h"
#include "RPGCharacter.h"
#include "RPGInterface.h"

using namespace zak;

class JuegoFinal : public Game
{
public:

	bool OnInit();
	void OnFrame();	
	void OnDraw();
	bool OnShutdown();

	JuegoFinal(void);
	~JuegoFinal(void);

private:

	RPGInterface*	m_pInterface;
	RPGMap			m_Mapa;
	
	RPGCharacter*	m_pJugador;
	RPGCharacter*	m_pPersonaje01;
	RPGCharacter*	m_pPersonaje02;
};
