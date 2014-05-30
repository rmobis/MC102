/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 14B - Whiteworse
 *
 * Gerencia o banco do Tio Patinhas; lê uma série de contas e transações de
 * arquivos binários e realiza essas transações, quando estas forem válidas.
 * Imprime na saída padrão todas as transações válidos e reescreve o estado das
 * contas após as transações serem realizados em um outro arquivo, também
 * binário.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Tamanho maximo do nome do titular */
#define MAXNOME 21
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Numero maximo de contas */
#define MAXCONTAS 20
/* Numero maximo de transacoes */
#define MAXTRANS 40
/* Valor da taxa de deposito em conta com saldo negativo */
#define TAXA 5.00

/* Conta
 * ag = numero da agencia
 * cc = numero da conta corrente
 * titular = Nome do titular da conta
 * saldo = Saldo da conta
 */
struct Conta {
	int ag;
	int cc;
	char titular[MAXNOME];
	double saldo;
};

typedef struct Conta Conta;

/* Transacao
 * tipo - 'D' para Depositos e 'S' para Saques
 * ag - Numero da agencia
 * cc - Numero da conta corrente
 * valor - Valor da operacao
 */
struct Transacao {
	char tipo;
	int ag;
	int cc;
	double valor;
};

typedef struct Transacao Transacao;

/* Executa uma transação e retorna se ela é válida ou não */
bool executarTransacao(Conta contas[], int numContas, Transacao trans);

int main(int argc, char **argv) {
	int i;
	int numContas, numTrans;
	Conta contas[MAXCONTAS];
	Transacao trans[MAXTRANS];
	FILE *arqConta, *arqTrans, *arqSaida;
	char nomeArqConta[MAXNOMEARQ], nomeArqTrans[MAXNOMEARQ], nomeArqSaida[MAXNOMEARQ];

	/* Obtendo o nome dos arquivos */
	strcpy(nomeArqConta, argv[1]);
	strcpy(nomeArqTrans, argv[2]);
	strcpy(nomeArqSaida, argv[3]);

	/* Leitura das contas */
	arqConta = fopen(nomeArqConta, "rb");
	fread(&numContas, sizeof(int), 1, arqConta);
	fread(contas, sizeof(Conta), numContas, arqConta);
	fclose(arqConta);

	/* Leitura das transações */
	arqTrans = fopen(nomeArqTrans, "rb");
	fread(&numTrans, sizeof(int), 1, arqTrans);
	fread(trans, sizeof(Transacao), numTrans, arqTrans);
	fclose(arqTrans);

	/* Realiza todas as transações */
	for (i = 0; i < numTrans; i++) {
		if (executarTransacao(contas, numContas, trans[i])) {
			printf("T%d: %c %d %d %.2f\n", i, trans[i].tipo, trans[i].ag, trans[i].cc, trans[i].valor);
		}
	}

	/* Imprime os novos estados das contas no arquivo de saída */
	arqSaida = fopen(nomeArqSaida, "wb");
	fwrite(&numContas, sizeof(int), 1, arqSaida);
	fwrite(contas, sizeof(Conta), numContas, arqSaida);
	fclose(arqSaida);

	return 0;
}

/* Executa uma transação e retorna se ela é válida ou não */
bool executarTransacao(Conta contas[], int numContas, Transacao trans) {
	int i;
	Conta *transConta = NULL;
	bool contaEncontrada = false;

	/* Procura a conta em que a transação será efetuada */
	for (i = 0; i < numContas && !contaEncontrada; i++) {
		if (trans.ag == contas[i].ag && trans.cc == contas[i].cc) {
			transConta = &contas[i];
		}
	}

	/* A transação não é válida se não for efetuada em uma conta existente */
	if (transConta == NULL) {
		return false;
	}

	if (trans.tipo == 'D') {
		(*transConta).saldo += trans.valor;
	} else {

		/* A transação não é válida se o saldo inicial da conta for negativo ou
		 * se ao final dela o saldo da conta for menor do que R$ -100,00.
		 */
		if ((*transConta).saldo < 0 || (*transConta).saldo - trans.valor < -100) {
			return false;
		} else {
			(*transConta).saldo -= trans.valor;

			if ((*transConta).saldo < 0) {
				(*transConta).saldo -= TAXA;
			}
		}
	}

	return true;
}