/* 
   ========================================================================
   Autoren       : Fabian Prinz, Fabian Kremer
   Firma       : A-Team // HHBKTendo Research Center
   Dateiname   : solver.c
   Datum       : 14.06.2016
   Beschreibung: solver.c kann Sudokus generieren, indem es die Zahlen 1-9
         zufällig im Sudoku-Array verteilt und dieses dann löst. Dazu werden,
         abhängig von einem Parameter, zufällige Zahlen gelöscht, um das Sudoku
         "spielbar" zu machen.
         Eine weitere Funktion des Solvers ist das Zählen der noch freien 
         Stellen und das Überprüfen, ob ein vollständig ausgefülltes Sudoku
         korrekt ist.
   Version     : 1.3
   Programmschnittstellen: 
            int sudokuPruefung(int[][MATRIX_SIZE]);
            int loeseSudoku(int[][MATRIX_SIZE]);
            int zifferPruefung(int[][MATRIX_SIZE], int, int, int);
            int zaehleLeereFelder(int[][MATRIX_SIZE]);
            void generiereSudoku(int[][MATRIX_SIZE], int);
            int sudokuPruefungUnfertig(int[][MATRIX_SIZE]);
            int gibHinweis(int [][MATRIX_SIZE]);
   ======================================================================== 
*/

/* 
   ======================================================================== 
   Include Dateien
   ======================================================================== 
*/
#include "solver.h"

//int main(void) {
//  int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE];
//  int backupMatrix[MATRIX_SIZE][MATRIX_SIZE];
//  int iAnzahlLoeschen = 15; /*Abhängig von Schwierigkeitsgrad*/
//  
//  generiereSudoku(sudokumatrix, iAnzahlLoeschen);
//
//  if (sudokuPruefung(sudokumatrix)){
//    printf("correct sudoku\n");
//  }
//  
//  return 0;
//}

/* 
   ======================================================================== 
   Funktion: int loeseSudoku()
   Beschreibung: Die Funktion versucht, dass Sudoku rekursiv zu lösen, indem
         jede Spalte von oben bis unten durchlaufen wird, und die Zahlen
         gemäß den Sudoku-Regeln eingesetzt werden. Sollte keine Zahl passen,
         geht der Algorithmus durch die Rekursion zurück und setzt an der 
         letzten Stelle die nächstgrößere Zahl ein und fährt nach diesem
         Prinzip fort.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]
   Rueckgabewerte: 0, 1
   ======================================================================== 
*/
int loeseSudoku(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]){
	int i,j,k,l;
   int izahlenArray[MATRIX_SIZE];
   int iZufall, iZiffer;
	
	/* Suche nach "leeren Feldern" (Felder mit Wert = 0) */
	for (i = 0; i < MATRIX_SIZE; i++) {
		for (j = 0; j < MATRIX_SIZE; j++) {
			if (sudokumatrix[i][j].value == 0) {
				/* 
				Ist ein "leeres Feld" gefunden, wird vom Algorithmus
            eine zufällige Zahl zwischen 1 und 9 geprüft und,
            falls sie passend ist, eingesetzt.
				*/

            //Initialisierung des Zufallsgenerators
            srand((unsigned)time(NULL));
	
            //Initialisierung des Arrays von 1-9
	    for (l = 0; l < MATRIX_SIZE; l++) {
		  izahlenArray[l] = l + 1;
            }

	      for (k = 0; k < MATRIX_SIZE; k++) {
               /*
               Holt eine zufällige Zahl aus dem Array, setzt danach
               die letzte Zahl des Arrays an die angefragte Stelle.
               Nach einer weiteren for-Schleife ist der "Abfrage-
               Bereich" dementsprechend kleiner, so dass immer eine
               Stelle des Arrays weniger abgefragt wird.
               */
               iZufall = RAND((MATRIX_SIZE-k));
               iZiffer = izahlenArray[iZufall];
               izahlenArray[iZufall] = izahlenArray[MATRIX_SIZE-(k+1)];              

					if (zifferPruefung(sudokumatrix, i, j, iZiffer)) {
						sudokumatrix[i][j].value = iZiffer;
						/* 	
						Nach dem Einsetzen einer passenden Zahl wird der 
                  Algorithmus rekursiv aufgerufen und prüft die nächste 
                  freie Stelle wieder mit Zahlen von 1 beginnend.
						*/
						if (loeseSudoku(sudokumatrix)) {
							return 1;
						} else {
							/*
							Falls die Rekursion 0 zurückgegeben hat, wird
							der letzte Wert wieder auf 0 gesetzt und die nächste
							mögliche Zahl geprüft. (for-Schleife in Zeile 92)
							*/
							sudokumatrix[i][j].value = 0;
						}
					}
				}
				/* 
				Falls keine Zahl mehr passt, gibt der Algorithmus 0 zurück
				und die Rekursion wird weiter abgearbeitet
				*/
				return 0;
			}
		}
	}
	return 1;
}

