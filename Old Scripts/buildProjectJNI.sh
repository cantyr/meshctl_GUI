#!/bin/sh
javac -h . meshgui/Home.java
sudo gcc -fPIC -I/usr/lib/jvm/java-8-openjdk-amd64/include/ -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux -shared -o /usr/lib/libmesh_lib.so jni/Home.c