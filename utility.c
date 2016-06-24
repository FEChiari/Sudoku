
/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include "utility.h"

/*
  ===========================================================================
  Funktion: Utility_GetKeyCode
  Übergabeparameter: -
  Rückgabeparameter: getch()
  Beschreibung:
  ===========================================================================
*/

int Utility_GetKeyCode()
{
  return getch();
}

/*
  ===========================================================================
  Funktion: Utility_WGetKeyCode
  Übergabeparameter: nTarget
  Rückgabeparameter: wgetch(nTarget)
  Beschreibung:
  ===========================================================================
*/

int Utility_WGetKeyCode( WINDOW* nTarget )
{
  return wgetch( nTarget );
}

u8 Utility_Confimation(struct sGame* nGame, struct sFieldSet* nFieldSet)
{
    wclear(nGame->whnd);
    char sPartOne[128];
    strcpy(sPartOne, "Sind sie sicher, dass sie :");
    strcat(sPartOne, nFieldSet->label);
    char sPartTwo[30];
    strcpy(sPartTwo, "ausführen möchten?");
    struct sFieldDef form_fields[3];

    //Fragestellung
    form_fields[0].position.x = 0;
    form_fields[0].position.y = 0;
    form_fields[0].dimension.x = 60;
    form_fields[0].dimension.y = 2;
    form_fields[0].type = STATIC_TEXT;
    form_fields[0].isDisabled = 1;
    form_fields[0].label = strcat(sPartOne, sPartTwo);
    form_fields[0].isPWField = 0;

    //ja
    form_fields[1].position.x = 25;
    form_fields[1].position.y = 2;
    form_fields[1].dimension.x = 2;
    form_fields[1].dimension.y = 1;
    form_fields[1].type = INPUT_BUTTON;
    form_fields[1].isDisabled = 0;
    form_fields[1].isPWField = 0;
    form_fields[1].label = "Ja";

    //nein
    form_fields[2].position.x = 28;
    form_fields[2].position.y = 2;
    form_fields[2].dimension.x = 4;
    form_fields[2].dimension.y = 1;
    form_fields[2].type = INPUT_BUTTON;
    form_fields[2].isDisabled = 0;
    form_fields[2].isPWField = 0;
    form_fields[2].label = "Nein";

    struct sFieldSet confirmation_form;


    confirmation_form.fields = &form_fields[0];
    confirmation_form.label = "Bestätigung";
    confirmation_form.activeFieldId = 2;
    confirmation_form.numFields = 3;
    confirmation_form.renderBorder = 1;
    confirmation_form.dimension = Forms_GetFieldSetDimensions(&confirmation_form);
    confirmation_form.position.x = getmaxx(nGame->whnd) / 2 - confirmation_form.dimension.x / 2;
    confirmation_form.position.y = getmaxy(nGame->whnd) / 2 - confirmation_form.dimension.y / 2;

    confirmation_form.whnd = derwin(nGame->whnd, confirmation_form.dimension.y, confirmation_form.dimension.x, confirmation_form.position.y, confirmation_form.position.x);
    for (int i = 0; i < confirmation_form.numFields; i++)
    {
        form_fields[i].whnd = derwin(confirmation_form.whnd, form_fields[i].dimension.y, form_fields[i].dimension.x, form_fields[i].position.y, form_fields[i].position.x);
        mvwaddstr(form_fields[i].whnd, 0, 0, form_fields[i].label);
    }
    box(confirmation_form.whnd, WA_VERTICAL, WA_HORIZONTAL);
    Forms_SetFieldActive(&form_fields[2], 1);
    wrefresh(nGame->whnd);
    u8 handleInput = 1;
    u8 returnByte;
    do
    {
        wclear(confirmation_form.whnd);
        wrefresh(nGame->whnd);
        char key = Utility_WGetKeyCode(confirmation_form.whnd);

        switch (key)
        {
        case 0x02: // down-arrow key
        case 0x05: // right-arrow key
        case 0x09: // tab-key

            // select the next field, if there is one
            // if not, reset to the first field of the form
            Form_MoveCursorToNextField(&confirmation_form);

            break;

        case 0x03: // up-arrow key
        case 0x04: // left-arrow key;
            // select the previous field, if there is one
            // if not, reset to the last field of the form
            Form_MoveCursorToPreviousField(&confirmation_form);


            break;

        case 0x0A:
            if (confirmation_form.activeFieldId == 1)
            {
                returnByte = 1;
            }
            else
            {
                returnByte = 0;
            }
            handleInput = 0;

        }

    } while (handleInput);

    Forms_FreeFieldSet(&confirmation_form);
    return returnByte;
}


void Utility_SetWindowMaximizable( u8 nState )
{

}