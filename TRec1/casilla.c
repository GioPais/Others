#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "colapri.h"
#include "colapri-arreglo.h"
#include "casilla.h"


/* Cambie este tipo por la estructura de la casilla */
//typedef void *Casilla;


/* Debe implementar estas funciones en el archivo casilla.c */

Casilla nuevaCasilla() {
  
  Casilla *c= malloc(sizeof(Casilla));
  cp->msgs= nuevaColaPriArreglo(5, max());
  return (Casilla)c;
}


void enviar(Casilla c, void *msg, int pri){

}

void *recibir(Casilla c){

}
