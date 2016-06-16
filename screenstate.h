#pragma once

/*
	===========================================================================
	Pr�prozessorkonstanten
	===========================================================================
*/


#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "forms.h"
#include "utility.h"
//#include "input.h"
#include "solver.h"
#include "dbh.h"
#include "lib/pdcurses/panel.h"


/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

void State_Login( struct sGame* nGame );
void State_Main_Menu( struct sGame* nGame );
void State_Ingame( struct sGame* nGame );
void State_Highscore( struct sGame* nGame );

int Callback_PrintScores( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );