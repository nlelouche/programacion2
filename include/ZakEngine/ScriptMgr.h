#ifndef _SCRIPTMGR_H_
#define _SCRIPTMGR_H_

#include <stdio.h>
#include <io.h>

// AngelScript
#include "ZakEngine/Messages.h"
#include "ZakEngine/FileLog.h"
#include "ZakEngine/defines.h"
#include "ZakEngine/list.h"
#include "angelscript.h"
#include "Script.h"

#ifdef _DEBUG
#pragma comment(lib, "angelscriptd.lib")
#else
#pragma comment(lib, "angelscript.lib")
#endif 

namespace zak { 

class Script;

class ZAKENGINE_API ScriptMgr
{ 
public:
	static bool StartUp();

	static void Shutdown();

	static int RegisterGlobalProperty(char *szDecl, void* var) 
	{ 
		return _asEngine->RegisterGlobalProperty(szDecl, var); 
	}

	static int RegisterGlobalFunction(char *szDecl, asUPtr funcPointer, asDWORD callConv) 
	{ 
		return _asEngine->RegisterGlobalFunction(szDecl, funcPointer, callConv); 
	}

	static int RegisterObjectType (const char *szClassName, int iSize, asDWORD flags) 
	{ 
		return _asEngine->RegisterObjectType(szClassName, iSize, flags); 
	}

	static int RegisterObjectProperty (const char *szClassName, const char *szPropertyDecl, int byteOffset) 
	{ 
		return _asEngine->RegisterObjectProperty(szClassName, szPropertyDecl, byteOffset); 
	}

	static int RegisterObjectMethod(const char *szClassName, const char *szDecl, asUPtr funcPointer, asDWORD callConv) 
	{
		return _asEngine->RegisterObjectMethod(szClassName, szDecl, funcPointer, callConv); 
	}

	static int RegisterObjectBehaviour(const char *szClassName, asDWORD behaviour, const char *szDeclaration, asUPtr funcPointer, asDWORD callConv) 
	{
		return _asEngine->RegisterObjectBehaviour(szClassName, behaviour, szDeclaration, funcPointer, callConv);
	}

	static Script*	AddScript(char *szModule, char *szSection);
	static bool		RemoveScript(Script *script);
	static bool		ClearScriptList();

	static bool		CompileModule(char *szModule);

private:
	static bool LoadScript (char *szFilename, char *szModule, char *szSection);
	static bool LoadByteCode (char *szFilename); // TODO
	static bool SaveByteCode (char *szFilename); // TODO

	static asIScriptContext* CreateContext() { return _asEngine->CreateContext(); }

	static int ReleaseContext(asIScriptContext *gsContext) { return gsContext->Release(); }
	static int Prepare(asIScriptContext *asContext, int iFunctionId) { return asContext->Prepare(iFunctionId); }
	static int Execute (asIScriptContext *asContext) { return asContext->Execute(); }

	static int GetFuncIDByDecl(char *szModule, char *szFuncDecl) { return _asEngine->GetFunctionIDByDecl(szModule, szFuncDecl); }
	static const char *GetFuncDeclaration(int funcId) { return _asEngine->GetFunctionDeclaration(funcId);}

	static asIScriptEngine	*_asEngine;
	static List<Script*>	_list;

	friend class Script;
};

} // end namespace 

#endif // _SCRIPTMGR_H_