#pragma once

#include "types.h"
#include "forms.h"
#include "utility.h"
#include "lib/pdcurses/panel.h"
#include "input.h"


void State_Login( struct sGame* nGame );
void State_Main_Menu( struct sGame* nGame );
void State_Ingame( struct sGame* nGame );
void State_Highscore( struct sGame* nGame );