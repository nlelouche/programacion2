#ifndef _ZAKSOUNDMGR_H_
#define _ZAKSOUNDMGR_H_

#include <vector>
#include "FileLog.h"
#include "Messages.h"
#include "Defines.h"
#include "Sound.h"
#include "audiere.h"

#pragma comment(lib, "audiere.lib")

using namespace std;

namespace zak {

class ZAKENGINE_API SoundMgr {
public:
	static void setSoundActive(bool active) { _active = active; }
	static bool getSoundActive() { return _active; }
	static bool openDevice();
	static Sound *openSound(char *filename, bool stream);
	static void closeSound(Sound *sound) { if (sound) delete sound; }
	static void logAudioDevices();

private:
	static bool _active;
	static audiere::AudioDevicePtr *_pDevice;
};

}

#endif // _ZAKSOUND_H_
