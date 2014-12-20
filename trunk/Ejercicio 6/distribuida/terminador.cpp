/* 
 * File:   terminador.cpp
 * Author: knoppix
 *
 * Created on October 4, 2014, 7:09 PM
 * 
 * Destruye todos los IPCs utilizados en la aplicacion
 */

#include <cstdlib>
#include "common/common.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "logger/Logger.h"
#include "ipc/Semaphore.h"


int main(int argc, char** argv) {
    
    Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
    Logger::error("Logger inicializado. Destruyendo IPCs...", __FILE__);
   
	//Semaforo y Planilla General
    key_t key = ftok(ipcFileName.c_str(), SHM_PLANILLA_GENERAL);
    int shmgeneralid = shmget(key, sizeof(resultado_t) * CANT_RESULTADOS,  0660);
    shmctl(shmgeneralid, IPC_RMID, NULL);
    
    Semaphore semPlanillaGeneral(SEM_PLANILLA_GENERAL);
    semPlanillaGeneral.getSem();
    semPlanillaGeneral.eliSem();
		
	Semaphore sem_cola_especiales(SEM_COLA_ESPECIALES);
	sem_cola_especiales.getSem();
	sem_cola_especiales.eliSem();
	
    //Destruccion de colas
    for (int q = MSGQUEUE_DISPOSITIVOS_ENVIOS; q <= MSGQUEUE_BROKER_ENVIO_MENSAJES_DISPOSITIVOS; q++){
		key = ftok(ipcFileName.c_str(), q);
		int cola = msgget(key, 0660);
		msgctl(cola ,IPC_RMID, NULL);
	}
	
	Semaphore sem_comunes(SEM_CANT_TESTERS_COMUNES);
	sem_comunes.getSem();
	sem_comunes.eliSem();
	
	for (int i = 0; i < MAX_TESTERS_ESPECIALES; i++){
		Semaphore sem_especial(SEM_ESPECIAL_DISPONIBLE + i);
		sem_especial.getSem();
		sem_especial.eliSem();
	}
	
	Semaphore sem_tabla(SEM_TABLA_TESTERS);
	sem_tabla.getSem();
	sem_tabla.eliSem();
	
	key = ftok(ipcFileName.c_str(), SHM_TABLA_TESTERS);
    int shmtabla = shmget(key, sizeof(tabla_testers_disponibles_t) , 0660);
    shmctl(shmtabla, IPC_RMID, NULL);
	
    return 0;
}
