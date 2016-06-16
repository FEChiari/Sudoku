
/*
	===========================================================================
	Pr�prozessorkonstanten
	===========================================================================
*/

#include "utility.h"

/*
	===========================================================================
	Funktion: Utility_GetKeyCode
	�bergabeparameter: -
	R�ckgabeparameter: getch()
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
	�bergabeparameter: nTarget
	R�ckgabeparameter: wgetch(nTarget)
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
	�bergabeparameter: nGame
	R�ckgabeparameter: -
	Beschreibung: Wird eine bestimmte Taste gedr�ckt, wird eine Funktion
				  ausgef�hrt.
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
	�bergabeparameter: nTarget
	R�ckgabeparameter: d
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