#ifndef _Game_H_
#define _Game_H_

#include <windows.h>
#include <iostream>
#include <sstream>
#include "Defines.h"
#include "renderer.h"
#include "FPSMeter.h"
#include "Window.h"		// solo para conocer el hWnd que necesita
#include "Input.h"
#include "TextureManager.h"
#include "Messages.h"
#include "CPUInfo.h"
#include "SoundMgr.h"

using namespace std;

namespace zak {

/**
 *	Clase que encapsula la inicializaci�n, el bucle principal y el apagado del motor.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Game {
	private:
		MSG _msg;
		CPUInfo		_CPUInfo;

	protected:
		STCPUInfo	_stCPUInfo;
		FPSMeter	_fpsMeter;
		bool		_clearScreen;


	public:

		/**
		*	M�todo virtual puro invocado luego de haberse inicializado correctamente el motor.
		*	@return Debemos retornar verdadero si todo sali� correctamente y falso en caso contrario.
		*/
		virtual bool OnInit()=0;

		/**
		*	M�todo virtual puro invocado antes de apagar el motor.
		*	@return Debemos retornar verdadero si todo sali� correctamente y falso en caso contrario.
		*/
		virtual bool OnShutdown()=0;

		/**
		*	M�todo virtual puro invocado durante el bucle principal antes de dibujar la escena. 
		*	Aqu� actualizaremos las variables, chequearemos los dispositivos de entrada, etc.
		*/
		virtual void OnFrame()=0;

		/**
		*	M�todo virtual puro invocado durante el bucle principal en el momento de dibujar la escena.
		*	Aqu� llamaremos a los m�todos correspondientes al dibujado de los elementos correspondientes.
		*/
		virtual void OnDraw(){}

		/**
		*	M�todo invocado cuando se pierde el dispositivo ante un ALT+TAB en pantalla completa o por alg�n error.
		*/
		virtual void OnResetDevice(){}

		/**
		*	M�todo que debemos invocar para inicializar la aplicaci�n. 
		*	Se encargar� de crear la ventana, inicializar DirectX, inicializar el sonido, etc. y luego invocar� al m�todo OnInit.
		*/
		bool StartUp ();

		/**
		*	M�todo que correr� el bucle principal.
		*	Se encargar� de llamar a los m�todos OnFrame y OnDraw respectivamente.
		*/
		void Loop();

		/**
		*	M�todo que apagar� la aplicaci�n.
		*	Se encargar� de invocar al m�todo OnShutdown y de apagar correctamente el motor.
		*/
		bool Shutdown();

	/**
	*	Constructor.
	*/
	Game(){}
};

}

#endif
