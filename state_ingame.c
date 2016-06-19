/*
===========================================================================
Präprozessorkonstanten
===========================================================================
*/

#include "screenstate.h"

/*
===========================================================================
Funktion: State_Ingame
Übergabeparameter: nGame
Rückgabeparameter: -
Beschreibung: Warte auf Code!
===========================================================================
*/

void ScreenState_Ingame( struct sGame* nGame )
{

  wclear( nGame->whnd );

  WINDOW* statusbar_container = derwin( nGame->whnd, nGame->whnd->_begy + 3, nGame->whnd->_maxx - 8, 2, 4 );
  box( statusbar_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* statusbar_inner = derwin( statusbar_container, 1, statusbar_container->_maxx - 2, 1, 1 );

  mvwaddstr( statusbar_inner, 0, 1, "Spielzeit: " );
  mvwaddstr( statusbar_inner, 0, 56, "Spieler: Gast" );

  WINDOW* left_container = derwin( nGame->whnd, nGame->whnd->_maxy - 8, nGame->whnd->_maxx - 36, statusbar_container->_maxy + 2, nGame->whnd->_begx + 4 );
  box( left_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* left_inner = derwin( left_container, left_container->_maxy - 2, left_container->_maxx - 2, 1, 1 );

  char left_text[ 32 ];
  sprintf( left_text, "left container\n(%dx%d)", left_container->_maxx, left_container->_maxy );
  mvwaddstr( left_inner, 0, 1, left_text );

  WINDOW* right_container = derwin( nGame->whnd, left_container->_maxy, 28, statusbar_container->_maxy + 2, left_container->_maxx + 4 );
  box( right_container, WA_VERTICAL, WA_HORIZONTAL );
  WINDOW* right_inner = derwin( right_container, right_container->_maxy - 2, right_container->_maxx - 2, 1, 1 );


  char right_text[ 32 ];
  sprintf( right_text, "right container\n(%dx%d)", right_container->_maxx, right_container->_maxy );
  mvwaddstr( right_inner, 0, 1, right_text );

  mvwaddstr( nGame->whnd, right_container->_begy + right_container->_maxy, right_container->_begx + right_container->_maxx - 15, "ESC: Hauptmenü" );












  u8 playing = 1;
  time_t time_then = time( NULL );
  double time_difference = 0;

  while ( playing )
  {



    u8 handleInput = 1;
    do
    {

      char time_played[ 12 ];
      time_difference = difftime( time( NULL ), time_then );

      if ( time_difference >= 3600 )
      {
        sprintf( time_played, "%dh %dm %ds", ( u8 ) time_difference / 3600, ( u8 ) time_difference / 60, ( u8 ) time_difference % 60 );
      }
      else if ( time_difference >= 60 )
      {
        sprintf( time_played, "%dm %ds", ( u8 ) time_difference / 60, ( u8 ) time_difference % 60 );
      }
      else
      {
        sprintf( time_played, "%ds", ( u8 ) time_difference );
      }
      mvwaddstr( statusbar_inner, 0, 12, time_played );
      wrefresh( statusbar_inner );



      char key = Utility_WGetKeyCode( nGame->whnd );

      switch ( key )
      {
      case 0x03: // up-arrow key

        break;
      case 0x05: // right-arrow key

        break;
      case 0x02: // down-arrow key

        break;
      case 0x04: // left-arrow key

        break;
      case 0x1B: // ESC-key
        handleInput = 0;
        playing = 0;
        nGame->screenState = nGame->prevScreenState;
        nGame->prevScreenState = SCREEN_INGAME;
        break;
      }

      // catch all numerical keys, top-row and numblock
      if ( key >= 0x30 && key <= 0x39 || key >= 0x60 && key <= 0x69 )
      {
        
      }

    }
    while ( handleInput );



  }

  delwin( statusbar_inner );
  delwin( statusbar_container );

  delwin( left_inner );
  delwin( left_container );

  delwin( right_inner );
  delwin( right_container );































  //int iSudoku[9][9];
  //generiereSudoku(iSudoku, (int)nGame->difficultyLvl);
  //WINDOW *ingameContainer = subwin(nGame->whnd, 21 , 39, 1, 1);
  //box(ingameContainer, WA_VERTICAL, WA_HORIZONTAL);
  //struct sFieldSet SpielFeld;
  //struct sFieldDef zahlenFeld[9][9];
  //
  ////Spielfeld
  //SpielFeld.dimension.x = 20;
  //SpielFeld.dimension.y = 38;
  //SpielFeld.position.x = 1;
  //SpielFeld.position.y = 1;
  //SpielFeld.label = "Sudoku 0.2.0";
  //SpielFeld.fields = &zahlenFeld[0][0];
  //SpielFeld.whnd = derwin(ingameContainer, SpielFeld.dimension.x, SpielFeld.dimension.y, 1, 1);
  //
  ////Felder
  //char chelp[3];
  //for (int i = 0; i < 9; i++)
  //{
  //    for (int j = 0; j < 9; j++)
  //    {
  //        zahlenFeld[i][j].dimension.x = 4;
  //        zahlenFeld[i][j].dimension.y = 2;
  //        zahlenFeld[i][j].position.x = j * 4;
  //        zahlenFeld[i][j].position.y = i * 2;
  //        zahlenFeld[i][j].type = INPUT_NUMERIC;
  //        zahlenFeld[i][j].whnd = derwin(SpielFeld.whnd, zahlenFeld[i][j].dimension.y, zahlenFeld[i][j].dimension.x, zahlenFeld[i][j].position.y, zahlenFeld[i][j].position.x);
  //        //Rahmen zeichen
  //        mvwaddstr(zahlenFeld[i][j].whnd, 0, 0, "+");
  //        mvwaddstr(zahlenFeld[i][j].whnd, 0, 1, "-");
  //        mvwaddstr(zahlenFeld[i][j].whnd, 0, 2, "-");
  //        mvwaddstr(zahlenFeld[i][j].whnd, 0, 3, "-");
  //        mvwaddstr(zahlenFeld[i][j].whnd, 1, 0, "|");
  //        //Werte einsetzen
  //        _itoa(iSudoku[i][j], chelp, 10);
  //        if (chelp[0] != '0')
  //        {
  //            wattron(zahlenFeld[i][j].whnd, COLOR_PAIR(3));
  //            mvwaddstr(zahlenFeld[i][j].whnd, 1, 2, chelp); 
  //            wattroff(zahlenFeld[i][j].whnd, COLOR_PAIR(3));
  //        }

  //        wrefresh(zahlenFeld[i][j].whnd);
  //    }
  //    mvwaddstr(SpielFeld.whnd, i*2, 36, "+");
  //    mvwaddstr(SpielFeld.whnd, i*2+1, 36, "|");
  //    mvwaddstr(SpielFeld.whnd, 18, i*4, "+---");
  //}
  //mvwaddstr(SpielFeld.whnd, 18, 36, "+");
  //wrefresh(ingameContainer);
  //wmove(SpielFeld.whnd, 2, 3);
  //wrefresh(SpielFeld.whnd);
  //
  //u8 handleInput = 1;
  //do
  //{
  //    char key = Utility_WGetKeyCode(nGame->whnd);

  //    switch (key)
  //    {
  //    case 0x1B: // ESC-key
  //        handleInput = 0;
  //        nGame->prevScreenState = nGame->screenState;
  //        nGame->screenState = SCREEN_MAIN_MENU;
  //        break;
  //    }

  //} while (handleInput);

  //delwin(SpielFeld.whnd);
  //delwin(ingameContainer);
}
