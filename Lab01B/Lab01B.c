/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 01B - Notas do Vestibular
 */

#include <stdio.h>
#include <math.h>

int main() {
	int A, NMO; /* Área e Nota Mínima */
	double Pcg, Pin, Ppo, Pma, Pch, Pcn; /* Pesos das provas */
	double Ncg, Mcg, DPcg; /* Nota, Média e Desvio da 1a Fase */
	double NPcg; /* Nota Padrozinada da 1a Fase */

	/* Notas, Médias e Desvios Padrão de cada prova */
	double Nin, Min, DPin;
	double Npo, Mpo, DPpo;
	double Nma, Mma, DPma;
	double Nch, Mch, DPch;
	double Ncn, Mcn, DPcn;

	/* Notas padronizadas de cada prova */
	double NPin, NPpo, NPma, NPch, NPcn;

	/* Nota Final */
	double NF;

	/* Leitura dos dados da 1a Fase */
	scanf("%d %d", &A, &NMO);
	scanf("%lf %lf %lf %lf %lf %lf", &Pcg, &Pin, &Ppo, &Pma, &Pch, &Pcn);
	scanf("%lf %lf %lf", &Ncg, &Mcg, &DPcg);

	/* Cálculos da 1a Fase */
	NPcg = (((Ncg - Mcg) * 100) / DPcg) + 500;

	/* Impressão dos dados da primeira fase */
	printf("Primeira Fase: %.1f\n", NPcg);


	/* Terminar o programa caso o candidato não tenha sido aprovado para a
	 * segunda fase. */
	if (NPcg < 550) {
		return 0;
	}


	/* Leitura dos dados da 2a Fase */
	scanf("%lf %lf %lf", &Nin, &Min, &DPin);
	scanf("%lf %lf %lf", &Npo, &Mpo, &DPpo);
	scanf("%lf %lf %lf", &Nma, &Mma, &DPma);
	scanf("%lf %lf %lf", &Nch, &Mch, &DPch);
	scanf("%lf %lf %lf", &Ncn, &Mcn, &DPcn);

	/* Cálculos da 2a Fase */
	NPin = (((Nin - Min) * 100) / DPin) + 500;
	NPpo = (((Npo - Mpo) * 100) / DPpo) + 500;
	NPma = (((Nma - Mma) * 100) / DPma) + 500;
	NPch = (((Nch - Mch) * 100) / DPch) + 500;
	NPcn = (((Ncn - Mcn) * 100) / DPcn) + 500;
	NF = ((NPcg * Pcg) + (NPin * Pin) + (NPpo * Ppo) + (NPma * Pma) + (NPch * Pch) + (NPcn * Pcn)) / (Pcg + Pin + Ppo + Pma + Pch + Pcn);


	/* Impressão dos dados da primeira fase */
	printf("Segunda Fase: %.1f\n", NF);

	/* Impressão do grupo */
	if (A == 1) { /* Exatas */
		if (NPma >= NMO && NPcn >= NMO) {
			printf("Grupo 1\n");
		} else {
			printf("Grupo 2\n");
		}
	} else if (A == 2) { /* Humanas */
		if (NPpo >= NMO && NPch >= NMO) {
			printf("Grupo 1\n");
		} else {
			printf("Grupo 2\n");
		}
	} else if (A == 3) { /* Biológicas */
		if (NPcn >= NMO) {
			printf("Grupo 1\n");
		} else {
			printf("Grupo 2\n");
		}
	}

    return 0;
}
