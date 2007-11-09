#pragma once

// AngelScript headers
#include "angelscript.h"

// Project headers
#include "defines.h"
#include "Script.h"

// C/C++ headers
#include <cstdio>
#include <io.h>
#include <iostream>
using namespace std;

namespace zak
{

class ZAKENGINE_API ScriptManager
{
	static const int MAX_SCRIPT_COUNT	= 256;
public:
	// Inicializa el manager
	static bool Startup();

	// Detiene el manager
	static void Shutdown();

	// Agrega un script al manager
	static Script * Add(const char * scriptFilename);
	// Elimina un script del manager
	static bool Delete(Script * pScript);
	// Limpia el manager
	static void Clear();

	// Registra una variable entera
	static void RegisterGlobalProperty(const char * pVariableType, void * pVar)
	{
		_engine->RegisterGlobalProperty(pVariableType, pVar);
	}

	static void ExecuteString(const char * pModuleName, const char * pCmd)
	{
		_engine->ExecuteString(pModuleName, pCmd);
	}

	// Registra una función
	static void RegisterGlobalFunction(const char * pFunctionType, asUPtr pFunc, unsigned int callingConv)
	{
		_engine->RegisterGlobalFunction(pFunctionType, pFunc, callingConv);
	}
	
public:
	static asIScriptEngine * _engine;					// Puntero al motor de scripting
private:
	static Script * _scriptList[MAX_SCRIPT_COUNT];		// Lista de scripts
	static int _scriptCount;							// Cantidad de scripts utilizados

	friend class Script;
};

} // end namespace

