#pragma once

#include "lib/pdcurses/panel.h"
#include "utility.h"
#include "gamestate.h"


void State_Login( struct sGame* nGame )
{

  unsigned char maxX = getmaxy( nGame->window );
  unsigned char maxY = getmaxx( nGame->window );
  unsigned char username[ 16 ];
  unsigned char password[ 16 ];

  // string in background
  mvaddstr( 1, 1, TITLE " " VERSION );
  mvaddstr( maxX - 2, 1, AUTHOR );

  // create a new window on top
  // height, width, ypos, xpos
  WINDOW* loginWindow = subwin( nGame->window, 10, 34, maxX / 2 - 5, maxY / 2 - 18 );

  // clear the contents, so the background will not show through
  wclear( loginWindow );

  // draw a box around it so it feels more like a window
  box( loginWindow, WA_VERTICAL, WA_HORIZONTAL );

  // window title - again, y,x coords
  mvwaddstr( loginWindow, 1, 2, "Login" );
  mvwhline( loginWindow, 2, 2, WA_HORIZONTAL, 30 );

  mvwaddstr( loginWindow, 4, 6, "User: " );
  mvwaddstr( loginWindow, 5, 2, "Password: " );
  mvwhline( loginWindow, 7, 2, WA_HORIZONTAL, 30 );

  mvwaddstr( loginWindow, 8, 2, "Enter" );
  mvwaddstr( loginWindow, 8, 8, "|" );
  mvwaddstr( loginWindow, 8, 10, "Play as a Guest" );
  mvwaddstr( loginWindow, 8, 26, "|" );
  mvwaddstr( loginWindow, 8, 28, "Quit" );

  // enable visible, blinking caret
  curs_set( 1 );

  // enable echo
  echo();

  // place cursor inside password field
  wmove( loginWindow, 4, 12 );

  // refresh the window
  wrefresh( loginWindow );


  // NOTE
  // The following part could probably be moved into a separate routine later on.
  // Since pdcurses doesn't support forms, the entire thing has to be emulated,
  // which might get pretty messy.


  //  handle any user input until we can take some sort of action
  u8 loop = 1;
  do
  {
    int key = WGetKeyCode( loginWindow );

    if ( key >= 0x20 && key <= 0x7E )
    {
      // handle character input (everything between space and tilde)

    }
    else
    {
      // handle special keys, such as tab, enter or space

      switch ( key )
      {
      case 0x1B: // 0x1B == ESC-Key
                 // quit the game
        loop = 0;
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
  while ( loop );

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
