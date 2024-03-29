#include <iostream>
#include <sys/msg.h>
#include <sys/shm.h>
#include <cstdlib>
#include <unistd.h>
#include "../common/common.h"
#include "../ipc/Semaphore.h"
#include "../logger/Logger.h"
#include "../ipc/semaforos_distribuidos.h"

int main (int argc, char** argv){
	Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
	Logger::notice("Creo los ipcs necesarias", __FILE__);
	key_t key;
	
	key = ftok(ipcFileName.c_str(), MSGQUEUE_BROKER_ENVIO_MENSAJES_TESTERS);
	int cola_hacia_testers = msgget(key, 0660 );
	
	key = ftok(ipcFileName.c_str(), MSGQUEUE_BROKER_ATENCION_REQUERIMIENTOS_DISPOSITIVOS);
	int cola_requerimiento = msgget(key, 0660 );
	
	Semaphore sem_comunes(SEM_CANT_TESTERS_COMUNES);
	sem_comunes.getSem();
	
    tabla_testers_disponibles_t* tabla = (tabla_testers_disponibles_t*) malloc(sizeof(tabla_testers_disponibles_t));
    
    int id_broker = atoi(argv[1]);
    
	Logger::notice("Termino la obtencion de ipcs", __FILE__);
	/* Fin Setup */
	TMessageAtendedor msg;
	
	while (true){
		Logger::notice("Espero por un requerimiento", __FILE__);
		int ok_read = msgrcv(cola_requerimiento, &msg, sizeof(TMessageAtendedor) - sizeof(long), 0, 0); //LEO TODOS
		if (ok_read == -1){
			exit(0);
		}
		std::stringstream ss;
		ss << "Me llego un requerimiento desde el dispositivo " << msg.idDispositivo;
		Logger::notice(ss.str(), __FILE__);
		ss.str("");
		
		msg.es_requerimiento = 0;
		//Logger::notice("Obtengo semaforo para actuar, esperando que haya testers comunes", __FILE__);
		//sem_comunes.p();
		//Logger::notice("Ya hay un tester comun, entonces puedo enviar el requerimiento", __FILE__);
		
		//sem_tabla.p();
		msg.mtype = 0;
		while (msg.mtype == 0){
			semaforoDistribuido_P(tabla, ID_SUB_BROKER_REQUERIMIENTOS);
			ss << "Tengo la shm!";
			Logger::notice (ss.str(), __FILE__);
			ss.str("");
			
			if (tabla->cant > 0){
				msg.mtype = tabla->testers_comunes[tabla->start];
				tabla->start = (tabla->start + 1) % MAX_TESTERS_COMUNES;
				tabla->cant--;
			}
			semaforoDistribuido_V(tabla, ID_SUB_BROKER_REQUERIMIENTOS);
		}
		msg.broker = id_broker;
		int ret = msgsnd(cola_hacia_testers, &msg, sizeof(TMessageAtendedor) - sizeof(long), 0);
		if(ret == -1) {
			exit(1);
		}
	}
}
