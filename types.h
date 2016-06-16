#pragma once

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

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
  SCREEN_LOGIN,
  SCREEN_MAIN_MENU,
  SCREEN_REGISTRATION,
  SCREEN_HIGHSCORE,
  SCREEN_INGAME
};

enum eGameDifficulty
{
  DIFFICULTY_EASY = 40,
  DIFFICULTY_MEDIUM = 50,
  DIFFICULTY_HARD = 55,
  DIFFICULTY_VHARD = 60
};

struct sUser
{
  u8 isGuest;
  u32 userId;
  char* username;
  char* password;
};

enum eFieldType
{
  INPUT_NUMERIC,
  INPUT_LOWERALPHA_NUMERIC,
  INPUT_BUTTON,
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
  WINDOW* whnd;
  enum eGameState prevScreenState;
  enum eGameState screenState;
  enum eGameDifficulty difficulty;
  struct sUser user;
  u32 gameTime;
  u32 SudokuContainer[9][9];
  struct  
  {
    u8 isRunning;
    u8 color_enabled;
  } flags;
};