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

int sudokuPruefung( struct sSudokuField[][ MATRIX_SIZE ] );
int loeseSudoku( struct sSudokuField[][ MATRIX_SIZE ] );
int zifferPruefung( struct sSudokuField[][ MATRIX_SIZE ], int, int, int );
int zaehleLeereFelder( struct sSudokuField[][ MATRIX_SIZE ] );
void generiereSudoku( struct sSudokuField[][ MATRIX_SIZE ], int );
