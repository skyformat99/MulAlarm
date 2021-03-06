CC = gcc
SRC = src/main.c src/MulAlarm.c
HEADER = src/MulAlarm.h
OUTPUT = bin/MulAlarm
CFLAG = -std=c99
LIBDIR = lib/libev
LIBFLAG = -lev -lm

all:build

build:${OUTPUT}

${OUTPUT}:${SRC} ${HEADER} ${LIBDIR}/libev.a bin
	${CC} ${SRC} -o${OUTPUT} -I${LIBDIR} -L${LIBDIR} ${LIBFLAG}

bin:
	mkdir bin

.PHONY:clean

clean:
	rm -rf bin

