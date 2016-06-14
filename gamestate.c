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
  //wmove( login_form.fields[ login_form.activeFieldId ].whnd, 
  //  login_form.fields[ login_form.activeFieldId ].position.y,
  //  login_form.fields[ login_form.activeFieldId ].position.x
  //);

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











































  //unsigned char maxX = getmaxy( nGame->window );
  //unsigned char maxY = getmaxx( nGame->window );

  //// string in background
  //mvaddstr( 1, 1, TITLE " " VERSION );
  //mvaddstr( maxX - 2, 1, AUTHOR );

  //// create a new window on top
  //// height, width, ypos, xpos
  //WINDOW* loginWindow = subwin( nGame->window, 10, 34, maxX / 2 - 5, maxY / 2 - 18 );

  //// clear the contents, so the background will not show through
  //wclear( loginWindow );

  //// draw a box around it so it feels more like a window
  //box( loginWindow, WA_VERTICAL, WA_HORIZONTAL );

  //// window title - again, y,x coords
  //mvwaddstr( loginWindow, 1, 2, "Login" );
  //mvwhline( loginWindow, 2, 2, WA_HORIZONTAL, 30 );

  //mvwaddstr( loginWindow, 4, 6, "User: " );
  //mvwaddstr( loginWindow, 5, 2, "Password: " );
  //mvwhline( loginWindow, 7, 2, WA_HORIZONTAL, 30 );

  //mvwaddstr( loginWindow, 8, 2, "Enter" );
  //mvwaddstr( loginWindow, 8, 8, "|" );
  //mvwaddstr( loginWindow, 8, 10, "Play as a Guest" );
  //mvwaddstr( loginWindow, 8, 26, "|" );
  //mvwaddstr( loginWindow, 8, 28, "Quit" );

  //// enable visible, blinking caret
  //curs_set( 1 );

  //// enable echo
  //echo();

  //// place cursor inside password field
  //wmove( loginWindow, 4, 12 );

  //// refresh the window
  //wrefresh( loginWindow );

  //// NOTE
  //// The following part could probably be moved into a separate routine later on.
  //// Since pdcurses doesn't support forms, the entire thing has to be emulated,
  //// which might get pretty messy.


  ////  handle any user input until we can take some sort of action
  ////u8 loop = 1;
  ////do
  ////{
  ////  int key = WGetKeyCode( loginWindow );

  ////  if ( key >= 0x20 && key <= 0x7E )
  ////  {
  ////    // handle character input (everything between space and tilde)

  ////  }
  ////  else
  ////  {
  ////    // handle special keys, such as tab, enter or space

  ////    switch ( key )
  ////    {
  ////    case 0x1B: // 0x1B == ESC-Key
  ////               // quit the game
  ////      loop = 0;
  ////      nGame->isRunning = 0;
  ////      break;
  ////    case 0x09: // 0x09 == TAB-Key
  ////               // switch fields
  ////      break;

  ////    case 0x0A: // 0x0A == ENTER-Key
  ////               // commit input
  ////      break;
  ////    }

  ////  }

  ////}
  ////while ( loop );

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
