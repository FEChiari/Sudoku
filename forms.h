#pragma once

#include "types.h"
#include "lib/pdcurses/panel.h"


enum eFieldType
{
  INPUT_NUMERIC,
  INPUT_LOWERALPHA_NUMERIC,
  INPUT_BUTTON
};

struct sFieldPosition
{
  u8 x;
  u8 y;
};

struct sFieldDimension
{
  u8 x;
  u8 y;
};

struct sFieldDef
{
  struct sFieldPosition position;
  struct sFieldDimension dimension;
  enum eFieldType type;
  char* label;
  u8 size;
  WINDOW* whnd;
};

struct sFieldSet
{
  struct sFieldDef* fields;
  u8 numFields;
  u8 activeFieldId;
  struct sFieldDimension dimension;
  struct sFieldPosition position;
  WINDOW* whnd;
  u8 renderBorder;
};

struct sFieldDimension Forms_GetFormDimensions( struct sFieldSet* nFieldSet );
void Forms_RenderFieldSet( WINDOW* nWindow, struct sFieldSet* nFieldSet );
void Forms_HandleFormInput( WINDOW* nTarget, struct sFieldSet* nForm );