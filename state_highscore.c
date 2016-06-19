
/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "screenstate.h"



/*
  ===========================================================================
  Funktion: State_Highscore
  Übergabeparameter: nGame
  Rückgabeparameter: -
  Beschreibung: Baut ein Fenster auf und holt sich die Highscores aus der
          Datenbank.
  ===========================================================================
*/
void ScreenState_Highscore( struct sGame* nGame )
{
  WINDOW* pScoresPanel;
  WINDOW* pScoresPanelContent;

  wclear( nGame->whnd );

  // Create the panel and frame
  pScoresPanel = subwin( nGame->whnd, nGame->whnd->_maxy - 4, nGame->whnd->_maxx - 8, 2, 4 );
  box( pScoresPanel, WA_VERTICAL, WA_HORIZONTAL );
  mvwaddstr( pScoresPanel, 1, ( nGame->whnd->_maxx - 8 ) / 2 - 9, "Highscores - Top 10" );
  mvwhline( pScoresPanel, 2, 1, WA_HORIZONTAL, nGame->whnd->_maxx - 10 );

  // Create an inner window for the actual contents
  pScoresPanelContent = derwin( pScoresPanel, pScoresPanel->_maxy - 4, pScoresPanel->_maxx - 2, 3, 1 );

  mvwaddstr( nGame->whnd, pScoresPanel->_maxy + 2, pScoresPanel->_maxx - 11, "ESC: Hauptmenü" );

  // Certainly not the cleanest way to do this ...
  // Takes a lot less time though.
  char* pQuerystring = malloc( 255 );
  memset( pQuerystring, 0, 255 );
  sprintf( pQuerystring,
    "SELECT Users.username, Highscores.score from Highscores \
    INNER JOIN  Users ON Users.id= Highscores.uid WHERE Highscores.difficulty = %d \
    ORDER BY Highscores.score DESC", nGame->difficultyLvl );

  struct DBH_CallbackArgumentPair args;
  args.rowIter = 0;
  args.additionalArgument = pScoresPanelContent;

  DBH_Query( pQuerystring, DBH_Callback_PrintScores, &args, NULL );

  free( pQuerystring );


  wrefresh( nGame->whnd );

  u8 handleInput = 1;
  do
  {
    char key = Utility_WGetKeyCode( nGame->whnd );

    switch ( key )
    {
    case 0x1B: // ESC-key
      handleInput = 0;
      nGame->screenState = nGame->prevScreenState;
      nGame->prevScreenState = SCREEN_HIGHSCORE;
      break;
    }

  }
  while ( handleInput );

  delwin( pScoresPanelContent );
  delwin( pScoresPanel );
}

/*
  ===========================================================================
  Funktion: Callback_PrintScores
  Übergabeparameter: nCallbackParam, nNumColumns, nColumns, nColumnNames
  Rückgabeparameter: 0
  Beschreibung: Gibt die Highscores aus der Datenbank aus.
  ===========================================================================
*/
int DBH_Callback_PrintScores( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames )
{
  struct DBH_CallbackArgumentPair* args = ( struct DBH_CallbackArgumentPair* ) nCallbackParam;
  WINDOW* pScoresPanelContent = ( WINDOW* ) args->additionalArgument;

  u8 rowWidth = getmaxx( pScoresPanelContent );

  char* row = malloc( rowWidth / 2 );
  memset( row, 0, rowWidth / 2 );
  sprintf( row, "%d. %s", args->rowIter, nColumns[ 0 ] );

  mvwaddstr( pScoresPanelContent, args->rowIter, 1, row );
  mvwaddstr( pScoresPanelContent, args->rowIter, rowWidth - strlen( nColumns[ 1 ] ) - 1, nColumns[ 1 ] );

  free( row );

  args->rowIter++;

  return 0;
}