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














//
//
//
///*
//  ===========================================================================
//  Dateiname: dbh.c
//  Firma: HHBK Trendo Research Center
//  Autor: Patrick Schorn
//  IDE: Visual Studio 2015
//  Programmschnittstellen:
//  Beschreibung: Stellt eine Verbindung zu den Datenbanken her. Ermöglicht das
//                Einloggen und Registrieren der Nutzer sowie deren Löschung
//          und Eintragungen in die Highscore-Liste.
//          Ebenso wird die Ausgabe der Highscore-Liste ermöglicht.
//  ===========================================================================
//*/
//
///*
//  ===========================================================================
//  Präprozessoranweisungen
//  ===========================================================================
//*/
//
//#include "dbh.h"
//
//
//
//
//
///*
//  ===========================================================================
//  Funktion: Login
//  Übergabeparameter: cname, cpasswd
//  Rückgabeparameter: 0, -1, -2
//  Beschreibung: Ermöglicht das Einloggen von Nutzern, um sich in die
//          Highscore-Liste eintragen und das Spiel spielen zu können.
//          Fragt die user_db nach eingegebenen Name und Passwort.
//          Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
//  ===========================================================================
//*/
//
//int login( char* cname, char* cpasswd )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  //Datenbank öffnen
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  //Überprüfung Username
//  sprintf( sql, "SELECT name FROM user_db WHERE name = '%s';", cname );
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//    exit( -1 );
//  }
//
//  //Überprüfung Passwort
//  sprintf( sql, "SELECT passwd FROM user_db WHERE passwd = '%s';", cpasswd );
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//    exit( -2 );
//  }
//
//  //Ausgabe Username  -> in PdCurses realisieren
//  sprintf( sql, "SELECT name FROM user_db WHERE name = '%s';", cname );
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//    exit( -1 );
//  }
//
//  //Datenbank schliessen
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Regist
//  Übergabeparameter: cname, cpasswd
//  Rückgabeparameter: 0, -1
//  Beschreibung: Nutzer registriert sich mit Name und Passwort. Diese Daten
//                werden in die user_db eingetragen.
//          Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
//  ===========================================================================
//*/
//
//int regist( char* cname, char* cpasswd )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  sprintf( sql, "INSERT INTO user_db (name, passwd)" \
//    "VALUES ('%s', '%s');", cname, cpasswd );
//
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//  printf( "Script wurde ausgeführt" );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//  }
//
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Delete
//  Übergabeparameter: cname, cpasswd
//  Rückgabeparameter: 0, -1
//  Beschreibung: Ermöglicht das Löschen von Usern
//  ===========================================================================
//*/
//
//int delete( char* cname, char* cpasswd )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  sprintf( sql, "DELETE FROM user_db WHERE name = '%s';", cname );
//
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//  printf( "Script wurde ausgeführt" );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//  }
//
//  rc = sqlite3_open( DATABASE_FILE_USER, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Highscore
//  Übergabeparameter: cname, iuserid, itime, idifficulty
//  Rückgabeparameter: 0, -1
//  Beschreibung: Nach erfolgreichem Abschließen des Sudokus werden der Name
//          und die Zeit in die highscore_db eingetragen. Die Highscores
//          werden durch den Schwierigkeitsgrad differenziert.
//  ===========================================================================
//*/
//
//int highscore( char* cname, int iuserid, int itime, int idifficulty )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_EASY, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_NORMAL, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_HARD, &pDb );
//
//  //Der Gast-User darf nicht in den Highscore speichern!
//  if ( iuserid == 0 )
//  {
//  }
//  else
//  {
//    switch ( idifficulty )
//    {
//    case 1:
//      sprintf( sql, "INSERT INTO highscore_easy_db (name, time)" \
//        "VALUES ('%s', '%i');", cname, itime );
//
//      rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//      if ( rc != SQLITE_OK )
//      {
//        printf( "\nSQL Fehler: %s\n", zErrMsg );
//        sqlite3_free( zErrMsg );
//      }
//
//    case 2:
//      sprintf( sql, "INSERT INTO highscore_normal_db (name, time)" \
//        "VALUES ('%s', '%i');", cname, itime );
//
//      rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//      if ( rc != SQLITE_OK )
//      {
//        printf( "\nSQL Fehler: %s\n", zErrMsg );
//        sqlite3_free( zErrMsg );
//      }
//
//    case 3:
//      sprintf( sql, "INSERT INTO highscore_hard_db (name, time)" \
//        "VALUES ('%s', '%i');", cname, itime );
//
//      rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//      if ( rc != SQLITE_OK )
//      {
//        printf( "\nSQL Fehler: %s\n", zErrMsg );
//        sqlite3_free( zErrMsg );
//      }
//    }
//  }
//
//
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_EASY, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_NORMAL, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_HARD, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Highscore_Print
//  Übergabeparameter: idifficulty
//  Rückgabeparameter: 0, -1
//  Beschreibung: Bereitet die Ausgabe der Highscore-Liste vor.
//  ===========================================================================
//*/
//
//int highscore_print( int argc, char **argv, char **colName, int idifficulty )
//{
//  int i = 0;
//  char *sql;
//  char *zErrMsg = 'x';
//  sqlite3_stmt *stmt;
//  int col = 0;
//  int cols = 0;
//  const char *data = ' ';
//  int rc;
//  sqlite3 * pDb;
//
//
//  switch ( idifficulty )
//  {
//  case 1:
//    rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_EASY, &pDb );
//
//    //SQL String vorbereiten und Speicher reservieren 
//    sql = sqlite3_mprintf( "SELECT * FROM highscore_easy_db WHERE time ORDER BY time ASC" );
//
//    //SQL Statement und Struktur erzeugen 
//    rc = sqlite3_prepare_v2( pDb, sql, strlen( sql ), &stmt, NULL );
//
//    //Anzahl der Spalten in der Ergebnismenge ermitteln 
//    cols = sqlite3_column_count( stmt );
//
//    highscore_ausgeben( rc, col, cols, sql, data, stmt, zErrMsg );
//
//    break;
//
//  case 2:
//    rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_NORMAL, &pDb );
//    sql = sqlite3_mprintf( "SELECT * FROM highscore_normal_db WHERE time ORDER BY time ASC" );
//    rc = sqlite3_prepare_v2( pDb, sql, strlen( sql ), &stmt, NULL );
//    cols = sqlite3_column_count( stmt );
//
//    highscore_ausgeben( rc, col, cols, sql, data, stmt, zErrMsg );
//
//    break;
//
//  case 3:
//    rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_HARD, &pDb );
//    sql = sqlite3_mprintf( "SELECT * FROM highscore_hard_db WHERE time ORDER BY time ASC" );
//    rc = sqlite3_prepare_v2( pDb, sql, strlen( sql ), &stmt, NULL );
//    cols = sqlite3_column_count( stmt );
//
//    highscore_ausgeben( rc, col, cols, sql, data, stmt, zErrMsg );
//  }
//
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_EASY, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_NORMAL, &pDb );
//  rc = sqlite3_open( DATABASE_FILE_HIGHSCORE_HARD, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Highscore_Ausgeben
//  Übergabeparameter: rc, col, cols, sql, data, stmt, zErrMsg
//  Rückgabeparameter: 0, -1
//  Beschreibung: Gibt die komplette Highscore-Liste aus, differenziert durch
//          den Schwierigkeitsgrad. Die Ausgabe wird nach der am
//          schnellsten abgschlossenen Zeit sortiert.
//  ===========================================================================
//*/
//
//int highscore_ausgeben( int rc, int col, int cols, char sql, char *data,
//  sqlite3_stmt *stmt, char *zErrMsg )
//{
//  //Spaltennamen ausgeben 
//  for ( col = 0; col < cols; col++ )
//  {
//    printf( "%s ", ( const char* ) sqlite3_column_name( stmt, col ) );
//  }
//  printf( "\n" );
//
//  // Iteriert über die Datensätze in der Ergebnismenge 
//  while ( sqlite3_step( stmt ) == SQLITE_ROW )
//  {
//    for ( col = 0; col < cols; col++ )
//    {
//      //Nächstes Attribut holen und ausgeben  
//      data = ( const char* ) sqlite3_column_text( stmt, col );
//      printf( "%s ", data ? data : "NULL" );
//    }
//    printf( "\n" );
//  }
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//    exit( -1 );
//  }
//
//  //Speicher für SQL String freigeben 
//  sqlite3_free( sql );
//  //Speicher für Statement Struktur freigeben 
//  sqlite3_finalize( stmt );
//
//  return 0;
//}
//
///*
//  ===========================================================================
//  Funktion: Save_Game
//  Übergabeparameter: iuserid, itime, crow1-9
//  Rückgabeparameter: 0, -1
//  Beschreibung: In die Datenbank savestate_db wird der aktuelle Spielstand
//          gespeichert, unter Berücksichtigung der UserID und der
//          bereits abgelaufenen Zeit.
//  ===========================================================================
//*/
//int save_game( int iuserid, int itime, char* crow1, char* crow2, char* crow3,
//  char* crow4, char* crow5, char* crow6, char* crow7,
//  char* crow8, char* crow9 )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_SAVESTATE, &pDb );
//
//  sprintf( sql, "INSERT INTO savestate_db (UserID, time, Row1, Row2, Row3,"
//    "Row4, Row5, Row6, Row7, Row8, Row9)" \
//    "VALUES ('%i','%i','%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s',"
//    "'%s');",
//    iuserid, itime, crow1, crow2, crow3, crow4, crow5, crow6, crow7,
//    crow8, crow9 );
//
//
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//  printf( "Script wurde ausgeführt" );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//  }
//
//  rc = sqlite3_open( DATABASE_FILE_SAVESTATE, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
///*
//  ===========================================================================
//  Funktion: Load_Game
//  Übergabeparameter: iuserid, itime, crow1-9
//  Rückgabeparameter: 0, -1
//  Beschreibung: Lädt ein aktuelles Spiel anhand der zugehörigen UserID
//          des eingeloggten Users.
//  ===========================================================================
//*/
//
//int load_game( int iuserid, int itime, char* crow1, char* crow2, char* crow3,
//  char* crow4, char* crow5, char* crow6, char* crow7,
//  char* crow8, char* crow9 )
//{
//  char sql[ 100 ];
//  char *zErrMsg;
//
//  int rc;
//  sqlite3 * pDb;
//  rc = sqlite3_open( DATABASE_FILE_SAVESTATE, &pDb );
//
//  sprintf( sql, "SELECT * FROM savestate_db" );
//  rc = sqlite3_exec( pDb, sql, NULL, NULL, &zErrMsg );
//
//  if ( rc != SQLITE_OK )
//  {
//    printf( "\nSQL Fehler: %s\n", zErrMsg );
//    sqlite3_free( zErrMsg );
//  }
//
//  rc = sqlite3_open( DATABASE_FILE_SAVESTATE, &pDb );
//
//  if ( rc != SQLITE_OK )
//  {
//    sqlite3_close( pDb );
//    exit( -1 );
//  }
//  else
//  {
//    return 0;
//  }
//}
//
//

