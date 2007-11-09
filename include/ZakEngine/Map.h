
#ifndef _Map_H_
#define _Map_H_

#include "renderer.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <iostream>

#define MAP_TILE_WIDTH		64
#define MAP_TILE_HEIGHT		64

namespace zak {

class Tiles {
	public:
		float _fPosX, _fPosY, _fU, _fV, _fUW, _fUH;
};

class ZAKENGINE_API Map : public Entity2D {
	private:
		TexVertex	*_Vertex;
		TexVertex	*_TempVert;
		Texture  	*_pTexture;
		float		_fUV[2];		// UV de la textura a usar
		float		_fW;			// Ancho del tile
		float		_fH;			// Alto del tile

		int			_iStartX,_iStartY;
		int			_iCountX,_iCountY;
		int			_iTempCountX,_iTempCountY;

		int			*_cMap;
		Tiles		*_Tiles;

		int			_iActualTile;
		int			_iTileWidth;
		int			_iTileHeight;

		int			_iWidth;
		int			_iHeight;
		
		bool		_bEnableAlpha;

		bool LoadTexture(const char *pszTextureFilename, unsigned int uiColorKey, bool persist = false); 
		bool LoadMap	(const char *pszMapFilename);

	public:
		void EnableAlphaBlend () {
			_bEnableAlpha = true;
		}
		void DisableAlphaBlend () {
			_bEnableAlpha = false;
		}

		int	 GetTileWidth() {
			return _iTileWidth;
		}
		int	 GetTileHeight() {
			return _iTileHeight;
		}
		int GetMapWidth() {
			return _iWidth;
		}
		int GetMapHeight() {
			return _iHeight;
		}

		void SetTile (int col, int row, int tileNum);

		int GetTileFromWorldCoords(float x, float y);
		bool GetColRowFromWorldCoords(float x, float y, int &col, int &row);
		void GetWorldCoordsFromColRow(int col, int row, float &x, float &y);

		bool Load		(const char *pszTextureFilename, const char *pszMapFilename, unsigned int uiColorKey, int tileWidth, int tileHeight, bool persist = false);
		void Draw		();

	Map();
	~Map();
};

}
#endif // _Map_H_