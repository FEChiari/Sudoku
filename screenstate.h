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
void ScreenState_Rules( struct sGame* nGame );
void ScreenState_Options( struct sGame* nGame );
void ScreenState_Difficulty( struct sGame* nGame );

void BtnCallback_OnQuitGame( struct sGame * nGame, struct sFieldSet* nFieldSet );

int DBH_Callback_PrintScores( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );

void Ingame_RenderBoard( WINDOW* nTargetWindow, u8 nXOffset, u8 nYOffset, struct sSudokuField nFields[ 9 ][ 9 ] );

void BtnCallback_OnLogin( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnPlayAsGuest( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnRegister( struct sGame* nGame, struct sFieldSet* nFieldSet );

void BtnCallback_OnRegisterUser( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnCancel( struct sGame* nGame, struct sFieldSet* nFieldSet );

void BtnCallback_OnContinueGame( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnStartNewGame( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnDisplayHighscores( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnDisplayRules( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnDisplayOptions( struct sGame* nGame, struct sFieldSet* nFieldSet );

void BtnCallback_OnResetMyHighscore( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnDeleteMyAccount( struct sGame* nGame, struct sFieldSet* nFieldSet );

void BtnCallback_OnLeicht( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnNormal( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnSchwer( struct sGame* nGame, struct sFieldSet* nFieldSet );
void BtnCallback_OnZurueck( struct sGame* nGame, struct sFieldSet* nFieldSet );

void BtnCallback_OnReturnToMainMenu( struct sGame* nGame, struct sFieldSet* nFieldSet );
