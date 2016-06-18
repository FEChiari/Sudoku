/*
===========================================================================
Pr�prozessorkonstanten
===========================================================================
*/

#include "screenstate.h"


void ScreenState_Rules( struct sGame* nGame )
{
  WINDOW* pRulesPanel;
  WINDOW* pRulesPanelContent;
  struct sVec2 sMainWindowDimensions, sRulesPanelDimensions;

  wclear( nGame->whnd );

  // Create the panel and frame
  sMainWindowDimensions = Utility_GetWindowDimensions( nGame->whnd );
  pRulesPanel = subwin( nGame->whnd, sMainWindowDimensions.y - 4, sMainWindowDimensions.x - 8, 2, 4 );
  box( pRulesPanel, WA_VERTICAL, WA_HORIZONTAL );
  mvwaddstr( pRulesPanel, 1, ( sMainWindowDimensions.x - 8 ) / 2 - 9, "Sudoku - Spielregeln" );
  mvwhline( pRulesPanel, 2, 1, WA_HORIZONTAL, sMainWindowDimensions.x - 10 );

  // Create an inner window for the actual contents
  sRulesPanelDimensions = Utility_GetWindowDimensions( pRulesPanel );
  pRulesPanelContent = derwin( pRulesPanel, sRulesPanelDimensions.y - 4, sRulesPanelDimensions.x - 2, 3, 1 );

  char rules[] =

    " In einem 9x9 Felder gro�en Spielfeld werden Zahlen von 1 bis 9 ein-" "\n"
    " getragen. Davon sind, je nach gew�hltem Schwierigkeitsgrad, bereits" "\n"
    " Zahlen vorgegeben - je h�her der Schwierigkeitsgrad, desto weniger." "\n"
    " Ziel des Spiels ist es, alle leeren Felder mit Zahlen zu f�llen." "\n"
    " Dabei m�ssen einige Regeln beachtet werden:" "\n"
    "\n"    
    "  -> In jeder Zeile darf eine Zahl nur einmal vorkommen." "\n"
    "  -> In jeder Spalte darf eine Zahl nur einmal vorkommen." "\n"
    "  -> In jedem Planquadrat darf eine Zahl nur einmal vorkommen." "\n"
    "\n"
    " Bei Sudoku ist zu beachten, dass nur eine L�sung g�ltig ist." "\n"
    " Das Spiel ist beendet, wenn alle leeren Felder korrekt ausgef�llt" "\n"
    " worden sind. Ist das nicht der Fall, geht das Spiel so lange weiter," "\n"
    " bis der/die Fehler gefunden wurden.";

  mvwaddstr( pRulesPanelContent, 0, 0, rules );
  mvwaddstr( nGame->whnd, sRulesPanelDimensions.y + 2, sRulesPanelDimensions.x - 8, "ESC: Zur�ck" );

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
      nGame->prevScreenState = SCREEN_RULES;
      break;
    }

  }
  while ( handleInput );

  delwin( pRulesPanelContent );
  delwin( pRulesPanel );
}