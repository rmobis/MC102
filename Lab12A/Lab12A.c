/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 12A - CUT++
 *
 * Gera um CSV reduzido com base nos dois arquivos de entrada, imprimindo apenas
 * os campos desejados, permitindo alteração na ordem e repetiçãpo do mesmo campo
 * múltiplas vezes.
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

/* Conta o número de colunas na primeira linha */
int countRows(FILE *inputFile);

/* Lê os campos requeridos */
void readWantedFields(int **wantedFields, int *wantedFieldsAmount);

/* Lê uma linha e seus campos do arquivo de entrada e imprime no arquivo de saída */
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

	lineData = malloc(rowCount * sizeof(char *));

	readWantedFields(&wantedFields, &wantedFieldsAmount);

	do {
		endOfFile = getRow(inputFile, outputFile, rowCount, lineData, wantedFields, wantedFieldsAmount);
	} while (!endOfFile);


	fclose(inputFile);
	fclose(outputFile);

	free(lineData);
	free(wantedFields);
}

/* Conta o número de colunas na primeira linha, contando a quantidade de
 * separadores, acrescido de 1.
 */
int countRows(FILE *inputFile) {
	char nextChar;
	int rowCount = 1;

	/* Volta ao início do arquivo, pois não assumimos que já estamos lá */
	rewind(inputFile);

	do {
		fscanf(inputFile, "%c", &nextChar);

		if (nextChar == SEPARATOR) {
			rowCount++;
		}
	} while (nextChar != EOL);

	/* Volta ao início do arquivo novamente */
	rewind(inputFile);

	return rowCount;
}

/* Lê os campos requeridos */
void readWantedFields(int **wantedFields, int *wantedFieldsAmount) {
	int i;

	scanf("%d", wantedFieldsAmount);

	*wantedFields = malloc(*wantedFieldsAmount * sizeof(int));

	for (i = 0; i < *wantedFieldsAmount; i++) {
		scanf("%d", &(*wantedFields)[i]);

		/* Descresce um para termos um valor com indíce 0-based */
		(*wantedFields)[i]--;
	}
}

/* Lê uma linha e seus campos do arquivo de entrada e imprime no arquivo de saída */
bool getRow(FILE *inputFile, FILE *outputFile, int rowCount, char **lineData, int wantedFields[], int wantedFieldsAmount) {
	int curFieldLength;
	char curField[MAX_FIELD_LENGTH + 1];
	bool endOfFile = false;
	char nextChar;
	int i;

	/* Para cada campo da linha, ler e salvar num vetor auxiliar */
	for (i = 0; i < rowCount; i++) {
		curFieldLength = 0;

		do {
			endOfFile = (fscanf(inputFile, "%c", &nextChar) == EOF);
			curField[curFieldLength++] = nextChar;
		} while (!endOfFile && nextChar != EOL && nextChar != SEPARATOR);

		curField[--curFieldLength] = '\0';

		lineData[i] = malloc(501 * sizeof(char));
		strcpy(lineData[i], curField);
	}

	/* Printar somente se esta linha não for a última, que está em branco */
	if (!endOfFile) {
		for (i = 0; i < wantedFieldsAmount; i++) {
			fprintf(outputFile, "%s", lineData[wantedFields[i]]);

			if (i != wantedFieldsAmount - 1) {
				fprintf(outputFile, ",");
			}
		}

		fprintf(outputFile, "\n");
	}

	/* Libera a memória */
	for (i = 0; i < rowCount; i++) {
		free(lineData[i]);
	}

	return endOfFile;
}