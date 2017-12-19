#include <stdio.h>
#include <stdlib.h>

#include "abb.h"

Nodo *abb(Nodo *a, int i, int j) {
  
  if (i>j)
  	return NULL;

  int index=(i+j)/2;
  if((i+j)%2!=0)
  	index+=1;
  a[index].izq = abb(a,i,index-1);
  a[index].der = abb(a,index+1,j);


  return a+index;

}
