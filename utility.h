#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

#include "types.h"
#include "forms.h"
#include "lib/pdcurses/panel.h"


int Utility_GetKeyCode();
int Utility_WGetKeyCode( WINDOW* nTarget );
u8 Utility_Confimation( struct sGame* nGame, struct sFieldSet* nFieldSet );

#ifdef _WIN32
void Utility_SetWindowMaximizable( u8 nState );
#endif