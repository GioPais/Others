#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "util.h"

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

uint factorizar(ulonglong x) {
  uint raiz_x= (uint)sqrt((double)x);
  int pid;
  int fds[2];
  pipe(fds);
  pid= fork();
  if (pid==0) {
    int ini= raiz_x/2+1; /* detalle: para x= 3, ini=1, pero ini debe ser >=2 */
    uint rh;
    if (ini<2)
      ini= 2;
    rh= buscarFactor(x, ini, raiz_x);
    printf("hijo [%u,%u] -> %u\n", ini, raiz_x, rh);
    write(fds[1], (char*)&rh, sizeof(rh));
    exit(rh==0 ? 1 : 0); /* cierra sus fds cuando termina */
  }
  else {
    int rc;
    uint rh;
    uint rp= buscarFactor(x, 2, raiz_x/2);
    printf("padre [%u,%u] -> %u\n", 2, raiz_x/2, rp);
    leer(fds[0], (char*)&rh, sizeof(rh)); /* pueden usar read */
    waitpid(pid, &rc, 0);
    close(fds[0]); /* hay que cerrarlos, porque si no se acumulan */
    close(fds[1]);
    return rp!=0 ? rp : rh;
  }
}

/* Esta parte es dada */

int main(int argc, char **argv) {
  ulonglong x= atoll(argv[1]);
  printf("%u\n", factorizar(x));
  return 0;
}
