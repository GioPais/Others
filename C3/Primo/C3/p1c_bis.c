/* Igual a p1c.c, solo que el hijo busca en el intervalo [2, raiz_x/2] */

#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>

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

static jmp_buf env;
static int pid;
static int termino;

void capturador() {
  int rc;
  termino= 1;
  waitpid(pid, &rc, 0);
  rc= WEXITSTATUS(rc);
  if (rc==0)
    siglongjmp(env, 1); /* el hijo encontro un factor => no es primo */
}

int es_primo(ulonglong x) {
  if (sigsetjmp(env,1)==0) {
    uint raiz_x= (uint)sqrt((double)x);
    void (*hdlr)(int)= signal(SIGCHLD, capturador);
    termino= 0;
    pid= fork();
    if (pid==0) {
      uint rh= buscarFactor(x, 2, raiz_x/2);
      printf("hijo [%u,%u] -> %u\n", 2, raiz_x/2, rh);
      exit(rh==0 ? 1 : 0);
    }
    else {
      int rc;
      uint rp;
      uint ini= raiz_x/2+1; /* detalle: para x=3, ini=1,pero ini debe ser >=2 */
      if (ini<2)
        ini= 2;
      rp= buscarFactor(x, ini, raiz_x);
      signal(SIGCHLD, hdlr); /* pueden omitirlo en el control */
      if (termino) {
        /* si se invoco capturador, ya se hizo waitpid y no
         * se invoco siglongjmp => el hijo no encontro un factor.
         */
        return rp==0;
      }
      else {
        if (rp!=0) {
          printf("terminando al hijo\n");
          kill(pid, SIGINT);
        }
        if (waitpid(pid, &rc, 0)<0) {
          /* Fallo el waitpid.  Esto puede suceder si ya se llamo
           * a waitpid en capturador, y este fue invocado despues
           * de restaurar el handler para SIGCHLD.  En teoria
           * no puede ocurrir, pero si ocurriese es porque
           * el hijo no encontro ningun factor.
           */
          printf("fallo waitpid\n");
          return rp==0;
        }
        rc= WEXITSTATUS(rc); /* pueden omitirlo en el control */
        printf("padre [%u,%u] -> %u\n", ini, raiz_x, rp);
        return rp==0 && rc;
      }
    }
  }
  else {
    printf("el hijo encontro un factor => no es primo\n");
    return 0;
  }
}

int main(int argc, char **argv) {
  ulonglong x= atoll(argv[1]);
  printf("%d\n", es_primo(x));
  return 0;
}
