#include "utility.h"


int GetKeyCosde()
{
  return getch();
}

int WGetKeyCode( WINDOW* nTarget )
{
  return wgetch( nTarget );
}