#define _BSD_SOURCE 1

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "casilla.h"

/* Un step corresponde a 1 segundo: 1000000 microsegundos */

#define STEP 1000000

Casilla c, c2;

char *m1= "primer mensaje de emisor 1 (hito 2)";
char *m2= "segundo mensaje de emisor 1 (hito 3)";
char *m3= "mensaje de emisor 2 (hito 5)";
char *m4= "mensaje de emisor 3 (hito 4)";

void error(char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);

  exit(1);
}

void *fun_emisor1(void *ptr) {
  usleep(2*STEP);
  printf("emisor 1: primera emision (hito 2)\n");
  enviar(c, m1, 1);
  printf("emisor 1: mensaje recibido\n");

  usleep(STEP);
  printf("emisor 1: segunda emision (hito 3)\n");
  enviar(c, m2, 1);
  printf("emisor 1: mensaje recibido\n");

  return NULL;
}

void *fun_emisor2(void *ptr) {
  usleep(5*STEP);
  printf("emisor 2: emision (hito 5)\n");
  enviar(c, m3, 2);
  printf("emisor 2: mensaje recibido\n");

  return NULL;
}

void *fun_emisor3(void *ptr) {
  usleep(4*STEP);
  printf("emisor 3: emision (hito 4)\n");
  enviar(c2, m4, 2);
  printf("emisor 3: mensaje recibido\n");

  return NULL;
}

void *fun_receptor(void *ptr) {
  usleep(STEP);

  printf("receptor: primera recepcion (hito 1)\n");
  char *r= recibir(c);
  if (r!=m1)
    error("receptor: el mensaje debio ser m1 y no %s", r);
  usleep(STEP/2);
  printf("receptor: se recibio correctamente %s\n", r);
  usleep(STEP/2);

  usleep(3*STEP);

  printf("receptor: segunda recepcion (hito 6)\n");
  char *s= recibir(c);
  if (s!=m3)
    error("receptor: el mensaje debio ser m3 y no %s", s);
  usleep(STEP/2);
  printf("receptor: se recibio correctamente %s\n", s);

  usleep(STEP/2);

  printf("receptor: tercera recepcion (hito 7)\n");
  char *t= recibir(c);
  if (t!=m2)
    error("receptor: el mensaje debio ser m2 y no %s", t);
  usleep(STEP/2);
  printf("receptor: se recibio correctamente %s\n", t);

  usleep(STEP/2);

  printf("receptor: cuarta recepcion (hito 8)\n");
  char *u= recibir(c2);
  if (u!=m4)
    error("receptor: el mensaje debio ser m4 y no %s", u);
  usleep(STEP/2);
  printf("receptor: se recibio correctamente %s\n", u);

  return NULL;
}

/* Para el test de robustez */

#define N 50
#define M 1000

typedef struct {
  Casilla c;
  long sum;
  int pri;
} Param;

void *fun_prod(void *ptr) {
  Param *pparam= ptr;
  long *v= malloc(M*sizeof(long));
  int j;
  pparam->sum= 0;
  for (j= 0; j<M; j++) {
    v[j]= random();
    enviar(pparam->c, &v[j], pparam->pri); 
    pparam->sum += v[j];
  }
  return NULL;
}
  
void *fun_cons(void *ptr) {
  Param *pparam= ptr;
  int j;
  pparam->sum= 0;
  for (j= 0; j<M; j++) {
    long *px= recibir(pparam->c);
    pparam->sum += *px;
  }
  return NULL;
}
  
int main() {

  printf("Primer test: el ejemplo del enunciado\n");
  c= nuevaCasilla();
  c2= nuevaCasilla();

  pthread_t receptor, emisor1, emisor2, emisor3;
  pthread_create(&receptor, NULL, fun_receptor, NULL);
  pthread_create(&emisor1, NULL, fun_emisor1, NULL);
  pthread_create(&emisor2, NULL, fun_emisor2, NULL);
  pthread_create(&emisor3, NULL, fun_emisor3, NULL);

  pthread_join(receptor, NULL);
  pthread_join(emisor1, NULL);
  pthread_join(emisor2, NULL);
  pthread_join(emisor3, NULL);

  printf("Segundo test: robustez\n");

  /* N threads emisores envian M numeros aleatorios a N threads
   * receptores.  La suma de los valores emitidos debe
   * coincidir con la suma de los valores recibidos.
   */

  pthread_t prods[N], cons[N];
  Param param_prods[N], param_cons[N];
  Casilla c3= nuevaCasilla();
  int i;
  for (i= 0; i<N; i++) {
    param_prods[i].c= c3;
    param_prods[i].pri= i;
    param_cons[i].c= c3;
    pthread_create(&prods[i], NULL, fun_prod, &param_prods[i]);
    pthread_create(&cons[i], NULL, fun_cons, &param_cons[i]);
  }

  long prod_sum= 0;
  long cons_sum= 0;
  for (i= 0; i<N; i++) {
    pthread_join(prods[i], NULL);
    prod_sum += param_prods[i].sum;
    pthread_join(cons[i], NULL);
    cons_sum += param_cons[i].sum;
  }

  if (prod_sum!=cons_sum)
    error("La suma de los numeros enviados no coincide con la suma recibida\n");

  printf("\n\nRevise que la salida de este programa coincide con salida.txt\n");
  printf("Para ello ejecute lo siguiente:\n");
  printf("   %% ./test-casilla > mi-salida.txt\n");
  printf("   %% diff salida.txt mi-salida.txt\n");
  printf("   %%\n");
  printf("Si diff notifica alguna diferencia, su programa *no* funciona\n");

  return 0;
}
