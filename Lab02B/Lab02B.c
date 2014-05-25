/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 02B - Pedra-Papel-Tesoura-Lagarto-Spock
 */

#include <stdio.h>

int main() {
	int i;
	int matches;
	int sheldon, leonard;
	int sheldonScore = 0, leonardScore = 0;

	scanf("%d", &matches);

	for (i = 0; i < matches; i++) {
		scanf("%d %d", &sheldon, &leonard);

		if (sheldon == leonard) {
			printf("Empate");
		} else {
			switch (sheldon) {
				case 1: /* Pedra */
					switch (leonard) {
						case 2: /* Papel */
							printf("Leonard: Papel embrulha Pedra");
							leonardScore++;
							break;

						case 3: /* Tesoura */
							printf("Sheldon: Pedra quebra Tesoura");
							sheldonScore++;
							break;

						case 4: /* Lagarto */
							printf("Sheldon: Pedra amassa Lagarto");
							sheldonScore++;
							break;

						case 5: /* Spock */
							printf("Leonard: Spock vaporiza Pedra");
							leonardScore++;
							break;
					}
					break;

				case 2: /* Papel */
					switch (leonard) {
						case 1: /* Pedra */
							printf("Sheldon: Papel embrulha Pedra");
							sheldonScore++;
							break;

						case 3: /* Tesoura */
							printf("Leonard: Tesoura corta Papel");
							leonardScore++;
							break;

						case 4: /* Lagarto */
							printf("Leonard: Lagarto come Papel");
							leonardScore++;
							break;

						case 5: /* Spock */
							printf("Sheldon: Papel refuta Spock");
							sheldonScore++;
							break;
					}
					break;

				case 3: /* Tesoura */
					switch (leonard) {
						case 1: /* Pedra */
							printf("Leonard: Pedra quebra Tesoura");
							leonardScore++;
							break;

						case 2: /* Papel */
							printf("Sheldon: Tesoura corta Papel");
							sheldonScore++;
							break;

						case 4: /* Lagarto */
							printf("Sheldon: Tesoura decepa Lagarto");
							sheldonScore++;
							break;

						case 5: /* Spock */
							printf("Leonard: Spock quebra Tesoura");
							leonardScore++;
							break;
					}
					break;

				case 4: /* Lagarto */
					switch (leonard) {
						case 1: /* Pedra */
							printf("Leonard: Pedra amassa Lagarto");
							leonardScore++;
							break;

						case 2: /* Papel */
							printf("Sheldon: Lagarto come Papel");
							sheldonScore++;
							break;

						case 3: /* Tesoura */
							printf("Leonard: Tesoura decepa Lagarto");
							leonardScore++;
							break;

						case 5: /* Spock */
							printf("Sheldon: Lagarto envenena Spock");
							sheldonScore++;
							break;
					}
					break;

				case 5: /* Spock */
					switch (leonard) {
						case 1: /* Pedra */
							printf("Sheldon: Spock vaporiza Pedra");
							sheldonScore++;
							break;

						case 2: /* Papel */
							printf("Leonard: Papel refuta Spock");
							leonardScore++;
							break;

						case 3: /* Tesoura */
							printf("Sheldon: Spock quebra Tesoura");
							sheldonScore++;
							break;

						case 4: /* Lagarto */
							printf("Leonard: Lagarto envenena Spock");
							leonardScore++;
							break;
					}
					break;
			}
		}

		printf("\n");
	}

	printf("Sheldon %d x %d Leonard\n", sheldonScore, leonardScore);

    return 0;
}
