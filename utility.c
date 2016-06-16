
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