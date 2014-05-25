/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 04A - Deep Web
 */

#include <stdio.h>

#define DIGITS_AMOUNT 15

/* Algorítmo para gerar as senhas para o site 'El Terror' com base nos N
 * primeiros dígitos fornecidos ao entrar no site. Os dígitos subsequentes são
 * calculados através do resto da divisão inteira da soma dos valores do dígitos
 * anteriores, multiplicados pelo número de dígitos já conhecidos e por suas
 * respectivas posições, por 11. Caso este resto seja 10, o dígito é 0; caso
 * contrário, é o valor do resto.
 */
int main() {
	int digits[DIGITS_AMOUNT];
	int knownDigits, digitsSum;
	int i;

	/* Inicializa o vetor dos dígitos da senha com -1, que significa que ainda
	 * não conhecemos o dígito.
	 */
	for (i = 0; i < DIGITS_AMOUNT; i++) {
		digits[i] = -1;
	}

	scanf("%d", &knownDigits);

	/* Lê todos os dígitos conhecidos. */
	for (i = 0; i < knownDigits; i++) {
		scanf("%d", &digits[i]);
	}

	/* Enquanto não soubermos todos os dígitos, continuar tentando descobrir o
	 * próximo.
	 */
	while (knownDigits < DIGITS_AMOUNT) {
		digitsSum = 0;

		for (i = 0; i < knownDigits; i++) {
			digitsSum += digits[i] * knownDigits * (i + 1);
		}

		digits[knownDigits] = (digitsSum % 11) % 10;

		knownDigits++;
	}

	/* Printa cada um dos dígitos da senha */
	for (i = 0; i < DIGITS_AMOUNT; i++) {
		printf("%d", digits[i]);
	}

	printf("\n");

	return 0;
}
