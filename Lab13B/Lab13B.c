/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 06B - Fruit Crush Saga - Part II
 *
 * Realiza varias cliques num tabuleiro de frutas. Cada clique remove frutas
 * iguais que estejam adjacentes. As frutas acima das posições removidas são
 * empurradas para baixo, exceto caso haja um gelo acima delas. No final,
 * mostra o score obtido e o tabuleiro após as modificações geradas pelos
 * cliques.
 */

#include <stdio.h>
#include <math.h>

#define MAX_WIDTH  50
#define MAX_HEIGHT 50

#define EMPTY_TILE      '.'
#define ICE_TILE        '*'

#define HALF_PI 1.570796326794897

/* Computa o resultado final do tabuleiro após um clique nas posições dadas. */
int computeClick(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn, char clickedFruit);

/* Empurra os campos acima dos que foram removidos */
void shiftEmptyTiles(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth);

int main() {
	int i, j;
	char clickedFruit;
	int clickScore, totalScore = 0;
	char fruitField[MAX_HEIGHT][MAX_WIDTH];
	int fieldHeight, fieldWidth, clicksNumber;
	int chosenLine, chosenColumn;

	/* Leitura dos dados básicos do problema */
	scanf("%d %d %d", &fieldHeight, &fieldWidth, &clicksNumber);

	/* Leitura do tabuleiro completo */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %c", &fruitField[i][j]);
		}
	}

	for (i = 0; i < clicksNumber; i++) {
		scanf("%d %d", &chosenLine, &chosenColumn);

		/* Como as linhas tem índice inicial 1, mas a matriz tem índice inicial 0,
		 * temos que subtrair 1 da linha e coluna recebidas.
		 */
		chosenLine--;
		chosenColumn--;

		clickedFruit = fruitField[chosenLine][chosenColumn];

		/* Cliques em posições sem frutas ou em blocos de gelo não contabilizam
		 * pontos nem alteram o tabuleiro.
		 */
		if (clickedFruit != EMPTY_TILE && clickedFruit != ICE_TILE) {
			clickScore = computeClick(
				fruitField,
				fieldHeight,
				fieldWidth,
				chosenLine,
				chosenColumn,
				clickedFruit
			);

			totalScore += clickScore * clickScore;

			shiftEmptyTiles(fruitField, fieldHeight, fieldWidth);
		}
	}

	printf("Score: %d\n", totalScore);

	/* Imprime o tabuleiro com as modificações geradas pelos clicks */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			printf("%c", fruitField[i][j]);
		}

		printf("\n");
	}

	return 0;
}

int computeClick(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn, char clickedFruit) {
	int i;
	char *chosenFruit;
	int fruitsRemoved = 0;


	/* Posições fora do tabuleiro são inválidas */
	if (chosenLine < 0 || chosenLine >= fieldHeight || chosenColumn < 0 || chosenColumn >= fieldWidth) {
		return 0;
	}

	chosenFruit = &field[chosenLine][chosenColumn];

	/* Se a fruta na posição atual for igual a fruta clickada inicialmente,
	 * removemos esta e procuramos as frutas adjacentes.
	 */
	if (*chosenFruit == clickedFruit) {

		*chosenFruit = EMPTY_TILE;
		fruitsRemoved++;

		/* Usamos as funções seno e cosseno para auxiliar na "direção" em que
		 * faremos a próxima verificação; andando na circunferência, PI/2 rad por
		 * vez, obtemos os pares de seno e cosseno (0;1), (1;0), (0;-1) e (-1;0), os
		 * quais somamos à posição inicial para andar, respectivamente, nas direções
		 * leste, norte, oeste e sul.
		 */
		for (i = 0; i < 4; i++) {
			fruitsRemoved += computeClick(
				field,
				fieldHeight,
				fieldWidth,
				chosenLine + (int) sin(HALF_PI * i),
				chosenColumn + (int) cos(HALF_PI * i),
				clickedFruit
			);
		}
	}

	return fruitsRemoved;
}

/* Empurra os campos acima dos que foram removidos, lendo uma coluna por
 * vez, começando de baixo.
 */
void shiftEmptyTiles(char field[][MAX_WIDTH], int fieldHeight, int fieldWidth) {
	int i, j;
	int curLine;

	for (j = 0; j < fieldWidth; j++) {
		i = fieldHeight - 1;
		curLine = i;

		/* Até o final da linha */
		while (i >= 0) {

			/* Copia os campos não vazios pro fundo da linha, até encontrar um
			 * gelo ou o final da linha.
			 */
			while (i >= 0 && field[i][j] != ICE_TILE) {
				if (field[i][j] != EMPTY_TILE) {
					field[curLine--][j] = field[i][j];
				}

				i--;
			}

			/* Completa até o gelo/final da linha encontrado com campos vazios */
			while (curLine > i) {
				field[curLine--][j] = EMPTY_TILE;
			}

			/* Pula o gelo/final da linha */
			curLine--;
			i--;
		}
	}
}