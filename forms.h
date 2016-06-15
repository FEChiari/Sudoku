#pragma once

#include "types.h"
#include "lib/pdcurses/panel.h"

struct sVec2 Forms_GetFieldSetDimensions( struct sFieldSet* nFieldSet );
void Forms_RenderFieldSet( WINDOW* nWindow, struct sFieldSet* nFieldSet );