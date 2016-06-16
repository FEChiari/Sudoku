#pragma once

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include "types.h"
#include "lib/pdcurses/panel.h"

/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

int Utility_GetKeyCode();
int Utility_WGetKeyCode( WINDOW* nTarget );
struct sVec2 Utility_GetWindowDimensions( WINDOW* nTarget );