
/* Cambie este tipo por la estructura de la casilla */
//typedef void *Casilla;
typedef struct {
	ColaPri msgs;
} Casilla;



/* Debe implementar estas funciones en el archivo casilla.c */
Casilla nuevaCasilla();
void enviar(Casilla c, void *msg, int pri);
void *recibir(Casilla c);

/* Esta funcion esta implementada en el archivo test-casilla.c */
void error(char *fmt, ...);

