#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Defines.h"
#include <string.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace zak {


/**
 *  Clase que contiene las propiedades comunes a todas las entidades.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API ENTITY {
protected:
	char _pszNombre[256];
	bool _bVisible;

public:
	/**
	 *  Fija la propiedad de visibilidad de la entidad
	 *	@param bVis Variable booleana que indica si la entidad es visible o no
	 */
	void SetVisible(bool bVis) 
	{
		_bVisible=bVis; 
	};
	
	/**
	 *  Devuelve si la entidad es visible o no
	 *	@return Retorna verdadero en caso de ser visible y falso en caso contrario
	 */
	bool GetVisible(void) const //protege _bVisible
	{
		return _bVisible; 
	};

	/**
	 *  Fija el nombre de la entidad
	 *	@param pszName Cadena de caracteres conteniendo el nombre de la entidad
	 */
	void SetName(char * pszName) 
	{
		strcpy(_pszNombre, pszName);
	}

	/**
	 *  Devuelve el nombre de la entidad
	 *	@return Retorna una cadena de caracteres conteniendo el nombre de la entidad
	 */
	char *GetName () 
	{
		return _pszNombre;
	}

	/**
	 *  Constructor
	 */
	ENTITY(){ _bVisible = true; };

	/**
	 *  Destructor
	 */
	virtual ~ENTITY(){};
};

}

#endif // _ENTITY_H_
