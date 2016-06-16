#pragma once

/*
===========================================================================
Pr�prozessorkonstanten
===========================================================================
*/

#include "types.h"
#include "lib/pdcurses/panel.h"

/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

struct sVec2 Forms_GetFieldSetDimensions( struct sFieldSet* nFieldSet );
void Forms_RenderFieldSet( WINDOW* nWindow, struct sFieldSet* nFieldSet );