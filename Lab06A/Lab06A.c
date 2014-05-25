/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 06A - Fruit Crush Saga - Part I
 */

#include <stdio.h>
#include <math.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50

#define HALF_PI 1.570796326794897

void computeClick(int chosenLine, int chosenColumn);

int score = 0;
int fieldHeight, fieldWidth;
char fruitField[MAX_HEIGHT][MAX_WIDTH];

int main() {
	int i, j;
	int chosenLine, chosenColumn;

	/* Leitura dos dados básicos do problema */
	scanf("%d %d %d %d", &fieldHeight, &fieldWidth, &chosenLine, &chosenColumn);

	/* Leitura do tabuleiro completo */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %c", &fruitField[i][j]);
		}
	}

	computeClick(chosenLine, chosenColumn);


	printf("Score: %d\n", score * score);

	/* Imprime o tabuleiro com as modificações geradas pelos clicks */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			printf("%c", fruitField[i][j]);
		}

		printf("\n");
	}

    return 0;
}

void computeClick(int chosenLine, int chosenColumn) {
	int i;
	char chosenFruit;
	int curLine, curColumn;
	int verOffset, horOffset;

	/* Como as linhas tem índice inicial 1, mas a matriz tem índice inicial 0,
	 * temos que subtrair um da linha e coluna recebidas.
	 */
	chosenLine--;
	chosenColumn--;

	chosenFruit = fruitField[chosenLine][chosenColumn];

	/* O local clicado sempre é removido */
	fruitField[chosenLine][chosenColumn] = 'X';
	score++;

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

		/* Enquanto ainda estivermos dentro do tabuleiro e o campo tiver uma
		 * fruta igual à da posição inicial do click.
		 */
		while (
			(curLine >= 0 && curLine < fieldHeight) &&
			(curColumn >= 0 && curColumn < fieldWidth) &&
			fruitField[curLine][curColumn] == chosenFruit
		) {
			fruitField[curLine][curColumn] = 'X';
			curColumn += horOffset;
			curLine += verOffset;
			score++;
		}
	}
}
