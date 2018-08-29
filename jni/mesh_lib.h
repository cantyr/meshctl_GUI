#ifndef _INIT_MESH_LIB
#define _INIT_MESH_LIB
#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>

enum eventKey {
	NO_EVENT = 0,
	NAME,
	UUID,
	END_OF_LIST
};

extern char *stringBuff;
extern pthread_mutex_t eventLock;
extern sem_t eventEmpty;
extern sem_t eventFull;
extern uint8_t exitEventLoop;
extern enum eventKey javaEvent;

int mesh_init(void);
//void cmd_security(int);
void cmd_scan_unprovisioned(int);
void cmd_start_prov(char *);
/*void cmd_appkey_add(int);
void cmd_bind(int, int, int);
void onoff_set(int);
void hsl_set(int, int, int);
void ctl_set(int, int);
void lightness_set(int);
void level_set(int);*/
void mainloop_exit_success();
void sendEventToJava(enum eventKey, char *);

#ifdef __cplusplus
}
#endif
#endif
