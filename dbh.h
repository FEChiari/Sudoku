/*
* Sudoku (dbh.h)
*
* Autoren: Werba, Schorn, Kremer, Prinz, Engels
* Datum: 19.06.16 - 24.06.16
*
* Beschreibung:
*
* Der DBHandler erm�glicht die Interaktion mit der f�r das Spiel notwendigen
* SQLite3 Datenbank.
*/

#ifndef _INCLUDE_DBH_H
#define _INCLUDE_DBH_H

/*
 * Definiert den Standardpfad, unter dem die SQLite Datenbank zu finden ist.
 */
#define DBH_DATABASE_FILE "databases/Sudoku.sqlite3"

#include <stdlib.h>

#include "types.h"
#include "lib\sqlite\sqlite3.h"

 /*
  * Typedef f�r standard SQLite-Callbacks.
  * Dient dazu, Funktionsprototypen k�rzer und lesbarer zu gestalten.
  */
typedef int( *DBH_pCallbackFn )( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );

/*
 * Mithilfe des Argumentenpaares wird es aufrufenden Funktionen erm�glicht,
 * festzustellen, wie viele Zeilen durchlaufen wurden.
 */
struct DBH_sCallbackArgumentPair
{
  u32 rowIter;
  void* additionalArgument;
};

/*
 * Die Funktion DBH_CreateHandle ist, wie die meisten DBH-Funktionen, ein recht
 * einfacher wrapper um SQLite3-native Funktionen. Intern wird sqlite3_open
 * aufgerufen, mit dem Unterschied, dass hier der Zeiger als Return-Wert
 * zur�ckgegeben wird.
 */
sqlite3* DBH_CreateHandle( char* nFilePath );

/*
 * Ebenso verh�lt es sich mit DBH_CloseHandle. Nach �bergabe eines ent-
 * sprechenden handles wird dieses geschlossen. Intern: sqlite3_close
 */
void DBH_CloseHandle( sqlite3* nHandle );

/*
 * Eine m�glichst generische Query-Funktion, die nutzerdefinierte Queries
 * vereinfachen soll.
 */
s32 DBH_Query( char* nQueryString, DBH_pCallbackFn nCallback, void* nCallbackArgument, char* nErrorMsg );

/*
 * Mehrere Convenience-Funktionen, die intern die respektiven Queries aufrufen.
 * Der R�ckgabewert indiziert, ob die Anfrage WAHR (1) oder FALSCH (0)
 * zur�ckgegeben hat.
 * Beispiel: UserExistsByName => SELECT 1 FROM Users WHERE username = '%s'
 */
u8 DBH_UserExistsByName( char* nUsername );
u8 DBH_UserExistsById( u32 nUserId );
u8 DBH_IsValidAuthByName( char* nUsername, char* nPassword );
u8 DBH_IsValidAuthById( u32 nUserId, char* nPassword );
u8 DBH_DeleteUser( u8 nUserId, char* nPassword );

/*
 * Eine Ausnahme bildet DBH_RegisterUser. Hier wird entweder die ID des neu
 * erstellten Benutzers oder, bei einem Fehler, 0 zur�ckgegeben.
 */
u32 DBH_RegisterUser( char* nUsername, char* nPassword );

/*
 * Generische Callback-Funktion zum z�hlen von Zeilen bei einer DB-Abfrage.
 */
int DBH_Callback_GetRowCount( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );

#endif