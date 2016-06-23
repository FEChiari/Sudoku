
/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include "screenstate.h"

/*
===========================================================================
Funktion: ScreenState_Difficulty
Übergabeparameter: nGame
Rückgabeparameter: -
Beschreibung: Warte auf Code!
===========================================================================
*/

void ScreenState_Difficulty(struct sGame* nGame)
{

	wclear(nGame->whnd);

	struct sFieldDef form_fields[4];

	// continue
	form_fields[0].position.x = 0;
	form_fields[0].position.y = 0;
	form_fields[0].dimension.x = 16;
	form_fields[0].dimension.y = 1;
	form_fields[0].type = INPUT_BUTTON;
	form_fields[0].label = "Leicht";
	form_fields[0].isDisabled = 0;
	form_fields[0].btnCallback = BtnCallback_OnLeicht;

	// new game
	form_fields[1].position.x = 0;
	form_fields[1].position.y = 1;
	form_fields[1].dimension.x = 16;
	form_fields[1].dimension.y = 1;
	form_fields[1].type = INPUT_BUTTON;
	form_fields[1].label = "Normal";
	form_fields[1].isDisabled = 0;
	form_fields[1].btnCallback = BtnCallback_OnNormal;

	// highscores
	form_fields[2].position.x = 0;
	form_fields[2].position.y = 2;
	form_fields[2].dimension.x = 16;
	form_fields[2].dimension.y = 1;
	form_fields[2].type = INPUT_BUTTON;
	form_fields[2].label = "Schwer";
	form_fields[2].isDisabled = 0;
	form_fields[2].btnCallback = BtnCallback_OnSchwer;

	// regeln
	form_fields[3].position.x = 0;
	form_fields[3].position.y = 3;
	form_fields[3].dimension.x = 16;
	form_fields[3].dimension.y = 1;
	form_fields[3].type = INPUT_BUTTON;
	form_fields[3].label = "Zurück";
	form_fields[3].isDisabled = 0;
	form_fields[3].btnCallback = BtnCallback_OnZurueck;



	// the form itself
	struct sFieldSet difficulty_form;

	difficulty_form.fields = &form_fields[0];
	difficulty_form.label = "Schwierigkeit";
	difficulty_form.activeFieldId = 1;
	difficulty_form.numFields = 4;
	difficulty_form.renderBorder = 1;
	difficulty_form.dimension = Forms_GetFieldSetDimensions(&difficulty_form);

	difficulty_form.position.x = getmaxx(nGame->whnd) / 2 - difficulty_form.dimension.x / 2;
	difficulty_form.position.y = getmaxy(nGame->whnd) / 2 - difficulty_form.dimension.y / 2;

	Forms_RenderFieldSet(nGame->whnd, &difficulty_form);
	Forms_HandleFieldSetInput(nGame, &difficulty_form);
	Forms_FreeFieldSet(&difficulty_form);
}



void BtnCallback_OnLeicht(struct sGame * nGame)
{
	nGame->gameState.difficultyLvl = DIFFICULTY_EASY;
	nGame->prevScreenState = nGame->screenState;
	nGame->screenState = SCREEN_INGAME;
	nGame->gameState.timePlayed = 0;
	//generiereSudoku( nGame->gameState.field );
}

void BtnCallback_OnNormal(struct sGame * nGame)
{
	nGame->gameState.difficultyLvl = DIFFICULTY_MEDIUM;
	nGame->prevScreenState = nGame->screenState;
	nGame->screenState = SCREEN_INGAME;
	nGame->gameState.timePlayed = 0;
	//generiereSudoku( nGame->gameState.field );
}

void BtnCallback_OnSchwer(struct sGame * nGame)
{
	nGame->gameState.difficultyLvl = DIFFICULTY_VHARD;
	nGame->prevScreenState = nGame->screenState;
	nGame->screenState = SCREEN_INGAME;
	nGame->gameState.timePlayed = 0;
	//generiereSudoku( nGame->gameState.field );
}

void BtnCallback_OnZurueck(struct sGame * nGame)
{
	nGame->prevScreenState = nGame->screenState;
	nGame->screenState = SCREEN_MAIN_MENU;
}

