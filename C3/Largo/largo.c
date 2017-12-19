#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

typedef struct nodo {
  int x;
  struct nodo *prox;
} Nodo;

jmp_buf env;

/* agregue otras funciones como una rutina de atencion para SIGSEGV */

/* esta es la funcion pedida */

int largo(Nodo *nodo) {
  /* ... completar ... */
}

/* Ahora viene el test de prueba */

Nodo nodo3= { 3, NULL };
Nodo nodo2= { 2, &nodo3 };
Nodo nodo1= { 1, &nodo2 };

int main() {
  char dummy;
  printf("Largo= %d\n", largo(&nodo1));
  nodo3.prox= (Nodo*)(&dummy - 100000000);
  printf("Largo= %d\n", largo(&nodo1));
  return 0;
}
