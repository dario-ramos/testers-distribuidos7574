/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REGISTRACION_H_RPCGEN
#define _REGISTRACION_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define REGISTER 0x2fffffff
#define REGISTER_V1 1

#if defined(__STDC__) || defined(__cplusplus)
#define GET_ID_DISPOSITIVO 1
extern  int * get_id_dispositivo_1(void *, CLIENT *);
extern  int * get_id_dispositivo_1_svc(void *, struct svc_req *);
#define GET_ID_TESTER 2
extern  int * get_id_tester_1(int *, CLIENT *);
extern  int * get_id_tester_1_svc(int *, struct svc_req *);
#define REGISTRAR_TESTER_ACTIVO 3
extern  int * registrar_tester_activo_1(int *, CLIENT *);
extern  int * registrar_tester_activo_1_svc(int *, struct svc_req *);
#define DEVOLVER_ID_DISPOSITIVO 4
extern  int * devolver_id_dispositivo_1(int *, CLIENT *);
extern  int * devolver_id_dispositivo_1_svc(int *, struct svc_req *);
#define DEVOLVER_ID_TESTER 5
extern  int * devolver_id_tester_1(int *, CLIENT *);
extern  int * devolver_id_tester_1_svc(int *, struct svc_req *);
extern int register_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GET_ID_DISPOSITIVO 1
extern  int * get_id_dispositivo_1();
extern  int * get_id_dispositivo_1_svc();
#define GET_ID_TESTER 2
extern  int * get_id_tester_1();
extern  int * get_id_tester_1_svc();
#define REGISTRAR_TESTER_ACTIVO 3
extern  int * registrar_tester_activo_1();
extern  int * registrar_tester_activo_1_svc();
#define DEVOLVER_ID_DISPOSITIVO 4
extern  int * devolver_id_dispositivo_1();
extern  int * devolver_id_dispositivo_1_svc();
#define DEVOLVER_ID_TESTER 5
extern  int * devolver_id_tester_1();
extern  int * devolver_id_tester_1_svc();
extern int register_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REGISTRACION_H_RPCGEN */
