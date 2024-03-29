/* 
 * File:   DespachadorTesters.cpp
 * Author: knoppix
 * 
 * Created on October 4, 2014, 10:30 PM
 */

#include "DespachadorTesters.h"
#include "../logger/Logger.h"

DespachadorTesters::DespachadorTesters() {
    
    key_t key = ftok(ipcFileName.c_str(), MSGQUEUE_DESPACHADOR);
    this->msgQueueId = msgget(key, 0666 | IPC_CREAT); 
    if(this->msgQueueId == -1) {
		std::string error = std::string("Error creando la cola de mensajes del despachador. Errno = ") + std::string(strerror(errno));
        Logger::error(error, __FILE__);
    }
    
}

DespachadorTesters::DespachadorTesters(const DespachadorTesters& orig) {
}

DespachadorTesters::~DespachadorTesters() {
}

void DespachadorTesters::enviarOrden(int idDispositivo) {

    TMessageDespachador msg;
    msg.mtype = MTYPE_ORDEN;
    msg.idDispositivo = idDispositivo;
    
    int ret = msgsnd(this->msgQueueId, &msg, sizeof(TMessageDespachador) - sizeof(long), 0);
    if(ret == -1) {
        std::string error = std::string("Error al enviar orden al despachador. Error: ") + std::string(strerror(errno));
        Logger::error(error.c_str(), __FILE__);
        throw error;
    }

}
