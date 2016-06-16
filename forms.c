/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "forms.h"

/*
  ===========================================================================
  Funktion: Forms_GetFieldSetDimensions
  Übergabeparameter: nFieldSet
  Rückgabeparameter: d
  Beschreibung:
  ===========================================================================
*/
struct sVec2 Forms_GetFieldSetDimensions( struct sFieldSet* nFieldSet )
{
  struct sVec2 d;
  u8 xWidth = 0;
  u8 yWidth = 0;

  // initialize
  d.x = 0;
  d.y = 0;

  for ( u8 fieldId = 0; fieldId < nFieldSet->numFields; fieldId++ )
  {
    xWidth = nFieldSet->fields[ fieldId ].position.x + nFieldSet->fields[ fieldId ].dimension.x;

    if ( xWidth > d.x )
      d.x = xWidth;

    yWidth = nFieldSet->fields[ fieldId ].position.y + nFieldSet->fields[ fieldId ].dimension.y;
    if ( yWidth > d.y )
      d.y = yWidth;
  }

  if ( nFieldSet->renderBorder )
  {
    // account for border
    d.x += 2;
    d.y += 2;
  }

  return d;
}

/*
  ===========================================================================
  Funktion: Forms_RenderFieldSet
  Übergabeparameter: nParentWindow, nFieldSet
  Rückgabeparameter: -
  Beschreibung:
  ===========================================================================
*/
void Forms_RenderFieldSet( WINDOW* nParentWindow, struct sFieldSet* nFieldSet )
{

  /// TODO@FE: handle field labels

  WINDOW* form = nFieldSet->whnd = derwin(
    nParentWindow,
    nFieldSet->dimension.y,
    nFieldSet->dimension.x,
    nFieldSet->position.y,
    nFieldSet->position.x
  );

  WINDOW* inner = NULL;

  wclear( form );

  if ( nFieldSet->renderBorder )
  {
    // create an 'inner' window so that we can still
    // use zero coords without overwriting the frame
    box( form, WA_VERTICAL, WA_HORIZONTAL );
    inner = derwin( form, getmaxy( form ) - 2, getmaxx( form ) - 2, 1, 1 );
  }

  for ( u8 fieldId = 0; fieldId < nFieldSet->numFields; fieldId++ )
  {

    WINDOW* form_field =
      nFieldSet->fields[ fieldId ].whnd = derwin(
      ( inner != NULL ) ? inner : form,
        nFieldSet->fields[ fieldId ].dimension.y,
        nFieldSet->fields[ fieldId ].dimension.x,
        nFieldSet->fields[ fieldId ].position.y,
        nFieldSet->fields[ fieldId ].position.x
      );

    wclear( form_field );
    mvwaddstr( form_field, 0, 0, nFieldSet->fields[ fieldId ].label );

  }

  wrefresh( nParentWindow );
}

void Forms_SetFieldActive( struct sFieldDef* nField, u8 nUseColors )
{
  switch ( nField->type )
  {
  case INPUT_NUMERIC:
  case INPUT_LOWERALPHA_NUMERIC:
    curs_set( 1 );
    echo();
    wmove( nField->whnd, 0, strlen( nField->label ) + 1 );

    if ( nUseColors )
      wbkgd( nField->whnd, COLOR_PAIR( 2 ) );

    break;
  case INPUT_BUTTON:
    curs_set( 0 );
    noecho();

    if ( nUseColors )
      wbkgd( nField->whnd, COLOR_PAIR( 2 ) );

    break;
  }
  wrefresh( nField->whnd );
}

void Forms_SetFieldInactive( struct sFieldDef* nField, u8 nUseColors )
{
  switch ( nField->type )
  {
  case INPUT_NUMERIC:
  case INPUT_LOWERALPHA_NUMERIC:
  case INPUT_BUTTON:

    if ( nUseColors )
      wbkgd( nField->whnd, COLOR_PAIR( 1 ) );

    break;
  }
  wrefresh( nField->whnd );
}

void Forms_HandleFormInput( struct sGame* nGame, struct sFieldSet* nFieldSet )
{
  // get active field
  // highlight it
  // set cursor to it's position
  // if tab, switch field
  // enter/space on buttons activates

  enum eGameState state = SCREEN_LOGIN;
  while ( state == nGame->screenState )
  {
    u8 fieldId = 0;
    for ( ; fieldId < nFieldSet->numFields; fieldId++ )
    {
      if ( fieldId == nFieldSet->activeFieldId )
      {
        Forms_SetFieldActive( &nFieldSet->fields[ fieldId ], nGame->flags.color_enabled );
      }
      else
      {
        Forms_SetFieldInactive( &nFieldSet->fields[ fieldId ], nGame->flags.color_enabled );
      }
    }

    u8 handleInput = 1;
    while ( handleInput )
    {

      u8 key = Utility_WGetKeyCode( nFieldSet->fields[ nFieldSet->activeFieldId ].whnd );
      
      switch ( key )
      {
      case 0x09: // tab-key

                 // select the next field, if there is one
                 // if not, reset to the first field of the form
        if ( ++nFieldSet->activeFieldId >= nFieldSet->numFields )
          nFieldSet->activeFieldId = 0;

        handleInput = 0;

        break;
      case 0x0A: // enter-key

        if ( nFieldSet->fields[ nFieldSet->activeFieldId ].type == INPUT_BUTTON && nFieldSet->fields[ nFieldSet->activeFieldId ].btnCallback != NULL )
        {
          // execute callback
          nFieldSet->fields[ nFieldSet->activeFieldId ].btnCallback( nGame );
        }

        handleInput = 0;

        break;
      }

    }

  }

}