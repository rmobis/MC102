/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 03B - Fringe
 */

#include <stdio.h>
#include <stdbool.h>

/* Verifica se a máquina do Dr. Walter Bishop conseguiu sincronizar no local,
 * de acordo com as informações das fases das ondas medidas neste. Caso tenha
 * ocorrido sincronia, diz quantos mols de matéria podem atravessar em uma
 * única fase
 */
int main() {
	int SFactor, molAmount;

	bool isFirstPhase = true;
	int curPhase, curPhaseLength;
	int lastPhase = -1, lastPhaseLength = -1;
	int phaseStreak = 0;

	/* Ler número de mols por segundo e o fator S */
	scanf("%d %d", &molAmount, &SFactor);

	scanf("%d", &curPhase);

	/* Continuar recebendo input enquanto este for diferente de -1 ou enquanto
	 * a máquina ainda não tiver sincronizado.
	 */
	while (curPhase != -1 && phaseStreak < SFactor) {
		/* Se o input da fase atual tem mesmo "sentido" que o input anterior,
		 * ainda estamos na mesma fase, então devemos incrementar o tamanho da
		 * fase.
		 */
		if (curPhase == lastPhase) {
			curPhaseLength++;

		/* Caso tenha acontecido uma inversão de fases, resetar a duração da
		 * fase atual.
		 */
		} else {
			/* A primeira fase não conta */
			if (!isFirstPhase) {
				/* Se a duração da fase atual foi a mesma que a anterior,
				 * incrementar o número de fases de mesma duração que ocorreram
				 * em sequência.
				 */
				if (lastPhaseLength == curPhaseLength) {
					phaseStreak++;

				/* Caso a fase atual tenha uma duração diferente da anterior,
				 * resetar a contagem de fases em sequência
				 */
				} else {
					lastPhaseLength = curPhaseLength;
					phaseStreak = 1;
				}
			}

			/* Enquanto lastPhase = -1, ainda estamos na primeira fase */
			isFirstPhase = (lastPhase == -1);

			/* Resetamos a duração da fase para 1 ao invés de 0 pois na verdade
			 * este é o primeiro input desta fase, logo ela tem duração de no
			 * mínimo 1.
			 */
			curPhaseLength = 1;
			lastPhase = curPhase;
		}

		scanf("%d", &curPhase);
	}

	/* Se o número máximo de fases de mesma duração que ocorreram em sequência
	 * foi menor do que o fator S, o portal não abriu.
	 */
	if (phaseStreak < SFactor) {
		printf("Portal nao abriu\n");

	/* Caso o portal tenho aberto, o número de mols de matéria que podem
	 * atravessar o portal de uma só vez é o numero de mols por segundo vezes
	 * a duração da ultima fase medida antes da saída do loop, uma vez que este
	 * é terminado assim que a máquina sincroniza.
	 */
	} else {
		printf("%d mols\n", molAmount * lastPhaseLength);
	}

	return 0;
}
