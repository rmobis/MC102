/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 08A - Amigos dos amigos
 *
 * Faz sugestões de novas amizades procurando por amigos de amigos que não são
 * seus amigos.
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_USERS 100

int main() {
	int i, j;
	bool suggestFriend;
	int usersAmount, chosenUser;
	int friendshipTable[MAX_USERS][MAX_USERS];
	int friendCount = 0, notFriendCount = 0, suggestedFriendCount = 0;
	int friends[MAX_USERS - 1], notFriends[MAX_USERS - 1], suggestedFriends[MAX_USERS - 2];

	scanf("%d %d", &usersAmount, &chosenUser);

	/* Leitura da relação de amizades */
	for (i = 0; i < usersAmount; i++) {
		for (j = 0; j < usersAmount; j++) {
			scanf("%d", &friendshipTable[i][j]);

			/* Já salva quais usuários são e quais não são amigos do usuário
			 * escolhido.
			 */
			if (i == chosenUser && i != j) {
				if (friendshipTable[i][j]) {
					friends[friendCount++] = j;
				} else {
					notFriends[notFriendCount++] = j;
				}
			}
		}
	}

	/* Procura por sugestões de amizade */
	for (i = 0; i < notFriendCount; i++) {
		suggestFriend = false;

		for (j = 0; j < friendCount && !suggestFriend; j++) {
			suggestFriend = (friendshipTable[notFriends[i]][friends[j]]);
		}

		if (suggestFriend) {
			suggestedFriends[suggestedFriendCount++] = notFriends[i];
		}
	}

	/* Impressão das sugestões */
	if (suggestedFriendCount == 0) {
		printf("Sem sugestao de novos amigos\n");
	} else {
		printf("Sugestao de amigos:");

		for (i = 0; i < suggestedFriendCount; i++) {
			printf(" %d", suggestedFriends[i]);
		}

		printf("\n");
	}

    return 0;
}
