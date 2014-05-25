/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 08B - Processamento de Imagens
 *
 * Faz sugestões de novas amizades procurando por amigos de amigos que não são
 * seus amigos.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* Le uma imagem em formato PGM a partir da entrada padrao.
 * Retorna 1 se a leitura for realmente de um arquivo PGM
 * e 0 caso contrario.
 * VOCE NAO DEVE ALTERAR ESTA FUNCAO                       */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,
			int *F, double *Px, double *Py) {
	char nome_formato[3];
	char c;
	int i,j;

	/* Le o formato da imagem. P2 indica o formato PGM */
	scanf("%s ", nome_formato);
	if (strcmp(nome_formato, "P2") != 0)
		return 0;

	/* Le o '#', que indica um comentario, e os numeros indicando
	* o filtro e o parametro, se houver */
	scanf("%[#]c", &c);
	scanf("%d", F);
	if (*F == 4) {
		scanf("%lf %lf", Px, Py);
	}

	/* Le dimensoes e intensidade maxima da imagem */
	scanf("%d", W);
	scanf("%d", H);
	scanf("%d", MaxV);

	/* Le o valor de cada pixel da imagem */
	for (i = 0; i < (*H); i++) {
		for (j = 0; j < (*W); j++) {
			scanf("%d", &img[i][j]);
		}
	}

	return 1;
}

/* Escreve a imagem em formato pgm na saida padrao
 * VOCE NAO DEVE ALTERAR ESTA FUNCAO               */
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
	int i, j;

	/* Escreve os atributos da imagem */
	/* Tipo da imagem: P2 significa pgm*/
	printf("P2\n");
	/* Dimensoes e intensidade maxima da imagem */
	printf("%d %d %d\n", W, H, MaxV);

	/* Escreve os pixels da imagem */
	for (i = 0; i < H; i++) {
		printf("%d", img[i][0]);
		for (j = 1; j < W; j++) {
			printf(" %d", img[i][j]);
		}
		printf("\n");
	}
}

/* Normaliza o valor, retornando 0 para valores negativos e o máximo para
 * acima deste.
 */
int normalizeValue(int value, int maxValue) {
	if (value < 0) {
		return 0;
	} else if (value > maxValue) {
		return maxValue;
	}

	return value;
}

/* Negativo */
void negativo(int img[][MAX_TAM], int W, int H, int MaxV) {
	int i, j;

	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			img[i][j] = MaxV - img[i][j];
		}
	}
}

/* Rotacao de 180 graus */
void rotacao180(int img[][MAX_TAM], int W, int H) {
	int i, j;
	int tempHolder;

	/* Inverte verticalmente */
	for (i = 0; i < H / 2; i++) {
		for (j = 0; j < W; j++) {
			tempHolder = img[i][j];
			img[i][j] = img[H - i - 1][j];
			img[H - i - 1][j] = tempHolder;
		}
	}

	/* Inverte horizontalmente */
	for (i = 0; i < H; i++) {
		for (j = 0; j < W / 2; j++) {
			tempHolder = img[i][j];
			img[i][j] = img[i][W - j - 1];
			img[i][W - j - 1] = tempHolder;
		}
	}
}

/* Deteccao de bordas */
void detectaBorda(int img[][MAX_TAM], int W, int H, int MaxV) {
	int i, j, k, l;
	int pixelValue;
	int newImg[MAX_TAM][MAX_TAM];
	int filter[3][3] = {
		{-1, -4, -1},
		{-4, 20, -4},
		{-1, -4, -1}
	};

	/* Pulamos as bordas, pois estas nao são processadas */
	for (i = 1; i < H - 1; i++) {
		for (j = 1; j < W - 1; j++) {
			pixelValue = 0;

			for (k = -1; k <= 1; k++) {
				for (l = -1; l <= 1; l++) {
					pixelValue += (filter[1 + k][1 + l] * img[i + k][j + l]);
				}
			}

			newImg[i][j] = normalizeValue(pixelValue, MaxV);
		}
	}

	/* Copia de volta para a antiga matriz */
	for (i = 1; i < H - 1; i++) {
		for (j = 1; j < W - 1; j++) {
			img[i][j] = newImg[i][j];
		}
	}
}

/* Cisalhamento */
void cisalhamento(int img[][MAX_TAM], int W, int H, double Px, double Py) {
	int i, j;
	int newX, newY;
	int newImg[MAX_TAM][MAX_TAM];

	/* Zera a nova matriz */
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			newImg[i][j] = 0;
		}
	}

	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			newY = i + (int) floor(Py * j);
			newX = j + (int) floor(Px * i);

			if (newX < W && newY < H) {
				newImg[newY][newX] = img[i][j];
			}
		}
	}

	/* Copia de volta para a antiga matriz */
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			img[i][j] = newImg[i][j];
		}
	}
}


/* VOCE NAO DEVE ALTERAR A FUNCAO PRINCIPAL */
int main() {
	/* Matriz que armazena os pixels da imagem */
	int img[MAX_TAM][MAX_TAM];
	/* Atributos da imagem */
	int W, H, MaxV;
	/* Identificador do filtro a ser utilizado */
	int F;
	/* Parametro a ser passado para o cisalhamento */
	double Px, Py;

	/* Le a imagem */
	if (ler_pgm(img, &W, &H, &MaxV, &F, &Px, &Py) != 1) {
		printf("Error: nao foi possivel ler a imagem\n");
		return 0;
	}

	/* Seleciona o filtro */
	switch (F) {
		case 1:
			negativo(img, W, H, MaxV);
			break;
		case 2:
			rotacao180(img, W, H);
			break;
		case 3:
			detectaBorda(img, W, H, MaxV);
			break;
		case 4:
			cisalhamento(img, W, H, Px, Py);
			break;
	}

	/* Escreve a imagem */
	escrever_pgm(img, W, H, MaxV);

	return 0;
}
