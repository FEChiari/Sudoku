#pragma once

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include "types.h"
#include "forms.h"
#include "lib/pdcurses/panel.h"

/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

int Utility_GetKeyCode();
int Utility_WGetKeyCode( WINDOW* nTarget );
u8 Utility_Confimation(struct sGame* nGame, struct sFieldSet* nFieldSet);



void Utility_SetWindowMaximizable( u8 nState );