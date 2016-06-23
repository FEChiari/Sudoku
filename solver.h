#pragma once

/*
  ===========================================================================
  Präprozessorkonstanten
  ===========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"

#define MATRIX_SIZE 9
#define RAND(max) (rand() % max)

/*
  ===========================================================================
  Funktionsprototypen
  ===========================================================================
*/

u8 sudokuPruefung( struct sSudokuField[ MATRIX_SIZE ][ MATRIX_SIZE ] );
u8 loeseSudoku( struct sSudokuField[ MATRIX_SIZE ][ MATRIX_SIZE ] );
u8 zifferPruefung( struct sSudokuField[ MATRIX_SIZE ][ MATRIX_SIZE ], u8, u8, u8 );
u8 zaehleLeereFelder( struct sSudokuField[ MATRIX_SIZE ][ MATRIX_SIZE ] );
void generiereSudoku( struct sSudokuField[ MATRIX_SIZE ][ MATRIX_SIZE ], u8 );
