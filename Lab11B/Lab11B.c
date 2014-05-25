/* Nome: Raphael Mobis Tacla
* RA: 157104
* Laboratorio 11B - BibTex
*
* Lê uma série de referências bibliográficas em formato BibTeX e, visando
* auxiliar na procura de entradas repetidas, os reimprime, ordenados de acordo
* com seu Title, com a ordem inicial como critério de desempate, no formato
* especificado abaixo:
*
* `Title, Author, Journal, Volume*, Number*, Pages*, Year.`
*
* Onde os campos marcados com * são opcionais.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_NAME_MAX_LENGTH 7
#define FULL_LINE_MAX_LENGTH  507 + FIELD_NAME_MAX_LENGTH

typedef struct Article {
	int index;
	char *author;
	char *title;
	char *journal;
	char *year;
	char *volume;
	char *number;
	char *pages;
} Article;

/* Inicializa os ponteiros do Article e define o indíce deste */
Article initializeArticle();

/* Lê o Article em formato BibTeX e dá parse nos dados */
Article readArticle();

/* Define a propriedade dada do Article com o valor dado */
void setArticleProperty(Article *article, char property[], char *value);

/* Imprime o Article no formato especificado */
void printArticle(Article *article);

/* Usada na ordenação dos Articles */
int compArticles(const void *firstPointer, const void *secondPointer);

/* Libera a memória alocada dinamicamente do Article */
void freeArticle(Article *article);

int main() {
	int i;
	int articlesAmount;
	Article *articles;

	scanf("%% %d", &articlesAmount);

	articles = (Article*)malloc(articlesAmount * sizeof(Article));

	/* Leitura */
	for (i = 0; i < articlesAmount; i++) {
		articles[i] = readArticle();
	}

	/* Ordenação */
	qsort(articles, articlesAmount, sizeof(Article), compArticles);

	/* Impressão */
	for (i = 0; i < articlesAmount; i++) {
		printArticle(&articles[i]);
	}

	/* Liberando a memória */
	for (i = 0; i < articlesAmount; i++) {
		freeArticle(&articles[i]);
	}

	free(articles);

	return 0;
}

/* Inicializa os ponteiros do Article e define o índice deste */
Article initializeArticle() {
	Article newArticle;
	static int i = 0;

	newArticle.index = i++;
	newArticle.author = NULL;
	newArticle.title = NULL;
	newArticle.journal = NULL;
	newArticle.year = NULL;
	newArticle.volume = NULL;
	newArticle.number = NULL;
	newArticle.pages = NULL;

	return newArticle;
}

/* Lê o Article em formato BibTeX e dá parse nos dados */
Article readArticle() {
	Article newArticle = initializeArticle();
	char *fieldValue;
	char fullLine[FULL_LINE_MAX_LENGTH + 2];
	char fieldName[FIELD_NAME_MAX_LENGTH + 1];

	/* Encontra o início do article e pula a label, uma vez que a esta não é
	* utilizada ao longo do programa.
	*/
	scanf("\n@article{%*s\n");

	/* Finalmente lemos a primeira linha de informações úteis */
	fgets(fullLine, FULL_LINE_MAX_LENGTH + 2, stdin);

	/* Enquanto o primeiro caractere da linha for diferente de uma chave fechando,
	 * que sinaliza o fim do article, continuamos lendo dados deste.
	*/
	while (fullLine[0] != '}') {
		/* Copia para o nome do campo todo o conteúdo entre os primeiros espaços
		* em branco.
		*/
		strcpy(fieldName, strtok(fullLine, " "));

		/* Pula até a posição antes do '{' */
		strtok(NULL, " ");

		/* Salva o ponteiro que aponta para o valor do campo, que é todo o
		* conteúdo entre chaves ({}).
		*/
		fieldValue = strtok(NULL, "{}");

		/* Define a propriedade corresponde ao campo encontrado */
		setArticleProperty(&newArticle, fieldName, fieldValue);

		/* Lê a próxima linha */
		fgets(fullLine, FULL_LINE_MAX_LENGTH + 2, stdin);
	}

	return newArticle;
}

/* Define a propriedade dada do Article com o valor dado */
void setArticleProperty(Article *article, char property[], char *value) {
	if (strcmp(property, "author") == 0) {
		(*article).author = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).author, value);
	} else if (strcmp(property, "title") == 0) {
		(*article).title = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).title, value);
	} else if (strcmp(property, "journal") == 0) {
		(*article).journal = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).journal, value);
	} else if (strcmp(property, "year") == 0) {
		(*article).year = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).year, value);
	} else if (strcmp(property, "volume") == 0) {
		(*article).volume = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).volume, value);
	} else if (strcmp(property, "number") == 0) {
		(*article).number = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).number, value);
	} else if (strcmp(property, "pages") == 0) {
		(*article).pages = (char*)malloc((strlen(value) + 1) * sizeof(char));
		strcpy((*article).pages, value);
	}
}

/* Usada na ordenação dos Articles; usa o Title como fator principal e o Index
 * como fator de desempate.
 */
int compArticles(const void *firstPointer, const void *secondPointer) {
	Article *firstArticle = (Article*)firstPointer;
	Article *secondArticle = (Article*)secondPointer;
	int strResult = strcmp((*firstArticle).title, (*secondArticle).title);

	/* Caso os Titles sejam diferentes, usar a ordem alfabética; caso contrário,
	 * usar a ordem de leitura como desempate.
	 */
	return strResult ? strResult : (*firstArticle).index - (*secondArticle).index;
}

/* Imprime o Article no formato especificado:
 *
 * `Title, Author, Journal, Volume*, Number*, Pages*, Year.`
 *
 * Onde os campos marcados com * são opcionais.
 */
void printArticle(Article *article) {
	printf("%s, %s, %s,", (*article).title, (*article).author, (*article).journal);

	if ((*article).volume != NULL) {
		printf(" %s,", (*article).volume);
	}

	if ((*article).number != NULL) {
		printf(" %s,", (*article).number);
	}

	if ((*article).pages != NULL) {
		printf(" %s,", (*article).pages);
	}

	printf(" %s.\n\n", (*article).year);
}

/* Libera a memória alocada dinamicamente do Article */
void freeArticle(Article *article) {
	if ((*article).title != NULL) {
		free((*article).title);
	}

	if ((*article).author != NULL) {
		free((*article).author);
	}

	if ((*article).journal != NULL) {
		free((*article).journal);
	}

	if ((*article).volume != NULL) {
		free((*article).volume);
	}

	if ((*article).number != NULL) {
		free((*article).number);
	}

	if ((*article).pages != NULL) {
		free((*article).pages);
	}

	if ((*article).year != NULL) {
		free((*article).year);
	}
}
