/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 14B - Libera8
 *
 * Dado um campo com bombas de alcances variados e a posição da primeira bomba a
 * explodir, mostra o campo após a explosão, considerando também o efeito da
 * explosão de bombas que estejam ao alcance de outros bombas que explodiram.
 *
 * .   - Área inafetada
 * x   - Área explodiu
 * B   - Bomba explodiu
 * 1-9 - Bomba inafetada
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_WIDTH  50
#define MAX_HEIGHT 50

#define TILE_EMPTY         '.'
#define TILE_EXPLODED_BOMB 'B'
#define TILE_EXPLODED      'x'

/* Explode uma posição do campo */
void explodeTile(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth, int tileX, int tileY);

/* Verifica se a posição do campo é uma bomba ainda não detonada */
bool isBomb(char tile);

/* Lê o campo */
void readField(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth);

/* Imprime o campo */
void printField(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth);

int main() {
	int bombX, bombY;
	int fieldHeight, fieldWidth;
	char field[MAX_HEIGHT][MAX_WIDTH];

	scanf("%d %d %d %d", &fieldHeight, &fieldWidth, &bombY, &bombX);

	readField(field, fieldHeight, fieldWidth);

	explodeTile(field, fieldHeight, fieldWidth, --bombY, --bombX);

	printField(field, fieldHeight, fieldWidth);

	return 0;
}

/* Explode uma posição do campo */
void explodeTile(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth, int tileY, int tileX) {
	int i, j;
	int bombRange;

	/* Posições fora do campo são inválidas */
	if (tileY < 0 || tileY >= fieldHeight || tileX < 0 || tileX >= fieldWidth) {
		return;
	}

	/* Se tivermos uma posição vazia, simplesmente a explodimos */
	if (field[tileY][tileX] == TILE_EMPTY) {
		field[tileY][tileX] = TILE_EXPLODED;
	}
	else if (isBomb(field[tileY][tileX])) {
		/* Caso tenhamos uma bomba, explodimos todos os campos no alcance dessa
		 * bomba.
		 */
		bombRange = (int)(field[tileY][tileX] - '0');
		field[tileY][tileX] = TILE_EXPLODED_BOMB;

		for (j = tileY - bombRange; j <= tileY + bombRange; j++) {
			for (i = tileX - bombRange; i <= tileX + bombRange; i++) {
				explodeTile(field, fieldHeight, fieldWidth, j, i);
			}
		}
	}
}

/* Verifica se a posição do campo é uma bomba ainda não detonada */
bool isBomb(char tile) {
	return tile >= '1' && tile <= '9';
}

/* Lê o campo */
void readField(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth) {
	int i, j;

	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %c", &field[i][j]);
		}
	}
}

/* Imprime o campo */
void printField(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth) {
	int i, j;

	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			printf("%c", field[i][j]);
		}
		printf("\n");
	}
}