/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "identificador.h"


void
identificadorprog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char *getiddispositivo_1_arg;
	int  *result_2;
	char *getidtestercomun_1_arg;
	int  *result_3;
	char *getidtesterespecial_1_arg;

//#ifndef	DEBUG
	clnt = clnt_create (host, IDENTIFICADORPROG, IDENTIFICADORVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
//#endif	/* DEBUG */

	result_1 = getiddispositivo_1((void*)&getiddispositivo_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = getidtestercomun_1((void*)&getidtestercomun_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = getidtesterespecial_1((void*)&getidtesterespecial_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printf("Los resultados fueron: %d, %d, %d\n", *result_1, *result_2, *result_3);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char host[] = "127.0.0.1";
	identificadorprog_1 (host);
exit (0);
}
