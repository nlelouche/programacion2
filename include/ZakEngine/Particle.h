////////////////////////////////////////////////////////////////////////
//
// TODO:
//		- Poder cambiar el tamaño desde afuera, 
//		- Interpolar entre tamaños
//		- Rotar a una velocidad (eso lo tengo que agregar en Sprite)
//
// REMEMBER:
//		Cantidad de Particulas = _fLifeTime / _fFrequency	
//		
//
////////////////////////////////////////////////////////////////////////


#ifndef _Particle_H_
#define _Particle_H_

#include "Sprite.h"
#include "Entity2D.h"

namespace zak {

class ZAKENGINE_API Particle : public Sprite {

	private:

	public:
		DWORD	_dwColor,_dwStartColor;
		char	*_pdwColor;
		char	*_pdwStartColor;
		char	*_pdwTemp;

		float	_rotSpeed;

		float	_fRedInterpolation;
		float	_fGreenInterpolation;
		float	_fBlueInterpolation;
		float	_fAlphaInterpolation;
		
		float	_startSizeX;
		float	_startSizeY;
		float	_sizeInterpolationX;
		float	_sizeInterpolationY;

		float	_fTimeAccum;

		float	_fLifeTime;

		bool	_bIsDead;

		void Update(float fTimeBetweenFrames);
//		void Draw(float fTimeBetweenFrames);

	Particle(){
		_rotSpeed = 0.0f;
		_fLifeTime = 0.0f;
		_bIsDead = false;
		_pdwColor = (char*)&_dwColor;
		_pdwStartColor = (char*)&_dwStartColor;
		
		_fRedInterpolation=0.0f;
		_fGreenInterpolation=0.0f;
		_fBlueInterpolation=0.0f;
		_fAlphaInterpolation=0.0f;

		_sizeInterpolationX=0.0f;
		_sizeInterpolationY=0.0f;
		
		_fTimeAccum = 0.0f;
	};
	~Particle(){};
};

class ZAKENGINE_API ParticleSystem : public Entity2D {
	private:
		Particle		*_prtParticles;

		DWORD	_dwStartColor;
		DWORD	_dwEndColor;

		char	*_pdwStartColor;
		char	*_pdwEndColor;

		float	_fLifeTime;
		float	_fFrequency;
		float	_fAccum;

		float	_startSizeX;
		float	_startSizeY;
		float	_endSizeX;
		float	_endSizeY;

		float	_fParticlesSpeed;
		float	_fParticlesAngle;
		float	_rotSpeed;
		float	_fAngleNoise;
		float	_fSpeedNoise;
		float	_fLifeNoise;
		float	_rotSpeedNoise;

		int		_iMaxParticles;

		bool	_bSystemEnabled;

		bool	_bIsAllDead;

	public:
		void SetStartDim(float sizeX, float sizeY) {
			_startSizeX = sizeX;
			_startSizeY = sizeY;
		}
		void SetEndDim(float sizeX, float sizeY) {
			_endSizeX = sizeX;
			_endSizeY = sizeY;
		}
		void SetStartColor(DWORD dwColor) {
			_dwStartColor = dwColor;
		} 

		void SetEndColor(DWORD dwColor) {
			_dwEndColor = dwColor;
		} 

		void SetLifeTime (float fLifeTime) {
			_fLifeTime = fLifeTime;
		}

		void SetRotationSpeed(float rotSpeed) {
			_rotSpeed = rotSpeed;
		}
		void SetRotationSpeedNoise(float rotSpeedNoise) {
			_rotSpeedNoise = rotSpeedNoise;
		}

		void SetParticlesSpeed (float fParticlesSpeed) {
			_fParticlesSpeed = fParticlesSpeed;
		}

		void SetParticlesAngle (float fParticlesAngle) {
			_fParticlesAngle = fParticlesAngle;
		}

		void SetLifeNoise (float fLifeNoise) {
			_fLifeNoise  = fLifeNoise;
		}

		void SetSpeedNoise (float fSpeedNoise) {
			_fSpeedNoise = fSpeedNoise;
		}

		void SetAngleNoise (float fAngleNoise) {
			_fAngleNoise = fAngleNoise;
		}

		void SetAllDead() {
			for (int i=0; i<_iMaxParticles; i++) 
				_prtParticles[i]._bIsDead = true;
		}

		void SetEnableSystem() {
			_bSystemEnabled = true;
		}

		void SetDisableSystem() {
			_bSystemEnabled = false;
		}


		virtual void Draw ();
		virtual void Update (float fTimeBetweenFrames);

		bool Initialize(int iMaxParticles, float fFrequency, char *szFilename, DWORD dwColorKey, bool texPersist=false) {
			_fFrequency = fFrequency;
			_fAccum = 0.0f;

			if (iMaxParticles>0) {
				_iMaxParticles = iMaxParticles;
				_prtParticles = new Particle[iMaxParticles];
				if (_prtParticles) {
					for (int i=0; i<_iMaxParticles; i++) {
						_prtParticles[i]._bIsDead = true;
						//_prtParticles[i].SetDim(64,64);
						_prtParticles[i].SetPos(0,0);
						if (!_prtParticles[i].Load(szFilename,dwColorKey, texPersist)){
							return false;
						}
						_prtParticles[i].InitFrames(1,128,128,1);
						_prtParticles[i].SetFrame(0);
						_prtParticles[i]._dwColor = 0;
						_prtParticles[i]._fLifeTime = 0;
						_prtParticles[i].SetSpeed(0);
						_prtParticles[i].SetMovDirection(0);
						_prtParticles[i].SetMoving(false);
						_prtParticles[i].SetVisible(false);
					}
					return true;
				} else {
					return false;
				}
			} else {
				_prtParticles = NULL;
				_iMaxParticles = 0;
				return false;
			}
			return false;
		}


	ParticleSystem() {
		_rotSpeedNoise = 0.0f;
		_rotSpeed = 0.0f;
		_startSizeX = 0.0f;
		_startSizeY = 0.0f;
		_endSizeX = 0.0f;
		_endSizeY = 0.0f;
		_fParticlesSpeed = 0.0f;
		_fParticlesAngle = 0.0f;
		_fSpeedNoise = 0;
		_fAngleNoise = 0;
		_dwStartColor = 0;
		_dwEndColor = 0;
		_fLifeTime = 0.0f;
		_fLifeNoise = 0;
		_pdwStartColor = (char*)&_dwStartColor;
		_pdwEndColor = (char*)&_dwEndColor;
		_prtParticles = NULL;
		_bSystemEnabled = true;
		_bIsAllDead = true;
	};

	~ParticleSystem() {
		if (_prtParticles)
			delete [] _prtParticles;
	};
};


}
#endif //_Particle_H_