/* 
 * File:   common.h
 * Author: knoppix
 *
 * Created on October 4, 2014, 7:13 PM
 * 
 * Aqui se almacenan las constantes correspondientes a toda la app, incluido nombre de archivos para IPCs
 */

#ifndef COMMON_H
#define	COMMON_H

#include <string>
#include <stddef.h>

// Constantes del sistema

const int CANT_TESTERS_COMUNES = 5;
const int MAX_TESTER_COMUNES = 30;
const int CANT_TESTERS_ESPECIALES = 30;
const int MAX_TESTER_ESPECIALES = 60;
const int MAX_DISPOSITIVOS_EN_SISTEMA = 100;
const int MAX_TAREAS_ESPECIALES = 10;

static int ID_DISPOSITIVO = 5;
const int ID_TESTER_COMUN_START = ID_DISPOSITIVO + MAX_DISPOSITIVOS_EN_SISTEMA;
const int ID_TESTER_ESP_START = ID_TESTER_COMUN_START + MAX_TESTER_COMUNES;
const int ID_EQUIPO_ESPECIAL = ID_TESTER_ESP_START + MAX_TESTER_ESPECIALES;

// IDs de los IPC
const int SEM_PLANILLA_GENERAL = 1;
const int SHM_PLANILLA_GENERAL = 2;
const int SEM_PLANILLA_CANT_TESTER_ASIGNADOS = 4;
const int SEM_PLANILLA_CANT_TAREAS_ASIGNADAS = 5;
const int SHM_PLANILLA_CANT_TESTER_ASIGNADOS = 6;
const int SHM_PLANILLA_CANT_TAREAS_ASIGNADAS = 7;
const int SHM_PLANILLA_GENERAL_POSICIONES = 8;

const int SHM_TESTERS_COMUNES_DISPONIBLES = 9;
const int SHM_TESTERS_ESPECIALES_DISPONIBLES = 10;

const int SEM_TABLA_TESTERS_COMUNES_DISPONIBLES = 11;
const int SEM_TABLA_TESTERS_ESPECIALES_DISPONIBLES = 12;

const int SEM_IDENTIFICADOR = 13;

const int SHM_CANTIDAD_REQUERIMIENTOS_BROKER_SHM = 18;
const int SEM_CANTIDAD_REQUERIMIENTOS_BROKER_SHM = 19;

const int SHM_CANTIDAD_REQUERIMIENTOS_PLANILLAS_SHM = 20;
const int SEM_CANTIDAD_REQUERIMIENTOS_PLANILLAS_SHM = 21;

const int MSGQUEUE_ENVIO_DISP = 20;
const int MSGQUEUE_RECEPCIONES_DISP = 21;
const int MSGQUEUE_BROKER_RECEPTOR_DISPOSITIVOS = 22;
const int MSGQUEUE_BROKER_EMISOR_DISPOSITIVOS = 23;
const int MSGQUEUE_BROKER_RECEPTOR = 24;
const int MSGQUEUE_BROKER_EMISOR = 25;
const int MSGQUEUE_ENVIO_TESTER_COMUN = 26;
const int MSGQUEUE_RECEPCIONES_TESTER_COMUN = 27;
const int MSGQUEUE_REQUERIMIENTOS_TESTER_COMUN = 28;
const int MSGQUEUE_RECEPCIONES_NO_REQ_TESTER_COMUN = 29;
const int MSGQUEUE_ENVIO_TESTER_ESPECIAL = 30;
const int MSGQUEUE_RECEPCIONES_TESTER_ESPECIAL = 31;
const int MSGQUEUE_RECEPCIONES_EQUIPO_ESPECIAL = 32;
const int MSGQUEUE_ENVIO_EQUIPO_ESPECIAL = 33;
const int MSGQUEUE_DESPACHADOR = 34;
const int MSGQUEUE_ENVIO_TESTERS_SHMEM_PLANILLA_GENERAL = 35;
const int MSGQUEUE_RECEPCION_TESTERS_SHMEM_PLANILLA_GENERAL = 36;
const int MSGQUEUE_ENVIO_TESTERS_SHMEM_PLANILLA_ASIGNACION = 37;
const int MSGQUEUE_RECEPCION_TESTERS_SHMEM_PLANILLA_ASIGNACION = 38;
const int MSGQUEUE_REQ_TESTERS_SHMEM_PLANILLAS = 39;
const int MSGQUEUE_BROKER_REQUERIMIENTOS_DISPOSITIVOS = 40;
const int MSGQUEUE_BROKER_REQUERIMIENTOS_TESTER_ESPECIAL = 41;
const int MSGQUEUE_BROKER_REGISTRO_TESTERS = 42;

