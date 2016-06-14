#include "forms.h"


struct sFieldDimension Forms_GetFormDimensions( struct sFieldSet* nFieldSet ) {

  struct sFieldDimension x;
  x.x = 1;
  x.y = 2;
  return x;
}

void Forms_RenderFieldSet( WINDOW* nParentWindow, struct sFieldSet* nFieldSet )
{

  WINDOW* form = nFieldSet->whnd = subwin( nParentWindow, nFieldSet->dimension.y, nFieldSet->dimension.x, nFieldSet->position.y, nFieldSet->position.x );

  wclear( form );

  if ( nFieldSet->renderBorder )
    box( form, WA_VERTICAL, WA_HORIZONTAL );






  for ( u8 fieldId = 0; fieldId < nFieldSet->numFields; fieldId++ )
  {
    /*printf( "rendering %s\n", nFieldSet->fields[ fieldId ].label );*/

    WINDOW* win =
      nFieldSet->fields[ fieldId ].whnd = subwin( nParentWindow,
        nFieldSet->fields[ fieldId ].dimension.y,
        nFieldSet->fields[ fieldId ].dimension.x,
        nFieldSet->fields[ fieldId ].position.y,
        nFieldSet->fields[ fieldId ].position.x
        );

    wclear( win );
    mvwaddstr( win, 0, 0, nFieldSet->fields[ fieldId ].label );
 
  }
  
  
  wrefresh( nParentWindow );
}

void Forms_HandleFormInput( WINDOW* nTarget, struct sFieldSet* nForm )
{

}