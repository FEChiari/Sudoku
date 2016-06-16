#pragma once

/*
	===========================================================================
	Präprozessorkonstanten
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

void ScreenState_Login( struct sGame* nGame );
void ScreenState_Main_Menu( struct sGame* nGame );
void ScreenState_Ingame( struct sGame* nGame );
void ScreenState_Highscore( struct sGame* nGame );
void ScreenState_Registration( struct sGame* nGame );

int DBH_Callback_PrintScores( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );

void BtnCallback_OnLogin( struct sGame* nGame );
void BtnCallback_OnRegister( struct sGame* nGame );
void BtnCallback_OnPlayAsGuest( struct sGame* nGame );