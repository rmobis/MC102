/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 15A - Transferência de Bitcoins
 *
 * Verifica se uma transferência de bitcoins é válida ou não, verificando se
 * existe alguma combinação de operações que podem ser intercaladas entre um ou
 * mais dígitos do código de verificação para que o resultado da aplicação
 * destas seja o código de segurança. Imprime se a transferência foi aceita ou
 * não.
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define VERIFICATION_CODE_LENGTH 9

/* Verifica se existe algum combinação de operações que podem ser intercaladas
 * entre um ou mais dígitos de `verifCode` para que o resultado dê `secCode`.
 */
bool checkCode(int verifCode, int secCode, int nextDigit, int prevValue);

/* Retorna o valor de dígitos intermediários. */
int splitDigitsValue(int digits, int digitsStart, int digitsEnd);

int main() {
	int securityCode;
	bool isTransactionValid;
	int verificationCode;

	scanf("%d %d", &verificationCode, &securityCode);

	isTransactionValid = checkCode(verificationCode, securityCode, 0, 0);

	printf("Transferencia %s\n", isTransactionValid ? "aceita" : "abortada");

	return 0;
}

/* Verifica se existe algum combinação de operações que podem ser intercaladas
 * entre um ou mais dígitos de `verifCode` para que o resultado dê `secCode`. O
 * processo é feito usando brute force, gerando todas as combinações possíveis e
 * verificando, uma a uma, se são soluções.
 */
bool checkCode(int verifCode, int secCode, int nextDigit, int prevValue) {
	int i;
	int curValue, totalValue;

	/* Obtém o valor de todos os dígitos restantes */
	totalValue = splitDigitsValue(verifCode, nextDigit, VERIFICATION_CODE_LENGTH - 1);

	/* Se essa combinação satisfaz nosso problema, retornamos */
	if (prevValue + totalValue == secCode) {
		return true;
	} else if (nextDigit != 0 && prevValue - totalValue == secCode) {
		/* Só podemos usar a subtração caso não estejamos no primeiro dígito */
		return true;
	}

	for (i = nextDigit + 1; i < VERIFICATION_CODE_LENGTH; i++) {
		curValue = splitDigitsValue(verifCode, nextDigit, i - 1);

		/* Se alguma combinação posterior satisfaz nosso problema, retornamos */
		if (checkCode(verifCode, secCode, i, prevValue + curValue)) {
			return true
		} else if (nextDigit != 0 && checkCode(verifCode, secCode, i, prevValue - curValue)) {
			/* Só podemos usar a subtração caso não estejamos no primeiro dígito */
			return true;
		}
	}

	return false;
}

/* Retorna o valor de dígitos intermediários; isso feito em duas etapas:
 *
 * - Primeiro remove-se os maiories dígitos, através da obtenção do resto da
 *   divisão do valor total por 10^u, onde u é a quantidade de digitos maiores a
 *   ser removida.
 * - Depois remove-se os menores dígitos, através da divisão inteira do valor
 *   total por 10^k, onde k é a quantidade de digitos menores a ser removida.
 */
int splitDigitsValue(int digits, int digitsStart, int digitsEnd) {
	int upperBound = pow(10, VERIFICATION_CODE_LENGTH - digitsStart);
	int lowerBound = pow(10, VERIFICATION_CODE_LENGTH - digitsEnd - 1);

	return (digits % upperBound) / lowerBound;
}