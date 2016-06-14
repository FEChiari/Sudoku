#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_DEPRECATE 1
#define MATRIX_SIZE 9
#define True 1
#define False 0
#define RAND(max) (rand() % max + 1)


/* Funktionsprototypen */
int sudokuPruefung(int[][MATRIX_SIZE]);
int loeseSudoku(int[][MATRIX_SIZE]);
int zifferPruefung(int[][MATRIX_SIZE], int, int, int);
int zaehleLeereFelder(int[][MATRIX_SIZE]);
void generiereSudoku(int[][MATRIX_SIZE], int);

int main(void) {
	int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE];
	int backupMatrix[MATRIX_SIZE][MATRIX_SIZE];
	int iAnzahlLoeschen = 15; /*Abhängig von Schwierigkeitsgrad*/
	
	generiereSudoku(sudokumatrix, iAnzahlLoeschen);

	if (sudokuPruefung(sudokumatrix)){
		printf("correct sudoku\n");
	}
	
	return 0;
}

/* 
Die Funktion versucht, dass Sudoku rekursiv zu lösen, indem
jede Spalte von oben bis unten durchlaufen wird, und die Zahlen
gemäß den Sudoku-Regeln eingesetzt werden. Sollte keine Zahl passen,
geht der Algorithmus durch die Rekursion zurück und setzt an der 
letzten Stelle die nächstgrößere Zahl ein und fährt nach diesem
Prinzip fort.
 */
int loeseSudoku(int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]){
	int i,j,k;
	
	/* Suche nach "leeren Feldern" (Felder mit Wert = 0) */
	for (i = 0; i < MATRIX_SIZE; i++) {
		for (j = 0; j < MATRIX_SIZE; j++) {
			if (sudokumatrix[i][j] == 0) {
				/* 
				Ist ein "leeres Feld" gefunden, wird vom Algorithmus
				nacheinander geprüft, ob die Zahlen 1-9 (int: k) eingesetzt 
				werden können.
				*/
				for (k = 1; k <= MATRIX_SIZE; k++) {
					if (zifferPruefung(sudokumatrix, i, j, k)) {
						sudokumatrix[i][j] = k;
						/* 	
						Nach dem Einsetzen einer passenden Zahl wird der Algorithmus
						rekursiv aufgerufen und prüft die nächste freie Stelle 
						wieder mit Zahlen von 1 beginnend.
						*/
						if (loeseSudoku(sudokumatrix)) {
							return True;
						} else {
							/*
							Falls die Rekursion "False" zurückgegeben hat, wird
							der letzte Wert wieder auf 0 gesetzt und die nächste
							mögliche Zahl geprüft. (for-Schleife in Zeile 92)
							*/
							sudokumatrix[i][j] = 0;
						}
					}
				}
				/* 
				Falls keine Zahl mehr passt, gibt der Algorithmus "False" zurück
				und die Rekursion wird weiter abgearbeitet
				*/
				return False;
			}
		}
	}
	return 1;
}

/*
Die Funktion gleicht die übergebene Zahl (int iZahl) mit der Reihe, Spalte und dem Block
der ebenfalls übergebenen Koordinaten ab. Sie gibt "True" zurück, wenn die Zahl in noch
keiner Zeile, keiner Spalte und keinem Block vorkommt. "False" in dem Fall, dass sie 
bereits irgendwo auftaucht.
*/
int zifferPruefung(int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE], int x, int y, int iZahl) {
	int i;
	// Startkoordinaten des jeweiligen 3x3-Blockes der übergebenen Koordinaten x und y:
	int xBeginn=x-x%3;
	int yBeginn=y-y%3;
	for (i = 0; i < MATRIX_SIZE; i++) {
		// Reihe und Spalte der übergebenen Koordinaten x und y:
		if(sudokumatrix[i][y] == iZahl || sudokumatrix[x][i] == iZahl)
			return False;
		// Block der übergebenen Koordinaten x und y:
		if (sudokumatrix[xBeginn+i%3][yBeginn+i/3] == iZahl)
			return False;
	}
	return True;
}

/* 
Die Funktion gibt "True" zurück, wenn das übergebene Sudoku
korrekt gelöst ist. Dazu werden jeweils alle Werte der 
Reihen, Spalten und der 3x3-Blöcke addiert und geprüft ob diese
zusammen 45 ergeben, was die Summe der Zahlen 1-9 ist.
*/
int sudokuPruefung(int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i, j, iZeile, iSpalte, iBlock;
	
	for (i = 0; i < MATRIX_SIZE; i++) {
		iZeile = 0; 
		iSpalte = 0;
		iBlock = 0;
		
		for (j = 0; j < MATRIX_SIZE; j++) {
			iZeile += sudokumatrix[i][j];
			iSpalte += sudokumatrix[j][i];
			iBlock += sudokumatrix[i%3*3+j%3][i%3*3+j/3];
		}
		
		if (iZeile != 45 || iSpalte != 45 || iBlock != 45)
			return False;
	}	
	return True;
}

/* 
Die Funktion zählt, wieviele "Leere Felder" (Wert 0) im Sudoku
enthalten sind und gibt die Anzahl dieser zurück.
*/
int zaehleLeereFelder(int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i, j;
	int iZaehler = 0;
	for (i = 0; i < MATRIX_SIZE; i++){
		for (j = 0; j < MATRIX_SIZE; j++){
         if(sudokumatrix[i][j] == 0){
            iZaehler++;
         }
      }
   }
	return iZaehler;
}

/*
Die Funktion generiert ein Sudoku, indem zunächst ein leeres Sudoku initialisiert wird
(Werte alle 0) und danach zufällig die Zahlen 1-9 an zufällige Stellen eingetragen werden.
Danach wird dieses unfertige Sudoku gelöst und die (vom Schwierigkeitsgrad abhängige) Anzahl
an Zahlen gelöscht wird.
*/
void generiereSudoku(int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE], int iAnzahlLoeschen) {
   int i, j, iZeile, iSpalte;
	int zahlenArray[MATRIX_SIZE];
	
   srand(time(NULL));
	
   /*
   Es werden die Zahlen 1-9 in das Array geschrieben und das zweidimensionale
   Sudoku-Array mit "0en" an jeder Stelle initialisiert.
   */
	for (i = 0; i < MATRIX_SIZE; i++) {
		zahlenArray[i] = i + 1;
		for (j = 0; j < MATRIX_SIZE; j++){
			sudokumatrix[i][j] = 0;
		}
	}
	
	i=0;
   while (i < MATRIX_SIZE) {
      iZeile = RAND(MATRIX_SIZE);
      iSpalte = RAND(MATRIX_SIZE);
      if (sudokumatrix[iZeile][iSpalte] == 0) {
         sudokumatrix[iZeile][iSpalte] = zahlenArray[i];
         i++;
      }
   }

	// Löst das vorhandene nicht komplette Sudoku
	loeseSudoku(sudokumatrix);
	
	// Löscht die übergebene Anzahl (iAnzahlLoeschen) an Zahlen zufällig aus dem Sudoku
	for (i = 0; i < iAnzahlLoeschen; i++){
		sudokumatrix[RAND(MATRIX_SIZE)][RAND(MATRIX_SIZE)] = 0;
	}
}
