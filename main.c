/*
 * Sudoku (main.c)
 *
 * Autoren: Werba, Schorn, Kremer, Prinz, Engels
 * Datum: 19.06.16 - 24.06.16
 *
 * Beschreibung:
 *
 * Bei dem Programm handelt es sich um ein kommandozeilenbasiertes Sudoku-Spiel
 * mit textbasierter Oberfläche. Als einzige externe Abhängigkeit kommt
 * PDCurses, ein Win32 NCurses-Port, zum Einsatz.
 *
 * Das Spiel wird in mehrere, sogenannte ScreenStates unterteilt. Ein Screen-
 * State beschreibt dabei einen einzelnen Bildschirm, beispielsweise Highscores
 * oder das Regelwerk. Die ScreenStates ihrerseits interagieren mit der
 * Struktur sGame, welche alle Spielrelevanten informationen zentral speichert.
 */
#include "game.h"

/*
 * Debugging-relevante defines für Standard-Schwierigkeitsgrad und -ScreenState
 */
#define DEFAULT_GAMESTATE SCREEN_LOGIN
#define DEFAULT_DIFFICULTY DIFFICULTY_EASY

/*
 * Ein globaler Zeiger auf die Datenbank erspart es, diesen bei jedem
 * Datenbank-relevanten Funktionsaufruf übergeben zu müssen. Globale
 * Variablen sollten nach Möglichkeit vermieden werden, weshalb bspw.
 * auf sGame nicht auf diese Weise zugegriffen wird.
 */
sqlite3* DBH_dbhnd = NULL;

/*
 * Die Funktion Initialize initialisiert das Spiel, bringt es also in einen
 * lauffähigen Zustand. Ist dies nicht möglich ...
 */
void Initialize( struct sGame* nGame );

/*
 * ... oder wird das Spiel anderweitig beendet, sorgt Terminate für einen
 * sauberen Ausstieg. Momentan wird hier nur das initiale Fenster freigegeben
 * sowie die Datenbankverbindung geschlossen.
 */
void Terminate( struct sGame* nGame );

int main( int argc, char* argv[] )
{
  /*
   * Siehe types.h
   */
  struct sGame g;

  Initialize( &g );

  /*
   * Der initiale Game-Loop, welcher durchlaufen wird, bis das Spiel endet.
   */
  while ( g.flags.isRunning )
  {

    /*
     * Je nach ScreenState wird die entsprechende Hauptfunktion aufgerufen.
     * Jede dieser Funktionen kümmert sich um sämtliche Aufgaben und
     * Interaktionen, die mit diesem ScreenState zusammenhängen. Wie bereits
     * erwähnt, wird sGame als zentraler Speicher für spielrelevante
     * Informationen übergeben.
     */
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
    case SCREEN_DIFFICULTY:
      ScreenState_Difficulty( &g );
      break;
    case SCREEN_OPTIONS:
      ScreenState_Options( &g );
      break;
    }
  }

  Terminate( &g );

  return EXIT_SUCCESS;
}

void Initialize( struct sGame* nGame )
{
  /*
   * Setzen von Standardwerten, die für das Spiel zwingend nötig sind.
   * C erlaubt keine Konstruktoren, was bedeutet, dass diese Arbeit
   * grundsätzlich vom Programmierer ausgeführt werden muss. Auslassen
   * von Werten hat undefiniertes Verhalten zur Folge.
   */
  nGame->flags.isRunning = 1;
  nGame->screenState = DEFAULT_GAMESTATE;
  nGame->prevScreenState = nGame->screenState;
  nGame->gameState.difficultyLvl = DEFAULT_DIFFICULTY;
  nGame->gameState.timePlayed = 0;

  /*
   * Kann NCurses nicht initialisiert werden, so bedeutet dies einen fatalen
   * Fehler, von dem sich das Programm nicht selbstständig erholen kann.
   * In diesem Fall gibt es eine entsprechende Meldung und das Spiel wird beendet.
   */
  if ( ( nGame->whnd = initscr() ) == NULL )
  {
    printf( "[Fatal] Failed to initialize curses" "\n" );
    exit( EXIT_FAILURE );
  }

  /*
   * Die Konsole wird auf vorgegebene Maße gesetzt, um ein optimales Spiel-
   * erlebnis zu garantieren. Das Konsolenfenster wird danach, falls möglich,
   * mithilfe der Win32-API fixiert, kann also nicht mehr maximiert werden.
   * Dies dient dazu, Darstellungsprobleme zu vermeiden. Auch der Titel des
   * Fensters wird geändert.
   */
  resize_term( 30, 80 );

#ifdef _WIN32
  SetConsoleTitle( GAME_TITLE " - " GAME_VERSION );
  Utility_SetWindowMaximizable( 0 );
#endif

  /*
   * NCurses unterstützt, je nach Terminal, Mehrfarbigkeit.
   * Falls das aktuelle Terminal Farben unterstützt, wird das entsprechende
   * Flag in sGame gesetzt und einige Farbdefinitionen folgen.
   */
  if ( has_colors() )
  {
    start_color();
    nGame->flags.color_enabled = 1;
    init_pair( 1, COLOR_WHITE, COLOR_BLACK ); /* Standard-Text                          */
    init_pair( 2, COLOR_BLACK, COLOR_WHITE ); /* Invertierter Text                      */
    init_pair( 3, COLOR_GREEN, COLOR_BLACK ); /* Vorgefüllte Zahlen auf dem Sudoku-Feld */
  }

  /*
   * Der DBHandler wird initialisiert. Weiteres in dbh.h / dbh.c.
   */
  DBH_dbhnd = DBH_CreateHandle( DBH_DATABASE_FILE );

  /*
   * Auch ohne Datenbankanbindung ist das Spiel nicht lauffähig. Wenn keine
   * Verbindung hergestellt werden konnte, wird das Spiel beendet.
   */
  if ( DBH_dbhnd == NULL )
  {
    printf( "[Fatal] Failed to access database file '" DBH_DATABASE_FILE "'" "\n" );
    Terminate( nGame );
    exit( EXIT_FAILURE );
  }

  /*
   * Schlussendlich werden mehrere Maus- und Tastaturrelevante Standards
   * gesetzt:
   *
   * - kein Cursor
   * - keine Ausgabe beim Tippen
   * - keine Verzögerung bei Eingaben
   * - Der Ziffernblock kann genutzt werden
   */
  curs_set( 0 );
  noecho();
  nodelay( nGame->whnd, TRUE );
  keypad( nGame->whnd, TRUE );
}

void Terminate( struct sGame* nGame )
{
  if ( DBH_dbhnd != NULL )
    DBH_CloseHandle( DBH_dbhnd );

  if ( nGame->whnd != NULL )
  {
    delwin( nGame->whnd );
    endwin();
  }
}