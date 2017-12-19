CFLAGS= -g -Wall -pedantic -std=c99
LFLAGS= -g

all: test-casilla

colapri-arreglo.o: colapri.h colapri-arreglo.h

casilla.o: casilla.h colapri-arreglo.h colapri.h

test-casilla: colapri-arreglo.o test-casilla.o casilla.o
	gcc $(LFLAGS) -pthread -o test-casilla colapri-arreglo.o test-casilla.o casilla.o
	
clean:
	rm -f *.o test-casilla
