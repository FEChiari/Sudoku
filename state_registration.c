/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include "screenstate.h"

/*
===========================================================================
Funktion: State_Registration
Übergabeparameter: nGame
Rückgabeparameter: -
Beschreibung: Baut ein Registrierungs-Fenster mit Textfeldern und Buttons auf.
===========================================================================
*/
void ScreenState_Registration( struct sGame* nGame )
{
    wclear(nGame->whnd);

    struct sFieldDef form_fields[6];

    // username label
    form_fields[0].position.x = 0;
    form_fields[0].position.y = 0;
    form_fields[0].dimension.x = 10;
    form_fields[0].dimension.y = 1;
    form_fields[0].type = STATIC_TEXT;
    form_fields[0].label = "Benutzer:";
    form_fields[0].isDisabled = 1;

    // username input
    form_fields[1].position.x = 10;
    form_fields[1].position.y = 0;
    form_fields[1].dimension.x = 13;
    form_fields[1].dimension.y = 1;
    form_fields[1].type = INPUT_LOWERALPHA_NUMERIC;
    form_fields[1].label = "";
    form_fields[1].isDisabled = 0;

    // password label
    form_fields[2].position.x = 0;
    form_fields[2].position.y = 1;
    form_fields[2].dimension.x = 10;
    form_fields[2].dimension.y = 1;
    form_fields[2].type = STATIC_TEXT;
    form_fields[2].label = "Password:";
    form_fields[2].isDisabled = 1;

    // password input
    form_fields[3].position.x = 10;
    form_fields[3].position.y = 1;
    form_fields[3].dimension.x = 13;
    form_fields[3].dimension.y = 1;
    form_fields[3].type = INPUT_LOWERALPHA_NUMERIC;
    form_fields[3].label = "";
    form_fields[3].isDisabled = 0;
    form_fields[3].isPWField = 1;

    // button enter
    form_fields[4].position.x = 0;
    form_fields[4].position.y = 3;
    form_fields[4].dimension.x = 12;
    form_fields[4].dimension.y = 1;
    form_fields[4].type = INPUT_BUTTON;
    form_fields[4].label = "Registrieren";
    form_fields[4].btnCallback = BtnCallback_OnRegisterUser;
    form_fields[4].isDisabled = 0;

    // button play-as-guest
    form_fields[5].position.x = 14;
    form_fields[5].position.y = 3;
    form_fields[5].dimension.x = 9;
    form_fields[5].dimension.y = 1;
    form_fields[5].type = INPUT_BUTTON;
    form_fields[5].label = "Abbrechen";
    form_fields[5].btnCallback = BtnCallback_OnCancel;
    form_fields[5].isDisabled = 0;


    // the form itself
    struct sFieldSet registration_form;

    registration_form.fields = &form_fields[0];
    registration_form.label = "Registration";
    registration_form.activeFieldId = 1;
    registration_form.numFields = 6;
    registration_form.renderBorder = 1;
    registration_form.dimension = Forms_GetFieldSetDimensions(&registration_form);
    registration_form.position.x = getmaxx(nGame->whnd) / 2 - registration_form.dimension.x / 2;
    registration_form.position.y = getmaxy(nGame->whnd) / 2 - registration_form.dimension.y / 2;

    Forms_RenderFieldSet(nGame->whnd, &registration_form);
    Forms_HandleFieldSetInput(nGame, &registration_form);
    Forms_FreeFieldSet(&registration_form);
}

void BtnCallback_OnRegisterUser(struct sGame* nGame, struct sFieldSet* nFieldSet )
{

}

void BtnCallback_OnCancel(struct sGame* nGame, struct sFieldSet* nFieldSet)
{
    nGame->prevScreenState = nGame->screenState;
    nGame->screenState = SCREEN_LOGIN;
}