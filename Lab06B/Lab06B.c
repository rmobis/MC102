/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 06B - Fruit Crush Saga - Part II
 *
 * Realiza varias cliques num tabuleiro de frutas. Cada clique remove frutas
 * iguais que estejam juntas, em cada uma das quatro direções. As frutas acima
 * das posições removidas são empurradas para baixo. No final, mostra o score
 * obtido e o tabuleiro após as modificações geradas pelos cliques.
 */

#include <stdio.h>
#include <math.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50
#define TEMP_EMPTY_TILE 'X'
#define EMPTY_TILE '.'

#define HALF_PI 1.570796326794897

int computeClick(char *field, int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn);
void shiftEmptyTiles(char *field, int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn);

int main() {
	int i, j;
	int score = 0;
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

		score += computeClick(&fruitField[0][0], fieldHeight, fieldWidth, chosenLine, chosenColumn);
	}

	printf("Score: %d\n", score);

	/* Imprime o tabuleiro com as modificações geradas pelos clicks */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			printf("%c", fruitField[i][j]);
		}

		printf("\n");
	}

	return 0;
}

int computeClick(char *field, int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn) {
	int i;
	int clickScore = 0;
	char chosenFruit;
	char *curFruit;
	int curLine, curColumn;
	int verOffset, horOffset;

	/* Como as linhas tem índice inicial 1, mas a matriz tem índice inicial 0,
	 * temos que subtrair 1 da linha e coluna recebidas.
	 */
	chosenLine--;
	chosenColumn--;

	curFruit = field + (chosenLine * MAX_WIDTH) + chosenColumn;
	chosenFruit = *curFruit;

	/* Cliques fora do tabuleiro são ingorados. */
	if (chosenFruit == EMPTY_TILE) {
		return 0;
	}

	/* O local clicado sempre é removido */
	*curFruit = TEMP_EMPTY_TILE;
	clickScore++;

	/* Usamos as funções seno e cosseno para auxiliar na "direção" em que
	 * faremos a próxima verificação; andando na circunferência, PI/2 rad por
	 * vez, obtemos os pares de seno e cosseno (0;1), (1;0), (0;-1) e (-1;0), os
	 * quais somamos à posição inicial para andar, respectivamente, nas direções
	 * leste, norte, oeste e sul.
	 */
	for (i = 0; i < 4; i++) {
		verOffset = (int) sin(HALF_PI * i);
		horOffset = (int) cos(HALF_PI * i);

		curLine = chosenLine + verOffset;
		curColumn = chosenColumn + horOffset;

		curFruit = field + (curLine * MAX_WIDTH) + curColumn;

		/* Enquanto ainda estivermos dentro do tabuleiro e o campo tiver uma
		 * fruta igual à da posição inicial do click.
		 */
		while (
			(curLine >= 0 && curLine < fieldHeight) &&
			(curColumn >= 0 && curColumn < fieldWidth) &&
			*curFruit == chosenFruit
		) {
			*curFruit = TEMP_EMPTY_TILE;
			clickScore++;

			curColumn += horOffset;
			curLine += verOffset;
			curFruit = field + (curLine * MAX_WIDTH) + curColumn;
		}
	}

	shiftEmptyTiles(field, fieldHeight, fieldWidth, chosenLine, chosenColumn);

	return clickScore * clickScore;
}

/* Empurra os campos acima dos que foram removidos, lendo uma coluna por
 * vez, começando de baixo.
 */
void shiftEmptyTiles(char *field, int fieldHeight, int fieldWidth, int chosenLine, int chosenColumn) {
	int j;
	char *curFruit, *compFruit;

	for (j = 0; j < fieldWidth; j++) {
		/* Só precisamos começar da última linha caso a coluna atual não for a
		 * que clicamos. Isso por que nas colunas aonde não clicamos, só pode
		 * haver campos vazios na na linha em que clicamos.
		 */
		if (j == chosenColumn) {
			curFruit = field + (fieldHeight * MAX_WIDTH) + j;
		} else {
			curFruit = field + (chosenLine * MAX_WIDTH) + j;
		}

		compFruit = curFruit;

		while (compFruit >= field) {
			while (*compFruit == TEMP_EMPTY_TILE && compFruit >= field) {
				/* Sobe uma linha */
				compFruit -= MAX_WIDTH;
			}

			if (compFruit >= field) {
				if (curFruit != compFruit) {
					*curFruit = *compFruit;
				}

				curFruit -= MAX_WIDTH;
				compFruit -= MAX_WIDTH;
			}
		}

		/* Completa os espaços vazios no topo com o caractere correto. */
		while (curFruit >= field) {
			*curFruit = EMPTY_TILE;
			curFruit -= MAX_WIDTH;
		}
	}
}