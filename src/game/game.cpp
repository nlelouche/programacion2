#include "game.h"

TestGame::TestGame() {

}

TestGame::~TestGame() { 

}
bool TestGame::OnInit() {

	_clearScreen = true;

	return true;
}

void TestGame::OnFrame() {
	if (KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);
}

void TestGame::OnDraw() {
	wstringstream ss;

	ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
	g_renderer.SetFontColor(0xFFFF0000);
	g_renderer.DrawString(ss.str(),10,10,800-20,600-20,ZAK_TEXT_LEFT);
}

bool TestGame::OnShutdown() {
	return true;
}