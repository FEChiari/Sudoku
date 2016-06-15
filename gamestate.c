#pragma once

#include "gamestate.h"


void State_Login( struct sGame* nGame )
{

  struct sFieldDef form_fields[ 5 ];

  // username
  form_fields[ 0 ].position.x = 0;
  form_fields[ 0 ].position.y = 0;
  form_fields[ 0 ].dimension.x = 25;
  form_fields[ 0 ].dimension.y = 1;
  form_fields[ 0 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 0 ].label = "Benutzer:";
  form_fields[ 0 ].inputSize = 16;

  // password
  form_fields[ 1 ].position.x = 0;
  form_fields[ 1 ].position.y = 1;
  form_fields[ 1 ].dimension.x = 25;
  form_fields[ 1 ].dimension.y = 1;
  form_fields[ 1 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 1 ].label = "Password:";
  form_fields[ 1 ].inputSize = 16;

  // button enter
  form_fields[ 2 ].position.x = 1;
  form_fields[ 2 ].position.y = 4;
  form_fields[ 2 ].dimension.x = 5;
  form_fields[ 2 ].dimension.y = 1;
  form_fields[ 2 ].type = INPUT_BUTTON;
  form_fields[ 2 ].label = "Login";

  // button play-as-guest
  form_fields[ 3 ].position.x = 7;
  form_fields[ 3 ].position.y = 4;
  form_fields[ 3 ].dimension.x = 4;
  form_fields[ 3 ].dimension.y = 1;
  form_fields[ 3 ].type = INPUT_BUTTON;
  form_fields[ 3 ].label = "Gast";

  // button register
  form_fields[ 4 ].position.x = 12;
  form_fields[ 4 ].position.y = 4;
  form_fields[ 4 ].dimension.x = 12;
  form_fields[ 4 ].dimension.y = 1;
  form_fields[ 4 ].type = INPUT_BUTTON;
  form_fields[ 4 ].label = "Registrieren";

  // the form itself
  struct sFieldSet login_form;
  login_form.fields = &form_fields[ 0 ];
  login_form.label = "Login";
  login_form.activeFieldId = 1;
  login_form.numFields = 5;
  login_form.renderBorder = 1;
  login_form.dimension = Forms_GetFieldSetDimensions( &login_form );
  login_form.position.x = getmaxx( nGame->window ) / 2 - login_form.dimension.x / 2;
  login_form.position.y = getmaxy( nGame->window ) / 2 - login_form.dimension.y / 2;

  Forms_RenderFieldSet( nGame->window, &login_form );



  // enable visible, blinking caret
  curs_set( 1 );

  // enable echo
  echo();

  // place cursor inside first field
  wmove( login_form.fields[ login_form.activeFieldId ].whnd, 0, 10 );
  wrefresh( login_form.fields[ login_form.activeFieldId ].whnd );

  do 
  {
    // FIXME@FE: WGetKeyCode resets cursor position
  } while ( 1 );



  // handle any user input until we can take some sort of action
  u8 handleInput = 1;
  do
  {
    int key = WGetKeyCode( nGame->window );
    int key = Utility_WGetKeyCode( nGame->window );

    if ( key >= 0x20 && key <= 0x7E )
    {
       //handle character input (everything between space and tilde)
    }
    else
    {
      // handle special keys, such as tab, enter or space
      switch ( key )
      {
      case 0x1B: // 0x1B == ESC-Key
                 // quit the game
        handleInput = 0;
        nGame->isRunning = 0;
        break;
      case 0x09: // 0x09 == TAB-Key
                 // switch fields
        break;

      case 0x0A: // 0x0A == ENTER-Key
                 // commit input
        break;
      }

    }

  }
  while ( handleInput );

}

void State_Main_Menu( struct sGame* nGame )
{
  // here be dragons
}

void State_Ingame( struct sGame* nGame )
{
  // here be dragons
}

void State_Highscore( struct sGame* nGame )
{
  // here be dragons
}
