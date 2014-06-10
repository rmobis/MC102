/* Nome: Raphael Mobis Tacla
* RA: 157104
* Laboratorio 14A - Gerenciador de Memória
*
* Lê uma série de caracteres, cada um representando uma ação a ser realizada
* quanto à região de memória atual:
*
* I - Aloca a região em sua totalidade
* D - Aloca metade da região e passa as duas sub-regiões de 1/4 restantes para
*     o próximo programa.
* # - Encerra as alocações.
*
* Ao final, informa se a alocação foi parcial, total ou inválida.
*/

#include <stdio.h>
#include <stdbool.h>

#define ALLOCATE_SHARE 'D'
#define ALLOCATE_FULL  'I'
#define ALLOCATE_END   '#'

/* Aloca as regiões de memória */
void allocateSpace(bool *endOfInput);

int main() {
	bool endOfInput = false;
	char nextAllocation;


	allocateSpace(&endOfInput);

	/* Se chegamos ao final das alocações dentro de `allocateSpace`, é por que
	 * lemos o caractere '#' antes de alocar todos as regiões esperadas.
	 */
	if (endOfInput) {
		printf("Alocacao parcial\n");
	} else {
		scanf("%c", &nextAllocation);


		if (nextAllocation == ALLOCATE_END) {
			/* Se não chegamos ao final das alocações dentro de `allocateSpace`,
			 * mas o próximo caractere indicaria o final das alocações, então
			 * alocamos todas as regiões disponíveis.
			 */
			printf("Alocacao total\n");
		} else {
			/* Se não chegamos ao final das alocações dentro de `allocateSpace`
			 * e o próximo caractere não indicaria o final das alocações, então
			 * alocamos todas as regiões disponíveis e ainda havia alocações a
			 * serem feitas.
			 */
			printf("Alocacao invalida\n");
		}
	}

	scanf("%*c%*c");

	return 0;

}

/* Aloca as regiões de memória */
void allocateSpace(bool *endOfInput) {
	char allocationType;

	/* Se já chegamos ao final da entrada, não há nada a ser alocado */
	if (*endOfInput) {
		return;
	}

	scanf("%c", &allocationType);

	if (allocationType == ALLOCATE_END) {
		*endOfInput = true;
	} else if (allocationType == ALLOCATE_SHARE) {
		allocateSpace(endOfInput);
		allocateSpace(endOfInput);
	}
}