#include "tcp.h"
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "common/common.h"
#include "comunes_tcp.h"
#include "logger/Logger.h"
/*
#ifdef EJEMPLO_TEST
#define IPCS_FILE "ipcs-prueba"
#else
#define IPCS_FILE "/tmp/pereira-ipcs"
#endif
*/
int main(int argc, char *argv[]) {
    
    Logger::initialize(logFileName.c_str(), Logger::LOG_DEBUG);
    if(argc != 4) {
        printf("Uso: %s <puerto> <idMsgQueue> <sizeMsg> \n", argv[0]);
        Logger::error("Bad arguments!", __FILE__);
        return -1;
    }
	
    int idMsgQueue = atoi(argv[2]);
    size_t size = atoi(argv[3]);
   
    int fd = tcpOpenPasivo(atoi(argv[1]));
    if(fd < 0) {
        Logger::error("Error creating server socket", __FILE__);
        return -2;
    }

//    signal(SIGPIPE, SIG_IGN);
	
    key_t key = ftok(ipcFileName.c_str(), idMsgQueue);
    int msgQueue = msgget(key, 0660);
	
    /* FIN del setup */
    //int cant_atendidos = 0;
	
    while(true) {
        //Verifico no estar atendiendo ya muchos clientes
        /*while (cant_atendidos >= MAXIMOS_ATENDIDOS) {
            wait(NULL);
            cant_atendidos--;
        }*/

        int clientFd = accept(fd, (struct sockaddr*)NULL, NULL);
        //cant_atendidos++;

        if (fork() == 0) {
            void* buffer = malloc(size);

            //Espero Primer mensaje, que me dice el identificador del cliente
            TFirstMessage firstMsg;
            recibir(clientFd, &firstMsg, sizeof(TFirstMessage));
            int idCliente = firstMsg.identificador;
/*
            int ok_read = msgrcv(cola_id_disp, buffer, sizeof(TMessageAtendedor) - sizeof(long), id_tester, 0);
            if (ok_read == -1) {
                exit(0);
            }

            long dispositivo_a_tratar = buffer->idDispositivo;
            pid_t receptor = buffer->value;

            buffer->tester = id_tester;
*/
            while (true) {
                //Espero un mensaje que deba ser enviado al dispositivo en cuestion
                int okRead = msgrcv(msgQueue, buffer, size - sizeof(long), idCliente, 0);
                if (okRead == -1) {
                    std::stringstream ss;
                    ss << "Error recibiendo mensaje de la cola para el cliente " << idCliente <<". Errno: " << strerror(errno);
                    Logger::error(ss.str(), __FILE__);
                    close(clientFd);
                    exit(1);
                }

                enviar(clientFd, buffer, size);
            }			
        }
        close(clientFd);
    }
	
}
