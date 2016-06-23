
/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "screenstate.h"

/*
  ===========================================================================
  Funktion: State_Main_Menu
  Übergabeparameter: nGame
  Rückgabeparameter: -
  Beschreibung: Warte auf Code!
  ===========================================================================
*/

void ScreenState_Main_Menu( struct sGame* nGame )
{
  // continue (falls verf.)
  // new game
  // highscores
  // regeln
  // optionen (falls kein gast)
    // highscore zurücksetzen
    // benutzer löschen

  wclear( nGame->whnd );

  struct sFieldDef form_fields[ 6 ];

  // continue
  form_fields[ 0 ].position.x = 0;
  form_fields[ 0 ].position.y = 0;
  form_fields[ 0 ].dimension.x = 16;
  form_fields[ 0 ].dimension.y = 1;
  form_fields[ 0 ].type = INPUT_BUTTON;
  form_fields[ 0 ].label = "Spiel fortsetzen";
  form_fields[ 0 ].isDisabled = 1;
  form_fields[ 0 ].btnCallback = BtnCallback_OnContinueGame;

  // new game
  form_fields[ 1 ].position.x = 0;
  form_fields[ 1 ].position.y = 1;
  form_fields[ 1 ].dimension.x = 11;
  form_fields[ 1 ].dimension.y = 1;
  form_fields[ 1 ].type = INPUT_BUTTON;
  form_fields[ 1 ].label = "Neues Spiel";
  form_fields[ 1 ].isDisabled = 0;
  form_fields[ 1 ].btnCallback = BtnCallback_OnStartNewGame;

  // highscores
  form_fields[ 2 ].position.x = 0;
  form_fields[ 2 ].position.y = 2;
  form_fields[ 2 ].dimension.x = 10;
  form_fields[ 2 ].dimension.y = 1;
  form_fields[ 2 ].type = INPUT_BUTTON;
  form_fields[ 2 ].label = "Highscores";
  form_fields[ 2 ].isDisabled = 0;
  form_fields[ 2 ].btnCallback = BtnCallback_OnDisplayHighscores;

  // regeln
  form_fields[ 3 ].position.x = 0;
  form_fields[ 3 ].position.y = 3;
  form_fields[ 3 ].dimension.x = 11;
  form_fields[ 3 ].dimension.y = 1;
  form_fields[ 3 ].type = INPUT_BUTTON;
  form_fields[ 3 ].label = "Spielregeln";
  form_fields[ 3 ].isDisabled = 0;
  form_fields[ 3 ].btnCallback = BtnCallback_OnDisplayRules;

  // optionen
  form_fields[ 4 ].position.x = 0;
  form_fields[ 4 ].position.y = 4;
  form_fields[ 4 ].dimension.x = 8;
  form_fields[ 4 ].dimension.y = 1;
  form_fields[ 4 ].type = INPUT_BUTTON;
  form_fields[ 4 ].label = "Optionen";
  form_fields[ 4 ].isDisabled = 0;
  form_fields[ 4 ].btnCallback = BtnCallback_OnDisplayOptions;

  // spiel beenden
  form_fields[ 5 ].position.x = 0;
  form_fields[ 5 ].position.y = 5;
  form_fields[ 5 ].dimension.x = 13;
  form_fields[ 5 ].dimension.y = 1;
  form_fields[ 5 ].type = INPUT_BUTTON;
  form_fields[ 5 ].label = "Spiel beenden";
  form_fields[ 5 ].isDisabled = 0;
  form_fields[ 5 ].btnCallback = BtnCallback_OnQuitGame;

  // disable options if guest
  if ( nGame->user.isGuest )
  {
    form_fields[ 0 ].isDisabled = 1;
    form_fields[ 4 ].isDisabled = 1;
  }

  // the form itself
  struct sFieldSet menu_form;

  menu_form.fields = &form_fields[ 0 ];
  menu_form.label = "Hauptmenü";
  menu_form.activeFieldId = 1;
  menu_form.numFields = 6;
  menu_form.renderBorder = 1;
  menu_form.dimension = Forms_GetFieldSetDimensions( &menu_form );

  menu_form.position.x = getmaxx( nGame->whnd ) / 2 - menu_form.dimension.x / 2;
  menu_form.position.y = getmaxy( nGame->whnd ) / 2 - menu_form.dimension.y / 2;

  Forms_RenderFieldSet( nGame->whnd, &menu_form );
  Forms_HandleFieldSetInput( nGame, &menu_form );
  Forms_FreeFieldSet( &menu_form );
}

void BtnCallback_OnContinueGame( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  // TBD
}

void BtnCallback_OnStartNewGame( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  nGame->prevScreenState = nGame->screenState;
  nGame->screenState = SCREEN_DIFFICULTY;
}

void BtnCallback_OnDisplayHighscores( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  nGame->prevScreenState = nGame->screenState;
  nGame->screenState = SCREEN_HIGHSCORE;
}

void BtnCallback_OnDisplayRules( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  nGame->prevScreenState = nGame->screenState;
  nGame->screenState = SCREEN_RULES;
}

void BtnCallback_OnDisplayOptions( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  nGame->prevScreenState = nGame->screenState;
  nGame->screenState = SCREEN_OPTIONS;
}

void BtnCallback_OnQuitGame( struct sGame * nGame, struct sFieldSet* nFieldSet )
{
  nGame->flags.isRunning = 0;
}