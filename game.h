#pragma

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "utility.h"
#include "forms.h"
#include "dbh.h"
#include "screenstate.h"

#ifdef _WIN32
#define MOUSE_MOVED_CURSES MOUSE_MOVED
#undef MOUSE_MOVED
#include <consoleapi.h>
#undef MOUSE_MOVED
#define MOUSE_MOVED MOUSE_MOVED_CURSES
#endif