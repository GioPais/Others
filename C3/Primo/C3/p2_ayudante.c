#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"

#define SIZE 1000000

/* Esta parte es dada */

typedef unsigned long long ulonglong;
typedef unsigned int uint;

uint buscarFactor(ulonglong x, uint i, uint j) {
  int k;
  for (k= i; k<=j; k++) {
    if (x % k == 0)
      return k;
  }
  return 0;
}

/* Esta es la parte que tiene que programar el alumno */

int main(int argc, char **argv) {
  int s;
  char *servidor= argv[1];
  ulonglong x;

  s = j_socket();
  if (j_connect(s, servidor, 3000)<0)
    error("conexion rechazada");
  /* recibimos el numero x */
  if (leer(s, (char*)&x, sizeof(x)))
    error("fallo la conexion");
  printf("factorizando %llu\n", x);
  for (;;) {
    uint i, j, res;
    /* Obtenemos el comienzo del intervalo */
    if (leer(s, (char*)&i, sizeof(i)))
      break; /* se acabaron los intervalos o alguien encontro un factor */
    if (leer(s, (char*)&j, sizeof(j)))
      error("fallo la conexion");
    printf("buscando entre %u y %u\n", i, j);
    res= buscarFactor(x, i, j);
    if (res!=0)
      printf("encontrado! factor= %u\n", res);
    write(s, &res, sizeof(res));
  }
  close(s); /* no se requiere */
  printf("se acabaron los intervalos o alguien encontro un factor\n");
  return 0;
}
