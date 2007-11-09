#ifndef _Texture_H_	
#define _Texture_H_

#include <stdio.h>
#include <io.h>
#include <string.h>
#include "renderer.h"

namespace zak {

class Texture
{
	private:
		TextureInfo _info;
		char * _pszTextureFileName;
		unsigned int _uiReferenceCount;

		int _iTextureWidth;
		int _iTextureHeight;

		DWORD _color;

		unsigned int _uiTexNum;

	public:

		bool		 Load(const char * _pszTextureFileName, unsigned int ck, bool persist);
		bool		 Reload();
		const char  *GetName()const{return const_cast<const char*>(_pszTextureFileName);}
		void		 DecRef(){_uiReferenceCount--;}  
		void		 IncRef(){_uiReferenceCount++;}  
		int			 GetRefCount(){return _uiReferenceCount;}
		unsigned int GetTexNum(){return _uiTexNum;} 
		int			 GetWidth(){return _iTextureWidth;} 
		int			 GetHeight(){return _iTextureHeight;}

	Texture();
	~Texture();
};

}

#endif