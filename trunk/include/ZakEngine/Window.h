#ifndef _Window_H_
#define _Window_H_

#include "Defines.h"
#include "FileLog.h"
#include "Input.h"
#include "Messages.h"

namespace zak {

class ZAKENGINE_API Window {
	private:
		HWND		hWnd;

	public:
		bool		ActiveWindow;
		int         Reacquire;

		ATOM RegistrarClase ();

		bool CrearVentana   (wstring *titulo,
							 int iAncho, int iAlto);
		void SaveScreenshot(char *szArchivo,int w,int h,int bpp);

		HWND GetHWnd() { return hWnd; }

};

extern ZAKENGINE_API Window g_window;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // _Window_H_
