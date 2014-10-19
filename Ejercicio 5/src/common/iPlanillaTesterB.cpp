#include "iPlanillaTesterB.h"
#include <sys/ipc.h>
#include "common.h"

iPlanillaTesterB::iPlanillaTesterB(int id) {
    idTester = id;
    key_t key = ftok(ipcFileName.c_str(), MSGQUEUE_PLANILLA);
    this->cola = msgget(key, IPC_CREAT);
}

iPlanillaTesterB::iPlanillaTesterB(const iPlanillaTesterB& orig) {
}

iPlanillaTesterB::~iPlanillaTesterB() {
}

void iPlanillaTesterB::eliminarDispositivo(int iDdispositivo){
    requerimiento_planilla_t requerimiento;
    requerimiento.tester = idTester;
    requerimiento.tipoReq = REQUERIMIENTO_ELIMINAR_DISPOSITIVO;
    requerimiento.idDispositivo = idDispositivo;
    
    msgsnd(cola,&requerimiento, sizeof(requerimiento_planilla_t) - sizeof(long),0);
    //Deberia esperar un ok?
}

void iPlanillaTesterB::iniciarProcesamientoDeResultados(){
    requerimiento_planilla_t requerimiento;
    requerimiento.tester = idTester;
    requerimiento.tipoReq = REQUERIMIENTO_ELIMINAR_DISPOSITIVO;
    requerimiento.idDispositivo = 0;
    
    msgsnd(cola,&requerimiento, sizeof(requerimiento_planilla_t) - sizeof(long),0);
}

void iPlanillaTesterB::procesarSiguiente(){
    requerimiento_planilla_t requerimiento;
    requerimiento.tester = idTester;
    requerimiento.tipoReq = REQUERIMIENTO_ELIMINAR_DISPOSITIVO;
    requerimiento.idDispositivo = 0;
    
    msgsnd(cola,&requerimiento, sizeof(requerimiento_planilla_t) - sizeof(long),0);
}



