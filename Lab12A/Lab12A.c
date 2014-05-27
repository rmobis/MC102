/* Nome: Raphael Mobis Tacla
* RA: 157104
* Laboratorio 12A - CUT++
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_FIELD_LENGTH    500

#define EOL       '\n'
#define SEPARATOR ','

/* Prototipo das funcoes utilizadas pela main */
void generateReducedCSV(char fnamein[], char fnameout[]);

int countRows(FILE *inputFile);

void readWantedFields(int **wantedFields, int *wantedFieldsAmount);

bool getRow(FILE *inputFile, FILE *outputFile, int rowCount, char **lineData, int wantedFields[], int wantedFieldsAmount);

int main(int argc, char *argv[]) {
	char fnamein[MAX_FILENAME_LENGTH + 1], fnameout[MAX_FILENAME_LENGTH + 1];

	strcpy(fnamein, argv[1]);
	strcpy(fnameout, argv[2]);

	generateReducedCSV(fnamein, fnameout);

	return 0;
}

void generateReducedCSV(char fnamein[], char fnameout[]) {
	char **lineData;
	FILE *inputFile, *outputFile;
	int wantedFieldsAmount;
	int *wantedFields;
	bool endOfFile;
	int rowCount;

	inputFile = fopen(fnamein, "r");
	outputFile = fopen(fnameout, "w");

	rowCount = countRows(inputFile);

	lineData = (char **) malloc(rowCount * sizeof(char *));

	readWantedFields(&wantedFields, &wantedFieldsAmount);

	do {
		endOfFile = getRow(inputFile, outputFile, rowCount, lineData, wantedFields, wantedFieldsAmount);
	} while (!endOfFile);

	fclose(inputFile);
	fclose(outputFile);
	free(lineData);
}

int countRows(FILE *inputFile) {
	char nextChar;
	int rowCount = 1;

	rewind(inputFile);

	do {
		fscanf(inputFile, "%c", &nextChar);

		if (nextChar == SEPARATOR) {
			rowCount++;
		}
	} while (nextChar != EOL);

	rewind(inputFile);

	return rowCount;
}

void readWantedFields(int **wantedFields, int *wantedFieldsAmount) {
	int i;

	scanf("%d", wantedFieldsAmount);

	*wantedFields = (int *) malloc((*wantedFieldsAmount - 1) * sizeof(int));

	for (i = 0; i < *wantedFieldsAmount; i++) {
		scanf("%d", &(*wantedFields)[i]);
		(*wantedFields)[i]--;
	}
}

bool getRow(FILE *inputFile, FILE *outputFile, int rowCount, char **lineData, int wantedFields[], int wantedFieldsAmount) {
	int curFieldLength;
	char curField[MAX_FIELD_LENGTH + 1];
	bool endOfFile = false;
	char nextChar;
	int i;

	for (i = 0; i < rowCount; i++) {
		curFieldLength = 0;

		do {
			endOfFile = (fscanf(inputFile, "%c", &nextChar) == EOF);
			curField[curFieldLength++] = nextChar;
		} while (!endOfFile && nextChar != EOL && nextChar != SEPARATOR);

		curField[--curFieldLength] = '\0';

		lineData[i] = (char *) malloc((strlen(curField) + 1) * sizeof(char));
		strcpy(lineData[i], curField);
	}

	for (i = 0; i < wantedFieldsAmount; i++) {
		fprintf(outputFile, "%s", lineData[wantedFields[i]]);

		if (i != wantedFieldsAmount - 1) {
			fprintf(outputFile, ",");
		}
	}

	if (!endOfFile) {
		fprintf(outputFile, "\n");
	}

	for (i = 0; i < rowCount; i++) {
		free(lineData[i]);
	}

	return endOfFile;
}