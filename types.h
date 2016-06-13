#pragma once

#include "lib/pdcurses/panel.h"

#define TITLE "Sudoku"
#define VERSION "0.0.1"
#define AUTHOR "Werba, Schorn, Kr�mer, Prinz, Engels"

typedef unsigned int u8;

enum eGameState
{
  LOGIN
};

struct sGame
{
  WINDOW* window;
  u8 isRunning;
  enum eGameState state;
};