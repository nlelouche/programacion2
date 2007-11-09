#ifndef _TextureManager_H_
#define _TextureManager_H_

#include "EntityList.h"
#include "Texture.h"

namespace zak {

class ZAKENGINE_API TextureManager {
	private:
		EntityList	Map;

	public:
		Texture * Load(const char *szFilename, unsigned int uiColorKey, bool persist);
		void		Remove(const char *szFilename);
		void		Remove(Texture *pTexture);
		void		Clear();
		int			GetCount();
		bool		Reload();

	TextureManager(int iSize);
	~TextureManager();
};

extern ZAKENGINE_API TextureManager g_textureManager;

}

#endif // _TextureManager_H_