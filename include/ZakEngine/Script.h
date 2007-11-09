#pragma once

#include "ZakEngine/defines.h"
#include "ScriptMgr.h"

namespace zak {

#define SCRIPT_MAX_CHARS_NAME	100

class ZAKENGINE_API Script {
	friend class ScriptMgr;

public:
	int	 GetFunctionIdByDecl(char *functionPrototype);
	bool Prepare (char *functionPrototype);
	bool Prepare (int funcId);
	bool Execute();

	bool LoadScript(char *filename);
	bool LoadByteCode(char *filename);

	int  SetArgDWord(int iArg, asDWORD value) { return _context->SetArgDWord(iArg, value); }
	int  SetArgQWord(int iArg, asQWORD value) { return _context->SetArgQWord(iArg, value); }
	int  SetArgFloat(int iArg, float value) { return _context->SetArgFloat(iArg, value); }
	int  SetArgDouble(int iArg, double value){ return _context->SetArgDouble(iArg, value); }
	int  SetArgObject(int iArg, void *object){ return _context->SetArgObject(iArg, object); }

	asDWORD GetReturnDWord() { return _context->GetReturnDWord(); }
	asQWORD GetReturnQWord() { return _context->GetReturnQWord(); }
	float GetReturnFloat() { return _context->GetReturnFloat(); }
	double GetReturnDouble() { return _context->GetReturnDouble(); }
	void *GetReturnObject() { return _context->GetReturnObject(); }

private:

	Script(char *moduleName, char *sectionName);
	~Script();

	char _moduleName[SCRIPT_MAX_CHARS_NAME];
	char _sectionName[SCRIPT_MAX_CHARS_NAME];

	asIScriptContext* _context;

	int	_currentFunc;


};

} // end namespace