#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "reserva.h"

/* Implemente aca las funciones reservar y liberar */
//void inicializar();

int libres[5]={5,4,3,2,1};
char nombres[5][100];
pthread_mutex_t mutex;
pthread_cond_t cond;


void update(){

	int i=0;
	int space=0;
	int j=0;
	for(i=0;i<5;i++){
		
		for(j=i;j<5;j++){

			if (libres[j]==0){
				break;
			}
			else{
				space=space+1;
			}
		}

		libres[i]=space;
		space=0;
	}
}

int reservar(char *nom, int k){
	
	pthread_mutex_lock(&mutex);
	//printf("|%i",libres[0]);
	//printf("|%i",libres[1]);
	//printf("|%i",libres[2]);
	//printf("|%i",libres[3]);
	//printf("|%i|\n",libres[4]);

	while(1){
		int i=0;
		for (i=0;i<5;i++){
			if(libres[i]>=k){
				int j=0;
				for(j=0;j<k;j++){
					libres[i+j]=0;
					strcpy(nombres[i+j],nom);
				}

				update();

				printf("|%i",libres[0]);
				printf("|%i",libres[1]);
				printf("|%i",libres[2]);
				printf("|%i",libres[3]);
				printf("|%i|\n",libres[4]);

				printf("|%s",nombres[0]);
				printf("|%s",nombres[1]);
				printf("|%s",nombres[2]);
				printf("|%s",nombres[3]);
				printf("|%s|\n",nombres[4]);

				pthread_mutex_unlock(&mutex);
				return i;
			}
		}
		//No se encontró espacio
		pthread_cond_wait(&cond, &mutex);
	}

				
}


void liberar(char *nom){

	//Clear
	int i=0;
	for(i=0;i<5;i++){
		if(strcmp(nombres[i],nom)==0){
			*nombres[i] ='\0';
			libres[i]=1;
		}
	}

	update();
	printf("|%i",libres[0]);
	printf("|%i",libres[1]);
	printf("|%i",libres[2]);
	printf("|%i",libres[3]);
	printf("|%i|\n",libres[4]);

	printf("|%s",nombres[0]);
	printf("|%s",nombres[1]);
	printf("|%s",nombres[2]);
	printf("|%s",nombres[3]);
	printf("|%s|\n",nombres[4]);

	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}
