#include "plugin.h"

#include <ctime>

#define DECL_AMX_NATIVE(a) PLUGIN_EXTERN_C cell AMX_NATIVE_CALL Native_##a (AMX* amx, cell* params)
#define DECL_AMX_MAP(a) { #a, Native_##a }

typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;
AMX* gAmx;

/* Natives */
DECL_AMX_NATIVE(UnixTimestamp)
{
	return time(NULL);
}

/* Main */
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("\n\n<< SimpleTranslator has been loaded >>");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("\n\n<< SimpleTranslator has been unloaded >>");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	AMX_NATIVE_INFO aNatives[] =
	{
		DECL_AMX_MAP(UnixTimestamp),
		{ 0, 0 }
	};
	return amx_Register( amx, aNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}