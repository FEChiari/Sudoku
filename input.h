#pragma once

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include "types.h"
#include "game.h"
#include "lib/pdcurses/panel.h"
#include "utility.h"

/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

void GetKey(struct sGame* nGame, u8* handleInput);
