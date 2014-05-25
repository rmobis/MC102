/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 01A - Cálculo de Média das Notas do Semestre
 */

#include <stdio.h>
#include <math.h>

int main() {
	double P1, P2, P3, L;
	double P, MH, MA, MG;

	/* Leitura dos dados */
	scanf("%lf %lf %lf %lf", &P1, &P2, &P3, &L);

	/* Realização dos cálculos */
	P = ((P1 * 3) + (P2 * 3) + (P3 * 4)) / 10;
	MA = (P + L) / 2;
	MH = (2 * P * L) / (P + L);
	MG = sqrt(P * L);

	/* Impressão da resposta */
	printf("Media aritmetica: %.1f\n", MA);
	printf("Media harmonica: %.1f\n", MH);
	printf("Media geometrica: %.1f\n", MG);

    return 0;
}