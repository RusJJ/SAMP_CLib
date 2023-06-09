#include "plugin.h"

typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;
AMX* gAmx;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}