#include <cstdlib>
#include "common/common.h"
#include "logger/Logger.h"
#include "common/Configuracion.h"
#include "common/Planilla.h"
#include <sstream>
#include <sys/msg.h>
#include <cerrno>
#include <cstring>
#include "logger/Logger.h"


using namespace Constantes;
using namespace std;

int main(int argc, char** argv) {

    Logger::initialize(Constantes::ARCHIVO_LOG.c_str(), Logger::LOG_DEBUG);
    std::stringstream nombre;
    nombre << __FILE__;
    Logger::notice("Inicia el procesamiento, cargando IPCS", nombre.str().c_str());

    Configuracion config;
    if (!config.LeerDeArchivo()) {
        Logger::error("Archivo de configuracion no encontrado", __FILE__);
        return 1;
    }
    
    int id = config.ObtenerParametroEntero("TesterRtaIdOffset") + atoi(argv[1]);

    Planilla planilla(atoi(argv[1]), config);
    requerimiento_planilla_t requerimiento;

    Logger::notice("Entrando a loop principal", nombre.str().c_str());
    while (true) {
        
    
        if (-1 == msgrcv(planilla.queue(), &requerimiento, sizeof (requerimiento_planilla_t) - sizeof (long), id, 0 )) {
            std::string error = std::string("Error al hacer msgrcv. Error: ") + std::string(strerror(errno));
            Logger::error(error.c_str(), __FILE__);
            exit(-1);
        }
    
        switch (requerimiento.tipoReq) {
            case REQUERIMIENTO_ELIMINAR_DISPOSITIVO:
                Logger::notice("Recibo un pedido para eliminar dispositivo", nombre.str().c_str());
                planilla.eliminar(requerimiento.idDispositivo);
                break;
            case REQUERIMIENTO_INICIAR_PROC_RESULTADOS:
                Logger::notice("Recibo un pedido para iniciar el procesamiento de resultados", nombre.str().c_str());
                planilla.iniciarProcesamientoResultados();
                break;
            case REQUERIMIENTO_PROCESAR_SIGUIENTE:
                Logger::notice("Recibo un pedido para procesar siguiente", nombre.str().c_str());
                planilla.procesarSiguienteResultado();
                break;
        }

    }

    return 0;
}

