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

static jmp_buf env;
static int pid;
static int termino;

#if 0
void capt_control_c() {
  printf("el hijo recibe SIGINT\n");
  exit(0);
}
#endif

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
      uint ini= raiz_x/2+1; /* detalle: para x=3, ini=1,pero ini debe ser >=2 */
      uint rh;
      if (ini<2)
        ini= 2;
      /* signal(SIGINT, capt_control_c); */
      rh= buscarFactor(x, ini, raiz_x);
      printf("hijo [%u,%u] -> %u\n", ini, raiz_x, rh);
      exit(rh==0 ? 1 : 0);
    }
    else {
      int rc;
      uint rp;
      rp= buscarFactor(x, 2, raiz_x/2);
      /* En el control pueden omitir restaurar el handler de SIGCHLD
       * en este punto.  En la practica si no se hace pueden haber
       * 2 llamadas a waitpid: una en capturador y otra aqui mismo
       * mas abajo.  Si no se maneja bien esa condicion de borde
       * el programa puede fallar, porque el segundo waitpid va
       * a fallar.  Esto se puede resolver verificando
       * la condicion de error de waitpid, como se hace mas abajo.
       */
      signal(SIGCHLD, hdlr);
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
        rc= WEXITSTATUS(rc); /* pueden omitir WEXITSTATUS en el control */
        printf("padre [%u,%u] -> %u\n", 2, raiz_x/2, rp);
        return rp==0 && rc;
      }
    }
  }
  else {
    printf("el hijo encontro un factor => no es primo\n");
    return 0;
  }
}

/* Esta parte es dada */

int main(int argc, char **argv) {
  ulonglong x= atoll(argv[1]);
  printf("%d\n", es_primo(x));
  return 0;
}
