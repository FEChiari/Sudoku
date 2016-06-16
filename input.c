
/*
	===========================================================================
	Pr�prozessorkonstanten
	===========================================================================
*/

#include "input.h"

/*
	===========================================================================
	Funktion: GetKey
	�bergabeparameter: nGame, handleInput
	R�ckgabeparameter: -
	Beschreibung: Wird eine bestimmte Taste gedr�ckt, wird eine entsprechende
				  Funktion ausgel�st
	===========================================================================
*/

void GetKey(struct sGame *nGame, u8* handleInput)
{
    int key = Utility_WGetKeyCode( nGame->whnd );

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