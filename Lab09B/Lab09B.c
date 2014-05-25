/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 09B - Concurso Público para Professor da UNICAMP
 *
 * ---
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_WIDTH  30
#define MAX_HEIGHT 5

/* Lê os dados e preenche a matriz de doubles */
void readField(double field[][MAX_WIDTH], int fieldHeight, int fieldWidth);

void insertionSort(int positions[], double comparingData[], int length);

void removeFromArray(int list[], int length, int key);

int main() {
	int i, j, k;
	int maxIndex;
	double gradeSum;
	int participantsAmount;
	double participantScores[MAX_WIDTH];
	double participantAverages[MAX_WIDTH];
	int participantsClassfication[MAX_WIDTH];
	double participantGrades[MAX_HEIGHT][MAX_WIDTH];
	int participantPositions[MAX_HEIGHT][MAX_WIDTH];

	scanf("%d", &participantsAmount);

	readField(participantGrades, MAX_HEIGHT, participantsAmount);

	/* Cálculo da Média */
	for (j = 0; j < participantsAmount; j++) {
		gradeSum = participantGrades[0][j];

		for (i = 1; i < MAX_HEIGHT; i++) {
			gradeSum += participantGrades[i][j];
		}

		participantAverages[j] = gradeSum / MAX_HEIGHT;
	}

	{
		printf("Nota Media:");
		for (j = 0; j < participantsAmount; j++) {
			printf(" %.1f", participantAverages[j]);
		}
		printf("\n");
		printf("\n");
	}

	/* Define a ordem inicial de classificação para cada jurado. */
	for (i = 0; i < MAX_HEIGHT; i++) {
		for (j = 0; j < participantsAmount; j++) {
			participantPositions[i][j] = j;
		}

		insertionSort(&participantPositions[i][0], &participantGrades[i][0], participantsAmount);
	}

	{
		printf("Preferencia:\n");
		for (i = 0; i < MAX_HEIGHT; i++) {
			printf("Membro %d:", i + 1);
			for (j = 0; j < participantsAmount; j++) {
				printf(" %d", participantPositions[i][j] + 1);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (j = 0; j < participantsAmount; j++) {
		participantScores[j] = participantAverages[j];
	}

	for (i = 0; i < MAX_HEIGHT; i++) {
		participantScores[participantPositions[i][0]] += 100;
	}

	for (k = 0; k < participantsAmount; k++) {
		maxIndex = 0;

		for (j = 1; j < participantsAmount; j++) {
			if (participantScores[maxIndex] < participantScores[j]) {
				maxIndex = j;
			}
		}

		participantsClassfication[k] = maxIndex;
		participantScores[maxIndex] = 0;

		for (i = 0; i < MAX_HEIGHT; i++) {
			if (participantPositions[i][0] == maxIndex) {
				if (participantsAmount - k > 1) {
					participantScores[participantPositions[i][1]] += 100;
				}
			}

			removeFromArray(&participantPositions[i][0], participantsAmount - k, maxIndex);
		}
	}

	{
		printf("Classificacao:");
		for (j = 0; j < participantsAmount; j++) {
			printf(" %d", participantsClassfication[j] + 1);
		}
		printf("\n");
	}

	return 0;
}

/* Lê os dados e preenche a matriz de doubles */
void readField(double field[][MAX_WIDTH], int fieldHeight, int fieldWidth) {
	int i, j;

	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %lf", &field[i][j]);
		}
	}
}

void insertionSort(int positions[], double comparingData[], int length) {
	int i, j;
	int curParticipant;
	double curItem;

	for (i = 1; i < length; i++) {
		curParticipant = positions[i];
		curItem = comparingData[curParticipant];

		for (j = i - 1; j >= 0 && comparingData[positions[j]] < curItem; j--) {
			positions[j + 1] = positions[j];
		}

		positions[j + 1] = curParticipant;
	}
}

void removeFromArray(int list[], int length, int key) {
	int i = 0;

	while (list[i] != key && i < length) {
		i++;
	}

	for (; i < length - 1; i++) {
		list[i] = list[i + 1];
	}
}