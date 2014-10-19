#ifndef PLANILLA_H
#define	PLANILLA_H
#include "../ipc/Semaphore.h"

class Planilla{
private:
    Semaphore mutex_planilla_general;
    int* shm_planilla_general;
    
    Semaphore mutex_planilla_local;
    planilla_local_t* shm_planilla_local;
        
    Semaphore sem_tester_A;
    Semaphore sem_tester_B;
    
    int cola;
    
public:
    Planilla(int tester);
    int queue();
    void agregar(int idDispositivo);
    void terminadoRequerimientoPendiente();
    void procesarSiguiente();
    void iniciarProcesamientoResultados();
    void eliminar(int idDispositivo);
};

#endif	/* PLANILLA_H */

