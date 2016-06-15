#include "utility.h"


int Utility_GetKeyCode()
{
  return getch();
}

int Utility_WGetKeyCode( WINDOW* nTarget )
{
  return wgetch( nTarget );
}

void Utility_HandleGlobalInput( struct sGame* nGame )
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

struct sVec2 Utility_GetWindowDimensions( WINDOW* nTarget )
{
  struct sVec2 d;

  d.x = getmaxx( nTarget );
  d.y = getmaxy( nTarget );

  return d;
}

}