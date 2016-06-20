/*
  ===========================================================================
  Programmname: Sudoku
  Autoren: Waldemar Werba, Fabian Engels, Fabian Kremer, Patrick Schorn,
           Fabian Prinz
  Datum: 19.06.2016
  IDE: Visual Studio
  Beschreibung: Dieses Programm ist ein Sudoku-Spiel, welches ermöglicht,
                in einer Konsole ein zufällig generiertes Sudoku zu lösen.
                Dabei ist es möglich, sich zu registrieren, um die 
                Highscore-Funktion zu nutzen. Es ist auch möglich, ohne
                Login zu spielen, doch dadurch wird es nicht möglich sein, 
                die Highscore-Funktion zu nutzen. Diese Funktionen werden 
                durch eine Datenbank ermöglicht. Das Spiel kann in drei
                verschiedenen Schwierigkeitsgraden gespielt werden.
  ===========================================================================
*/

/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "game.h"

#ifdef _WIN32
#define MOUSE_MOVED_CURSES MOUSE_MOVED
#undef MOUSE_MOVED
#include <consoleapi.h>
#undef MOUSE_MOVED
#define MOUSE_MOVED MOUSE_MOVED_CURSES
#endif

#define DEFAULT_GAMESTATE SCREEN_LOGIN
#define DEFAULT_DIFFICULTY DIFFICULTY_EASY

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
  while ( g.flags.isRunning )
  {
    switch ( g.screenState )
    {
    case SCREEN_LOGIN:
      ScreenState_Login( &g );
      break;
    case SCREEN_MAIN_MENU:
      ScreenState_Main_Menu( &g );
      break;
    case SCREEN_REGISTRATION:
      ScreenState_Registration( &g );
      break;
    case SCREEN_INGAME:
      ScreenState_Ingame( &g );
      break;
    case SCREEN_HIGHSCORE:
      ScreenState_Highscore( &g );
      break;
    case SCREEN_RULES:
      ScreenState_Rules( &g );
      break;
    }
  }

  terminate( &g );

  return EXIT_SUCCESS;
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
  nGame->flags.isRunning = 1;
  nGame->screenState = DEFAULT_GAMESTATE;
  nGame->prevScreenState = nGame->screenState;
  nGame->gameState.difficultyLvl = DEFAULT_DIFFICULTY;
  nGame->gameState.timePlayed = 0;

  if ( ( nGame->whnd = initscr() ) == NULL )
  {
    printf( "[Fatal] Failed to initialize curses" "\n" );
    terminate( nGame );
    exit( EXIT_FAILURE );
  }
  
#ifdef _WIN32
  SetConsoleTitle(GAME_TITLE " - " GAME_VERSION);
#endif

  resize_term( 30, 80);

  if ( has_colors() )
  {
    start_color();
    nGame->flags.color_enabled = 1;
    init_pair( 1, COLOR_WHITE, COLOR_BLACK ); // standard text
    init_pair( 2, COLOR_BLACK, COLOR_WHITE ); // inverted text
    init_pair( 3, COLOR_GREEN, COLOR_BLACK ); // start numbers
  }

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