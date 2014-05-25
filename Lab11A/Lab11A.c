/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 11A - Copa do Mundo (Não vai ter copa!)
 *
 * Dados os resultados de todos os jogos da fase de grupos da Copa do Mundo da
 * FIFA, este programa imprime em ordem de classificação os participantes de
 * cada um dos grupos, junto com suas pontuações, gols feitos e tomados e saldo
 * de gols. Além disso, imprime os jogos que acontecerão nas Oitavas de Final,
 * assumindo que os dois primeiros colocados de cada grupo se classificam.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_TEAM_NAME_LENGTH 15

#define GROUPS_AMOUNT       8
#define TEAMS_PER_GROUP     4
#define MATCHES_PER_GROUP   6
#define QUALIFIED_PER_GROUP 2

#define TEAM_POINTS     0
#define GOALS_SCORED    1
#define GOALS_AGAINST   2
#define GOAL_DIFFERENCE 3

#define WIN_POINTS    3
#define DRAW_POINTS   1
#define DEFEAT_POINTS 0


/* Lê e computa os resultados de uma partida */
void computeMatch(char groupTeams[][MAX_TEAM_NAME_LENGTH + 1], int groupData[][4], int *groupLength);

/* Calcula a quantidade de pontos de cada time na partida */
void getTeamPoints(int *firstTeamPoints, int *secondTeamPoints, int firstTeamScore, int secondTeamScore);

/* Ordena os times dentro dos seus grupos */
void sortGroup(char groupTeams[][MAX_TEAM_NAME_LENGTH + 1], int groupData[][4]);

/* Compara dois times e retorna se o primeiro tem melhor classificação */
bool isGreater(char curName[], int curData[], char compName[], int compData[]);

/* Preenche um vetor de inteiros com valores */
void fillArray(int array[], int start, int step, int length);


int main() {
	int i, j;
	int groupLength;
	int qualifiedLength;
	int groupData[TEAMS_PER_GROUP][4];
	char qualifiedTeams[GROUPS_AMOUNT * QUALIFIED_PER_GROUP][MAX_TEAM_NAME_LENGTH + 1];
	char groupTeams[TEAMS_PER_GROUP][MAX_TEAM_NAME_LENGTH + 1];


	qualifiedLength = 0;
	for (i = 0; i < GROUPS_AMOUNT; i++) {
		groupLength = 0;

		for (j = 0; j < MATCHES_PER_GROUP; j++) {
			computeMatch(groupTeams, groupData, &groupLength);
		}

		sortGroup(groupTeams, groupData);

		/* Copia os times classificados para o vetor de classificados */
		for (j = 0; j < QUALIFIED_PER_GROUP; j++) {
			strcpy(&qualifiedTeams[qualifiedLength++][0], &groupTeams[j][0]);
		}

		printf("Grupo %c:\n", 'A' + i);
		for (j = 0; j < TEAMS_PER_GROUP; j++) {
			printf("%-15s %3d %3d %3d %3d\n", &groupTeams[j][0], groupData[j][TEAM_POINTS], groupData[j][GOALS_SCORED], groupData[j][GOALS_AGAINST], groupData[j][GOAL_DIFFERENCE]);
		}
		printf("\n");
	}

	printf("Oitavas de final:\n");
	for (i = 0; i < GROUPS_AMOUNT * QUALIFIED_PER_GROUP; i += 4) {
		printf("%15s x %s\n", qualifiedTeams[i], qualifiedTeams[i + 3]);
		printf("%15s x %s\n", qualifiedTeams[i + 2], qualifiedTeams[i + 1]);
	}

	return 0;
}

/* Lê e computa os resultados de uma partida, adicionando os times que ainda não
 * foram incluídos no grupo e somando as pontuações, gols feitos e tomados e
 * saldo de gols.
 */
