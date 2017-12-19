#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "impr.h"

// agregue las variables globales que necesite

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
int ocup= 0;

// Agregue aca otras funciones que necesite

void imprimir(Doc *doc, int pri) {
  // Complete la implementacion de imprimir
  pthread_mutex_lock(&m);
  while (ocup))
    pthread_cond_wait(&cond, &m);
  ocup= 1;
  pthread_mutex_unlock(&m);

  doPrint(doc);

  pthread_mutex_lock(&m);
  ocup= 0;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
}
