/*
	===========================================================================
	Name: dbhc.c
	Autor: Patrick Schorn
	IDE: Visual Studio 2015
	Programmschnittstellen: 
	Beschreibung: Stellt eine Verbindung zu den Datenbanken her. Erm�glicht das
	              Einloggen und Registrieren der Nutzer und Eintragungen in die
				  Highscore-Liste. Ebenso wird die Ausgabe der Highscore-Liste
				  erm�glicht.
	===========================================================================
*/

/*
	===========================================================================
	Pr�prozessoranweisungen
	===========================================================================
*/

#include "dbh.h"

/*
	===========================================================================
	Funktionsprototypen
	===========================================================================
*/

int login(char* cname, char* cpasswd);
int regist(char* cname, char* cpasswd);
int highscore(char* cname, int itime);
int highscore_print(int argc, char **argv, char **colName);

/*
	===========================================================================
	Funktion: Login
	�bergabeparameter: cname, cpasswd
	R�ckgabeparameter: 0, -1, -2
	Beschreibung: Erm�glicht das Einloggen von Nutzern, um sich in die 
				  Highscore-Liste eintragen und das Spiel spielen zu k�nnen.
				  Fragt die user_db nach eingegebenen Name und Passwort.
				  Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
	===========================================================================
*/

int login(char* cname, char* cpasswd)
{
	static int callback(void *data, int argc, char **argv, char **colName);
	char sql[100];
	char *zErrMsg;

	//Datenbank �ffnen
	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	//�berpr�fung Username
	sprintf(sql, "SELECT name FROM user_db WHERE name = '%s';", cname);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}

	//�berpr�fung Passwort
	sprintf(sql, "SELECT passwd FROM user_db WHERE passwd = '%s';", cpasswd);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-2);
	}
	else
	{
		printf("Login erfolgreich!");
		exit(0);
	}

	//Ausgabe Username
	sprintf(sql, "SELECT name FROM user_db WHERE name = '%s';", cname);
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else
	{
		printf("Willkommen, %s!", cname);
		exit(0);
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
	�bergabeparameter: cname, cpasswd
	R�ckgabeparameter: 0, -1
	Beschreibung: Nutzer registriert sich mit Name und Passwort. Diese Daten 
	              werden in die user_db eingetragen.
				  Bei Fehleingaben wird eine Fehlermeldung ausgegeben.
	===========================================================================
*/

int regist (char* cname, char* cpasswd)
{
	static int callback(void *data, int argc, char **argv, char **colName);
	char sql[100];
	char *zErrMsg;

	//Datenbank �ffnen
	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_USER, &pDb);

	//SQL Statement erstellen
	sprintf(sql, "INSERT INTO user_db (name, passwd)" \
		"VALUES ('%s', '%s');", cname, cpasswd);


	//SQL Statement ausf�hren
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);
	printf("Script wurde ausgef�hrt");

	//Return-Code �berpr�fen
	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		printf("\nDatenersatz erfolgreich erstellt!\n");
		exit(0);
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
	Funktion: Highscore
	�bergabeparameter: cname, itime
	R�ckgabeparameter: 0, -1
	Beschreibung: Nach erfolgreichem Abschlie�en des Sudokus werden der Name 
				  und die Zeit in die highscore_db eingetragen. Dabei wird ein
				  Sortieralgorithmus angewandt, um die Platzierungen nach der
				  abgeschlossenen Zeit zu sortieren.
	===========================================================================
*/

int highscore(char* cname, int itime)
{
	char sql[100];
	char *zErrMsg;

	//Datenbank �ffnen
	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE, &pDb);

	//SQL Statement erstellen
	sprintf(sql, "INSERT INTO highscore_db (name, time)" \
		"VALUES ('%s', '%i');", cname, itime);


	//SQL Statement ausf�hren
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);
	printf("Script wurde ausgef�hrt");

	//Return-Code �berpr�fen
	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		printf("\nDatenersatz erfolgreich erstellt!\n");
		exit(0);
	}

	//Datenbank schliessen
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE, &pDb);

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
	Funktion: Highscore_print
	�bergabeparameter: 
	R�ckgabeparameter: 0
	Beschreibung: Gibt die komplette Highscore-Liste aus
	===========================================================================
*/

int highscore_print(int argc, char **argv, char **colName)
{
	static int callback(void *data, int argc, char **argv, char **colName);
	int i;
	char sql[100];
	char *zErrMsg;

	//Datenbank �ffnen
	int rc;
	sqlite3 * pDb;
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE, &pDb);

	//SQL Statement erstellen
	sprintf(sql, "SELECT * FROM highscore_db");
	rc = sqlite3_exec(pDb, sql, NULL, NULL, &zErrMsg);

	//Ausgabe der Highscore-Liste
	if (rc != SQLITE_OK)
	{
		printf("\nSQL Fehler: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		for (i = 0; i<argc; i++)
		{ 
			printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL"); 
		}
		exit(0);
	}

	//Datenbank schliessen
	rc = sqlite3_open(DATABASE_FILE_HIGHSCORE, &pDb);

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