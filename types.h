#pragma once

/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "lib/pdcurses/panel.h"

#define GAME_TITLE "Sudoku"
#define GAME_VERSION "0.0.1"
#define GAME_AUTHORS "Werba, Schorn, Krämer, Prinz, Engels"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef char s8;
typedef short s16;
typedef int s32;

enum eScreenState
{
  SCREEN_LOGIN,
  SCREEN_MAIN_MENU,
  SCREEN_REGISTRATION,
  SCREEN_HIGHSCORE,
  SCREEN_INGAME,
  SCREEN_RULES,
  SCREEN_OPTIONS,
  SCREEN_DIFFICULTY,
};

enum eDifficulty
{
  DIFFICULTY_EASY = 40,
  DIFFICULTY_MEDIUM = 50,
  DIFFICULTY_HARD = 55,
  DIFFICULTY_VHARD = 60,
};

struct sVec2
{
  u8 x;
  u8 y;
};

struct sUser
{
  u8 isGuest;
  u32 userId;
  char username[13];
  char password[13];
};

enum eSudokuFieldType
{
  FIELD_GENERATED,
  FIELD_USER_FILLED_IN,
};

struct sSudokuField
{
  u8 value;
  u8 row;
  u8 col;
  enum eSudokuFieldType type;
};

struct sGameState
{
  struct sSudokuField field[ 9 ][ 9 ];
  enum eDifficulty difficultyLvl;
  time_t timePlayed;
  u32 score;
};

struct sGame
{
  WINDOW* whnd;
  enum eScreenState prevScreenState;
  enum eScreenState screenState;
  struct sGameState gameState;
  struct sUser user;
  struct
  {
    u8 isRunning;
    u8 color_enabled;
  } flags;
};

enum eFieldType
{
  INPUT_NUMERIC,
  INPUT_LOWERALPHA_NUMERIC,
  INPUT_BUTTON,
  STATIC_TEXT,
};

struct sFieldDef
{
  struct sVec2 position;
  struct sVec2 dimension;
  enum eFieldType type;
  char* label;
  u8 inputSize;
  u8 isPWField;
  u8 isDisabled;
  void( *btnCallback )( struct sGame* nGame, struct sFieldSet* nFieldSet );
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