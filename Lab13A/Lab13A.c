/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 13A - JMob
 *
 * Verifica se os mobiles produzidos pela JMob estão devidamente equilibrados
 * após a mudança de fornecedor. Informa também o peso total do mobile.
 */

#include <stdio.h>
#include <stdbool.h>

/* Processa de maneira recursiva cada um dos nós do mobile */
int processTree(bool *isBalanced);

int main() {
	int treeWeight;
	bool isBalanced = true;

	treeWeight = processTree(&isBalanced);

	printf("Mobile %s\n", (isBalanced ? "equilibrado" : "desequilibrado"));
	printf("Peso total: %d\n", treeWeight);

	return 0;
}

/* Processa de maneira recursiva cada um dos nós do mobile, retornando seus
 * pesos.
 */
int processTree(bool *isBalanced) {
	int leftWeight, leftDist;
	int rightWeight, rightDist;

	scanf("%d %d %d %d", &leftWeight, &leftDist, &rightWeight, &rightDist);

	/* Se tivermos um outra barra, recursivamente calculamos o peso desta */
	if (leftWeight == 0) {
		leftWeight = processTree(isBalanced);
	}

	/* Se tivermos um outra barra, recursivamente calculamos o peso desta */
	if (rightWeight == 0) {
		rightWeight = processTree(isBalanced);
	}

	/* Se ainda acharmos que o mobile está balanceado, verificar se o nó atual
	 * também está.
	 */
	*isBalanced = *isBalanced && (leftWeight * leftDist == rightWeight * rightDist);


	return leftWeight + rightWeight;
}