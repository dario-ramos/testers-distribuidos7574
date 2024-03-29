#include <iostream>
#include <sys/msg.h>
#include <sys/shm.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include "../common/common.h"
#include "../ipc/Semaphore.h"
#include "../logger/Logger.h"
#include <string.h>

int main (void){
	Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
	Logger::notice("Creo los ipcs necesarias", __FILE__);
	key_t key;
	
	key = ftok(ipcFileName.c_str(), MSGQUEUE_BROKER_ENVIO_MENSAJES_DISPOSITIVOS);
	int cola_disponibilidad = msgget(key, 0660 );
	
	key = ftok(ipcFileName.c_str(), SHM_TABLA_TESTERS);
    int shmtabla = shmget(key, sizeof(tabla_testers_disponibles_t) , IPC_CREAT | 0660);
    tabla_testers_disponibles_t* tabla = (tabla_testers_disponibles_t*)shmat(shmtabla, NULL, 0);
    
    Semaphore sem_tabla(SEM_TABLA_TESTERS);
    sem_tabla.getSem();
		    
    Logger::notice("Termino la obtencion de ipcs", __FILE__);
    
	/* Fin Setup */
	TMessageAtendedor msg;
	
	while (true){
		Logger::notice("Espero por un tester que se marque como disponible", __FILE__);
		int ok_read = msgrcv(cola_disponibilidad, &msg, sizeof(TMessageAtendedor) - sizeof(long), MTYPE_TESTER_DISPONIBLE, 0);
		if (ok_read == -1){
			exit(0);
		}
		
		std::stringstream ss;
		ss << "Me llega un requerimiento de disponibilidad desde tester " << msg.tester << ". Espero por memoria compartida de tabla";
		Logger::notice(ss.str(), __FILE__);
		
		sem_tabla.p();
		if (msg.tester <= MAX_TESTERS_COMUNES){
			Logger::notice("Era un tester comun, lo agrego a cola de testers comunes", __FILE__);
			tabla->testers_comunes[tabla->end++] = msg.tester;
			tabla->cant++;
			Semaphore sem_comunes(SEM_CANT_TESTERS_COMUNES);
			sem_comunes.getSem();
			sem_comunes.v();
		}else{
			Logger::notice("Era un tester especial, indico que esta disponible", __FILE__);
			tabla->testers_especiales[msg.tester - MAX_TESTERS_COMUNES - 1] = true;
			Semaphore sem_especial(SEM_ESPECIAL_DISPONIBLE + (msg.tester - MAX_TESTERS_COMUNES - 1));
			sem_especial.getSem();
			sem_especial.v();
		}
		Logger::notice("Libero la memoria compartida de tabla", __FILE__);
		sem_tabla.v();
	}
}

