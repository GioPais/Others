#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



typedef unsigned long long Set;

Set leer(Set fd, void *buf, int n) {
 	if (n == 0)
 		return 0;
 	do {
 		Set rc = read(fd, buf, n);
 		if (rc <= 0)
 			return 1; /* fracaso: error o fin del archivo/pipe/socket */
 		n -= rc; /* descontamos los bytes leídos */
 		buf = (char*)buf + rc; /* avanzamos el buffer */
 	} while (n > 0); /* mientras no leamos todo lo que esperamos */
 	return 0; /* exito */
}

Set buscar2(int a[], Set start, Set end, int n) {

	for (Set k= start; k<=end; k++) {
		// k es el mapa de bits para el subconjunto { a[i] | bit k i de k es 1 }
		long long sum= 0;
		for (int i= 0; i<n; i++) {
			if ( k & ((Set)1<<i) ){ // si bit k i de k es 1
				sum+= a[i];
			}

		}
		if (sum==0) { 		// éxito: el subconjunto suma 0
			return k;		// y el mapa de bits para el subconjunto es k
	} }
	return 0;				// no existe subconjunto que sume 0

}

Set buscar(int a[], int n) {

	int i;

  	pid_t children[8];
  	int fds[8][2];
  	
	Set comb= (1<<(n-1)<<1)-1; // 2 n -1: no de combinaciones

	Set combs[9];
	combs[0]=1;
	for (i = 1; i <= 8; i++) {
		combs[i]=(comb/8)*i;
	}
	Set out[8];
	

	for (i = 0; i < 8; i++) {
	    
	    if (pipe(fds[i]) != 0) {
	      perror("Can't pipe");
	      exit(1);
	    }


	    if ((children[i] = fork()) == 0) {
		    close(STDERR_FILENO);
		    //dup(fd[1]);
		    close(fds[i][0]);
		    //printf("Corriendo proceso: (%i)\n", i);
		    out[i]=buscar2(a,combs[i],combs[i+1],n);

		    write(fds[i][1], &out[i], sizeof(Set));
			close(fds[i][1]);
			exit(1);

	    }
	    else {
	      //close(fd[1]);
	    }
		//printf("termino iteracion: %i\n",i );
	}
	//printf("Termino for para calculos\n");
	
	for (i = 0; i < 8; i++) {
	    close(fds[i][1]);
	}	


	Set output = 0;
	int break_cond=0;
	for(i = 0; i < 8; i++) {
	    pid_t ready = waitpid(0, NULL, 0);
		for (int j = 0; j < 8; j++) {
			//Revisar que hijo es el que termino
			if (children[j] == ready) {
				leer(fds[j][0], &output, sizeof(Set));
				close(fds[j][0]);
				if (output != 0) {
					//Ya que se encontró solucion se mata al resto
					for (int k = 0; k < 8; k++) {
						kill(children[k], SIGTERM);
					}
					break_cond=1; 
				}
			}
		}
		if(break_cond==1)
			break;

	}

	if (break_cond==1){
		for (i = 0; i < 8; i++) {
	    	waitpid(children[i], NULL, 0);
		}	
	}

	if(output !=0){
		return output;
	}
	
	return 0;				// no existe subconjunto que sume 0
}