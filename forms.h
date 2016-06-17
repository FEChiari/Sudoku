#pragma once

/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include <string.h>

#include "types.h"
#include "utility.h"
#include "lib/pdcurses/panel.h"

/*
  ===========================================================================
  Funktionsprototypen
  ===========================================================================
*/

struct sVec2 Forms_GetFieldSetDimensions( struct sFieldSet* nFieldSet );
void Forms_SetFieldActive( struct sFieldDef* nField, u8 nUseColors );
void Forms_SetFieldInactive( struct sFieldDef* nField, u8 nUseColors );
void Forms_RenderFieldSet( WINDOW* nWindow, struct sFieldSet* nFieldSet );
void Forms_HandleFieldSetInput( struct sGame* nGame, struct sFieldSet* nFieldSet );
void Forms_FreeFieldSet( struct sFieldSet* nFieldSet );
void Form_AdvanceToNextField( struct sFieldSet* nFieldSet );