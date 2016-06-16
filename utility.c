
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