/* NUEVOS IPCS PARA MSG-INTER-BROKERS*/
const int MSGQUEUE_BROKER_HACIA_BROKER = 43;
const int MSGQUEUE_BROKER_DESDE_BROKER = 44;

/* MSGQUEUE PARA LA SHMEM INTER-BROKER (TESTERS DISPONIBLES)*/
const int MSGQUEUE_INTERNAL_BROKER_SHM = 45;
const int MSGQUEUE_ENVIO_BROKER_SHM = 46; // Envio de la shm inter-broker a otros brokers
const int MSGQUEUE_RECEPCION_BROKER_SHM = 47; // Recepcion de la shm inter-broker desde otros brokers

/* MSGQUEUE PARA LAS SHMEMS PLANILLAS ENTRE-BROKERS*/
const int MSGQUEUE_RECEPCION_BROKER_SHM_PLANILLA_GENERAL = 48;
const int MSGQUEUE_RECEPCION_BROKER_SHM_PLANILLA_ASIGNACION = 49;
const int MSGQUEUE_ENVIO_BROKER_SHM_PLANILLA_GENERAL = 50;
const int MSGQUEUE_ENVIO_BROKER_SHM_PLANILLA_ASIGNACION = 51;

/* MSGQUEUE PARA LAS SHMEMS PLANILLAS HACIA TESTER/EQUIPO*/
const int MSGQUEUE_BROKER_RECEPCION_SHMEM_HANDLER = 52;
const int MSGQUEUE_BROKER_ENVIO_SHMEM_HANDLER = 53;
const int MSGQUEUE_BROKER_REQUERIMIENTO_SHMEM_HANDLER = 54;

/* MSGQUEUE PARA USO INTERNO DEL BROKER CONTADOR DE REQUERIMIENTOS DE SHMEM DE PLANILLAS*/
const int MSGQUEUE_BROKER_INTERNAL_REQUERIMIENTO_PLANILLAS_HANDLER = 55;

const int LAST_ID_IPC = MSGQUEUE_BROKER_INTERNAL_REQUERIMIENTO_PLANILLAS_HANDLER + 1;

// mtypes desde el dispositivo
const int MTYPE_REQUERIMIENTO_DISPOSITIVO = 1;
const int MTYPE_RESULTADO_INICIAL = 2;
const int MTYPE_RESULTADO_ESPECIAL = 3;
// mtypes desde tester comun
const int MTYPE_PROGRAMA_INICIAL = 1;
const int MTYPE_REGISTRAR_TESTER = 2;
const int MTYPE_REQUERIMIENTO_TESTER_ESPECIAL = 4;
// mtypes desde tester especial
const int MTYPE_TAREA_ESPECIAL = 1;
const int MTYPE_AVISAR_DISPONIBILIDAD = 6;
// mtypes desde equipo especial
const int MTYPE_ORDEN = 1;
const int MTYPE_HAY_QUE_REINICIAR = 3;
const int MTYPE_FIN_TEST_ESPECIAL = 5;

