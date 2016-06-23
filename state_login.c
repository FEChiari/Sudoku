/*
  ===========================================================================
  Pr�prozessorkonstanten
  ===========================================================================
*/

#include "screenstate.h"

/*
  ===========================================================================
  Funktion: State_Login
  �bergabeparameter: nGame
  R�ckgabeparameter: -
  Beschreibung: Baut ein Login-Fenster mit Textfeldern und Buttons auf.
  ===========================================================================
*/
void ScreenState_Login( struct sGame* nGame )
{
  wclear( nGame->whnd );

  struct sFieldDef form_fields[ 7 ];

  // username
  form_fields[ 0 ].position.x = 0;
  form_fields[ 0 ].position.y = 0;
  form_fields[ 0 ].dimension.x = 23;
  form_fields[ 0 ].dimension.y = 1;
  form_fields[ 0 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 0 ].label = "Benutzer:";
  form_fields[ 0 ].inputSize = 13;
  form_fields[ 0 ].isDisabled = 1;
  // password
  form_fields[ 1 ].position.x = 0;
  form_fields[ 1 ].position.y = 1;
  form_fields[ 1 ].dimension.x = 23;
  form_fields[ 1 ].dimension.y = 1;
  form_fields[ 1 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 1 ].label = "Password:";
  form_fields[ 1 ].inputSize = 13;
  form_fields[ 1 ].isDisabled = 1;

  // button enter
  form_fields[ 2 ].position.x = 0;
  form_fields[ 2 ].position.y = 3;
  form_fields[ 2 ].dimension.x = 5;
  form_fields[ 2 ].dimension.y = 1;
  form_fields[ 2 ].type = INPUT_BUTTON;
  form_fields[ 2 ].label = "Login";
  form_fields[ 2 ].btnCallback = BtnCallback_OnLogin;
  form_fields[ 2 ].isDisabled = 1;

  // button play-as-guest
  form_fields[ 3 ].position.x = 6;
  form_fields[ 3 ].position.y = 3;
  form_fields[ 3 ].dimension.x = 4;
  form_fields[ 3 ].dimension.y = 1;
  form_fields[ 3 ].type = INPUT_BUTTON;
  form_fields[ 3 ].label = "Gast";
  form_fields[ 3 ].btnCallback = BtnCallback_OnPlayAsGuest;
  form_fields[ 3 ].isDisabled = 0;

  // button register
  form_fields[ 4 ].position.x = 11;
  form_fields[ 4 ].position.y = 3;
  form_fields[ 4 ].dimension.x = 12;
  form_fields[ 4 ].dimension.y = 1;
  form_fields[ 4 ].type = INPUT_BUTTON;
  form_fields[ 4 ].label = "Registrieren";
  form_fields[ 4 ].btnCallback = BtnCallback_OnRegister;
  form_fields[ 4 ].isDisabled = 1;

  // the form itself
  struct sFieldSet login_form;

  login_form.fields = &form_fields[ 0 ];
  login_form.label = "Login";
  login_form.activeFieldId = 3;
  login_form.numFields = 5;
  login_form.renderBorder = 1;
  login_form.dimension = Forms_GetFieldSetDimensions( &login_form );
  login_form.position.x = getmaxx( nGame->whnd ) / 2 - login_form.dimension.x / 2;
  login_form.position.y = getmaxy( nGame->whnd ) / 2 - login_form.dimension.y / 2;

  Forms_RenderFieldSet( nGame->whnd, &login_form );
  Forms_HandleFieldSetInput( nGame, &login_form );
  Forms_FreeFieldSet( &login_form );
}

void BtnCallback_OnLogin( struct sGame* nGame )
{

}

void BtnCallback_OnRegister( struct sGame* nGame )
{

}

void BtnCallback_OnPlayAsGuest( struct sGame* nGame )
{
  nGame->prevScreenState = nGame->screenState;
  nGame->screenState = SCREEN_MAIN_MENU;
  nGame->user.isGuest = 1;
  strcpy(nGame->user.username, "Gast");
}