/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 07B - Modern Word Search
 *
 * Procura por uma palavra dada em um tabuleiro, considerando como caraceteres
 * curinga '_' (qualquer letra), '#' (qualquer vogal) e '%' (qualquer
 * consoante). Ao final, imprime o número de ocorrências da palavra encontradas
 * e um tabuleiro mostrando a posição dessas ocorrências.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define WILDCARD_ANY       '_'
#define WILDCARD_VOWEL     '#'
#define WILDCARD_CONSONANT '%'

/* Verifica se o caracetere é uma vogal. */
bool isVowel(char *letter);

/* Verifica se o caracetere é uma consoante. */
bool isConsonant(char *letter);

/* Verifica se os caraceteres são equivalentes. */
bool lettersMatch(char *firstLetter, char *secondLetter);

int main() {
	int i, j, k;
	char word[26];
	int wordLength;
	char wordField[50][50], markedField[50][50];
	int fieldHeight, fieldWidth;
	int curLine, curColumn, curLetter;
	bool wordMatch;

	int verOffset, horOffset;
	int directionOffsets[3][2] = {
		{1, 0}, /* Horizontal */
		{1, 1}, /*  Diagonal  */
		{0, 1}  /*  Vertical  */
	};

	int amountOfMatches = 0;

	/* Leitura dos dados básicos do problema */
	scanf("%d %d %s", &fieldHeight, &fieldWidth, word);

	wordLength = strlen(word);

	/* Leitura do tabuleiro completo e definição do campo padrão no tabuleiro
	 * a ser exibido no final.
	 */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			scanf(" %c", &wordField[i][j]);

			markedField[i][j] = '.';
		}
	}

	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {

			/* Para cada uma das direções definidas no vetor directionOffsets */
			for (k = 0; k < 3; k++) {
				horOffset = directionOffsets[k][0];
				verOffset = directionOffsets[k][1];

				/* Se a palavra não couber na direção em que estamos testando
				 * atualmente, não há necessidade de verificar se há
				 * combinações.
				 */
				if (
					i + (verOffset * wordLength) <= fieldHeight &&
					j + (horOffset * wordLength) <= fieldWidth
				) {
					curLine = i;
					curColumn = j;
					curLetter = 0;
					wordMatch = true;

					while (wordMatch && curLetter < wordLength) {
						wordMatch = lettersMatch(&word[curLetter], &wordField[curLine][curColumn]);

						curLetter++;
						curLine += verOffset;
						curColumn += horOffset;
					}


					if (wordMatch) {
						curLine -= verOffset;
						curColumn -= horOffset;

						/* Volta até a posição inicial, copiando a letra
						 * encontrada para a outra matriz.
						 */
						while (curLine >= i && curColumn >= j) {
							markedField[curLine][curColumn] = wordField[curLine][curColumn];

							curLine -= verOffset;
							curColumn -= horOffset;
						}

						amountOfMatches++;
					}
				}
			}
		}
	}


	printf("%s %d\n", word, amountOfMatches);

	/* Imprime o tabuleiro com as palavras encontradas */
	for (i = 0; i < fieldHeight; i++) {
		for (j = 0; j < fieldWidth; j++) {
			printf("%c", markedField[i][j]);
		}

		printf("\n");
	}

	return 0;
}

/* Verifica se o caracetere é uma vogal. */
bool isVowel(char *letter) {
	int i;

	for (i = 0; i < 5; i++) {
		if (*letter == "aeiou"[i]) {
			return true;
		}
	}

	return false;
}

/* Verifica se o caracetere é uma consoante. */
bool isConsonant(char *letter) {
	return !isVowel(letter);
}

/* Verifica se os caraceteres são equivalentes.
 * NOTA: firstLetter não pode ser um curinga.
 */
bool lettersMatch(char *firstLetter, char *secondLetter) {
	if (*firstLetter == *secondLetter) {
		return true;
	} else if (*secondLetter == WILDCARD_ANY) {
		return true;
	} else if (isVowel(firstLetter) && *secondLetter == WILDCARD_VOWEL) {
		return true;
	} else if (isConsonant(firstLetter) && *secondLetter == WILDCARD_CONSONANT) {
		return true;
	}

	return false;
}