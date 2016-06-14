#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"


#define MATRIX_SIZE 9
#define RAND(max) (rand() % max)

/* Funktionsprototypen */
int sudokuPruefung( int[][ MATRIX_SIZE ] );
int loeseSudoku( int[][ MATRIX_SIZE ] );
int zifferPruefung( int[][ MATRIX_SIZE ], int, int, int );
int zaehleLeereFelder( int[][ MATRIX_SIZE ] );
void generiereSudoku( int[][ MATRIX_SIZE ], int );
