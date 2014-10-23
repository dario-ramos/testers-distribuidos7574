#include <cstdlib>
#include "common/common.h"
#include "common/Planilla.h"
#include <sys/msg.h>

using namespace std;

int main(int argc, char** argv) {
    int id = atoi(argv[1]);
    Planilla planilla(id, TIPO_B);
    requerimiento_planilla_t requerimiento;
    while (true){
        if(msgrcv(planilla.queue(), &requerimiento, sizeof(requerimiento_planilla_t) - sizeof(long), id, 0 ) == -1)
			exit(0);
        switch(requerimiento.tipoReq){
            case REQUERIMIENTO_ELIMINAR_DISPOSITIVO:
                planilla.eliminar(requerimiento.idDispositivo);
                break;
            case REQUERIMIENTO_INICIAR_PROC_RESULTADOS:
                planilla.iniciarProcesamientoResultados();
                break;
            case REQUERIMIENTO_PROCESAR_SIGUIENTE:
                planilla.procesarSiguiente();
                break;
        }
              
    }
    
    return 0;
}

