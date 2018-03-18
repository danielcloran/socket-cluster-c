CC       = gcc
CFLAGS   = -O2
LDFLAGS  = 
PKGFLAGS = `pkg-config libwebsockets openssl json-c --libs --cflags`
TARGET   = client.test

all:
	gcc socket-cluster-client.c -o ${TARGET} ${PKGFLAGS} ${CFLAGS} -I./lib -lpthread
