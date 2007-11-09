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
 *	Clase que encapsula la inicialización, el bucle principal y el apagado del motor.
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
		*	Método virtual puro invocado luego de haberse inicializado correctamente el motor.
		*	@return Debemos retornar verdadero si todo salió correctamente y falso en caso contrario.
		*/
		virtual bool OnInit()=0;

		/**
		*	Método virtual puro invocado antes de apagar el motor.
		*	@return Debemos retornar verdadero si todo salió correctamente y falso en caso contrario.
		*/
		virtual bool OnShutdown()=0;

		/**
		*	Método virtual puro invocado durante el bucle principal antes de dibujar la escena. 
		*	Aquí actualizaremos las variables, chequearemos los dispositivos de entrada, etc.
		*/
		virtual void OnFrame()=0;

		/**
		*	Método virtual puro invocado durante el bucle principal en el momento de dibujar la escena.
		*	Aquí llamaremos a los métodos correspondientes al dibujado de los elementos correspondientes.
		*/
		virtual void OnDraw(){}

		/**
		*	Método invocado cuando se pierde el dispositivo ante un ALT+TAB en pantalla completa o por algún error.
		*/
		virtual void OnResetDevice(){}

		/**
		*	Método que debemos invocar para inicializar la aplicación. 
		*	Se encargará de crear la ventana, inicializar DirectX, inicializar el sonido, etc. y luego invocará al método OnInit.
		*/
		bool StartUp ();

		/**
		*	Método que correrá el bucle principal.
		*	Se encargará de llamar a los métodos OnFrame y OnDraw respectivamente.
		*/
		void Loop();

		/**
		*	Método que apagará la aplicación.
		*	Se encargará de invocar al método OnShutdown y de apagar correctamente el motor.
		*/
		bool Shutdown();

	/**
	*	Constructor.
	*/
	Game(){}
};

}

#endif
