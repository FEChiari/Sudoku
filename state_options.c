/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include "screenstate.h"
void ScreenState_Options(struct sGame* nGame)
{
    // continue (falls verf.)
    // new game
    // highscores
    // regeln
    // optionen (falls kein gast)
    // highscore zurücksetzen
    // benutzer löschen

    wclear(nGame->whnd);

    struct sFieldDef form_fields[3];

    // continue
    form_fields[0].position.x = 0;
    form_fields[0].position.y = 0;
    form_fields[0].dimension.x = 26;
    form_fields[0].dimension.y = 1;
    form_fields[0].type = INPUT_BUTTON;
    form_fields[0].label = "Bestleistung zurücksetzten";
    form_fields[0].isDisabled = 0;
    form_fields[0].btnCallback = BtnCallback_OnResetMyHighscore;

    // new game
    form_fields[1].position.x = 7;
    form_fields[1].position.y = 1;
    form_fields[1].dimension.x = 13;
    form_fields[1].dimension.y = 1;
    form_fields[1].type = INPUT_BUTTON;
    form_fields[1].label = "Konto Löschen";
    form_fields[1].isDisabled = 0;
    form_fields[1].btnCallback = BtnCallback_OnDeleteMyAccount;

    // highscores
    form_fields[2].position.x = 10;
    form_fields[2].position.y = 2;
    form_fields[2].dimension.x = 6;
    form_fields[2].dimension.y = 1;
    form_fields[2].type = INPUT_BUTTON;
    form_fields[2].label = "Zurück";
    form_fields[2].isDisabled = 0;
    form_fields[2].btnCallback = BtnCallback_OnReturnToMainMenu;

    struct sFieldSet options_form;

    options_form.fields = &form_fields[0];
    options_form.label = "Optionen";
    options_form.activeFieldId = 2;
    options_form.numFields = 3;
    options_form.renderBorder = 1;
    options_form.dimension = Forms_GetFieldSetDimensions(&options_form);

    options_form.position.x = getmaxx(nGame->whnd) / 2 - options_form.dimension.x / 2;
    options_form.position.y = getmaxy(nGame->whnd) / 2 - options_form.dimension.y / 2;

    Forms_RenderFieldSet(nGame->whnd, &options_form);
    Forms_HandleFieldSetInput(nGame, &options_form);
    Forms_FreeFieldSet(&options_form);
}


void BtnCallback_OnResetMyHighscore( struct sGame* nGame, struct sFieldSet* nFieldSet )
{

}

void BtnCallback_OnDeleteMyAccount( struct sGame* nGame, struct sFieldSet* nFieldSet )
{

}

void BtnCallback_OnReturnToMainMenu(struct sGame* nGame, struct sFieldSet* nFieldSet )
{
    nGame->prevScreenState = nGame->screenState;
    nGame->screenState = SCREEN_MAIN_MENU;
}