void computeMatch(char groupTeams[][MAX_TEAM_NAME_LENGTH + 1], int groupData[][4], int *groupLength) {
	int i, j;
	bool entryFound;
	int teamScores[2];
	int teamPoints[2];
	char teamNames[2][MAX_TEAM_NAME_LENGTH + 1];

	scanf("%s %d x %d %s", &teamNames[0][0], &teamScores[0], &teamScores[1], &teamNames[1][0]);

	/* Nós assumimos que se todos os times do grupo ainda não foram encontrados,
	 * os times da partida atual não foram encontrados. Sendo assim, inserimos
	 * estes na array de times e zeramos a array com sua pontuação, gols feitos
	 * e tomados e saldo de gols.
	 */
	if (*groupLength < TEAMS_PER_GROUP) {
		strcpy(&groupTeams[(*groupLength)][0], &teamNames[0][0]);
		fillArray(&groupData[(*groupLength)][0], 0, 0, TEAMS_PER_GROUP);
		(*groupLength)++;

		strcpy(&groupTeams[(*groupLength)][0], &teamNames[1][0]);
		fillArray(&groupData[(*groupLength)][0], 0, 0, TEAMS_PER_GROUP);
		(*groupLength)++;
	}

	/* Descobre os pontos ganhos por cada time nesta partida */
	getTeamPoints(&teamPoints[0], &teamPoints[1], teamScores[0], teamScores[1]);

	/* Para cada um dos times da partida */
	for (i = 0; i < 2; i++) {
		entryFound = false;

		/* Procura o índice do time na array de times */
		for (j = 0; j < *groupLength && !entryFound; j++) {
			if (strcmp(&teamNames[i][0], &groupTeams[j][0]) == 0) {

				/* Soma os dados encontrados aos dados anteriores.
				 *
				 * NOTA: teamScores[(i + 1) % 2] retorna os gols marcados pelo
				 * outro time, uma vez que para i = 0, (i + 1) % 2 = 1 e, para
				 * i = 1, (i + 1) % 2 = 0;
				 */
				groupData[j][TEAM_POINTS]     += teamPoints[i];
				groupData[j][GOALS_SCORED]    += teamScores[i];
				groupData[j][GOALS_AGAINST]   += teamScores[(i + 1) % 2];
				groupData[j][GOAL_DIFFERENCE] += teamScores[i] - teamScores[(i + 1) % 2];

				entryFound = true;
			}
		}
	}
}

/* Dado o placar da partida, calcula a quantidade de pontos que cada time deve
 * receber pelo desempenho na partida.
 */
void getTeamPoints(int *firstTeamPoints, int *secondTeamPoints, int firstTeamScore, int secondTeamScore) {
	if (firstTeamScore > secondTeamScore) {
		*firstTeamPoints  = WIN_POINTS;
		*secondTeamPoints = DEFEAT_POINTS;
	} else if (firstTeamScore < secondTeamScore) {
		*firstTeamPoints  = DEFEAT_POINTS;
		*secondTeamPoints = WIN_POINTS;
	} else {
		/* Se não houve vitória de nenhum dos times, houve um empate */
		*firstTeamPoints  = DRAW_POINTS;
		*secondTeamPoints = DRAW_POINTS;
	}
}

/* Ordena os times dentro dos seus grupos seguindo os seguintes critérios, em
 * ordem de relevância:
 *
 * - Total de Pontos
 * - Saldo de Gols
 * - Gols Marcados
 * - Ordem Alfabética
 */
void sortGroup(char groupTeams[][MAX_TEAM_NAME_LENGTH + 1], int groupData[][4]) {
	int i, j;
	char curName[MAX_TEAM_NAME_LENGTH + 1];
	int curData[4];

	for (i = 1; i < TEAMS_PER_GROUP; i++) {
		strcpy(curName, &groupTeams[i][0]);
		memcpy(curData, &groupData[i][0], 4 * sizeof(int));

		for (j = i - 1; j >= 0 && isGreater(curName, curData, &groupTeams[j][0], &groupData[j][0]); j--) {
			strcpy(&groupTeams[j + 1][0], &groupTeams[j][0]);
			memcpy(&groupData[j + 1][0], &groupData[j][0], 4 * sizeof(int));
		}

		strcpy(&groupTeams[j + 1][0], curName);
		memcpy(&groupData[j + 1][0], curData, 4 * sizeof(int));
	}
}

/* Compara dois times, seguindo os seguintes critérios, em
 * ordem de relevância:
 *
 * - Total de Pontos
 * - Saldo de Gols
 * - Gols Marcados
 * - Ordem Alfabética
 *
 * Retorna `true` se o primeiro time deve estar classificado acima do segundo,
 * `false` caso contrário.
 */
bool isGreater(char curName[], int curData[], char compName[], int compData[]) {
	int k;
	int comparingOrder[] = {TEAM_POINTS, GOAL_DIFFERENCE, GOALS_SCORED};

	/* Verifica cada um dos critérios de ordenação, em ordem de relevância.
	 * Apenas no caso de o critério atual ser igual para ambos os times, faz a
	 * verificação do próximo critério.
	 */
	for (k = 0; k < 3; k++) {
		if (curData[comparingOrder[k]] > compData[comparingOrder[k]]) {
			return true;
		} else if (curData[comparingOrder[k]] < compData[comparingOrder[k]]) {
			return false;
		}
	}

	/* Se todos os critérios anteriores forem iguais, utiliza a ordem alfabética
	 * como critério final.
	 */
	return strcmp(curName, compName) < 0;
}

/* Preenche um vetor de inteiros com valores; a primeira posição recebe `start`
 * e `step` é adicionado a cada posição subsequente.
 */
void fillArray(int array[], int start, int step, int length) {
	int i;

	for (i = 0; i < length; i++) {
		array[i] = start + (step * i);
	}
}