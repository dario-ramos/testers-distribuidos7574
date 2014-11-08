#ifndef PLANILLA_H
#define	PLANILLA_H

#include <cstdlib>
#include "../ipc/Semaphore.h"
#include "common.h"

class Planilla {
private:
	resultado_t* resultados;
	Semaphore mutex_resul;
	
	int obtenerLugar();
	
public:
    Planilla();
    virtual ~Planilla();
    
    int setRequerimiento(int idDispositivo, bool testers[]); //devuelve el lugar que ocupa en la shm
    int terminarProcesamiento(int idTesterEspecial,int req, bool resultado_grave);//devuelve si hay que seguir, o el resultado final
    int dispositivoEnLugar(int lugar);
    bool hayLugar();
    
};

#endif	/* PLANILLA_H */
