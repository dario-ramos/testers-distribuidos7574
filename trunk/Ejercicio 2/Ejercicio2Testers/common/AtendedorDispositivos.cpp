/* 
 * File:   AtendedorDispositivos.cpp
 * Author: knoppix
 * 
 * Created on October 4, 2014, 8:04 PM
 */
#include "AtendedorDispositivos.h"
#include <cstdlib>

AtendedorDispositivos::AtendedorDispositivos() { 
    key_t key = ftok(ipcFileName.c_str(), MSGQUEUE_NUEVO_REQUERIMIENTO);
    this->cola_requerimiento = msgget(key, 0666);
    if(this->cola_requerimiento == -1) {
		std::cout << "PIFIA Error al obtener la cola del atendedor de dispositivos. Errno: ";
		std::cout << errno << std::endl;
        exit(1);
    }
    
    key = ftok(ipcFileName.c_str(), MSGQUEUE_ESCRITURA_RESULTADOS);
    this->cola_tests = msgget(key, 0666);
    if(this->cola_tests == -1) {
        msgctl(this->cola_requerimiento, IPC_RMID, (struct msqid_ds*)0);
        std::cout << "PIFIA Error al obtener la cola del atendedor de dispositivos. Errno: " + errno << std::endl;
        exit(1);
    }
}

AtendedorDispositivos::AtendedorDispositivos(const AtendedorDispositivos& orig) {
}

AtendedorDispositivos::~AtendedorDispositivos() {
}
    
void AtendedorDispositivos::enviarRequerimiento(int idDispositivo) {

    TMessageAtendedor msg;
    msg.mtype = MTYPE_REQUERIMIENTO;
    msg.idDispositivo = idDispositivo;
    
    int ret = msgsnd(this->cola_requerimiento, &msg, sizeof(TMessageAtendedor) - sizeof(long), 0);
    if(ret == -1) {
        std::string error("Error al enviar mensaje al atendedor. Error: " + errno);
        Logger::error(error.c_str(), __FILE__);
        throw error;
    }
}

int AtendedorDispositivos::recibirPrograma(int idDispositivo) {
    TMessageAtendedor msg;
    int ret = msgrcv(this->cola_requerimiento, &msg, sizeof(TMessageAtendedor) - sizeof(long), idDispositivo, 0);
    if(ret == -1) {
        std::string error("Error al recibir programa del atendedor. Error: " + errno);
        Logger::error(error.c_str(), __FILE__);
        throw error;
    }
    this->ultimoTester = msg.idDispositivo; //HACE DE TESTER EN ESTE CASO.. FIXME?
    return msg.value;

}
void AtendedorDispositivos::enviarResultado(int idDispositivo, int resultado) {

    TMessageAtendedor msg;
    msg.mtype = this->ultimoTester;
    msg.idDispositivo = idDispositivo;
    msg.value = resultado;
    
    int ret = msgsnd(this->cola_tests, &msg, sizeof(TMessageAtendedor) - sizeof(long), 0);
    if(ret == -1) {
        std::string error("Error al enviar resultado al atendedor. Error: " + errno);
        Logger::error(error.c_str(), __FILE__);
        throw error;
    }

}

int AtendedorDispositivos::recibirOrden(int idDispositivo) {

    TMessageAtendedor msg;
    int ret = msgrcv(this->cola_tests, &msg, sizeof(TMessageAtendedor) - sizeof(long), idDispositivo, 0);
    if(ret == -1) {
        std::string error("Error al recibir orden del atendedor. Error: " + errno);
        Logger::error(error.c_str(), __FILE__);
        throw error;
    }
    return msg.value;

}
