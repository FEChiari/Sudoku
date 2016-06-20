/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include "screenstate.h"


/*
===========================================================================
Funktion: State_Ingame
Übergabeparameter: nGame
Rückgabeparameter: -
Beschreibung: Warte auf Code!
===========================================================================
*/
void ScreenState_Ingame( struct sGame* nGame )
{

  wclear( nGame->whnd );

  WINDOW* statusbar_container = derwin( nGame->whnd, nGame->whnd->_begy + 3, nGame->whnd->_maxx - 8, 2, 4 );
  box( statusbar_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* statusbar_inner = derwin( statusbar_container, 1, statusbar_container->_maxx - 2, 1, 1 );

  mvwaddstr( statusbar_inner, 0, 1, "Spielzeit: " );

  char* player_text = malloc( 64 );
  memset( player_text, 0, 64 );
  sprintf( player_text, "Spieler: %s", nGame->user.username );

  mvwaddstr( statusbar_inner, 0, statusbar_inner->_maxx - strlen( player_text ) - 1, player_text );

  WINDOW* left_container = derwin( nGame->whnd, nGame->whnd->_maxy - 9, nGame->whnd->_maxx - 39, statusbar_container->_maxy + 2, nGame->whnd->_begx + 4 );
  box( left_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* left_inner = derwin( left_container, left_container->_maxy - 2, left_container->_maxx - 2, 1, 1 );

  WINDOW* right_container = derwin( nGame->whnd, left_container->_maxy, 31, statusbar_container->_maxy + 2, left_container->_maxx + 4 );
  box( right_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* right_inner = derwin( right_container, right_container->_maxy - 2, right_container->_maxx - 2, 1, 1 );

  mvwaddstr( right_inner, 0, 1, "Hotkeys" );
  mvwaddstr( right_inner, 2, 1, "LEER - Zahl vorschlagen" );
  mvwaddstr( right_inner, 4, 4, "H - Regeln" );
  mvwaddstr( right_inner, 6, 2, "DEL - Ausgewähltes Feld" );
  mvwaddstr( right_inner, 7, 8, "löschen" );

  mvwaddstr( nGame->whnd, right_container->_begy + right_container->_maxy + 1, right_container->_begx + right_container->_maxx - 15, "ESC: Hauptmenü" );

  Ingame_RenderField( left_inner, 2, 1, &nGame->gameState.field[ 0 ][ 0 ] );
  
  u8 playing = 1;
  time_t time_then = time( NULL ) - nGame->gameState.timePlayed;

  while ( playing )
  {
    u8 handleInput = 1;
    do
    {
      char timeString[ 12 ];

      if ( nGame->gameState.timePlayed >= 3600 )
      {
        sprintf( timeString, "%.2dh %.2dm %.2ds", ( u8 ) nGame->gameState.timePlayed / 3600, ( u8 ) nGame->gameState.timePlayed / 60, ( u8 ) nGame->gameState.timePlayed % 60 );
      }
      else if ( nGame->gameState.timePlayed >= 60 )
      {
        sprintf( timeString, "%.2dm %.2ds", ( u8 ) nGame->gameState.timePlayed / 60, ( u8 ) nGame->gameState.timePlayed % 60 );
      }
      else
      {
        sprintf( timeString, "%.2ds", ( u8 ) nGame->gameState.timePlayed );
      }
      mvwaddstr( statusbar_inner, 0, 12, timeString );
      wrefresh( statusbar_inner );




      char key = Utility_WGetKeyCode( nGame->whnd );

      switch ( key )
      {
      case 0x03: // up-arrow key

        break;
      case 0x05: // right-arrow key

        break;
      case 0x02: // down-arrow key

        break;
      case 0x04: // left-arrow key

        break;
      case 0x1B: // ESC-key
        handleInput = 0;
        playing = 0;
        nGame->screenState = nGame->prevScreenState;
        nGame->prevScreenState = SCREEN_INGAME;
        break;
      }

      // catch all numerical keys, top-row and numblock
      if ( key >= 0x30 && key <= 0x39 || key >= 0x60 && key <= 0x69 )
      {

      }

      nGame->gameState.timePlayed = (u8) difftime(time(NULL), time_then);

    }
    while ( handleInput );
  }

  free( player_text );

  delwin( statusbar_inner );
  delwin( statusbar_container );

  delwin( left_inner );
  delwin( left_container );

  delwin( right_inner );
  delwin( right_container );
}

void Ingame_RenderField( WINDOW* nTargetWindow, u8 nXOffset, u8 nYOffset, struct sSudokuField* nFields )
{

  mvwaddstr( nTargetWindow, 0 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 1 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 2 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 3 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 4 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );

  mvwaddstr( nTargetWindow, 6 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 7 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 8 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 9 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 10 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );

  mvwaddstr( nTargetWindow, 12 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 13 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 14 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );
  mvwaddstr( nTargetWindow, 15 + nYOffset, 0 + nXOffset, "                                     " );
  mvwaddstr( nTargetWindow, 16 + nYOffset, 0 + nXOffset, " 9   9   9   9   9   9   9   9   9 " );

  // render the gridlines

  mvwhline( nTargetWindow, 5 + nYOffset, 0 + nXOffset, ACS_HLINE, 11 );
  mvwhline( nTargetWindow, 5 + nYOffset, 11 + nXOffset, ACS_PLUS, 1 );
  mvwhline( nTargetWindow, 5 + nYOffset, 12 + nXOffset, ACS_HLINE, 11 );
  mvwhline( nTargetWindow, 5 + nYOffset, 23 + nXOffset, ACS_PLUS, 1 );
  mvwhline( nTargetWindow, 5 + nYOffset, 24 + nXOffset, ACS_HLINE, 11 );

  mvwhline( nTargetWindow, 11 + nYOffset, 0 + nXOffset, ACS_HLINE, 11 );
  mvwhline( nTargetWindow, 11 + nYOffset, 11 + nXOffset, ACS_PLUS, 1 );
  mvwhline( nTargetWindow, 11 + nYOffset, 12 + nXOffset, ACS_HLINE, 11 );
  mvwhline( nTargetWindow, 11 + nYOffset, 23 + nXOffset, ACS_PLUS, 1 );
  mvwhline( nTargetWindow, 11 + nYOffset, 24 + nXOffset, ACS_HLINE, 11 );

  mvwvline( nTargetWindow, 0 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 1 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 2 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 3 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 4 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );

  mvwvline( nTargetWindow, 0 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 1 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 2 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 3 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 4 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );

  mvwvline( nTargetWindow, 6 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 7 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 8 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 9 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 10 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );

  mvwvline( nTargetWindow, 6 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 7 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 8 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 9 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 10 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );

  mvwvline( nTargetWindow, 12 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 13 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 14 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 15 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 16 + nYOffset, 11 + nXOffset, ACS_VLINE, 1 );

  mvwvline( nTargetWindow, 12 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 13 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 14 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 15 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );
  mvwvline( nTargetWindow, 16 + nYOffset, 23 + nXOffset, ACS_VLINE, 1 );

}