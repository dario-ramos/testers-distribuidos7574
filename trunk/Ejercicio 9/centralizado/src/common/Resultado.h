/* 
 * File:   Resultado.h
 * Author: knoppix
 *
 * Created on October 4, 2014, 10:28 PM
 */

#ifndef RESULTADO_H
#define	RESULTADO_H

#include "common.h"

class Resultado {
public:
    Resultado();
    Resultado(const Resultado& orig);
    virtual ~Resultado();
    
    static int esGrave(int resultado) {return (resultado == RESULTADO_GRAVE);};
    
    static int necesitaTestingEspecial(int resultado) {return (resultado == SEGUIR_TESTEANDO);};
    
};

#endif	/* RESULTADO_H */