const int ORDEN_APAGADO = 0;
const int ORDEN_REINICIO = 1;
const int ORDEN_SEGUIR_TESTEANDO = 2;
const int SIN_LUGAR = -1;

const int CANT_RESULTADOS = MAX_DISPOSITIVOS_EN_SISTEMA;
const int RESULTADO_GRAVE = 0;
const int RESULTADO_NO_GRAVE = 1;
const int SEGUIR_TESTEANDO = 2;
const int NO_CONTESTAR = 3;
const int FIN_TEST_ESPECIAL = 4;

const int MAX_TESTERS_ESPECIALES_PARA_ASIGNAR = 4;
const int TESTER_ESPECIAL_NO_ASIGNADO = 0;
//const int MINIMO_TESTERS_ESPECIALES_POR_ESPECIFICACION = 2;
// Archivos necesarios

const std::string ipcFileName = "/tmp/pereira-ipcs";

const std::string logFileName = "log.txt";

//Estructuras communes:
typedef struct resultado{
	int idDispositivo;
	int resultadosPendientes;
	int resultadosGraves;
}resultado_t;

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

// Primer mensaje de protocolo que cliente receptor le envia al server emisor
typedef struct TFirstMessage {
    int identificador;
} TFirstMessage;

typedef struct message {
    long mtype;
    long mtypeMensaje;
    long mtypeMensajeBroker;
    int idDispositivo;
    int tester;
    bool esTesterEspecial;
    bool hayQueReiniciar; // Se usa para avisarle al tester especial si debe reiniciar o no
    int idBroker;
    int idBrokerOrigen;
    int value; // Este parametro posee el valor del programa, del resultado y de la orden
    int posicionDispositivo;
    int idTestersEspeciales[MAX_TESTERS_ESPECIALES_PARA_ASIGNAR];
    int cantTestersEspecialesAsignados;
} TMessageAtendedor;

typedef struct TTablaBrokerTestersRegistrados {
    bool registrados[MAX_TESTER_COMUNES + MAX_TESTER_ESPECIALES + 1];
    bool disponible[MAX_TESTER_COMUNES + MAX_TESTER_ESPECIALES + 1];
    int brokerAsignado[MAX_TESTER_COMUNES + MAX_TESTER_ESPECIALES + 1]; // Especifica el ID del broker de cada ID
    int ultimoTesterElegido;
} TTablaBrokerTestersRegistrados;

// Para el server RPC de identificadores
typedef struct TTablaIdTestersDisponibles {
    bool disponibles[MAX_TESTER_COMUNES];
} TTablaIdTestersDisponibles;

typedef struct TTablaIdTestersEspecialesDisponibles {
    bool disponibles[MAX_TESTER_ESPECIALES];
} TTablaIdTestersEspecialesDisponibles;

/*******BROKERS CONFIG!********/
const int MASTER_BROKER = 1;
const int ID_BROKER_START = 1;
const int CANT_BROKERS = 2;
const int ID_BROKER = 1;
const int ID_BROKER_SIGUIENTE = (ID_BROKER == CANT_BROKERS) ? ID_BROKER_START : ID_BROKER + 1;
// LAS IPS DE LOS BROKERS ESTA EN EL ARCHIVO BROKER.CPP
const char PUERTO_CONTRA_BROKERS[] = "40000";
const char PUERTO_CONTRA_BROKERS_SHMEM_BROKERS[] = "40005";
const char PUERTO_CONTRA_BROKERS_SHMEM_PLANILLA_GENERAL[] = "40010";
const char PUERTO_CONTRA_BROKERS_SHMEM_PLANILLA_ASIGNACION[] = "40015";

// Para el mtypeMessageBroker del InterBroker-Message-Handler
const int MTYPE_HACIA_DISPOSITIVO = 1;
const int MTYPE_HACIA_TESTER = 2;
const int MTYPE_HACIA_EQUIPO_ESPECIAL = 3;

