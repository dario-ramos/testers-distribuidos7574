/* 
 * File:   AtendedorTesters.h
 * Author: knoppix
 *
 * Created on October 7, 2014, 8:54 PM
 */

#ifndef ATENDEDORTESTERS_H
#define	ATENDEDORTESTERS_H

#include <cstring>
#include <sys/msg.h>
#include "errno.h"

#include "logger/Logger.h"
#include "common/common.h"

class AtendedorTesters {
private:
    int msgQueueId;
    key_t key;
    
public:
    AtendedorTesters();
    AtendedorTesters(const AtendedorTesters& orig);
    virtual ~AtendedorTesters();
    
    int recibirRequerimiento();
    void enviarPrograma(int idDispositivo, int idPrograma, int idTester);  // Tester -> Disp
    int recibirResultado(int idDispositivo);
    void enviarOrden(int idDispositivo, int orden); // Tester -> Disp: Reinicio o apagado

    bool destruirComunicacion();

};

#endif	/* ATENDEDORTESTERS_H */

