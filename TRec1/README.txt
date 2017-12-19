Archivos:

casilla.h: encabezados para las funciones pedidas.  Ademas
  se incluye la funcion error, que esta implementada en test-casilla.c.
test-casilla.c: el programa de prueba de su tarea.
salida.txt: la salida correcta del programa de prueba.  Cualquier
  diferencia en la salida significa que su tarea *no* funciona.
colapri-arreglo.c: una implementacion de la colas de prioridad 
  en base a arreglos.  Usela!
colapri.h y colapri-arreglo.h: necesita incluir estos archivos
  para poder usar la cola de prioridad.
Makefile: Para que compile su tarea.

casilla.c: no incluido.  Ud. debe crearlo colocando ahi
  la implementacion de las funciones pedidas.

Note que una casilla es un caso particular del buffer del problema
del productor/consumidor.  La variante esta en que el buffer
de la casilla es de tamaño 0.

La cola de prioridades es generica y usa una estructura similar al
diccionario generico de la clase auxiliar 5.

Para usar la cola de prioridades:

#include "colapri.h"
#include "colapri-arreglo.h"

...

int compRec(void *a, void *b) {
  ... compara la prioridad de los elementos a y b en la cola ...
  return ...; // < 0 a tiene mejor prioridad que b, ==0 a y b con igual prio.
}

ColaPri cola= nuevaColaPriArreglo(100, compRec); // crea una cola de prioridad
cola->ops->agregar(cola, a); // agrega el objeto a a la cola
int tam= cola->ops->tamano(cola); // entrega cuantos objetos almacena la cola
void *b= cola->ops->extraer(cola); // extrae el objeto de mejor prioridad