/* 
   ======================================================================== 
   Funktion: int zifferPruefung()
   Beschreibung: Die Funktion gleicht die übergebene Zahl (int iZahl) mit 
         der Reihe, Spalte und dem Block der ebenfalls übergebenen Koordinaten
         ab. Sie gibt 1 zurück, wenn die Zahl in noch keiner Zeile, 
         keiner Spalte und keinem Block vorkommt. 0 in dem Fall, dass 
         sie bereits irgendwo auftaucht.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE], 
         int x, int y, int iZahl
   Rueckgabewerte: 0, 1
   ======================================================================== 
*/
int zifferPruefung(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE], int x, 
                     int y, int iZahl) {
	int i;
	/*
   Startkoordinaten des jeweiligen 3x3-Blockes der übergebenen 
   Koordinaten x und y:
   */
	int xBeginn=x-x%3;
	int yBeginn=y-y%3;
	for (i = 0; i < MATRIX_SIZE; i++) {
		// Reihe und Spalte der übergebenen Koordinaten x und y:
		if(sudokumatrix[i][y].value == iZahl || sudokumatrix[x][i].value == iZahl)
			return 0;
		// Block der übergebenen Koordinaten x und y:
		if (sudokumatrix[xBeginn+i%3][yBeginn+i/3].value == iZahl)
			return 0;
	}
	return 1;
}

/*
Die Funktion gibt 1 zurück, wenn das übergebene Sudoku
korrekt gelöst ist. Dazu werden jeweils alle Werte der
Reihen, Spalten und der 3x3-Blöcke addiert und geprüft ob diese
zusammen 45 ergeben, was die Summe der Zahlen 1-9 ist.
*/
/*
   ======================================================================== 
   Funktion: int sudokuPruefung()
   Beschreibung: Die Funktion gibt 1 zurück, wenn das übergebene Sudoku
         korrekt gelöst ist. Dazu werden jeweils alle Werte der Reihen, 
         Spalten und der 3x3-Blöcke addiert und geprüft ob diese zusammen 
         45 ergeben, was die Summe der Zahlen 1-9 ist.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]
   Rueckgabewerte: 0, 1
   ======================================================================== 
*/
int sudokuPruefung(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i, j, iZeile, iSpalte, iBlock;
	
	for (i = 0; i < MATRIX_SIZE; i++) {
		iZeile = 0; 
		iSpalte = 0;
		iBlock = 0;
		
		for (j = 0; j < MATRIX_SIZE; j++) {
			iZeile += sudokumatrix[i][j].value;
			iSpalte += sudokumatrix[j][i].value;
			iBlock += sudokumatrix[i%3*3+j%3][i%3*3+j/3].value;
		}
		
		if (iZeile != 45 || iSpalte != 45 || iBlock != 45)
			return 0;
	}	
	return 1;
}

/* 
   ======================================================================== 
   Funktion: int sudokuPruefungUnfertig()
   Beschreibung: Die Funktion prüft ein unfertiges Sudoku. Sie durchläuft
         das Array und ruft mit jedem Wert, der eingetragen ist die Funktion
         zifferPruefung() auf. Ist diese korrekt, wird mit dem nächsten Wert
         fortgefahren. Ist die Prüfung falsch, gibt die ganze Funktion 0
         zurück.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]
   Rueckgabewerte: 0, 1
   ======================================================================== 
*/
int sudokuPruefungUnfertig(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i, j;
	
	for (i = 0; i < MATRIX_SIZE; i++) {		
      j = 0;
		while(j < MATRIX_SIZE){
         if(sudokumatrix[i][j].value != 0 
               && zifferPruefung(sudokumatrix, i, j, sudokumatrix[i][j].value)){
            j++;
         } else {
            return 0;
         }
		}
   }
   return 1;
}

/* 
   ======================================================================== 
   Funktion: int zaehleLeereFelder()
   Beschreibung: Die Funktion zählt, wieviele "Leere Felder" (Wert 0) im 
         Sudoku enthalten sind und gibt die Anzahl dieser zurück.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]
   Rueckgabewerte: iZaehler
   ======================================================================== 
*/
int zaehleLeereFelder(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i, j;
	int iZaehler = 0;
	for (i = 0; i < MATRIX_SIZE; i++){
		for (j = 0; j < MATRIX_SIZE; j++){
         if(sudokumatrix[i][j].value == 0){
            iZaehler++;
         }
      }
   }
	return iZaehler;
}

