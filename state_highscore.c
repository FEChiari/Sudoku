#include "screenstate.h"

void State_Highscore( struct sGame* nGame )
{
  WINDOW* pScoresPanel;
  WINDOW* pScoresPanelContent;
  struct sVec2 sMainWindowDimensions, sScoresPanelDimensions;

  wclear( nGame->whnd );

  // Create the panel and frame
  sMainWindowDimensions = Utility_GetWindowDimensions( nGame->whnd );
  pScoresPanel = subwin( nGame->whnd, sMainWindowDimensions.y - 4, sMainWindowDimensions.x - 20, 2, 10 );
  box( pScoresPanel, WA_VERTICAL, WA_HORIZONTAL );
  mvwaddstr( pScoresPanel, 1, ( sMainWindowDimensions.x - 22 ) / 2 - 9, "Highscores - Top 10" );
  mvwhline( pScoresPanel, 2, 1, WA_HORIZONTAL, sMainWindowDimensions.x - 22 );

  // Create an inner window for the actual contents
  sScoresPanelDimensions = Utility_GetWindowDimensions( pScoresPanel );
  pScoresPanelContent = derwin( pScoresPanel, sScoresPanelDimensions.y - 4, sScoresPanelDimensions.x - 2, 3, 1 );

  // Certainly not the cleanest way to do this ...
  // Takes a lot less time though.
  char* pQuerystring = malloc( 255 );
  memset( pQuerystring, 0, 255 );
  sprintf( pQuerystring,
    "SELECT Users.username, Highscores.score from Highscores \
    INNER JOIN  Users ON Users.id= Highscores.uid WHERE Highscores.difficulty = %d \
    ORDER BY Highscores.score DESC", nGame->difficulty );
  DBH_Query( pQuerystring, Callback_PrintScores, pScoresPanelContent, NULL );
  free( pQuerystring );

  wrefresh( nGame->whnd );

  Utility_HandleGlobalInput( nGame );

  delwin( pScoresPanelContent );
  delwin( pScoresPanel );
}

int Callback_PrintScores( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames )
{
  static iRow = 1;

  WINDOW* pScoresPanelContent = ( WINDOW* ) nCallbackParam;

  u8 rowWidth = getmaxx( pScoresPanelContent );

  char* row = malloc( rowWidth / 2 );
  memset( row, 0, rowWidth / 2 );
  sprintf( row, "%d. %s", iRow, nColumns[0] );

  mvwaddstr( pScoresPanelContent, iRow, 1, row );
  mvwaddstr( pScoresPanelContent, iRow, rowWidth - strlen( nColumns[ 1 ] ) - 1, nColumns[ 1 ] );

  free( row );

  iRow++;

  return 0;
}