/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 09A - Oliver Queen is alive!
 *
 * Dado o tempo máximo e todo o mapa do local onde se encontra o "TREMOR",
 * descobre se Oliver Queen consegue desarmá-lo antes do tempo limite, seguindo
 * a lógica baseada na cor do campo atual em que ele estiver:
 *
 * - Regiões Brancas: seguir em frente; marcar a posição atual como azul
 * - Regiões Azuis: virar à esquerda; marcar a posição atual como verde
 * - Regiões Verdes: virar à direita; marcar a posição atual como branca
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define HALF_PI 1.570796326794897

#define MAX_WIDTH  30
#define MAX_HEIGHT 30

#define STATUS_LOOKING 1
#define STATUS_FOUND   2
#define STATUS_DEAD    3
#define STATUS_NO_TIME 4

#define TILE_WHITE  0
#define TILE_BLUE   1
#define TILE_GREEN  2
#define TILE_TRAP   3
#define TILE_TREMOR 4

/* Lê os dados e preenche a matriz de inteiros */
void readField(int field[][MAX_WIDTH], int fieldHeight, int fieldWidth);

/* Retorna o ângulo em que a direção deve mudar, em radianos */
double tileOffset(int tile);

int main() {
	double curDir;
	int curX, curY, curTile;
	int searchStatus, timeSpent;
	int fieldDimensions, timeLimit;
	int walkingField[MAX_HEIGHT][MAX_WIDTH];

	scanf("%d %d", &fieldDimensions, &timeLimit);

	readField(walkingField, fieldDimensions, fieldDimensions);

	/* O tempo começa como menos 1, pois consideramos que o primeiro passo seria
	 * o de entrar no campo (0, 0), saindo do (-1, 0) mas o problema define que
	 * já começamos lá. Sendo assim, esse tempo é desconsiderado.
	 */
	curY = 0;
	curX = -1;
	curDir = 0;
	timeSpent = -1;
	searchStatus = STATUS_LOOKING;
	while (searchStatus == STATUS_LOOKING) {
		timeSpent++;
		if (timeSpent >= timeLimit) {
			searchStatus = STATUS_NO_TIME;
		} else {
			/* Usamos seno e cosseno para auxiliar nas direções. Começando com
			 * uma direção de 0 radianos e adicionando/removendo PI/2 para virar
			 * à esquerda/direita.
			 */
			curX += (int) cos(curDir);
			curY += (int) sin(curDir);

			if (curX < 0 || curX >= fieldDimensions || curY < 0 || curY >= fieldDimensions) {
				searchStatus = STATUS_DEAD;
			} else {
				curTile = walkingField[curY][curX];

				if (curTile == TILE_TRAP) {
					searchStatus = STATUS_DEAD;
				} else if (curTile == TILE_TREMOR) {
					searchStatus = STATUS_FOUND;
				} else {
					/* Define o novo valor do campo. */
					walkingField[curY][curX] = (curTile + 1) % 3;

					curDir += tileOffset(curTile);
				}
			}
		}
	}

	switch (searchStatus) {
		case STATUS_FOUND:
			printf("Oliver destroi o dispositivo em %d segundos\n", timeSpent);
			break;

		case STATUS_DEAD:
			printf("Oliver morre\n");
			break;

		case STATUS_NO_TIME:
			printf("Oliver nao chega ao dispositivo a tempo\n");
			break;
	}

	return 0;
}

/* Lê os dados e preenche a matriz de inteiros */
void readField(int field[][MAX_WIDTH], int fieldHeight, int fieldWidth) {
	int i, j;

	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %d", &field[i][j]);
		}
	}
}

/* Retorna o ângulo em que a direção deve mudar, em radianos */
double tileOffset(int tile) {
	switch (tile) {
		case TILE_BLUE:
			return -HALF_PI;

		case TILE_GREEN:
			return HALF_PI;

		default:
			return 0;
	}
}