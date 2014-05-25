/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 03A - Composição de Senha
 */

#include <stdio.h>
#include <math.h>

/*
Recebe uma série de compassos músicais e os transforma em uma senha, seguindo
 * a lógica de que cada compasso é um digito da senha; caso o compasso seja um
 * compasso válido (tenha soma de durações igual à de uma semibreve (1)), o
 * dígito vale o número de durações do compasso; caso contrário, vale zero.
 */
int main() {
	char duration;
	int count = 0;
	double sum;

	scanf("%c", &duration);

	/* Enquanto não encontrarmos o caractere de saída, continuamos lendo a
	 * entrada.
	 */
	while (duration != '*') {

		/* A quebra de linha marca o final de um compasso */
		if (duration == '\n') {
			/* Se a soma tem valor 1, usamos o número de durações; caso
			 * contrário, zero
			 */
			if (sum == 1) {
				printf("%d", count);
			} else {
				printf("0");
			}

			/* Resetar a soma e a contagem de dígitos da linha */
			sum = 0;
			count = 0;
		} else {
			/* Como 65 é o valor na tabela ASCII para o caractere 'A', que
			 * representa a semibreve, e estes seguem sequencialmente, tendo
			 * sua duração cortada pela metade para cada incremento, podemos
			 * definir uma fórmula geral para o valor da duração em função do
			 * valor (v) de seu caractere na tabela ASCII (a) como dado abaixo:
			 *
			 * v = 1 / (2 ^ (a - 65))
			 *
			 */
			sum += 1 / pow(2, duration - 65);

			count++;
		}

		scanf("%c", &duration);
	}

	printf("\n");
    return 0;
}
