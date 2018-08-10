JNI_INCLUDE = /usr/lib/jvm/java-8-openjdk-amd64/include/
JNI_INCLUDE += /usr/lib/jvm/java-8-openjdk-amd64/include/linux
CC = gcc # C compiler
CFLAGS = -fPIC -O2 -g # C flags
CFLAGS += $(foreach d, $(JNI_INCLUDE), -I$d)
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = /usr/lib/libmesh_lib.so # target lib
JNI_SETUP = $(shell javac -h . meshgui/Home.java)

SRCS = jni/Home.c # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: meshgui_Home.h ${TARGET_LIB}

meshgui_Home.h: 
	$(JNI_SETUP)		

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) meshgui_Home.h