#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "jsocket.h"
#include "util.h"

typedef void *(*Thread_fun)(void *);
typedef unsigned long long ulonglong;
typedef unsigned int uint;

#define SIZE 1000000

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
ulonglong x;
uint raiz_x;
ulonglong base= 2;
int fin= 0;
uint factor= 0;

void *serv(long s) {
  write(s, (char*)&x, sizeof(x));
  pthread_mutex_lock(&m);
  while (!fin) {
    uint i= base;
    uint j, res;
    base += SIZE;
    if (base>raiz_x)
      fin= 1;
    pthread_mutex_unlock(&m);

    j= i+SIZE-1;
    if (j>raiz_x)
      j= raiz_x;
    printf("enviando [%u,%u]\n", i, j);
    write(s, (char*)&i, sizeof(i));
    write(s, (char*)&j, sizeof(j));
    leer(s, (char*)&res, sizeof(uint));

    pthread_mutex_lock(&m);
    if (res!=0) {
      factor= res;
      printf("el factor es %u\n", factor); /* no se pedia */
      fin= 1;
    }
  }
  pthread_mutex_unlock(&m);

  close(s);
  return NULL;
}

int main(int argc, char **argv) {
  long s, s2;
  pthread_t pid;

  signal(SIGPIPE, SIG_IGN);

  x= atoll(argv[1]);
  raiz_x= (uint)sqrt((double)x);

  printf("factorizando %llu con raiz=%u\n", x, raiz_x);

  s = j_socket();

  if (j_bind(s, 3000) < 0)
    error("bind fallo.  Port 3000 ocupado?");

  /* Cada vez que se conecta un cliente le creo un thread.
   * Esta parte es identica a lo que aparece en los apuntes.
   * Solo tienen que copiar.
   */
  for(;;) {
    pthread_attr_t attr;
    s2= j_accept(s);
    pthread_attr_init(&attr);
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
      fprintf(stderr, "No se puede establecer el atributo\n");
    }
    if ( pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) {
      fprintf(stderr, "No pude crear thread para nuevo cliente %ld!!!\n", s2);
      close(s2);
    }
    pthread_attr_destroy(&attr);
  }
}
