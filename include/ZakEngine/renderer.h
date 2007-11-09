// El config file se lee en el metodo Startup de esta clase

#ifndef _Renderer_H_
#define _Renderer_H_

#include <d3d9.h>
#include <D3dx9math.h>
#include <vector>

#include "Defines.h"
#include "Window.h"
#include "ConfigFile.h"
#include "FileLog.h"
#include "VertexBufferManager.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

using namespace std;

#define D3DFVF_ZAKVERTEX    (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define D3DFVF_ZAKTEXVERTEX (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0))

#define ZAK_TEXT_BOTTOM		 DT_BOTTOM
#define ZAK_TEXT_CALCRECT	 DT_CALCRECT
#define ZAK_TEXT_CENTER		 DT_CENTER
#define ZAK_TEXT_EXPANDTABS	 DT_EXPANDTABS
#define ZAK_TEXT_LEFT		 DT_LEFT
#define ZAK_TEXT_NOCLIP		 DT_NOCLIP
#define ZAK_TEXT_RIGHT		 DT_RIGHT
#define ZAK_TEXT_RTLREADING	 DT_RTLREADING
#define ZAK_TEXT_SINGLELINE  DT_SINGLELINE
#define ZAK_TEXT_TOP		 DT_TOP
#define ZAK_TEXT_VCENTER	 DT_VCENTER
#define ZAK_TEXT_WORDBREAK	 DT_WORDBREAK

namespace zak {


class TextureInfo{
	public:
		char * szFileName;
		char * pData;
		unsigned int texColorKey;
		int iMipLevels;
		unsigned int uiTexWidth;
		unsigned int uiTexHeight;
		unsigned int size;
		bool persist;

	TextureInfo()
	{
		pData = NULL;
		szFileName = NULL;
		texColorKey = 0;
		iMipLevels = 0;
		uiTexWidth = 0;
		uiTexHeight = 0;
		size = 0;
		persist = false;
	}
};

enum RenderStates {
	ZAK_RENDER_STATE_BLEND = 0,
	ZAK_RENDER_STATE_BLENDFUNCBRIGHT
};


class ZAKENGINE_API TexVertex {
	private:
		float _fX,_fY,_fZ;
		float _fU, _fV;

	public:
		void SetVal(float fX, float fY, float fZ, float fU, float fV);

		float GetValX() {
			return _fX;
		}

		float GetValY() {
			return _fY;
		}

	TexVertex();
};

class ZAKENGINE_API ColorVertex {

	private:
		float _fX,_fY,_fZ;
		DWORD _dwColor;

	public:
		void SetVal(float fX, float fY, float fZ, DWORD dwColor);

		float GetValX() {
			return _fX;
		}

		float GetValY() {
			return _fY;
		}

	ColorVertex();
};

enum DRAWPRIMITIVES
{
	ZAK_PRI_POINTLIST=0,
	ZAK_PRI_LINELIST,
	ZAK_PRI_LINESTRIP,
	ZAK_PRI_TRIANGLELIST,
	ZAK_PRI_TRIANGLESTRIP
};

enum MATRIX_MODES {
	ZAK_WORLD_MATRIX=0,
	ZAK_VIEW_MATRIX,
	ZAK_PROJECTION_MATRIX,
	ZAK_TEXTURE_MATRIX
};

enum ZAK_FONT_TYPES {
	FT_ARIAL = 0,
	FT_COURIER,
	FT_TIMES,
	FT_VERDANA,
	FT_TAHOMA
};


class ZAKENGINE_API Renderer {
	private:
		ID3DXFont*		_pDefDXFont;
		ZAK_FONT_TYPES	_pDefDXFontType;
		INT				*_characterWidth;
		D3DCOLOR		_color;


		D3DPRESENT_PARAMETERS	D3DPresentParameter;
		bool					_deviceLost;
		LPDIRECT3DSURFACE9		_BackSurface;

		unsigned int			_ClearColor;
		float					_fViewPosX;
		float					_fViewPosY;

		int						_iBits;

		D3DFORMAT				_d3DFormat;

		D3DVIEWPORT9			vp;//objeto tipo viewport

		IDirect3D9				*_pD3D;
		IDirect3DDevice9		*_pD3DDevice;
		IDirect3DVertexBuffer9	*_pD3DVertexBuffer;

		MATRIX_MODES			_CurrentMatrixMode;

		D3DXMATRIX _theMatrix;

		//Pila de matrices
		LPD3DXMATRIXSTACK		_pWorldMatrixStack;
		LPD3DXMATRIXSTACK		_pProjectionMatrixStack;
		LPD3DXMATRIXSTACK		_pViewMatrixStack;
		LPD3DXMATRIXSTACK		_pTextureMatrixStack;

		D3DPRIMITIVETYPE		_PrimitiveVector[5];

		ConfigFile			*_ConfigFile;

		VertexBufferManager<ColorVertex,D3DFVF_ZAKVERTEX>		_VertexBufferManager;
		VertexBufferManager<TexVertex,D3DFVF_ZAKTEXVERTEX>	_VertexBufferTexManager;

