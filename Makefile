include blueZ/Makefile
JNI_INCLUDE = /usr/lib/jvm/java-8-openjdk-amd64/include/
JNI_INCLUDE += /usr/lib/jvm/java-8-openjdk-amd64/include/linux
CC = gcc # C compiler
CFLAGS = -fPIC -O2 -g # C flags
CFLAGS += $(foreach d, $(JNI_INCLUDE), -I$d)
CFLAGS += $(foreach d, $(BLUEZ_INCLUDE), -I$d)
LDFLAGS = $(foreach d, $(BLUEZ_LIBS), -l$d) # linking flags
LDFLAGS += -shared
RM = rm -f  # rm command
TARGET_LIB = /usr/lib/libmesh_lib.so # target lib
JNI_SETUP = javac -h . meshgui/Home.java

SRCS = jni/Home.c # source files
SRCS += $(BLUEZ_SRCS)
OBJS = $(SRCS:.c=.o)
CLASSES = meshgui/*.class

.PHONY: all
all: meshgui_Home.h ${TARGET_LIB}

meshgui_Home.h: 
	$(JNI_SETUP)		

$(TARGET_LIB): $(OBJS)
	$(CC) -o $@ $^ ${LDFLAGS}
	java meshgui.Home

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) meshgui_Home.h ${CLASSES}