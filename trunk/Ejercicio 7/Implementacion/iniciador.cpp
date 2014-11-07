/* 
 * File:   iniciador.cpp
 * Author: knoppix
 *
 * Created on October 4, 2014, 7:09 PM
 * 
 * Crea todos los IPCs a usar e inicia todos los procesos correspondientes a la aplicacion
 */

#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#include "common/common.h"
#include "ipc/Semaphore.h"
#include "logger/Logger.h"

void createIPCObjects();
void createSystemProcesses();

int main(int argc, char** argv) {
    
    Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
    Logger::error("Logger inicializado. Inicializando IPCs...", __FILE__);
    
    try {
        createIPCObjects();
    } catch(std::string err) {
        Logger::error("Error al crear los objetos activos...", __FILE__);
        Logger::destroy();
        return 1;
    }
    Logger::debug("Objetos IPC inicializados correctamente. Iniciando procesos...", __FILE__);
    
    createSystemProcesses();
    Logger::debug("Procesos iniciados correctamente...", __FILE__);
    
    Logger::notice("Sistema inicializado correctamente...", __FILE__);
    
    Logger::destroy();
    
    return 0;
}

void createIPCObjects() {

    // Creo el archivo que se usara para obtener las keys
    std::fstream ipcFile(ipcFileName.c_str(), std::ios::out);
    if (ipcFile.bad() || ipcFile.fail()) {
	std::string err = std::string("Error creando el archivo de IPCs. Error: ") + std::string(strerror(errno));
        Logger::error(err.c_str(), __FILE__);
        throw err;
    }
    ipcFile.close();
       
    // Creo semaforo para la shmem de la planilla
    Semaphore semPlanillaGeneral(SEM_PLANILLA_GENERAL);
    semPlanillaGeneral.creaSem();
    semPlanillaGeneral.iniSem(1); // Inicializa el semaforo en 1

    key_t key = ftok(ipcFileName.c_str(), SHM_PLANILLA_GENERAL);
    int shmgeneralid = shmget(key, sizeof(resultado_t) * CANT_RESULTADOS, IPC_CREAT | IPC_EXCL | 0660);
    resultado_t* resultados = (resultado_t*)shmat(shmgeneralid, NULL, 0);
    
    for (int i = 0; i < CANT_RESULTADOS; i++){
		resultados[i].resultadosPendientes = 0;
    }
    shmdt(resultados);
    
    
    //creacion de colas
    for (int q = MSGQUEUE_DISPOSITIVOS; q <= MSGQUEUE_DESPACHADOR; q++){
			key = ftok(ipcFileName.c_str(), q);
		if (msgget(key, 0660 | IPC_CREAT | IPC_EXCL) == -1){
			std::cout << "No se pudo crear una cola: " << strerror(errno)<< std::endl;
		}
	}
   
}

void createSystemProcesses() {
    // Creo dispositivos
    int idDispositivo = ID_DISPOSITIVO_START;
    for(int i = 1; i <= CANT_DISPOSITIVOS; i++) {
        char param[3];
        sprintf(param, "%d", idDispositivo);
        idDispositivo++;
        usleep(10);
        pid_t newPid = fork();
        if(newPid == 0) {
            // Inicio el programa correspondiente
            execlp("./Dispositivo", "Dispositivo", param, (char*)0);
            Logger::error("Error al ejecutar el programa dispositivo de ID" + idDispositivo, __FILE__);
            exit(1);
        }
    }
    
    // Creo testers
    int idTester = ID_TESTER_START;
    for(int i = 0; i < CANT_TESTERS_COMUNES; i++, idTester++) {
        char param[3];
        sprintf(param, "%d", idTester);
        usleep(10);
        pid_t newPid = fork();
        if(newPid == 0) {
			// Inicio el programa correspondiente
            execlp("./TesterComun", "TesterComun", param, (char*)0);
            Logger::error("Error al ejecutar el programa TesterComun de ID" + idTester, __FILE__);
            exit(1);
        }
    }
    
    for(int i = 0; i < CANT_TESTERS_ESPECIALES; i++, idTester++) {
        char param[3];
        sprintf(param, "%d", idTester);
        usleep(10);
        pid_t newPid = fork();
        if(newPid == 0) {
			// Inicio el programa correspondiente
            execlp("./TesterEspecial", "TesterEspecial", param, (char*)0);
            Logger::error("Error al ejecutar el programa TesterEspecial de ID" + idTester, __FILE__);
            exit(1);
        }
    }

    // Creo al tecnico
    pid_t tecPid = fork();
    if(tecPid == 0) {
        execlp("./Tecnico", "Tecnico", (char*)0);
        Logger::error("Error al ejecutar el programa tecnico", __FILE__);
        exit(1);
    }
    
    Logger::debug("Programas iniciados correctamente...", __FILE__);
    
}