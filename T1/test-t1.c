#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t1.h"

int main() {
  printf("Test de insert_bits\n");

  if (insertar_bits(0x2, 0, 1, 1)!= 5) {
    fprintf(stderr, "insertar_bits(0b0010, 0 , 0b1, 1) != 0b0101\n");
    exit(1);
  }

  if (insertar_bits(0x20000002, 31, 1, 1)!= 0xa0000002) {
    fprintf(stderr, "insertar_bits(0b0010...0010, 31 , 0b1, 1) != "
                    "0b1010...0010\n");
    exit(1);
  }

  if (insertar_bits(0x2d, 3, 0x0, 2)!=0xa5) {
    fprintf(stderr, "insertar_bits(0b10 1101, 3, 0b00, 2) != 0b1010 0101\n");
    exit(1);
  }

  if (insertar_bits(0x37, 0, 0x3, 3)!=0x1bb) {
    fprintf(stderr, "insertar_bits(0b11 0111, 0, 0b011, 3) != 0b1 1011 1011\n");
    exit(1);
  }

  if (insertar_bits(0x17, 2, 0x0e, 5)!=0x2bb) {
    fprintf(stderr, "insertar_bits(0b1 0111, 2, 0b01110, 5) es 0b10 1011 1011\n");
    exit(1);
  }

  printf("Test de eliminar_espacios\n");

  char s[]= "hola   que   tal";
  eliminar_espacios(s);
  if (strcmp(s,"hola que tal")!=0) {
    fprintf(stderr, "Resultado incorrecto: \"%s\"\n", s);
    exit(1);
  }

  char s2[]= "   hola que tal   ";
  eliminar_espacios(s2);
  if (strcmp(s2, " hola que tal ")!=0) {
    fprintf(stderr, "Resultado incorrecto: \"%s\"\n", s2);
    exit(1);
  }

  char s3[]= "     ";
  eliminar_espacios(s3);
  if (strcmp(s3, " ")!=0) {
    fprintf(stderr, "Resultado incorrecto: \"%s\"\n", s3);
    exit(1);
  }

  printf("Felicitaciones, todos los tests funcionan correctamente\n");
  return 0;
}
