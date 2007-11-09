#ifndef _VertexBufferManager_H_
#define _VertexBufferManager_H_

#include <windows.h>
#include <d3d9.h>
//#include "Renderer.h"
//#include <assert.h>

namespace zak {

template <class PixelFormatClass, unsigned int FVF>
class VertexBufferManager
{
	static const int VB_SIZE		= 450;
	static const int FLUSH_COUNT	= 150;
public:
	// Constructor (es conveniente que flush sea m�ltiplo de size y de 3)
	VertexBufferManager() : _vbSize(VB_SIZE), _flushCount(FLUSH_COUNT), _pVertexBuffer(NULL), _primitiveType(D3DPT_TRIANGLELIST) {}
	
	// Destructor
	~VertexBufferManager() { if (_pVertexBuffer) _pVertexBuffer->Release(); }

	// Crea un vertex buffer
	bool Create(IDirect3DDevice9 *pDev, bool bDynamic=true);

	// Libera a un vertex buffer
	void Release(void) { if (_pVertexBuffer) _pVertexBuffer->Release(); _pVertexBuffer=NULL; }

	// Actualiza el contenido del vertex buffer
	bool Draw(PixelFormatClass * pVtxCollection, D3DPRIMITIVETYPE primitiveType, unsigned int uiVtxCount);

	// Bind
	void Bind(void)
	{
		_pDev->SetVertexShader(NULL);
		_pDev->SetFVF(FVF);
		_pDev->SetStreamSource(0, _pVertexBuffer, 0, sizeof(PixelFormatClass));
	}
	
	// Env�a los datos al pipeline
	void Flush();

private:
	const unsigned int _vbSize;					// Cantidad de v�rtices que contiene el vertex buffer
	const unsigned int _flushCount;				// Cantidad de v�rtices entre flushes
	LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;		// Vertex Buffer encapsulado
	IDirect3DDevice9		*_pDev;				// Device asociado en el m�todo Create
	
	unsigned int _baseNum;						// Base del vertex buffer a lockear
	unsigned int _vtxToLock;					// Indica la cantidad de v�rtices lockeados en el vb
	D3DPRIMITIVETYPE _primitiveType;			// Primitiva actual

	
};

// ------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
bool VertexBufferManager<PixelFormatClass, FVF>::Create(IDirect3DDevice9 *pDev, bool bDynamic)
{
	_pDev = pDev;

	HRESULT hr = pDev->CreateVertexBuffer(_vbSize*sizeof(PixelFormatClass),
		(bDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : 0),
		FVF,
		D3DPOOL_DEFAULT,
		&_pVertexBuffer, NULL);

	// Indico que la base de vb a lockear es cero
	_baseNum = 0;
	
	if (hr == D3D_OK)
		return true;
	else
		return false;
}
// ------------------------------------------------------------------------------
// Actualiza el contenido del vertex buffer
template <class PixelFormatClass, unsigned int FVF>
bool VertexBufferManager<PixelFormatClass, FVF>::Draw(PixelFormatClass * pVtxCollection, D3DPRIMITIVETYPE primitiveType, unsigned int uiVtxCount)
{
	VOID * pVertices;

	// Almaceno cual es la primitiva deseada
	_primitiveType = primitiveType;

	// Si la cantidad de v�rtices que faltan para realizar un flush es menor
	// a la cantidad de v�rtices pasados, copio primero s�lo los que faltan
	// para el flush y realizo el mismo
	_vtxToLock = (_flushCount < uiVtxCount ? _flushCount : uiVtxCount);
	
	// Verifico que la cantidad de v�rtices a lockear + la base
	// no exeda el tama�o total del vertex buffer
	if (_baseNum + _vtxToLock > _vbSize)
		_baseNum = 0;

	// Lockeo el vertex buffer a partir de la base y un chunk correspondiente
	// al tama�o del flush
	HRESULT hr = _pVertexBuffer->Lock(_baseNum * sizeof(PixelFormatClass),
										_vtxToLock * sizeof(PixelFormatClass),
										(VOID **) &pVertices,
										_baseNum ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	// Si no he podido realizar un lock, retorno false
	if (hr != D3D_OK)
		return false;

	unsigned int uiVtxProcNow = 0;
	// Mientras que queden v�rtices a copiar...
	while (_vtxToLock > 0)
	{
		// Copio v�rtices al vertex buffer
		memcpy( pVertices, &pVtxCollection[uiVtxProcNow], sizeof(PixelFormatClass)*_vtxToLock);

		// Actualizo el �ndice de copia de los v�rtices pasados como par�metros
		uiVtxProcNow += _vtxToLock;
		
		// -------------------------------------------------------------------------
		// Copiados los v�rtices al vb, los env�o al pipeline
		// por medio del DrawPrimitive
		// -------------------------------------------------------------------------
		
		// Destrabo el vb
		_pVertexBuffer->Unlock();

		// Realizo el DrawPrimitive
		Flush();

		// Actualizo la base de v�rtices a lockear
		_baseNum += _vtxToLock;
		
		// Calculo nuevamente la cantidad de v�rtices a copiar
		_vtxToLock = (_flushCount < (uiVtxCount-uiVtxProcNow) ? _flushCount : uiVtxCount-uiVtxProcNow);

		// Verifico que la cantidad de v�rtices a lockear + la base
		// no exeda el tama�o total del vertex buffer
		if (_baseNum + _vtxToLock > _vbSize)
			_baseNum = 0;

		hr = _pVertexBuffer->Lock(_baseNum * sizeof(PixelFormatClass),
									_vtxToLock * sizeof(PixelFormatClass),
									(VOID **) &pVertices,
									_baseNum ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		// Si no he podido realizar un lock, retorno false
		if (hr != D3D_OK)
			return false;
	}

	// Destrabo el vb
	_pVertexBuffer->Unlock();

	return true;
}

// ------------------------------------------------------------------------------
// Env�a los datos al pipeline
template <class PixelFormatClass, unsigned int FVF>
void VertexBufferManager<PixelFormatClass, FVF>::Flush(void)
{
	HRESULT hr;

	int primitiveCount;
	
	// Determino la cantidad de primitivas a realizar en funci�n
	// del tipo
	if (_primitiveType == D3DPT_POINTLIST)
		primitiveCount = _vtxToLock;
	else if (_primitiveType == D3DPT_LINELIST)
		primitiveCount = _vtxToLock/2;
	else if (_primitiveType == D3DPT_LINESTRIP)
		primitiveCount = _vtxToLock-1;
	else if (_primitiveType == D3DPT_TRIANGLELIST)
		primitiveCount = _vtxToLock/3;
	else if (_primitiveType == D3DPT_TRIANGLESTRIP)
		primitiveCount = _vtxToLock-2;
	else
		primitiveCount = 0;

	hr = _pDev->DrawPrimitive(_primitiveType, _baseNum, primitiveCount);

}

}

#endif // _VertexBufferManager_H_
