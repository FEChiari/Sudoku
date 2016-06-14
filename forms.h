#pragma once

#include "types.h"
#include "lib/pdcurses/panel.h"


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

struct sVec2 Forms_GetFieldSetDimensions( struct sFieldSet* nFieldSet );
void Forms_RenderFieldSet( WINDOW* nWindow, struct sFieldSet* nFieldSet );