/*
	===========================================================================
	Dateiname: dbh.c
	Firma: HHBK Trendo Research Center
	Autor: Patrick Schorn, Fabian Engels
	IDE: Visual Studio 2015
	Programmschnittstellen:
	Beschreibung: Stellt eine Verbindung zu den Datenbanken her. Ermöglicht das
	    		  Einloggen und Registrieren der Nutzer sowie deren Löschung.
	===========================================================================
*/

/*
	===========================================================================
	Präprozessorkonstanten
	===========================================================================
*/

#include "dbh.h"

extern sqlite3* DBH_dbhnd;

/*
	===========================================================================
	Funktion: DBH_CreateHandle
	Übergabeparameter: nFilePath
	Rückgabeparameter: db
	Beschreibung: Erstellt einen Handler für die Datenbank
	===========================================================================
*/

sqlite3* DBH_CreateHandle( char* nFilePath )
{
  sqlite3* db = NULL;

  if ( sqlite3_open( nFilePath, &db ) == SQLITE_OK )
    return db;

  return NULL;
}

/*
	===========================================================================
	Funktion: DBH_CloseHandle
	Übergabeparameter: nHandle
	Rückgabeparameter: -
	Beschreibung: Schließt den Handler für die Datenbank
	===========================================================================
*/

void DBH_CloseHandle( sqlite3* nHandle )
{
  sqlite3_close( nHandle );
}

/*
	===========================================================================
	Funktion: DBH_Query
	Übergabeparameter: nQueryString, nCallback, nCallbackArgument, pErrMsgnErrorMsg
	Rückgabeparameter: sqlite3_exec
	Beschreibung: 
	===========================================================================
*/

s32 DBH_Query( char* nQueryString, DBH_pCallbackFn nCallback, void* nCallbackArgument, char* pErrMsgnErrorMsg )
{
  if ( nQueryString == NULL )
    return SQLITE_FAIL;

  return sqlite3_exec( DBH_dbhnd, nQueryString, nCallback, nCallbackArgument, &pErrMsgnErrorMsg );
}

/*
	===========================================================================
	Funktion: DBH_UserExistsByName
	Übergabeparameter: nUsername
	Rückgabeparameter: exists
	Beschreibung: Prüft in der Datenbank, ob der Username bereits existiert.
	===========================================================================
*/

u8 DBH_UserExistsByName( char* nUsername )
{
  u8 exists = 0;
  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "SELECT 1 FROM Users WHERE username = '%s'", nUsername );
  DBH_Query( pQueryString, DBH_Callback_GetRowCount, &exists, NULL );

  free( pQueryString );

  return exists;
}

/*
	===========================================================================
	Funktion: DBH_UserExistsByID
	Übergabeparameter: nUserId
	Rückgabeparameter: exists
	Beschreibung: Prüft in der Datenbank, ob die UserID bereits existiert.
	===========================================================================
*/

u8 DBH_UserExistsById( u32 nUserId )
{
  u8 exists = 0;
  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "SELECT 1 FROM Users WHERE id = '%d'", nUserId );
  DBH_Query( pQueryString, DBH_Callback_GetRowCount, &exists, NULL );

  free( pQueryString );

  return exists;
}

/*
	===========================================================================
	Funktion: DBH_IsValidAuthByName
	Übergabeparameter: nUsername, nPassword
	Rückgabeparameter: isValid
	Beschreibung: Prüft in der Datenbank, ob die Kombination von Username und
				  Passwort übereinstimmt.
	===========================================================================
*/

u8 DBH_IsValidAuthByName( char* nUsername, char* nPassword )
{
  u8 isValid = 0;
  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "SELECT 1 FROM Users WHERE username = '%s' and password = '%s'", nUsername, nPassword );
  DBH_Query( pQueryString, DBH_Callback_GetRowCount, &isValid, NULL );

  free( pQueryString );

  return isValid;
}

/*
	===========================================================================
	Funktion: DBH_IsValidAuthById
	Übergabeparameter: nUserId, nPassword
	Rückgabeparameter: isValid
	Beschreibung: Prüft in der Datenbank, ob die Kombination UserId und 
				  Passwort übereinstimmt.
	===========================================================================
*/

u8 DBH_IsValidAuthById( u32 nUserId, char* nPassword )
{
  u8 isValid = 0;
  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "SELECT 1 FROM Users WHERE id = '%d' and password = '%s'", nUserId, nPassword );
  DBH_Query( pQueryString, DBH_Callback_GetRowCount, &isValid, NULL );

  free( pQueryString );

  return isValid;
}

/*
	===========================================================================
	Funktion: DBH_RegisterUser
	Übergabeparameter: nUsername, nPassword
	Rückgabeparameter: uid
	Beschreibung: Ermöglicht die Registrierung eines Users in der Datenbank.
	===========================================================================
*/

u32 DBH_RegisterUser( char* nUsername, char* nPassword )
{
  u32 uid = 0;

  if ( DBH_UserExistsByName( nUsername ) ) return uid;

  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "INSERT INTO Users (username, password) VALUES ('%s', '%s')", nUsername, nPassword );
  DBH_Query( pQueryString, NULL, NULL, NULL );

  free( pQueryString );

  // assumes a maximum user id of 2^32
  uid = (u32) sqlite3_last_insert_rowid( DBH_dbhnd );

  return uid;
}

/*
	===========================================================================
	Funktion: DBH_DeleteUser
	Übergabeparameter: nUserId, nPassword
	Rückgabeparameter: deleted
	Beschreibung: Ermöglicht die Löschung eines Users aus der Datenbank.
	===========================================================================
*/

u8 DBH_DeleteUser( u8 nUserId, char* nPassword )
{
  s32 rc;
  u8 deleted = 0;

  if ( !DBH_UserExistsById( nUserId ) || !DBH_IsValidAuthById( nUserId, nPassword ) )
    return deleted;

  char* pQueryString = malloc( 128 );
  memset( pQueryString, 0, 128 );

  sprintf( pQueryString, "DELETE FROM Users WHERE id = %d", nUserId );
  rc = DBH_Query( pQueryString, NULL, NULL, NULL );

  free( pQueryString );

  if ( rc = SQLITE_OK ) deleted = 1;

  return deleted;
}

/*
	===========================================================================
	Funktion: DBH_Callback_GetRowCount
	Übergabeparameter: nCallbackParam, nNumColumns, nColumns, nColumnNames
	Rückgabeparameter: 0
	Beschreibung: Zählt die Anzahl der Spalten in der Datenbank.
	===========================================================================
*/

int DBH_Callback_GetRowCount( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames )
{
  static i = 0;
  *( ( u8* ) nCallbackParam ) = ++i;
  return 0;
}