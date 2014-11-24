#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>


typedef struct mensaje{
	long mtype;
	char buffer[10];
} mensaje_t;


int main(void){
	
	key_t key = ftok("ipcs-prueba", 1);
	int cola_server = msgget(key, 0660 | IPC_CREAT | IPC_EXCL);
	key = ftok("ipcs-prueba", 2);
	int cola_client = msgget(key, 0660 | IPC_CREAT | IPC_EXCL);
	
	mensaje_t mensaje;
	printf("Tam del mensaje: %zu\n", sizeof(mensaje_t));
	
	mensaje.mtype = 1;
	int i;
	for (i = 0; i < 9; i++){
		mensaje.buffer[i] = 'A' + i;
	}
	mensaje.buffer[9] = '\0';
	
	int ok = msgsnd(cola_server, &mensaje, sizeof(mensaje_t) - sizeof(long), 0);
    if (ok == -1){
		exit(0);
	}
	
	mensaje_t otro_mensaje;
	
	int ok_read = msgrcv(cola_client, &otro_mensaje, sizeof(mensaje_t) - sizeof(long), 1, 0);
    if (ok_read == -1){
		exit(0);
	}
	
	printf("El mensaje recibido fue %s\n", otro_mensaje.buffer);
	
	msgctl(cola_server ,IPC_RMID, NULL);
	msgctl(cola_client ,IPC_RMID, NULL);
}
