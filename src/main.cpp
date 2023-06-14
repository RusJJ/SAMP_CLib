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
DECL_AMX_NATIVE(time)
{
	return time(NULL);
}
DECL_AMX_NATIVE(rand)
{
	return rand();
}
DECL_AMX_NATIVE(srand)
{
	return srand(params[1]);
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

	logprintf("\n\n<< CLib by RusJJ has been loaded >>");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("\n\n<< CLib by RusJJ has been unloaded >>");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	AMX_NATIVE_INFO aNatives[] =
	{
		DECL_AMX_MAP(time),
		DECL_AMX_MAP(rand),
		DECL_AMX_MAP(srand),
		{ 0, 0 }
	};
	return amx_Register( amx, aNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}