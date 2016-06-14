#pragma once

#include "lib/pdcurses/panel.h"

#define TITLE "Sudoku"
#define VERSION "0.0.1"
#define AUTHOR "Werba, Schorn, Krämer, Prinz, Engels"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef char s8;
typedef short s16;
typedef int s32;

enum eGameState
{
  LOGIN,
  MAIN_MENU,
  REGISTRATION,
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
  u32 gameTime;
};