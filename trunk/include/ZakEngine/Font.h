#ifndef _Font_H_
#define _Font_H_

#include <string.h>
#include "Entity2D.h"
#include "renderer.h"
#include "TextureManager.h"



namespace zak {

/**
*	Clase que muestra texto en pantalla
*	@Author: Juan Pablo "McKrackeN" Bettini
*/
class ZAKENGINE_API Font : public Entity2D {
	private:
		TexVertex	*_pVertex;
		Texture  	*_pTexture;
		char		*_pszText;
		int			_iTextLenght;
		int			_fontWidth;
		int			_fontHeight;
		int			_fontSideCount;
		float		_spacing;

		bool Load(const char *pszImageFilename, unsigned int uiColorKey, bool persist = false);

	public:
		/**
		*	Almacena el texto formateado a mostrar (estilo printf).
		*	Nota: si se modifica las dimensiones utilizando el método SetDim, 
		*	éste método debe invocarse inmediatamente después.
		*	@param pszText texto formateado a mostrar
		*/
		void SetText(char *psz_Text,...); 

		/**
		*	Dibuja el texto en pantalla
		*/
		void Draw();

		/**
		*	Carga un texto desde un archivo de inicialización .ini
		*	@param pszFilename nombre del archivo a cargar
		*	@return Verdadero si se cargó correctamente y falso en caso contrario
		*/
		bool LoadIni(const char *pszFilename);

	/**
	*	Constructor
	*/
	Font();

	/**
	*	Destructor
	*/
	~Font();
};

}

#endif // _Font_H_
