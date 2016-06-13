#pragma once

#include "lib/pdcurses/panel.h"

#define TITLE "Sudoku"
#define VERSION "0.0.1"
#define AUTHOR "Werba, Schorn, Krämer, Prinz, Engels"

typedef unsigned int u8;

enum eGameState
{
  LOGIN,
  MAIN_MENU,
  HIGHSCORE,
  INGAME
};

struct sUser
{
  u8 isGuest;  
};

struct sGame
{
  WINDOW* window;
  u8 isRunning;
  enum eGameState state;
  struct sUser user;
};