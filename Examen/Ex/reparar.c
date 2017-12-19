#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <setjmp.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

#include "reparar.h"
 
// Declare aca las variables globales que necesite
jmp_buf env;


// Declare aca otras funciones que necesite
void error(){longjmp(env,1);}

void reparar(Nodo **pa) {
	Nodo *t;
	if(sigsetjmp(env,1)!=0){
		*pa = NULL;
		return;
	}
	signal(SIGSEGV,error);
	t = *pa;
	char x = t->x;
	x+=1;
	if(t!=NULL){
		reparar(&(t->izq));
		reparar(&(t->der));
	}
}
