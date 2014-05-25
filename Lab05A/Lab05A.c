/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 05A - Caça ao Tesouro
 */

#include <stdio.h>

#define MAX_LENGTH 100

/* Segue as dicas dadas pelo mapa de tesouro até encontra-lo, ou até perceber
 * que o mapa não leva a nenhum tesouro.
 */
int main() {
	int i, stepsAmount;
	int currentStep = 1, stepsTaken = 0;
	int steps[MAX_LENGTH];

	/* Leitura do Input */
	scanf("%d", &stepsAmount);
	for (i = 0; i < stepsAmount; i++) {
		scanf("%d", &steps[i]);
	}

	/* Enquanto a posição atual não for a de um tesouro, e nós tivermos dado
	 * menos passos do que o número de posições totais, continuar procurando o
	 * tesouro.
	 */
	while (steps[currentStep - 1] != currentStep && stepsTaken < MAX_LENGTH) {
		currentStep = steps[steps[currentStep - 1] - 1];
		stepsTaken++;
	}

	if (steps[currentStep - 1] == currentStep) {
		printf("Tesouro existe em %d\n", currentStep);
	} else {
		printf("Nao existe tesouro\n");
	}

    return 0;
}
