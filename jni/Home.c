#include <stdio.h>
#include "mesh_lib.h"
#include "../meshgui_Home.h"
#include <jni.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

char *stringBuff;
pthread_mutex_t eventLock;
sem_t eventEmpty;
sem_t eventFull;
uint8_t exitEventLoop;
enum eventKey javaEvent = NO_EVENT;

JNIEXPORT void JNICALL Java_meshgui_Home_init
(JNIEnv *env, jclass class) {
  	printf("init()!!\n");
    mesh_init();
}

JNIEXPORT void JNICALL Java_meshgui_Home_security
(JNIEnv *env, jclass class, jint secLvl) {
  	printf("Setting security to %d\n", secLvl );
}

JNIEXPORT void JNICALL Java_meshgui_Home_discoverUnprovisioned
(JNIEnv *env, jclass class, jint onoff) {
	printf("Discover Unprovisoned %d\n", onoff );
	cmd_scan_unprovisioned( onoff );
}

JNIEXPORT void JNICALL Java_meshgui_Home_provision
(JNIEnv *env, jclass class, jstring uuid) {
	char *str= (*env)->GetStringUTFChars(env,uuid,0);
	printf("Provision %s\n", str);
    cmd_start_prov(str);
	(*env)->ReleaseStringUTFChars(env, uuid, str);
}

JNIEXPORT void JNICALL Java_meshgui_Home_appKeyAdd
(JNIEnv *env, jclass class, jint keyIdx) {
  	printf("Adding App Key at index %d\n", keyIdx );
}

JNIEXPORT void JNICALL Java_meshgui_Home_appKeyBind
(JNIEnv *env, jclass class, jint elmtIdx, jint keyIdx, jint modelId) {
  	printf("Binding App Key at index %d to element at index %d with model ID of %d\n", keyIdx, elmtIdx, modelId );
}

JNIEXPORT void JNICALL Java_meshgui_Home_removeNode
(JNIEnv *env, jclass class, jstring device) {
	const char *str= (*env)->GetStringUTFChars(env,device,0);
  printf("Removing node %s\n", str );
  (*env)->ReleaseStringUTFChars(env, device, str);
}

JNIEXPORT void JNICALL Java_meshgui_Home_endMainloop
  (JNIEnv *env, jclass class) {
    printf("ending mainloop()!!\n");
    mainloop_exit_success();
}

JNIEXPORT void JNICALL Java_meshgui_Home_onoff
(JNIEnv *env, jclass class, jint onoff) {
  	printf("Sending onoff value of  %d\n", onoff );
}

JNIEXPORT void JNICALL Java_meshgui_Home_hsl
(JNIEnv *env, jclass class, jint h, jint s, jint l) {
  	printf("Sending HSL value of %d, %d, %d\n", h, s, l );
}

JNIEXPORT void JNICALL Java_meshgui_Home_ctl
(JNIEnv *env, jclass class, jint cct, jint l) {
    printf("Sending CTL value of %d, %d\n", cct, l );
}

JNIEXPORT void JNICALL Java_meshgui_Home_lightness
(JNIEnv *env, jclass class, jint lightness) {
  	printf("Sending lightness value of %d\n", lightness );
}

JNIEXPORT void JNICALL Java_meshgui_Home_level
(JNIEnv *env, jclass class, jint lvl) {
    printf("Sending Level value of %d\n", lvl );
}

JNIEXPORT void JNICALL Java_meshgui_Home_eventCallback
(JNIEnv *env, jobject foo_obj) {

  // Get the class from the object we got passed in
  jclass cls_foo = (*env)->GetObjectClass(env, foo_obj);

  char name[100];
  char uuid[32];
  static jmethodID mid_callbackDevDetails;

  memset(uuid, 0, 32);
  memset(name, 0, 100);


  exitEventLoop = 0;

  do {
    sem_wait(&eventFull);
    pthread_mutex_lock(&eventLock);
    if(!exitEventLoop)
    {
      switch (javaEvent)
      {
        case NAME:
              memcpy(name, stringBuff, strlen(stringBuff));
              jstring jname = (*env)->NewStringUTF(env, name);
              if (!mid_callbackDevDetails)
                mid_callbackDevDetails        = (*env)->GetMethodID      (env, cls_foo, "discoverUnprovisionedCallback"       , "(ILjava/lang/String;)V");
              //jmethodID mid_callback_static = (*env)->GetStaticMethodID(env, cls_foo, "callback_static", "()V");

              (*env)->CallVoidMethod      (env, foo_obj, mid_callbackDevDetails, javaEvent, jname);
              //(*env)->CallStaticVoidMethod(env, cls_foo, mid_callback_static);
              break;
        case UUID:
              memcpy(uuid, stringBuff, strlen(stringBuff));
              jstring juuid = (*env)->NewStringUTF(env, uuid);
              if (!mid_callbackDevDetails)
                mid_callbackDevDetails        = (*env)->GetMethodID      (env, cls_foo, "discoverUnprovisionedCallback"       , "(ILjava/lang/String;)V");
              //jmethodID mid_callback_static = (*env)->GetStaticMethodID(env, cls_foo, "callback_static", "()V");

              (*env)->CallVoidMethod      (env, foo_obj, mid_callbackDevDetails, javaEvent, juuid);
              //do stuff
              break;
        default:
            break;
      }
       memset(stringBuff, 0, 512);
    }
    pthread_mutex_unlock(&eventLock);
    sem_post(&eventEmpty);
  } while (!exitEventLoop);

  
}