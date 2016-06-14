#include "game.h"


void init( struct sGame* nGame )
{
  nGame->isRunning = 1;
  nGame->state = LOGIN;

  if ( ( nGame->window = initscr() ) == NULL )
  {
    printf( "[Fatal] Failed to initialize curses" );
    exit( EXIT_FAILURE );
  }

  curs_set( 0 );
  noecho();
  nodelay( nGame->window, TRUE );
  keypad( nGame->window, TRUE );
}

int main( int argc, char* argv[] )
{

  struct sGame g;

  init( &g );




  struct sFieldDef form_fields[ 5 ];

  // username
  form_fields[ 0 ].position.x = 1;
  form_fields[ 0 ].position.y = 1;
  form_fields[ 0 ].dimension.x = 12;
  form_fields[ 0 ].dimension.y = 1;
  form_fields[ 0 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 0 ].label = "Benutzer:";
  form_fields[ 0 ].size = 32;

  // password
  form_fields[ 1 ].position.x = 1;
  form_fields[ 1 ].position.y = 2;
  form_fields[ 1 ].dimension.x = 12;
  form_fields[ 1 ].dimension.y = 1;
  form_fields[ 1 ].type = INPUT_LOWERALPHA_NUMERIC;
  form_fields[ 1 ].label = "Password:";
  form_fields[ 1 ].size = 32;

  // button enter
  form_fields[ 2 ].position.x = 1;
  form_fields[ 2 ].position.y = 3;
  form_fields[ 2 ].dimension.x = 12;
  form_fields[ 2 ].dimension.y = 1;
  form_fields[ 2 ].type = INPUT_BUTTON;
  form_fields[ 2 ].label = "Login";
  form_fields[ 2 ].size = 0;

  // button play-as-guest
  form_fields[ 3 ].position.x = 1;
  form_fields[ 3 ].position.y = 4;
  form_fields[ 3 ].dimension.x = 12;
  form_fields[ 3 ].dimension.y = 1;
  form_fields[ 3 ].type = INPUT_BUTTON;
  form_fields[ 3 ].label = "Gast";
  form_fields[ 3 ].size = 0;

  // button register
  form_fields[ 4 ].position.x = 1;
  form_fields[ 4 ].position.y = 5;
  form_fields[ 4 ].dimension.x = 12;
  form_fields[ 4 ].dimension.y = 1;
  form_fields[ 4 ].type = INPUT_BUTTON;
  form_fields[ 4 ].label = "Registrieren";
  form_fields[ 4 ].size = 0;

  // the form itself
  struct sFieldSet login_form;
  login_form.fields = &form_fields;
  login_form.activeFieldId = 1;
  login_form.numFields = 5;
  login_form.renderBorder = 0;
  //login_form.dimension = getFormDimensions( &login_form );
  //login_form.position.x = getmaxx( &g.window ) / 2 - login_form.dimension.x;
  //login_form.position.y = getmaxy( &g.window ) / 2 - login_form.dimension.y;

  Forms_RenderFieldSet( g.window, &login_form );
  Forms_HandleFormInput( g.window, &login_form );






















  exit( 0 );

  while ( g.isRunning )
  {
    switch ( g.state )
    {
    case LOGIN:
      State_Login( &g );
      break;
    case MAIN_MENU:
      State_Main_Menu( &g );
      break;
    case INGAME:
      State_Ingame( &g );
      break;
    case HIGHSCORE:
      State_Highscore( &g );
      break;
    }
  }

}