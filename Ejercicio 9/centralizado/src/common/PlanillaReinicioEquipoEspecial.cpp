/* 
 * File:   PlanillaReinicioEquipoEspecial.cpp
 * Author: knoppix
 * 
 * Created on November 17, 2014, 1:35 PM
 */

#include "PlanillaReinicioEquipoEspecial.h"
#include "Configuracion.h"
#include "common.h"

using namespace Constantes::NombresDeParametros;
using std::string;

PlanillaReinicioEquipoEspecial::PlanillaReinicioEquipoEspecial( const Configuracion& config ) {
    const string ipcFileName = config.ObtenerParametroString( ARCHIVO_IPCS );
    key_t key = ftok( ipcFileName.c_str(),
                      config.ObtenerParametroEntero(MSGQUEUE_REINICIO_TESTEO) );
    m_MsgqReinicioId = msgget(key, 0666);
    if(m_MsgqReinicioId == -1) {
        std::string err = std::string("Error al obtener la cola de reinicio de tests de la planilla de reinicio del equipo especial. Errno: ") +
                          std::string(strerror(errno));
        Logger::error(err, __FILE__);
        exit(1);
    }
}

PlanillaReinicioEquipoEspecial::~PlanillaReinicioEquipoEspecial() {
}

void PlanillaReinicioEquipoEspecial::avisarReinicio(const std::set<int>& idTesters, bool reiniciar) {

    TMessageReinicioTest msg;
    for (std::set<int>::const_iterator it = idTesters.begin(); it != idTesters.end(); it++) {
        msg.mtype = *it;
        msg.hayQueReiniciar = reiniciar;
        std::stringstream ss;
        ss << "Se avisa del reinicio al tester especial " << *it;
        Logger::debug(ss.str(), __FILE__);
        int ret = msgsnd( m_MsgqReinicioId, &msg, sizeof(TMessageReinicioTest) - sizeof(long), 0 );
        if(ret == -1) {
            std::string error = std::string("Error al enviar reinicio de tests desde el equipo especial. Error: ") + std::string(strerror(errno));
            Logger::error(error.c_str(), __FILE__);
            exit(0);
        }
    }
}
