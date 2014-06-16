/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 15A - Transferência de Bitcoins
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#define VERIFICATION_CODE_LENGTH 9

/* Converte um caractere de dígito para sua representação como número inteiro */
int parseDigit(char digit);
int splitDigitsValue(int digits, int digitsStart, int digitsEnd);
bool checkCode(int verificationCode, int securityCode, int nextDigit, int previousValue);

int main() {
	int securityCode;
	bool isTransactionValid;
	int verificationCode;

	scanf("%d %d", &verificationCode, &securityCode);

	isTransactionValid = checkCode(verificationCode, securityCode, 0, 0);
	printf("Transferencia %s\n", isTransactionValid ? "aceita" : "abortada");

	return 0;
}

bool checkCode(int verificationCode, int securityCode, int nextDigit, int previousValue) {
	int i;
	int curValue, totalValue;

	totalValue = splitDigitsValue(verificationCode, nextDigit, VERIFICATION_CODE_LENGTH - 1);

	if (
		previousValue + totalValue == securityCode ||
		previousValue - totalValue == securityCode
	) {
		return true;
	}

	for (i = nextDigit + 1; i < VERIFICATION_CODE_LENGTH; i++) {
		curValue = splitDigitsValue(verificationCode, nextDigit, i - 1);

		if (
			checkCode(verificationCode, securityCode, i, previousValue + curValue) ||
			(nextDigit && checkCode(verificationCode, securityCode, i, previousValue - curValue))
		) {
			return true;
		}
	}

	return false;
}

int splitDigitsValue(int digits, int digitsStart, int digitsEnd) {
	int upperBound = pow(10, VERIFICATION_CODE_LENGTH - digitsStart);
	int lowerBound = pow(10, VERIFICATION_CODE_LENGTH - digitsEnd - 1);

	return (digits % upperBound) / lowerBound;
}

/* Converte um caractere de dígito para sua representação como número inteiro */
int parseDigit(char digit) {
	return (int) (digit - '0');
}