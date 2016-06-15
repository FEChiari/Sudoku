/*
	===========================================================================
	Dateiname: dbh.c
	Firma: HHBK Trendo Research Center
	Autor: Patrick Schorn
	IDE: Visual Studio 2015
	Programmschnittstellen: 
	Beschreibung: Stellt eine Verbindung zu den Datenbanken her. Ermöglicht das
	              Einloggen und Registrieren der Nutzer sowie deren Löschung
				  und Eintragungen in die Highscore-Liste. 
				  Ebenso wird die Ausgabe der Highscore-Liste ermöglicht.
	===========================================================================
*/

/*
	===========================================================================
	Präprozessoranweisungen
	===========================================================================
*/

#include "dbh.h"

/*
	===========================================================================
	Funktion: Login
	Übergabeparameter: cname, cpasswd
	Rückgabeparameter: 0, -1, -2
	Beschreibung: Ermöglicht das Einloggen von Nutzern, um sich in die 
				  Highscore-Liste eintragen und das Spiel spielen zu können.
				  Fragt die user_db nach eingegebenen Name und Passwort.
				  Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
	===========================================================================
*/

int login(char* cname, char* cpasswd)
{
	char sql[100];
	char *zErrMsg;

	//Datenbank öffnen
	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	//Überprüfung Username
	sprintf(sql, "SELECT name FROM user_db WHERE name = '%s';", cname);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}

	//Überprüfung Passwort
	sprintf(sql, "SELECT passwd FROM user_db WHERE passwd = '%s';", cpasswd);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-2);
	}

	//Ausgabe Username  -> in PdCurses realisieren
	sprintf(sql, "SELECT name FROM user_db WHERE name = '%s';", cname);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}

	//Datenbank schliessen
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Regist
	Übergabeparameter: cname, cpasswd
	Rückgabeparameter: 0, -1
	Beschreibung: Nutzer registriert sich mit Name und Passwort. Diese Daten 
	              werden in die user_db eingetragen.
				  Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
	===========================================================================
*/

int regist (char* cname, char* cpasswd)
{
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	sprintf(sql, "INSERT INTO user_db (name, passwd)" \
		"VALUES ('%s', '%s');", cname, cpasswd);

	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);
	printf("Script wurde ausgeführt");

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Delete
	Übergabeparameter: cname, cpasswd
	Rückgabeparameter: 0, -1
	Beschreibung: Ermöglicht das Löschen von Usern
	===========================================================================
*/

int delete(char* cname, char* cpasswd)
{
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	sprintf(sql, "DELETE FROM user_db WHERE name = '%s';", cname);

	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);
	printf("Script wurde ausgeführt");

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Highscore
	Übergabeparameter: cname, iuserid, itime, idifficulty
	Rückgabeparameter: 0, -1
	Beschreibung: Nach erfolgreichem Abschließen des Sudokus werden der Name
				  und die Zeit in die highscore_db eingetragen. Die Highscores
				  werden durch den Schwierigkeitsgrad differenziert.
	===========================================================================
*/

int highscore(char* cname, int iuserid, int itime, int idifficulty)
{
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_EASY, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_NORMAL, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_HARD, &pDb);
	
	//Der Gast-User darf nicht in den Highscore speichern!
	if (iuserid == 0)
	{
	}
	else
	{
		switch (idifficulty)
		{
			case 1:
				sprintf(sql, "INSERT INTO highscore_easy_db (name, time)" \
					"VALUES ('%s', '%i');", cname, itime);

				rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

				if (rc != SQLITE_OK)
				{
					printf("\nSQL Fehler: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
		
			case 2:	
				sprintf(sql, "INSERT INTO highscore_normal_db (name, time)" \
					"VALUES ('%s', '%i');", cname, itime);

				rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

				if (rc != SQLITE_OK)
				{
					printf("\nSQL Fehler: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
		
			case 3:	
				sprintf(sql, "INSERT INTO highscore_hard_db (name, time)" \
					"VALUES ('%s', '%i');", cname, itime);

				rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

				if (rc != SQLITE_OK)
				{
					printf("\nSQL Fehler: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
			}
		}
	

	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_EASY, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_NORMAL, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_HARD, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Highscore_Print
	Übergabeparameter: idifficulty
	Rückgabeparameter: 0, -1
	Beschreibung: Gibt die komplette Highscore-Liste aus, differenziert durch 
				  den Schwierigkeitsgrad. Die Ausgabe wird nach der am 
				  schnellsten abgschlossenen Zeit sortiert.
	===========================================================================
*/

int highscore_print(int argc, char **argv, char **colName, int idifficulty)
{
	static int callback(void *data, int argc, char **argv, char **colName);
	int i;
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_EASY, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_NORMAL, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_HARD, &pDb);

	switch (idifficulty)
	{
		case 1:
			sprintf(sql, "SELECT id, time FROM highscore_easy_db ORDER BY time ASC");

			rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

			if (rc != SQLITE_OK)
			{
				printf("\nSQL Fehler: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			break;

		case 2:
			sprintf(sql, "SELECT id, time FROM highscore_normal_db ORDER BY time ASC");

			rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

			if (rc != SQLITE_OK)
			{
				printf("\nSQL Fehler: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			break;

		case 3:
			sprintf(sql, "SELECT id, time FROM highscore_hard_db ORDER BY time ASC");

			rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

			if (rc != SQLITE_OK)
			{
				printf("\nSQL Fehler: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
	}

	//Ausgabe der Highscore-Liste -> in PdCurses realisieren
	for (i = 0; i<argc; i++)
	{ 
		printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL"); 
	}
	printf("\n");
	exit(0);

	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_EASY, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_NORMAL, &pDb);
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE_HARD, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Save_Game
	Übergabeparameter: iuserid, itime, crow1-9
	Rückgabeparameter: 0, -1
	Beschreibung: In die Datenbank savestate_db wird der aktuelle Spielstand
				  gespeichert, unter Berücksichtigung der UserID und der 
				  bereits abgelaufenen Zeit.
	===========================================================================
*/
int save_game(int iuserid, int itime, char* crow1, char* crow2, char* crow3,
	char* crow4, char* crow5, char* crow6, char* crow7,
	char* crow8, char* crow9)
{
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_SAVESTATE, &pDb);

	sprintf(sql, "INSERT INTO savestate_db (UserID, time, Row1, Row2, Row3," 
		"Row4, Row5, Row6, Row7, Row8, Row9)" \
		"VALUES ('%i','%i','%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'," 
		"'%s');",
		iuserid, itime, crow1, crow2, crow3, crow4, crow5, crow6, crow7, 
		crow8, crow9);


	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);
	printf("Script wurde ausgeführt");

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	rc = sqlite3_open(DATABASE_FILE_SAVESTATE, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}

/*
	===========================================================================
	Funktion: Load_Game
	Übergabeparameter: iuserid, itime, crow1-9
	Rückgabeparameter: 0, -1
	Beschreibung: Lädt ein aktuelles Spiel anhand der zugehörigen UserID 
				  des eingeloggten Users.
	===========================================================================
*/

int load_game(int iuserid, int itime, char* crow1, char* crow2, char* crow3,
	char* crow4, char* crow5, char* crow6, char* crow7,
	char* crow8, char* crow9)
{
	char sql[100];
	char *zErrMsg;

	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_SAVESTATE, &pDb);

	sprintf(sql, "SELECT * FROM savestate_db");
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	rc = sqlite3_open(DATABASE_FILE_SAVESTATE, &pDb);

	if (rc != SQLITE_OK)
	{
		sqlite3_close(pDb);
		exit(-1);
	}
	else
	{
		return 0;
	}
}