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

  WINDOW* form = nFieldSet->whnd = subwin( nParentWindow, nFieldSet->dimension.y, nFieldSet->dimension.x, nFieldSet->position.y, nFieldSet->position.x );

  wclear( form );

  if ( nFieldSet->renderBorder )
  {
    // create an 'inner' window so that we can still
    // use zero coords without overwriting the frame
    box( form, WA_VERTICAL, WA_HORIZONTAL );
    form = derwin( form, getmaxy( form ) - 2, getmaxx( form ) - 2, 1, 1 );
  }


  for ( u8 fieldId = 0; fieldId < nFieldSet->numFields; fieldId++ )
  {

    WINDOW* form_field =
      nFieldSet->fields[ fieldId ].whnd = derwin( form,
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