#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integral.h"



/* Programe aca la funcion integral */


typedef double (*Funcion)(void *p, double x);

double integral(Funcion f, void *p, double xi, double xf, int n){

	double h=(xf-xi)/n;

	//Sumatoria

	int k;
	double suma=0;
	double aux=0;
	for(k=1;k<n;k++){
		aux=xi+k*h;
		suma=suma+f(p,aux);
	}

	double out= h*(((f(p,xi)+f(p,xf))/2)+suma);

	return out;
}

