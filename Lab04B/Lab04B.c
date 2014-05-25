/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 04B - Semanada
 */

#include <stdio.h>

#define DIGITS_AMOUNT 100

/* Dado um número de n dígitos, remove m dígitos retornando o maior valor
 * possível. O algorítmo funciona comparando dígitos adjacentes e removendo o
 * da esquerda caso este seja menor que o da direita.
 */
int main() {
	int i;
	int currentDigit = 0, comparingDigit = 1;
	int digits[DIGITS_AMOUNT];
	int digitsAmount, removableDigits, desiredDigits;

	/* Leitura do input */
	scanf("%d %d", &digitsAmount, &removableDigits);

	for (i = 0; i < digitsAmount; i++) {
		scanf("%d", &digits[i]);
	}

	desiredDigits = digitsAmount - removableDigits;

	/* Enquanto ainda tivermos que remover dígitos ou não tivermos atingido o
	 * último dígito, continuar removendo.
	 */
	while (removableDigits > 0 && comparingDigit < digitsAmount) {

		/* Pular os dígitos excluídos */
		while (digits[currentDigit] == -1) {
			currentDigit++;
		}

		/* Se o dígito atual for menor do que o que está sendo comparado,
		 * remover este.
		 */
		if (digits[currentDigit] < digits[comparingDigit]) {
			digits[currentDigit] = -1;
			removableDigits--;

			/* Comparar denovo com o dígito anterior */
			if (currentDigit > 0) {
				currentDigit--;
				comparingDigit--;

				/* Pular os dígitos excluídos */
				while (digits[currentDigit] == -1) {
					currentDigit--;
				}

				currentDigit--;
			}
		}

		currentDigit++;
		comparingDigit++;
	}

	printf("Maior valor: ");

	/* Printa cada um dos dígitos do valor */
	for (i = 0; i < desiredDigits; i++) {

		/* Se -1 for o valor do dígito, ignoramos este */
		if (digits[i] != -1) {
			printf("%d", digits[i]);
		} else {

			/* Se um digito foi ignorado, precisamos de mais um */
			desiredDigits++;
		}
	}

	printf("\n");

	return 0;
}