/* 
   ======================================================================== 
   Funktion: int gibHinweis()
   Beschreibung: Die Funktion löst eine zufällige Stelle im Sudoku an dem 
         der Spieler gerade spielt. Dazu wird die Sudokumatrix zwischen-
         gespeichert und falls sie lösbar ist, wird ein zufälliger Wert in 
         die Original-Matrix eingetragen und es wird 1 zurückgegeben. Ist das
         Sudoku so nicht lösbar, gibt die Funktion 0 zurück.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE]
   Rueckgabewerte: 0, 1
   ======================================================================== 
*/
int gibHinweis(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE])
{
   int backupmatrix[MATRIX_SIZE][MATRIX_SIZE];
   int i,j;
   int iZufallx, iZufally;
   int k = 0;

   /*
   Zwischenspeichern der Spiel-Matrix in backupmatrix[][]
   */
   for(i = 0; i < MATRIX_SIZE; i++){
      for(j = 0; j < MATRIX_SIZE; j++){
         backupmatrix[i][j] = sudokumatrix[i][j].value;
      }
   }

   /*
   Ist das Sudoku zum Zeitpunkt des Aufrufs lösbar, wird eine richtige 
   Zahl in das Sudoku gesetzt und 1 zurückgegeben. Ist es nicht lösbar
   wird 0 zurückgegeben.
   */
   if(loeseSudoku(backupmatrix)){
      do{
         iZufallx = RAND(MATRIX_SIZE);
         iZufally = RAND(MATRIX_SIZE);
         if(sudokumatrix[iZufallx][iZufally].value == 0){
            sudokumatrix[iZufallx][iZufally].value = backupmatrix[iZufallx][iZufally];
            k = 1;
         }
      }while(k == 0);
      return 1;
   }else{
      return 0;
   }
}

/* 
   ======================================================================== 
   Funktion: void generiereSudoku()
   Beschreibung: Die Funktion generiert ein Sudoku, indem zunächst ein leeres
         Sudoku initialisiert wird (Werte alle 0) und danach zufällig die 
         Zahlen 1-9 an zufällige Stellen eingetragen werden. Danach wird 
         dieses unfertige Sudoku gelöst und die (vom Schwierigkeitsgrad 
         abhängige) Anzahl an Zahlen gelöscht wird.
   Uebergabeparameter: int sudokumatrix[MATRIX_SIZE][MATRIX_SIZE], 
         int iAnzahlLoeschen
   Rueckgabewerte: -
   ======================================================================== 
*/
void generiereSudoku(struct sSudokuField sudokumatrix[MATRIX_SIZE][MATRIX_SIZE],
                     int iAnzahlLoeschen) {
   int i, j, iZeile, iSpalte;
	int zahlenArray[MATRIX_SIZE];
	
   //Initialisierung des Zufallsgenerators
   srand((unsigned)time(NULL));
	
   /*
   Es werden die Zahlen 1-9 in das Array geschrieben und das zweidimensionale
   Sudoku-Array mit "0en" an jeder Stelle initialisiert.
   */
	for (i = 0; i < MATRIX_SIZE; i++) {
		zahlenArray[i] = i + 1;
		for (j = 0; j < MATRIX_SIZE; j++){
			sudokumatrix[i][j].value = 0;
		}
	}
	
	i=0;
   while (i < MATRIX_SIZE) {
      iZeile = RAND(MATRIX_SIZE);
      iSpalte = RAND(MATRIX_SIZE);
      if (sudokumatrix[iZeile][iSpalte].value == 0) {
         sudokumatrix[iZeile][iSpalte].value = zahlenArray[i];
		 sudokumatrix[iZeile][iSpalte].type = FIELD_FILLED_IN;
		 i++;
      }
   }

	// Löst das vorhandene nicht komplette Sudoku
	loeseSudoku(sudokumatrix);
	
	/*
   Löscht die übergebene Anzahl (iAnzahlLoeschen) an Zahlen 
   zufällig aus dem Sudoku
   */
   i=0;
   while (i < iAnzahlLoeschen) {
      iZeile = RAND(MATRIX_SIZE);
      iSpalte = RAND(MATRIX_SIZE);
      if (sudokumatrix[iZeile][iSpalte].value != 0) {
         sudokumatrix[iZeile][iSpalte].value = 0;
		 sudokumatrix[iZeile][iSpalte].type = FIELD_FILLED_IN;
         i++;
      }
   }
}
