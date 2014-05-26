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



bool getLineFields(FILE *inputFile, FILE *outputFile, int *wantedFieldsOrder, int wantedFieldsAmount, bool *wantedFields, int maxWantedIndex) {
	int i;
	char curField[MAX_FIELD_LENGTH + 1];
	int curFieldLength;
	char nextChar;
	char **lineFields;

	bool endOfFile = false;

	lineFields = malloc(maxWantedIndex * sizeof(char*));

	for (i = 0; i <= maxWantedIndex; i++) {
		if (wantedFields[i]) {
			curFieldLength = 0;

			do {
				endOfFile = (fscanf(inputFile, "%c", &nextChar) == EOF);
				curField[curFieldLength++] = nextChar;
			} while (!endOfFile && nextChar != SEPARATOR && nextChar != EOL);

			curFieldLength -= (i == maxWantedIndex);
			curField[curFieldLength] = '\0';

			lineFields[i] = malloc(501 * sizeof(char));
			/*strcpy(lineFields[i], curField);*/
		} else {
			/* Ignorar campos que não queremos, economizando memória e processamento */
			do {
				endOfFile = (fscanf(inputFile, "%c", &nextChar) == EOF);
			} while (!endOfFile && nextChar != SEPARATOR && nextChar != EOL);
		}
	}


	while (!endOfFile && nextChar != EOL) {
		endOfFile = (fscanf(inputFile, "%c", &nextChar) == EOF);
	}

	/*for (i = 0; i < wantedFieldsAmount; i++) {
		fprintf(outputFile, "%s", lineFields[wantedFieldsOrder[i]]);
	}*/

	for (i = 0; i <= maxWantedIndex; i++) {
		if (wantedFields[i]) {
			free(lineFields[i]);
		}
	}

	if (!endOfFile && curField[0]) {
		fprintf(outputFile, "\n");
	}

	return endOfFile;
}

void readWantedFields(int **wantedFieldsOrder, int *wantedFieldsAmount, bool **wantedFields, int *maxWantedIndex) {
	int i;

	scanf("%d", wantedFieldsAmount);

	*wantedFieldsOrder = malloc((*wantedFieldsAmount - 1) * sizeof(int));

	*maxWantedIndex = 0;
	for (i = 0; i < *wantedFieldsAmount; i++) {
		scanf("%d", &(*wantedFieldsOrder)[i]);
		(*wantedFieldsOrder)[i]--;

		if (*maxWantedIndex < (*wantedFieldsOrder)[i]) {
			*maxWantedIndex = (*wantedFieldsOrder)[i];
		}
	}


	*wantedFields = malloc((*maxWantedIndex + 1) * sizeof(bool));

	for (i = 0; i <= *maxWantedIndex; i++) {
		(*wantedFields)[i] = false;
	}

	for (i = 0; i < *wantedFieldsAmount; i++) {
		(*wantedFields)[(*wantedFieldsOrder)[i]] = true;
	}
}

void generateReducedCSV(char fnamein[], char fnameout[]) {
	FILE *inputFile, *outputFile;
	int wantedFieldsAmount;
	int maxWantedIndex;
	bool *wantedFields;
	int *wantedFieldsOrder;
	bool endOfFile;

	readWantedFields(&wantedFieldsOrder, &wantedFieldsAmount, &wantedFields, &maxWantedIndex);

	inputFile = fopen(fnamein, "r");
	outputFile = fopen(fnameout, "w");

	endOfFile = false;
	while (!endOfFile) {
		endOfFile = getLineFields(inputFile, outputFile, wantedFieldsOrder, wantedFieldsAmount, wantedFields, maxWantedIndex);
	}



	fclose(inputFile);
	fclose(outputFile);
}

int main(int argc, char *argv[]) {
	char fnamein[MAX_FILENAME_LENGTH + 1], fnameout[MAX_FILENAME_LENGTH + 1];

	strcpy(fnamein, argv[1]);
	strcpy(fnameout, argv[2]);

	generateReducedCSV(fnamein, fnameout);
	return 0;
}