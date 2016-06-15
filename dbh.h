#pragma once

#include "lib\sqlite\sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATABASE_FILE_USER "databases/user_db.sqlite3"
#define DATABASE_FILE_HIGHSCORE_EASY "databases/highscore-easy_db.sqlite3"
#define DATABASE_FILE_HIGHSCORE_NORMAL "databases/highscore-normal_db.sqlite3"
#define DATABASE_FILE_HIGHSCORE_HARD "databases/highscore-hard_db.sqlite3"
#define DATABASE_FILE_SAVESTATE "databases/savestate_db.sqlite3"


/*
===========================================================================
Funktionsprototypen
===========================================================================
*/

int login( char* cname, char* cpasswd );
int regist( char* cname, char* cpasswd );
int delete( char* cname, char* cpasswd );
int highscore( char* cname, int iuserid, int itime, int idifficulty );
int highscore_print( int argc, char **argv, char **colName, int idifficulty );

int save_game( int iuserid, int itime, char* crow1, char* crow2, char* crow3,
  char* crow4, char* crow5, char* crow6, char* crow7,
  char* crow8, char* crow9 );

int load_game( int iuserid, int itime, char* crow1, char* crow2, char* crow3,
  char* crow4, char* crow5, char* crow6, char* crow7,
  char* crow8, char* crow9 );