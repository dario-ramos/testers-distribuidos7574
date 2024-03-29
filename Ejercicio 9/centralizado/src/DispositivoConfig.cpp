/* 
 * File:   Dispositivo.cpp
 * Author: knoppix
 *
 * Created on October 4, 2014, 8:12 PM
 * 
 * El dispositivo recibe ordenes de cambiar variables de configuracion.
 * Procesar dichas ordenes tiene mayor prioridad que procesar las
 * ordenes de tests especiales.
 * Ademas, mientras se esta alterando una variable de configuracion,
 * no se puede correr un test especial.
 */

#include "common/AtendedorDispositivos.h"
#include "common/PlanillaVariablesDisp.h"
#include "common/Configuracion.h"
#include "common/common.h"
#include "logger/Logger.h"
#include <cstdlib>
#include <sstream>

using namespace std;

void realizarCambioDeVariable( int idDisp, PlanillaVariablesDisp& planillaVariables,
                               int idVar, int nuevoValor, const char* nombreProceso ){
    planillaVariables.iniciarCambioDeVariable( idVar );
    usleep(rand() % 1000 + 1000);
    std::stringstream ss;
    ss << "El dispositivo-config " << idDisp << " cambiara la variable de configuracion " 
       << idVar << " al valor " << nuevoValor;
    Logger::debug(ss.str().c_str(), nombreProceso);
    ss.str("");
    planillaVariables.finalizarCambioDeVariable( idVar );
    ss << "El dispositivo-config " << idDisp << " cambió exitosamente la variable de configuracion " 
       << idVar;
    Logger::debug(ss.str().c_str(), nombreProceso);
    ss.str("");
}

int main(int argc, char** argv) {
    srand(time(NULL));
    Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
    // Por parametro se recibe el ID del dispositivo
    int id = atoi(argv[1]);
    
    std::stringstream nombreProceso;
    nombreProceso << __FILE__ << " " << id;

    std::stringstream ss;
    ss << "Dispositivo-Config " << id << " creado";
    Logger::debug(ss.str().c_str(), nombreProceso.str().c_str());
    ss.str("");

    Configuracion config;
    if( !config.LeerDeArchivo() ){
        Logger::error("Archivo de configuracion no encontrado", nombreProceso.str().c_str());
        return 1;
    }
    
    // Comunicacion con el sistema de testeo
    AtendedorDispositivos atendedor( config );
    PlanillaVariablesDisp planillaVariables( config, id );
    
    while(true) {
        try {
            TMessageDispConfig cambio = atendedor.recibirPedidoCambioVariable( id );
            realizarCambioDeVariable( id, planillaVariables, cambio.idVariable, cambio.nuevoValor, nombreProceso.str().c_str() );
            atendedor.notificarCambioDeVariableFinalizado( id, cambio.idTesterConfig, cambio.ultimo );
        } catch(std::string exception) {
            Logger::error("Error en el dispositivo...", nombreProceso.str().c_str());
            break;
        }
    }
    ss << "El dispositivo-config " << id << " ha terminado";
    Logger::notice(ss.str().c_str(), nombreProceso.str().c_str());
    Logger::destroy();
    return 0;
}

