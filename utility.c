
/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include "utility.h"

/*
	===========================================================================
	Funktion: Utility_GetKeyCode
	Übergabeparameter: -
	Rückgabeparameter: getch()
	Beschreibung:
	===========================================================================
*/

int Utility_GetKeyCode()
{
  return getch();
}

/*
	===========================================================================
	Funktion: Utility_WGetKeyCode
	Übergabeparameter: nTarget
	Rückgabeparameter: wgetch(nTarget)
	Beschreibung:
	===========================================================================
*/

int Utility_WGetKeyCode( WINDOW* nTarget )
{
  return wgetch( nTarget );
}

/*
	===========================================================================
	Funktion: Utility_HandleGlobalInput
	Übergabeparameter: nGame
	Rückgabeparameter: -
	Beschreibung: Wird eine bestimmte Taste gedrückt, wird eine Funktion
				  ausgeführt.
	===========================================================================
*/

void Utility_HandleGlobalInput( struct sGame* nGame )
{

  while ( 1 )
  {
    int key = Utility_GetKeyCode();
    switch ( key )
    {
    case 0x1B: // ESC
      nGame->isRunning = 0;
      break;
    case 0x68: // h
      printf( "help" );
      break;
    }
  }

}

/*
	===========================================================================
	Funktion: Utility_GetWindowDimensions
	Übergabeparameter: nTarget
	Rückgabeparameter: d
	Beschreibung: 
	===========================================================================
*/

struct sVec2 Utility_GetWindowDimensions( WINDOW* nTarget )
{
  struct sVec2 d;

  d.x = getmaxx( nTarget );
  d.y = getmaxy( nTarget );

  return d;
}