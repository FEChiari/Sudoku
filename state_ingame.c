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
int SetDifficulty(int DiffValue)
{
    int iDifficulty;
    switch (DiffValue)
    {
    case 0:
        iDifficulty = 40;
        break;
    case 1:
        iDifficulty = 50;
        break;
    case 2:
        iDifficulty = 55;
        break;
    case 3:
        iDifficulty = 60;
        break;
    default:
        iDifficulty = 0;
        break;
    }
    
    return iDifficulty;
}


void State_Ingame(struct sGame* nGame)
{
    int iSudoku[9][9];
    int iDifficulty = SetDifficulty((int)nGame->difficulty);
    
    generiereSudoku(iSudoku, iDifficulty);
    WINDOW *ingameContainer = subwin(nGame->whnd, 100, 30, 2, 2);
    box(ingameContainer, WA_VERTICAL, WA_HORIZONTAL);
    
    wrefresh(nGame->whnd);
    wrefresh(ingameContainer);
    
    system("pause");
}