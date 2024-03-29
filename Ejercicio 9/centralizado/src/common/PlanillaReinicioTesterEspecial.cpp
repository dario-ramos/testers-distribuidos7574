/* 
 * File:   PlanillaReinicioTesterEspecial.cpp
 * Author: knoppix
 * 
 * Created on November 17, 2014, 12:19 AM
 */

#include "PlanillaReinicioTesterEspecial.h"
#include "Configuracion.h"

using namespace Constantes::NombresDeParametros;
using std::string;

PlanillaReinicioTesterEspecial::PlanillaReinicioTesterEspecial( const Configuracion& config ) {
    const string ipcFileName = config.ObtenerParametroString(ARCHIVO_IPCS);
    key_t key = ftok( ipcFileName.c_str(), config.ObtenerParametroEntero(MSGQUEUE_REINICIO_TESTEO) );
    m_MsgqReinicioId = msgget( key, 0666 );
    if( m_MsgqReinicioId == -1 ) {
        std::string err = std::string("Error al obtener la cola de reinicio de tests. Errno: ") + std::string(strerror(errno));
        Logger::error(err, __FILE__);
        exit(1);
    }
}

PlanillaReinicioTesterEspecial::~PlanillaReinicioTesterEspecial() {
}

bool PlanillaReinicioTesterEspecial::hayQueReiniciar(int idTester) {

    TMessageReinicioTest msg;
    int ret = msgrcv( m_MsgqReinicioId, &msg, sizeof(TMessageReinicioTest) - sizeof(long), idTester, 0 );
    if(ret == -1) {
        std::ostringstream ss;
        ss << "Error al recibir reinicio de testeo para tester " << idTester << ". Error: ";
        std::string error = ss.str() + std::string(strerror(errno));
        Logger::error(error.c_str(), __FILE__);
        exit(0);
    }
    return msg.hayQueReiniciar;
}
