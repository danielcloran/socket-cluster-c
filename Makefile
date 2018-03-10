CC       = gcc
CFLAGS   = -O2 -std=c99 
LDFLAGS  = 
PKGFLAGS = `pkg-config libwebsockets openssl json-c --libs --cflags`
TARGET   = client.test

all:
	gcc socket-cluster-client.c -o ${TARGET} ${PKGFLAGS} -I./lib -lpthread