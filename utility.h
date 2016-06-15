#pragma once

#include "types.h"
#include "lib/pdcurses/panel.h"


int Utility_GetKeyCode();
int Utility_WGetKeyCode( WINDOW* nTarget );
struct sVec2 Utility_GetWindowDimensions( WINDOW* nTarget );
void Utility_HandleGlobalInput(struct sGame* nGame);
