
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