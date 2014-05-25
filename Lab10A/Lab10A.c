/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 10A - LSCrypto
 *
 *
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 501
#define MAX_LINES       15

#define ALPHABET_LENGTH 26

/* Lê os dados do problema */
void readData(char text[][MAX_LINE_LENGTH], int *linesAmount);

/* Imprimete o texto criptografado */
void printData(char text[][MAX_LINE_LENGTH], int linesAmount);

/* Conta o número de ocorrências de cada letra dentro do texto */
void countOccurrences(int letterOccurrences[], char text[][MAX_LINE_LENGTH], int linesAmount);

/* Substitui as letras de acordo com a quantidade de ocorrências no texto */
void replaceLetters(int occurrencesOrder[], char text[][MAX_LINE_LENGTH], int linesAmount);

/* Retorna o ińdíce do caractere no alfabeto */
int getLetterIndex(char letter);

/* Retorna se o caractere recebido é uma letra */
bool isLetter(char character);

/* Preenche um vetor de inteiros com valores */
void fillArray(int array[], int start, int step, int length);

/* Ordena o vetor */
void insertionSort(int positions[], int comparingData[], int length);


int main() {
	int linesAmount;
	int occurrencesOrder[ALPHABET_LENGTH];
	int letterOccurrences[ALPHABET_LENGTH];
	char text[MAX_LINES][MAX_LINE_LENGTH];

	readData(text, &linesAmount);
	countOccurrences(letterOccurrences, text, linesAmount);
	fillArray(occurrencesOrder, 0, 1, ALPHABET_LENGTH);
	insertionSort(occurrencesOrder, letterOccurrences, ALPHABET_LENGTH);
	replaceLetters(occurrencesOrder, text, linesAmount);
	printData(text, linesAmount);

	return 0;
}

/* Lê os dados do problema */
void readData(char text[][MAX_LINE_LENGTH], int *linesAmount) {
	int i, j;

	scanf("%d\n", linesAmount);

	for (i = 0; i < *linesAmount; i++) {
		j = 0;
		do {
			scanf("%c", &text[i][j]);
		} while (text[i][j++] != '\n');

		/* Substitui o '\n' por '\0' */
		text[i][j - 1] = '\0';
	}
}

/* Imprimete o texto criptografado */
void printData(char text[][MAX_LINE_LENGTH], int linesAmount) {
	int i;

	for (i = 0; i < linesAmount; i++) {
		printf("%s\n", &text[i][0]);
	}
}

/* Conta o número de ocorrências de cada letra dentro do texto */
void countOccurrences(int letterOccurrences[], char text[][MAX_LINE_LENGTH], int linesAmount) {
	int i, j;

	/* Preenche a array com zeros */
	fillArray(letterOccurrences, 0, 0, ALPHABET_LENGTH);

	for (i = 0; i < linesAmount; i++) {

		j = 0;
		while (text[i][j]) {
			if (isLetter(text[i][j])) {
				letterOccurrences[getLetterIndex(text[i][j])]++;
			}

			j++;
		}
	}

}

/* Substitui as letras de acordo com a quantidade de ocorrências no texto */
void replaceLetters(int occurrencesOrder[], char text[][MAX_LINE_LENGTH], int linesAmount) {
	int i, j;
	int replacementTable[ALPHABET_LENGTH];

	/* Monta a tabela que especifica as transformações a serem feitas */
	for (i = 0; i < ALPHABET_LENGTH; i += 2) {
		replacementTable[occurrencesOrder[i]] = occurrencesOrder[i + 1];
		replacementTable[occurrencesOrder[i + 1]] = occurrencesOrder[i];
	}

	for (i = 0; i < linesAmount; i++) {

		j = 0;
		while (text[i][j]) {
			if (isLetter(text[i][j])) {

				/* Soma a diferença entre o índice da letra atual no alfabeto e
				 * o índice da nova letra. Isso nos deixa agir de maneira única
				 * tanto para letras minúsculas quanto maiúsculas.
				 */
				text[i][j] += replacementTable[getLetterIndex(text[i][j])] - getLetterIndex(text[i][j]);
			}

			j++;
		}
	}
}

/* Retorna o ińdíce da letra no alfabeto, independentemente de ser maiúscula ou
 * minúscula.
 */
int getLetterIndex(char letter) {
	return (letter % 97) % 65;
}

/* Retorna se o caractere recebido é uma letra */
bool isLetter(char character) {
	return (character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z');
}

/* Preenche um vetor de inteiros com valores; a primeira posição recebe `start`
 * e `step` é adicionado a cada posição subsequente.
 */
void fillArray(int array[], int start, int step, int length) {
	int i;

	for (i = 0; i < length; i++) {
		array[i] = start + (step * i);
	}
}

/* Ordena o vetor em order decrescente, usando outro vetor como comparação. O
 * algorítmo também preserva a ordem de items que tenham o mesmo valor.
 */
void insertionSort(int positions[], int comparingData[], int length) {
	int i, j;
	int curIndex;
	double curItem;

	for (i = 1; i < length; i++) {
		curIndex = positions[i];
		curItem = comparingData[curIndex];

		for (j = i - 1; j >= 0 && comparingData[positions[j]] < curItem; j--) {
			positions[j + 1] = positions[j];
		}

		positions[j + 1] = curIndex;
	}
}