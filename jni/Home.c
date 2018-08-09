#include <stdio.h>
#include "mesh_lib.h"
#include "../meshgui_Home.h"

JNIEXPORT void JNICALL Java_meshgui_Home_init
(JNIEnv *env, jclass class) {
  	printf("init()!!\n");
}

JNIEXPORT void JNICALL Java_meshgui_Home_security
(JNIEnv *env, jclass class, jint secLvl) {
  	printf("Setting security to %d\n", secLvl );
}

JNIEXPORT void JNICALL Java_meshgui_Home_discoverUnprovisioned
(JNIEnv *env, jclass class, jint onoff) {
	printf("Discover Unprovisoned %d\n", onoff );
}

JNIEXPORT void JNICALL Java_meshgui_Home_provision
(JNIEnv *env, jclass class, jstring uuid) {
	const char *str= (*env)->GetStringUTFChars(env,uuid,0);
	printf("Provision %s\n", str);
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
