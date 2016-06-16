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
    int iSudoku[9][9];
    generiereSudoku(iSudoku, (int)nGame->difficulty);
    WINDOW *ingameContainer = subwin(nGame->whnd, 21 , 39, 1, 1);
    box(ingameContainer, WA_VERTICAL, WA_HORIZONTAL);
    struct sFieldSet SpielFeld;
    struct sFieldDef zahlenFeld[9][9];
    
    //Spielfeld
    SpielFeld.dimension.x = 20;
    SpielFeld.dimension.y = 38;
    SpielFeld.position.x = 1;
    SpielFeld.position.y = 1;
    SpielFeld.label = "Sudoku 0.2.0";
    SpielFeld.fields = zahlenFeld;
    SpielFeld.whnd = derwin(ingameContainer, SpielFeld.dimension.x, SpielFeld.dimension.y, 1, 1);
    
    //Felder
    char chelp[3];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            zahlenFeld[i][j].dimension.x = 4;
            zahlenFeld[i][j].dimension.y = 2;
            zahlenFeld[i][j].position.x = j * 4;
            zahlenFeld[i][j].position.y = i * 2;
            zahlenFeld[i][j].type = INPUT_NUMERIC;
            zahlenFeld[i][j].whnd = derwin(SpielFeld.whnd, zahlenFeld[i][j].dimension.y, zahlenFeld[i][j].dimension.x, zahlenFeld[i][j].position.y, zahlenFeld[i][j].position.x);
            //Rahmen zeichen
            mvwaddstr(zahlenFeld[i][j].whnd, 0, 0, "+");
            mvwaddstr(zahlenFeld[i][j].whnd, 0, 1, "-");
            mvwaddstr(zahlenFeld[i][j].whnd, 0, 2, "-");
            mvwaddstr(zahlenFeld[i][j].whnd, 0, 3, "-");
            mvwaddstr(zahlenFeld[i][j].whnd, 1, 0, "|");
            //Werte einsetzen
            _itoa(iSudoku[i][j], &chelp, 10);
            if (chelp[0] != '0')
            {
                wattron(zahlenFeld[i][j].whnd, COLOR_PAIR(3));
                mvwaddstr(zahlenFeld[i][j].whnd, 1, 2, &chelp); 
                wattroff(zahlenFeld[i][j].whnd, COLOR_PAIR(3));
            }

            wrefresh(zahlenFeld[i][j].whnd);
        }
        mvwaddstr(SpielFeld.whnd, i*2, 36, "+");
        mvwaddstr(SpielFeld.whnd, i*2+1, 36, "|");
        mvwaddstr(SpielFeld.whnd, 18, i*4, "+---");
    }
    mvwaddstr(SpielFeld.whnd, 18, 36, "+");
    wrefresh(ingameContainer);
    wmove(SpielFeld.whnd, 2, 3);
    wrefresh(SpielFeld.whnd);
    
    u8 handleInput = 1;
    do
    {
        char key = Utility_WGetKeyCode(nGame->whnd);

        switch (key)
        {
        case 0x1B: // ESC-key
            handleInput = 0;
            nGame->prevScreenState = nGame->screenState;
            nGame->screenState = SCREEN_MAIN_MENU;
            break;
        }

    } while (handleInput);

    delwin(SpielFeld.whnd);
    delwin(ingameContainer);
}
