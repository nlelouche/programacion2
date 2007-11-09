#ifndef _Sprite_H_
#define _Sprite_H_

#include "Entity2D.h"
#include "renderer.h"
#include "TextureManager.h"

namespace zak {

class ZAKENGINE_API Sprite;

class Frame {
	public:
		float _fU, _fV, _fUW, _fUH;
};

class ZAKENGINE_API Animation {
public:
	bool Load(char *filename);
	
	//Animation(int iSize);
	Animation();
	~Animation();

	friend class Sprite;

private:
	int		_iSize;
	float	_fAnimationSpeed;
	bool	_bLoop;
	int		*_iFrameList;

	void SetSize(int iSize)
	{
		if (_iFrameList != NULL) {
			delete [] _iFrameList;
		}
		if (iSize>0)
			_iFrameList = new int [iSize];
		else
			_iFrameList = NULL;
		_iSize = iSize;
	} //prevents frame array redefinition
};

class ZAKENGINE_API Sprite : public Entity2D {
	private:
	
	protected:
		TexVertex	_Vertex[4];
		Texture  	*_pTexture;
		float			_fUV[2];		// UV de la textura a usar
		float			_fW;			// Ancho del tile
		float			_fH;			// Alto del tile
		Frame		*_Frames;
		int				_iFramesCount;
		int				_iActualFrame;
		Animation	*_Animation;
		bool			_bAnimationRuning;
		float			_fTime;
		
	public:
		void SetUVWH(float fU, float fV, float fW, float fH); // TEMPORAL!!!!! BORRAMEEE!
		bool Load(const char *pszImageFilename, unsigned int uiColorKey, bool persist = false);
		bool LoadIni(const char *iniFile);
		bool InitFrames(int iFramesCount, int iFrameWidth, int iFrameHeight,int iFramesCountPerWidth);
		void SetFrame(int iFrame);
		void SetAnimation(Animation *Animation);
		bool IsAnimationRunning();
		virtual void Draw();
		void Update(float fTimeBetweenFrames);
		int GetCurrentFrame(void){return _iActualFrame;}

	Sprite();
	~Sprite(){};
};

}

#endif // _Sprite_H_