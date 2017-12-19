# Defina aca la ubicacion de jsockets4
LIBJSOCKET=/u/i/lmateu/CC3301/jsockets4

CFLAGS= -g -Wall -std=c1x -I$(LIBJSOCKET)
LDFLAGS= -g

all: p2_ayudante p2_factorizar p1a p1b p1c p1c_bis

p2_ayudante: p2_ayudante.o util.o $(LIBJSOCKET)/libjsocket.o

p2_ayudante.o: util.h

p2_factorizar: p2_factorizar.o util.o $(LIBJSOCKET)/libjsocket.o -lpthread -lm

p2_factorizar.o: util.h

p1a: p1a.o util.o -lm

p1b: p1b.o util.o -lm

p1c: p1c.o util.o -lm

p1c_bis: p1c_bis.o util.o -lm

clean:
	rm -f *.o
	rm -f p2_ayudante p2_factorizar p1a p1b p1c p1c_bis