// Para los sockets
const char PUERTO_SERVER_RECEPTOR_DISPOSITIVOS[] = "50000";
const char PUERTO_SERVER_EMISOR_DISPOSITIVOS[] = "50001";

const char PUERTO_SERVER_RECEPTOR[] = "50002";
const char PUERTO_SERVER_EMISOR[] = "50003";

// Para el broker al que se conectan dispositivos y testers de esta maquina
const char UBICACION_SERVER[] = "127.0.0.1";
//const char UBICACION_SERVER_IDENTIFICADOR[] = "192.168.2.7";
const char UBICACION_SERVER_IDENTIFICADOR[] = "192.168.2.10";

/*********CONFIG PEDIDO SHARED MEMORY TESTERS**********/
typedef struct TSharedMemoryPlanillaAsignacion {
    long mtype;
    TContadorTesterEspecial cantTestersEspecialesAsignados[MAX_DISPOSITIVOS_EN_SISTEMA];
    TContadorTareaEspecial cantTareasEspecialesAsignadas[MAX_DISPOSITIVOS_EN_SISTEMA];
} TSharedMemoryPlanillaAsignacion;

const int MTYPE_REQ_SHMEM_PLANILLA_ASIGNACION = 1;
const int MTYPE_DEVOLUCION_SHMEM_PLANILLA_ASIGNACION = 2;
const char PUERTO_SERVER_RECEPCION_SHM_PLANILLA_ASIGNACION[] = "60011";
const char PUERTO_SERVER_ENVIO_SHM_PLANILLA_ASIGNACION[] = "60012";

typedef struct TSharedMemoryPlanillaGeneral {
    long mtype;
    int cantDispositivosSiendoTesteados;
    bool idsPrivadosDispositivos[MAX_DISPOSITIVOS_EN_SISTEMA];
} TSharedMemoryPlanillaGeneral;

const int MTYPE_REQ_SHMEM_PLANILLA_GENERAL = 3;
const int MTYPE_DEVOLUCION_SHMEM_PLANILLA_GENERAL = 4;
const int INIT_MTYPE_SHMEM_PLANILLA_GENERAL = ID_EQUIPO_ESPECIAL + 1;
const char PUERTO_SERVER_RECEPCION_SHM_PLANILLA_GENERAL[] = "60013";
const char PUERTO_SERVER_ENVIO_SHM_PLANILLA_GENERAL[] = "60014";

typedef struct TRequerimientoSharedMemory {
    long mtype;
    int idSolicitante;
    int idDevolucion;
} TRequerimientoSharedMemory;
const char PUERTO_SERVER_RECEPCION_REQ_PLANILLAS[] = "60015";

typedef struct TShmemCantRequerimientos {
    int cantRequerimientosShmemPlanillaGeneral;
    int cantRequerimientosShmemPlanillaAsignacion;
} TShmemCantRequerimientos;
/*******FIN PEDIDO SHARED MEMORY TESTERS***********/

/*******SUB-BROKERS-CONFIG********/
const int MTYPE_DEVOLUCION_SHM_BROKER = 1;
const int MTYPE_REQUERIMIENTO_SHM_BROKER = 2; // Procurar que el ID de los subbrokers superen esto
const int ID_SUB_BROKER_REQUERIMIENTO_DISP = 5;
const int ID_SUB_BROKER_REQUERIMIENTO_ESP = 6;
const int ID_SUB_BROKER_REGISTRO_TESTER = 7;
const int ID_SUB_BROKER_PASAMANOS_RECEPTOR = 8;

typedef struct TMessageShMemInterBroker {
    long mtype;
    TTablaBrokerTestersRegistrados memoria;
} TMessageShMemInterBroker;

typedef struct TMessageRequerimientoBrokerShm {
    long mtype;
    int idSubBroker;
} TMessageRequerimientoBrokerShm;
/*******FIN SUB-BROKERS CONFIG*********/

#endif	/* COMMON_H */

