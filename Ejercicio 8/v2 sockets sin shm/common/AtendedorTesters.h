#ifndef ATENDEDORTESTERS_H
#define	ATENDEDORTESTERS_H

#include <cstring>
#include <sstream>
#include <sys/msg.h>
#include "errno.h"

#include "../logger/Logger.h"
#include "common.h"
#include "../ipc/Semaphore.h"

class AtendedorTesters {
private:
    int cola_testers_especiales;
    //int cola_tareas_especiales;
    int cola_envios;
    int cola_recepciones;

    Semaphore sem_cola_especiales;
    
public:
    AtendedorTesters();
    AtendedorTesters(const AtendedorTesters& orig);
    virtual ~AtendedorTesters();
    
    /**
     * Interaccion con el dispositivo
     */
    int recibirRequerimiento();
    void enviarPrograma(int idDispositivo, int tester, int idPrograma);  // Tester -> Disp
    int recibirResultado(int idTester);
    void enviarOrden(int idDispositivo, int orden); // Tester -> Disp: Reinicio o apagado

    /**
     * Interaccion con testers especiales
     */
    void enviarAEspeciales(bool cuales[], int idDispositivo, int posicionDispositivo);
    TMessageAssignTE recibirRequerimientoEspecial(int idEsp);

    /**
     * Interaccion entre tester especial y dispositivo
     */
    void enviarTareaEspecial(int idDispositivo, int idTester, int tarea, int posicionDispositivo);

    bool destruirComunicacion();
    int obtenerIdTester();
};

#endif	/* ATENDEDORTESTERS_H */

