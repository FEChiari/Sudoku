
/*
  ===========================================================================
  Pr�prozessorkonstanten
  ===========================================================================
*/

#include "screenstate.h"



/*
  ===========================================================================
  Funktion: State_Highscore
  �bergabeparameter: nGame
  R�ckgabeparameter: -
  Beschreibung: Baut ein Fenster auf und holt sich die Highscores aus der
          Datenbank.
  ===========================================================================
*/
void ScreenState_Highscore( struct sGame* nGame )
{
  WINDOW* pScoresPanel;
  WINDOW* pScoresPanelContent;
  struct sVec2 sMainWindowDimensions, sScoresPanelDimensions;

  wclear( nGame->whnd );

  // Create the panel and frame
  sMainWindowDimensions = Utility_GetWindowDimensions( nGame->whnd );
  pScoresPanel = subwin( nGame->whnd, sMainWindowDimensions.y - 4, sMainWindowDimensions.x - 8, 2, 4 );
  box( pScoresPanel, WA_VERTICAL, WA_HORIZONTAL );
  mvwaddstr( pScoresPanel, 1, ( sMainWindowDimensions.x - 8 ) / 2 - 9, "Highscores - Top 10" );
  mvwhline( pScoresPanel, 2, 1, WA_HORIZONTAL, sMainWindowDimensions.x - 10 );

  // Create an inner window for the actual contents
  sScoresPanelDimensions = Utility_GetWindowDimensions( pScoresPanel );
  pScoresPanelContent = derwin( pScoresPanel, sScoresPanelDimensions.y - 4, sScoresPanelDimensions.x - 2, 3, 1 );

  mvwaddstr( nGame->whnd, sScoresPanelDimensions.y + 2, sScoresPanelDimensions.x - 11, "ESC: Hauptmen�" );

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
  �bergabeparameter: nCallbackParam, nNumColumns, nColumns, nColumnNames
  R�ckgabeparameter: 0
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