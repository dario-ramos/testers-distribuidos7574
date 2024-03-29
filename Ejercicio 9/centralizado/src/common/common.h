/* 
 * File:   common.h
 * Author: knoppix
 *
 * Created on October 4, 2014, 7:13 PM
 * 
 * Aqui se almacenan las constantes correspondientes a toda la app, incluido nombre de archivos para IPCs
 */
 
 #pragma once

#include <string>
#include <stddef.h>

namespace Constantes{
    namespace NombresDeParametros{
        const std::string ARCHIVO_IPCS = "ArchivoIpcs";
        const std::string CANT_DISPOSITIVOS = "CantDispositivos";
        const std::string CANT_TESTERS_COMUNES = "CantTestersComunes";
        const std::string CANT_TESTERS_ESPECIALES = "CantTestersEspeciales";
        const std::string CANT_TIPOS_DISPOSITIVO = "CantTiposDispositivo";
        const std::string ID_DISPOSITIVO_START = "IdDispositivoStart";
        const std::string ID_TESTER_CONFIG_START = "IdTesterConfigStart";
        const std::string ID_TESTER_ESPECIAL_START = "IdTesterEspecialStart";
        const std::string ID_TESTER_START = "IdTesterStart";
        const std::string MAX_DISPOSITIVOS_EN_SISTEMA = "MaxDispositivosEnSistema";
        const std::string MAX_TAREAS_ESPECIALES = "MaxTareasEspeciales";
        const std::string MAX_VALOR_VARIABLE_DISP = "MaxValorVariableDisp";
        const std::string MAXIMO_TESTERS_ESPECIALES_POR_ESPECIFICACION = "MaxTestersEspecialesPorEspecificacion";
        const std::string MINIMO_TESTERS_ESPECIALES_POR_ESPECIFICACION = "MinTestersEspecialesPorEspecificacion";
        const std::string MAXIMOS_LANZADOS = "MaximosLanzados";
        const std::string MINIMOS_LANZADOS = "MinimosLanzados";
        const std::string MSGQUEUE_DESPACHADOR = "MsgQueueDespachador";
        const std::string MSGQUEUE_DISPOSITIVOS = "MsgQueueDispositivos";
        const std::string MSGQUEUE_DISPOSITIVOS_TESTERS_ESPECIALES = "MsgQueueDispositivosTestersEspeciales";
        const std::string MSGQUEUE_DISPOSITIVOS_CONFIG = "MsgQueueDispositivosConfig";
        const std::string MSGQUEUE_REINICIO_TESTEO = "MsgQueueReinicioTesteo";
        const std::string MSGQUEUE_TESTERS = "MsgQueueTesters";
        const std::string MSGQUEUE_TESTERS_CONFIG = "MsqQueueTestersConfig";
        const std::string MSGQUEUE_TESTERS_ESPECIALES = "MsgQueueTestersEspeciales";
        const std::string SEM_PLANILLA_CANT_TAREAS_ASIGNADAS = "SemPlanillaCantTareasAsignadas";
        const std::string SEM_PLANILLA_CANT_TESTER_ASIGNADOS = "SemPlanillaCantTesterAsignados";
        const std::string SEM_PLANILLA_GENERAL = "SemPlanillaGeneral";
        const std::string SEM_COLA_ESPECIALES = "SemColaEspeciales";
        const std::string SEM_MUTEX_PLANILLA_VARS_START = "SemMutexPlanillaVarsStart";
        const std::string SHM_PLANILLA_CANT_TAREAS_ASIGNADAS = "ShmPlanillaCantTareasAsignadas";
        const std::string SHM_PLANILLA_CANT_TESTER_ASIGNADOS = "ShmPlanillaCantTesterAsignados";
        const std::string SHM_PLANILLA_GENERAL = "ShmPlanillaGeneral";
        const std::string SHM_PLANILLA_GENERAL_POSICIONES = "ShmPlanillaGeneralPosiciones";
        const std::string SEM_PLANILLA_VARS_TE_START = "SemPlanillaVarsTeStart" ;
        const std::string SEM_PLANILLA_VARS_CV_START = "SemPlanillaVarsCvStart";
        const std::string SHM_PLANILLA_VARS_START = "ShmPlanillaVarsStart";        
        // Alias / equivalencias
        const std::string CANT_RESULTADOS = MAX_DISPOSITIVOS_EN_SISTEMA;
        const std::string MSGQUEUE_ULTIMO = MSGQUEUE_REINICIO_TESTEO;
    }
}

// MTypes
const int MTYPE_REQUERIMIENTO = 1001;
const int MTYPE_RESULTADO_ESPECIAL = 2001;
const int MTYPE_ORDEN = 3001;
const int MTYPE_CAMBIO_VAR = 4001;
const int MTYPE_BASE_TAREA_ESPECIAL = 5000;

//Otras constantes
const int ORDEN_APAGADO = 0;
const int ORDEN_REINICIO = 1;
const int ORDEN_SEGUIR_TESTEANDO = 2;
const int SIN_LUGAR = -1;

const int RESULTADO_GRAVE = 0;
const int RESULTADO_NO_GRAVE = 1;
const int SEGUIR_TESTEANDO = 2;
const int NO_CONTESTAR = 3;
const int FIN_TEST_ESPECIAL = 4;
const int FIN_TEST_CONFIG = 5;

// Archivos necesarios
const std::string logFileName = "log.txt";

//Estructuras communes:
typedef struct resultado_t{
    int idDispositivo;
    int resultadosPendientes;
    int resultadosGraves;
}resultado_t;

typedef struct TMessageAssignTE{
    long mtype;
    int idDispositivo;
    int posicionDispositivo;
    int tipoDispositivo;
} TMessageAssignTE;

typedef struct resultado_test{
    long mtype;
    int idDispositivo;
    int result;
}resultado_test_t;

typedef struct TContadorTesterEspecial {
    int cantTestersEspecialesTotal;
    int cantTestersEspecialesTerminados;
} TContadorTesterEspecial;

typedef struct TContadorTareaEspecial {
    int cantTareasEspecialesTotal;
    int cantTareasEspecialesTerminadas;
} TContadorTareaEspecial;

typedef struct TMessageReinicioTest {
    long mtype;
    bool hayQueReiniciar;
} TMessageReinicioTest;

typedef struct TMessageAtendedor {
    long mtype;
    int idDispositivo;
    int idTester;
    int value; // Este parametro posee el valor del requerimiento, del programa y del resultado
    int posicionDispositivo;
    int tipoDispositivo;
} TMessageAtendedor;

typedef struct TMessageTesterConfig {
    long mtype;
    int idDispositivo;
    int tipoDispositivo;    
} TMessageTesterConfig;

typedef struct TMessageDispConfig{
    long mtype;    
    int idVariable;
    int nuevoValor;
    int idTesterConfig;
    bool ultimo;
}TMessageDispConfig;

enum EstadoProcesoDisp{
    EPD_ESPERANDO,
    EPD_OCUPADO,
    EPD_LIBRE
};

typedef struct TEstadoDispositivo{
    EstadoProcesoDisp    estadoDisp;
    EstadoProcesoDisp    estadoDispConfig;
} TEstadoDispositivo;
