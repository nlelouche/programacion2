#ifndef _ZAKCONFIGFILE_H_
#define _ZAKCONFIGFILE_H_

#include <string.h>
#include <fstream>
//#include <iostream>
#include <stdlib.h>
#include "defines.h"

using namespace std;

#define ZAK_CFG_MAX_CHARACTERS			256

#define ZAK_CFG_START_SECTION_NAME		'['
#define ZAK_CFG_END_SECTION_NAME		']'
#define ZAK_CFG_EQUAL					'='
#define ZAK_CFG_COMMENT					';'
#define ZAK_CFG_STRING					'"'

namespace zak {

/**
 *  Esta clase analiza gramaticalmente archivos '.ini'.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API ConfigFile 
{
public:

	/**
	* Abre el archivo a analizar.
	* @param szFilename Nombre del archivo a analizar.
	* @return Retorna verdadero si la operaci�n fue exitosa
	*/
	bool Load(const char* szFilename);

	/**
	* Lee un n�mero entero del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Valor por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	int ReadInteger(const char *pszSection,
					const char *pszOption,
					int iDefaultValue);

	/**
	* Lee un n�mero entero largo del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Valor por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	long ReadLong (const char *pszSection,
					const char *pszOption,
					long lDefaultValue);

	/**
	* Lee un n�mero DWORD del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Valor por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	DWORD ReadDWord (const char *pszSection,
					const char *pszOption,
					DWORD DefaultValue);

	/**
	* Lee un n�mero booleano del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Valor por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	bool ReadBoolean(const char *pszSection,
						const char *pszOption,
						bool bDefaultValue);

	/**
	* Lee un n�mero decimal del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Valor por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	float ReadFloat(const char *pszSection,
					const char *pszOption,
					float fDefaultValue);

	/**
	* Lee una cadena de caracteres del archivo analizado.
	* @param Secci�n de la cual buscar la opci�n
	* @param Opci�n a buscar
	* @param Cadena de caraceteres por defecto en el caso de no encontrar la opci�n buscada
	* @return Retorna la cadena encontrada encontrado o el valor por defecto en caso de haber alg�n error.
	*/
	char *ReadString(const char *pszSection,
				        const char *pszOption,
				 		const char *pszDefaultValue);

	/**
	* Constructor.
	*/
  	ConfigFile();

	/**
	* Constructor.
	* @param Nombre del archivo a abrir.
	*/
	ConfigFile(const char *Filename);

	/**
	* Destructor.
	*/
	~ConfigFile();

private:
	ifstream    _ifs;

	char _szString[ZAK_CFG_MAX_CHARACTERS]; 
	
	// Deletes all the unneeded chars
	void deleteUnneeded(char *szString);

	// Search in file for a specific section
	void searchSection(const char *szSection);

	// Search a specific value in the file
	void searchValue(char *pszString, const char *szOption);
};

} // end namespace 

#endif // _CONFIGFILE_H_
