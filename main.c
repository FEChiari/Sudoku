#include "game.h"


void init( struct sGame* nGame )
{
  nGame->isRunning = 1;
  nGame->state = LOGIN;

  if ( ( nGame->window = initscr() ) == NULL )
  {
    printf( "[Fatal] Failed to initialize curses" );
    exit( EXIT_FAILURE );
  }

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
    case MAIN_MENU:
      State_Main_Menu( &g );
      break;
    case REGISTRATION:
      State_Main_Menu( &g );
      break;
    case INGAME:
      State_Ingame( &g );
      break;
    case HIGHSCORE:
      State_Highscore( &g );
      break;
    }
  }

}