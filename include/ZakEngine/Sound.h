#ifndef _ZAKSOUND_H_
#define _ZAKSOUND_H_

#include "Defines.h"
#include "audiere.h"

#pragma comment(lib, "audiere.lib")

namespace zak {

class ZAKENGINE_API Sound {
public:

	void setPitchShift(float pitch) { _pSound->setPitchShift(pitch); }
	void setRepeat(bool repeat) { _pSound->setRepeat(repeat); }
	void play() {
		if (!_isPlaying && _active) {
			_pSound->play();
			_isPlaying = true;
			if (_paused)
				_pSound->setPosition(_position);
			else
				_pSound->setPosition(0);
			_paused = false;
		}
	}

	void stop() { _pSound->stop(); _paused = false; _isPlaying = false; }

	void pause() {
		if (!_paused && _active) {
			_position = _pSound->getPosition();
			stop();
			_paused = true;
		}
	}

private:
	void setSoundActive(bool active) { _active = active; }

	Sound(audiere::OutputStreamPtr &pSound){ _pSound = pSound; _position = 0; _paused = false; _isPlaying = false; _pSound->ref(); _active = true; }
	~Sound(){  }

	audiere::OutputStreamPtr _pSound;
	int _position;
	bool _paused;
	bool _isPlaying;
	bool _active;


	friend class SoundMgr;
};

}

#endif // _ZAKSOUND_H_
