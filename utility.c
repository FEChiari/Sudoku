
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