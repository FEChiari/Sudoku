#pragma once

#define DBH_DATABASE_FILE "databases/Sudoku.sqlite3"

#include <stdlib.h>

#include "types.h"
#include "lib\sqlite\sqlite3.h"

typedef int( *DBH_pCallbackFn )( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );


sqlite3* DBH_CreateHandle( char* nFilePath );
void DBH_CloseHandle( sqlite3* nHandle );

s32 DBH_Query( char* nQueryString, DBH_pCallbackFn nCallback, void* nCallbackArgument, char* nErrorMsg );

u8 DBH_UserExistsByName( char* nUsername );
u8 DBH_UserExistsById( u32 nUserId );
u8 DBH_IsValidAuthByName( char* nUsername, char* nPassword );
u8 DBH_IsValidAuthById( u32 nUserId, char* nPassword );

u32 DBH_RegisterUser( char* nUsername, char* nPassword );
u8 DBH_DeleteUser( u8 nUserId, char* nPassword );

// struct sSaveState DBH_GetLastSaveState(u8 nUserId, char* nPassword);

int DBH_Callback_GetRowCount( void* nCallbackParam, int nNumColumns, char** nColumns, char** nColumnNames );