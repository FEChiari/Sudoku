#include "game.h"


void init(struct sGame* nGame)
{

  nGame->isRunning = 1;
  nGame->state = LOGIN;

  if ( ( nGame->window = initscr() ) == NULL )
    printf( "[Fatal] Failed to initialize curses" );

  curs_set( 0 );
  noecho();
  nodelay( nGame->window, TRUE );
  keypad( nGame->window, TRUE );
}

int main( int argc, char* argv[] )
{

  struct sGame g;

  init( &g );



  while ( g.isRunning )
  {
    switch ( g.state )
    {
    case LOGIN:
      State_Login( &g );
      break;
    }
  }

}