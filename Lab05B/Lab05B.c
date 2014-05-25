/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 05B - Killing the Messenger
 */

/*
 *       _____           _____
 *   ,ad8PPPP88b,     ,d88PPPP8ba,
 *  d8P"      "Y8b, ,d8P"      "Y8b
 * dP'           "8a8"           `Yd
 * 8(              "              )8
 * I8                             8I
 *  Yb,          Zanoni         ,dP
 *   "8a,                     ,a8"
 *     "8a,                 ,a8"
 *       "Yba             adP"
 *         `Y8a         a8P'
 *           `88,     ,88'
 *             "8b   d8"
 *              "8b d8"
 *               `888'
 *                 "
 */

#include <stdio.h>
#include <stdbool.h>

#define MRNA_MAX_LENGTH 100
#define OLIGO_MAX_LENGTH 25

int main() {
	int i, j;
	bool match = false;
	char curOligo;
	int mRNALength, oligoLength;
	char mRNA[MRNA_MAX_LENGTH], oligo[OLIGO_MAX_LENGTH];

	/* Leitura do Input */
	scanf("%d %d", &mRNALength, &oligoLength);
	for (i = 0; i < mRNALength; i++) {
		scanf(" %c", &mRNA[i]);
	}
	for (i = 0; i < oligoLength; i++) {
		/* Salva os caracteres na ordem inversa e já converte para o complemento
		 * esperado para facilitar a comparação posterior.
		 */
		scanf(" %c", &curOligo);
		switch (curOligo) {
			case 'A':
				curOligo = 'U';
				break;

			case 'C':
				curOligo = 'G';
				break;

			case 'G':
				curOligo = 'C';
				break;

			case 'U':
				curOligo = 'A';
				break;
		}

		oligo[oligoLength - i - 1] = curOligo;
	}

	i = 0;

	/* Para cada posição inicial possível de haver combinação, checar todas as
	 * bases seguintes.
	 */
	while (i < mRNALength - oligoLength + 1 && !match) {
		j = 0;


		while (mRNA[i + j] == oligo[j] && j < oligoLength) {
			j++;
		}

		/* Se as bases bateram até o final do oligonucletídeo, nos temos uma
		 * combinação bem sucedida.
		 */
		match = (j == oligoLength);

		i++;
	}

	if (match) {
		/* i armazena a posição do silenciamente pois após a verificação de que
		 * houve uma combinação, ela ainda é incrementada uma vez.
		 */
		printf("Silenciado em %d\n", i);
	} else {
		printf("Nao silenciado\n");
	}
    return 0;
}