		vector<LPDIRECT3DTEXTURE9>  _TextureVector;
		unsigned int				_uiCurrentTextureId;

		bool IniciarDX		(unsigned int uiAncho, unsigned int uiAlto, int iBits, bool bFullScreen, int refreshRate, bool vsync);
		void ApagarDX		();
		bool SetupDX		();

	public:
		void SetClearColor(unsigned int ClearColor) { _ClearColor = ClearColor; }

		void BindTexture(unsigned int uiTextureId);

		unsigned int LoadTexture(TextureInfo * pTexInfo);
		unsigned int GetViewPortHeight();
		unsigned int GetViewPortWidth();

		int	 GetBits() {
			return _iBits;
		}

		void LoadIdentity();

		void Scale(float fX, float fY);
		void Translate(float fX, float fY, float fZ);
		void RotationZ(float fAngle);

		void PushMatrix();
		void PopMatrix();

		void SetMatrixMode(enum MATRIX_MODES matType) {
			_CurrentMatrixMode=matType;
		}

		bool SetFont(ZAK_FONT_TYPES ft);
		void SetFontColor(unsigned int color) { _color = color; }

		ZAK_FONT_TYPES GetFont();

		void DrawString(wstring text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);

		void EnableModulate() {
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TFACTOR);

			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TFACTOR);
		}

		void SetModulationColor(DWORD dwColor) {
			_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, dwColor);
		}

		void DisableModulate() {
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_CURRENT);

			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		}


		void SetViewPosition(float fPosX, float fPosY) {
			_fViewPosX = fPosX;
			_fViewPosY = fPosY;

			D3DXVECTOR3 d3dvEyePos   (fPosX, fPosY, -5.0f);
			D3DXVECTOR3 d3dvLookPos  (fPosX, fPosY,  0.0f);
			D3DXVECTOR3 d3dvUpVector (0.0f,  1.0f,   0.0f);

			SetMatrixMode(ZAK_VIEW_MATRIX);

			D3DXMatrixLookAtLH(&_theMatrix,&d3dvEyePos,&d3dvLookPos, &d3dvUpVector);

			_pD3DDevice->SetTransform(D3DTS_VIEW,&_theMatrix);
		}

		void GetViewPosition(float &fPosX, float &fPosY) {
			fPosX = _fViewPosX;
			fPosY = _fViewPosY;
		}

		void EnableScissor() {
			_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
		}
		void DisableScissor() {
			_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}
		bool SetScissor(CONST RECT *rect) {
			if (_pD3DDevice->SetScissorRect(rect) != D3D_OK)
				return false;

			return true;
		}

		void GetWorldRect(RECT &Rect) {
			D3DXMATRIX mProj;
			_pD3DDevice->GetTransform(D3DTS_VIEW, &_theMatrix);
			_pD3DDevice->GetTransform(D3DTS_PROJECTION, &mProj);

			float fx = _theMatrix(3,0);
			float fy = _theMatrix(3,1);

			Rect.left   = (LONG) (-fx - 1/mProj(0,0));
			Rect.right  = (LONG) (-fx + 1/mProj(0,0));
			Rect.top    = (LONG) (-fy + 1/mProj(1,1));
			Rect.bottom = (LONG) (-fy - 1/mProj(1,1));
		}

		void EnableState(RenderStates eRenderState) {
			if (eRenderState == ZAK_RENDER_STATE_BLEND) {
				_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			} else if (eRenderState == ZAK_RENDER_STATE_BLENDFUNCBRIGHT) {
				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
		}

		void DisableState(RenderStates eRenderState) {
			if (eRenderState == ZAK_RENDER_STATE_BLEND) {
				_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			} else if (eRenderState == ZAK_RENDER_STATE_BLENDFUNCBRIGHT) {
//				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}
		}

		void Draw(ColorVertex * VertexCollection, DRAWPRIMITIVES ePrim, unsigned int uiVertexCount);
		void Draw(TexVertex * vertexCollection, DRAWPRIMITIVES prim, unsigned int uiVertexCount);

		bool Startup (unsigned int iAncho, unsigned int iAlto, int iBits, bool bFullScreen, int refreshRate, bool vsync);
		void CheckModes();
		void ShutDown();

		void BeginScene() {
			HRESULT hr = _pD3DDevice->BeginScene();
		}

		void EndEscene() {
			_pD3DDevice->EndScene();
		}

		void ClearTextures();

		void Clear() {
			_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET, _ClearColor,1.0f,0);
		}

		void Present(void) {
			if (_pD3DDevice->Present(NULL,NULL,NULL,NULL) != D3D_OK) {
				_deviceLost = true;
			}
		}
		bool IsDeviceLost() {
			return _deviceLost;
		}

		bool CheckForLostDevice();

		bool Reset() {
			if (_pD3DDevice->Reset(&D3DPresentParameter) != D3D_OK)
				return false;

			return true;
		}

	Renderer();
	~Renderer();
};

extern ZAKENGINE_API Renderer g_renderer;

}

#endif //_Renderer_H_
