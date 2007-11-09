#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include "renderer.h"
#include "Defines.h"
#include <dinput.h>

#pragma comment (lib, "dinput8.lib")

BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

namespace zak {

#define ZAK_MAX_INPUT_DEVICE						10

#define ZAK_INPUT_STATE_NOTHING						0
#define ZAK_INPUT_STATE_REACQUIRE					1
#define ZAK_INPUT_STATE_UNACQUIRE					2

#define ZAK_INPUT_POS_X                             0
#define ZAK_INPUT_POS_Y                             1
#define ZAK_INPUT_POS_Z                             2
#define ZAK_INPUT_MOUSE_POS_X                       0
#define ZAK_INPUT_MOUSE_POS_Y                       1
#define ZAK_INPUT_MOUSE_POS_Z                       2
#define ZAK_INPUT_MOUSE_BTN_1                       0
#define ZAK_INPUT_MOUSE_BTN_2                       1
#define ZAK_INPUT_MOUSE_BTN_3                       2

#define ZAK_INPUT_KEY_NONE							0
#define ZAK_INPUT_KEY_DOWN							1
#define ZAK_INPUT_KEY_UP							2
#define ZAK_INPUT_KEY_PRESSED						3

#define KeyUp(n)							(g_input._KeyEvent[n] == ZAK_INPUT_KEY_UP)
#define KeyDown(n)							(g_input._KeyEvent[n] == ZAK_INPUT_KEY_DOWN)
#define KeyPressed(n)						(g_input._KeyBuffer[n] & 0x80)
#define KeyEvent(n)							(g_input._KeyEvent[n])
#define MousePress(n)						(g_input._MouseData.Button[n] & 0x80)
#define MouseClick(n)                       (g_input._MouseData.ButtonClick[n])
#define MouseAbsPos(n)                      (g_input._MouseData.AbsPosition[n])
#define MouseAbsPosf(n)                     (float)(g_input._MouseData.AbsPosition[n])
#define MouseRelPos(n)                      (g_input._MouseData.RelPosition[n])
#define MouseRelPosf(n)                     (float)(g_input._MouseData.RelPosition[n])
#define MouseWorldPos(n)                    (g_input._MouseData.TtlPosition[n])
#define MouseWorldPosf(n)                   (float)(g_input._MouseData.TtlPosition[n])
#define JoystickPos(devNum, axis)			(g_input._joyData[devNum].Pos[axis])
#define JoystickRot(devNum, axis)			(g_input._joyData[devNum].Rot[axis])
#define JoystickPosf(devNum, axis)			(float)(g_input._joyData[devNum].Pos[axis])
#define JoystickRotf(devNum, axis)			(float)(g_input._joyData[devNum].Rot[axis])
#define JoystickButtons(devNum, button)		(g_input._joyData[devNum].Buttons[button] > 0)
#define JoystickCount()						(g_input._deviceCount)

struct InputJoystickData {
	long Pos[3];
	long Rot[3];
	BYTE Buttons[32];
};

struct InputMouseData {
	long TtlPosition[3];
	long AbsPosition[3];
	long RelPosition[3];
	BYTE Button[3];
    bool ButtonClick[3];
};

class ZAKENGINE_API Input {
public:
	BYTE			        _KeyBuffer[256];       // keyboard buffer for received data
	BYTE			        _KeyPrevBuffer[256];   // keyboard buffer for received data
	BYTE			        _KeyEvent[256];        // keyboard buffer for received data
	InputMouseData	        _MouseData;            // Mouse buffer for received data
	DIMOUSESTATE            MouseTaken;
	DIJOYSTATE				JoyTaken[ZAK_MAX_INPUT_DEVICE];
	InputJoystickData		_joyData[ZAK_MAX_INPUT_DEVICE];

	// Initialize DirecInput
	int  InitializeDirectInput(HINSTANCE hInstance, HWND hWnd);

	// End DirectInput
	void EndDirectInput(void);

	// Acquire Keyboard and mouse
	void Acquire(void);

	// Clean the input buffer
	void CleanBuffer(void);

	// Reacquire the input
	void Reacquire(void);

	// Unacquire the input
	void Unacquire(void);

	// Get the key events
	void GetKeyEvent(void);

	// Set the current input position
	void SetPosition(long x, long y, long z);

	// Clean the events
	void EventClean(void);

	Input();
	~Input();

	static int			_deviceCount;
	static GUID			_guid[ZAK_MAX_INPUT_DEVICE];

private:
	LPDIRECTINPUT8          _lpObjectOne;		// Direct Input ( Add )
	LPDIRECTINPUT8          _lpObjectTwo;		// Direct Input ( Add )
	LPDIRECTINPUT8          _lpObjectThree;		// Direct Input ( Add )
	LPDIRECTINPUTDEVICE8	_lpKeyboard;		// Keyboard Device ( Add )
	LPDIRECTINPUTDEVICE8    _lpMouse;			// Mouse Device (Add)
	LPDIRECTINPUTDEVICE8    _lpJoystick[ZAK_MAX_INPUT_DEVICE];	// Joystick Device (Add)
	bool                    _bButtonState[3];
	bool					_bMouseLastFrameState[3];

};

extern ZAKENGINE_API Input g_input;

}

#endif //_INPUT_H_

