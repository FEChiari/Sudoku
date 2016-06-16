
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

void State_Main_Menu( struct sGame* nGame )
{
  // continue (falls verf.)
  // new game
  // highscores
  // regeln
  // optionen (falls kein gast)
    // highscore zurücksetzen
    // benutzer löschen

  wclear( nGame->whnd );

  struct sVec2 menuDimensions;
  menuDimensions.x = 20;
  menuDimensions.y = 10;

  WINDOW* menuContainer = subwin( nGame->whnd, menuDimensions.y, menuDimensions.x, getmaxy(nGame->whnd) / 2 - menuDimensions.y / 2, getmaxx( nGame->whnd ) / 2 - menuDimensions.x / 2 );
  box( menuContainer, WA_VERTICAL, WA_HORIZONTAL );

  wrefresh( nGame->whnd );

  u8 handleInput = 1;
  do
  {

  }
  while ( handleInput );

}