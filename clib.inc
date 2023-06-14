#if defined _clib_included
	#endinput
#endif
#define _clib_included

#include <a_samp>

#define RAND_MAX 32767

#define exit() SendRconCommand("exit")

native time();
native rand();
native srand(seed);