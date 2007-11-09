#include "JuegoFinal.h"
#include "zakengine/zak.h"

//	HOLA SOY UN PROYECTO!!!!!

#ifdef _DEBUG
#pragma comment (lib, "zakengined.lib")
#else
#pragma comment (lib, "zakengine.lib")
#endif

int main()
{
	JuegoFinal game;
	if(game.StartUp())
	{
		game.Loop();
		game.Shutdown();
	}
	return 0;
}
