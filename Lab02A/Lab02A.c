/* Nome: Raphael Mobis Tacla
 * RA: 157104
 * Laboratorio 02A - INSS e IRPF
 */

#include <stdio.h>

int main() {
	double salary;
	int dependants;

	double INSS, IRPF;

	scanf("%lf %d", &salary, &dependants);

	/* Cálculo do INSS */
	if (salary > 4390.24) {
		INSS = 482.93;
	} else if (salary > 2195.12) {
		INSS = salary * 0.11;
	} else if (salary >  1317.07) {
		INSS = salary * 0.09;
	} else {
		INSS = salary * 0.08;
	}
	printf("INSS: R$ %.2f\n", INSS);

	/* Cálculo da Base */
	salary -= INSS + (dependants * 179.71);
	printf("Base: R$ %.2f\n", salary);

	/* Cálculo do IRPF */
	IRPF = 0;

	if (salary >= 4463.82) {
		IRPF += (salary - 4463.82) * .275;
		salary = 4463.81;
	}
	if (salary >= 3572.44) {
		IRPF += (salary - 3572.44) * .225;
		salary = 3572.43;
	}
	if (salary >= 2679.30) {
		IRPF += (salary - 2679.30) * .150;
		salary = 2679.29;
	}
	if (salary >= 1787.78) {
		IRPF += (salary - 1787.78) * .075;
	}

	printf("IRPF: R$ %.2f\n", IRPF);


    return 0;
}
