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
#include <common/common.h>
#include "unistd.h"
#include <errno.h>
#include <sstream>

#include "ipc/Semaphore.h"
#include "logger/Logger.h"
#include "common/AtendedorDispositivos.h"
#include "common/Planilla.h"
#include "common/DespachadorTecnicos.h"

/*
 * 
 */

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
    Semaphore semPlanilla(SEM_PLANILLA);
    semPlanilla.creaSem();
    semPlanilla.iniSem(1); // Inicializa el semaforo en 1
    
    // Creo la shmem de la planilla
    Planilla planilla;
    
    // Cola de mensajes entre dispositivo y testers
    AtendedorDispositivos atendedor;
    
    // Creo la cola de mensajes entre tester y tecnico
    DespachadorTecnicos despachador;
    
}

void createSystemProcesses() {

    // Creo dispositivos
    for(int i = 0; i < CANT_DISPOSITIVOS; i++) {
        char param[3];
        sprintf(param, "%d\n", i + ID_DISPOSITIVO_START);
        std::stringstream ss;
        ss << "Se creara el dispositivo " << param;
        Logger::notice(ss.str(), __FILE__);
        pid_t newPid = fork();
        if(newPid == 0) {
            // Inicio el programa correspondiente
            execlp("./dispositivo", "dispositivo", param, (char*)0);
            Logger::error("Error al ejecutar el programa dispositivo de ID", __FILE__);
            exit(1);
        }
    }
    
    // Creo testers
    for(int i = 0; i < CANT_TESTERS; i++) {
        char param[3];
        sprintf(param, "%d\n", i + ID_TESTER_START);
        pid_t newPid = fork();
        if(newPid == 0) {
            // Inicio el programa correspondiente
            execlp("./tester", "tester", param, (char*)0);
            Logger::error("Error al ejecutar el programa tester de ID", __FILE__);
            exit(1);
        }
    }
    
    // Creo al tecnico
    pid_t tecPid = fork();
    if(tecPid == 0) {
        execlp("./tecnico", "tecnico", (char*)0);
        Logger::error("Error al ejecutar el programa tecnico", __FILE__);
        exit(1);
    }
    
    Logger::debug("Programas iniciados correctamente...", __FILE__);
    
}
