/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "game.h"

// TODO@FE: Forms
// TODO@FE: Clock/Timekeeping
// TODO@FE: Cleanup/align conventions
// TODO@FE: Ensure code conforms to c89 before handoff!

// This is global so that it doesn't have to be passed to every
// single db-related function. It's initialized in main, so we
// just put it here instead of using a workaround for a non-problem.
sqlite3* DBH_dbhnd = NULL;

/*
  ===========================================================================
  Funktionsprototypen
  ===========================================================================
*/

// Game initialization.
// This ensures that the game *can* run, meaning the db is present
// and curses is working as intended.
void initialize( struct sGame* nGame );

// Game termination.
// This ensures that the game is terminated properly, regardless of
// its current state.
void terminate( struct sGame* nGame );

/*
  ===========================================================================
  Funktion: main
  Übergabeparameter: argc, argv
  Rückgabeparameter: -
  Beschreibung: Initialisiert die Fenster. Dabei wird das entsprechende 
          Fenster selektiert.
  ===========================================================================
*/

int main( int argc, char* argv[] )
{
  // This struct stores everything relevant to the current session,
  // such as screenstate, userdata and so on.
  struct sGame g;

  initialize( &g );

  // Main game-loop
  // - Switches between screenstates and calls the apropriate function.
  // - That function, in turn, handles and updates the gamestate.
  while ( g.isRunning )
  {
    switch ( g.screenState )
    {
    case SCREEN_LOGIN:
      State_Login( &g );
      break;
    case SCREEN_MAIN_MENU:
      State_Main_Menu( &g );
      break;
    case SCREEN_REGISTRATION:
      // TODO@FE: check whether this warrants an entire state
      break;
    case SCREEN_INGAME:
      State_Ingame( &g );
      break;
    case SCREEN_HIGHSCORE:
      State_Highscore( &g );
      break;
    }
  }

  terminate( &g );
}

/*
  ===========================================================================
  Funktion: initialize
  Übergabeparameter: nGame
  Rückgabeparameter: -
  Beschreibung:
  ===========================================================================
*/

void initialize( struct sGame* nGame )
{
  nGame->isRunning = 1;
  nGame->screenState = SCREEN_HIGHSCORE;
  nGame->prevScreenState = nGame->screenState;
  nGame->difficulty = DIFFICULTY_EASY;

  if ( ( nGame->whnd = initscr() ) == NULL )
  {
    printf( "[Fatal] Failed to initialize curses" "\n" );
    terminate( nGame );
    exit( EXIT_FAILURE );
  }

  resize_term( 30, 120 );

  DBH_dbhnd = DBH_CreateHandle( DBH_DATABASE_FILE );

  if ( DBH_dbhnd == NULL )
  {
    printf( "[Fatal] Failed to access database file '" DBH_DATABASE_FILE "'" "\n" );
    terminate( nGame );
    exit( EXIT_FAILURE );
  }

  // set some defaults
  // - no cursor
  // - no echo when typing
  // - no input delay
  // - activate keypad
  curs_set( 0 );
  noecho();
  nodelay( nGame->whnd, TRUE );
  keypad( nGame->whnd, TRUE );
}

/*
  ===========================================================================
  Funktion: terminate
  Übergabeparameter: nGame
  Rückgabeparameter: -
  Beschreibung: Beendet die laufenden Fenster.
  ===========================================================================
*/

void terminate( struct sGame* nGame )
{
  if ( DBH_dbhnd != NULL )
    DBH_CloseHandle( DBH_dbhnd );

  if ( nGame->whnd != NULL )
  {
    delwin( nGame->whnd );
    endwin();
  }
}