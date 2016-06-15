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


enum eFieldType
{
  INPUT_NUMERIC,
  INPUT_LOWERALPHA_NUMERIC,
  INPUT_BUTTON
};

struct sVec2
{
  u8 x;
  u8 y;
};

struct sFieldDef
{
  struct sVec2 position;
  struct sVec2 dimension;
  enum eFieldType type;
  char* label;
  u8 inputSize;
  WINDOW* whnd;
};

struct sFieldSet
{
  struct sFieldDef* fields;
  u8 numFields;
  char* label;
  u8 activeFieldId;
  struct sVec2 dimension;
  struct sVec2 position;
  WINDOW* whnd;
  u8 renderBorder;
};

struct sGame
{
  WINDOW* window;
  u8 isRunning;
  enum eGameState state;
  struct sUser user;
  u32 gameTime;
};