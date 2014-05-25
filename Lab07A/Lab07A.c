/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 07A - The Voice - Blind Auditions
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTICIPANTS 100
#define TEAMS_AMOUNT 4

int main() {
	int i, j;
	bool teamFound;
	int teamCount[TEAMS_AMOUNT];
	int teams[TEAMS_AMOUNT][MAX_PARTICIPANTS];
	int coachesChoices[TEAMS_AMOUNT], participantChoice;
	int participantsAmount;

	for (i = 0; i < TEAMS_AMOUNT; i++) {
		teamCount[i] = 0;
	}

	/* Leitura dos dados básicos do problema */
	scanf("%d", &participantsAmount);

	/* Leitura dos participantes */
	for (i = 0; i < participantsAmount; i++) {
		for (j = 0; j < TEAMS_AMOUNT; j++) {
			scanf("%d", &coachesChoices[j]);
		}

		teamFound = false;
		for (j = 0; j < TEAMS_AMOUNT; j++) {
			scanf("%d", &participantChoice);

			if (!teamFound && coachesChoices[participantChoice - 1]) {
				teams[participantChoice - 1][teamCount[participantChoice - 1]++] = i + 1;
				teamFound = true;
			}
		}
	}

	for (i = 0; i < TEAMS_AMOUNT; i++) {
		printf("Time %d:", i + 1);

		if (teamCount[i] == 0) {
			printf(" Nenhum participante");
		} else {
			for (j = 0; j < teamCount[i]; j++) {
				printf(" %d", teams[i][j]);
			}
		}

		printf("\n");
	}

	return 0;
}
