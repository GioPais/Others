#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void line_analysis(FILE *in,char *izq,char *der,char *key,char *value){

	int i=1;
	char aux='a';
	int save=1;
	char buff[101];
	fread(buff,1,100,in);
	buff[100]='\0';
	//printf("%s",buff );
	for(i=0;i<10;i++){
		aux=buff[i];
		if(aux==' '){
			izq[i]='\0';
			save=0;
		}
		if(save==1){
			izq[i]=aux;	
		}
		
	}
	save=1;
	for(i=0;i<10;i++){
		aux=buff[i+10];
		if(aux==' '){
			der[i]='\0';
			save=0;
		}
		if(save==1){
			der[i]=aux;
		}
		
	}

	save=1;
	for(i=0;i<20;i++){
		aux=buff[i+20];
		if(aux==' '){
			key[i]='\0';
			save=0;
		}
		if(save==1){
			key[i]=aux;
		}
	}

	save=1;
	int count=0;
	for(i=0;i<60;i++){
		aux=buff[i+40];
		value[i]=aux;
		if(aux==' '){
			count=count+1;
		}
		else{
			count=0;
		}
		if(count ==2){
			value[i-1]='\0';		
		}
	}
	//value[i]='\0';

	if(ferror(in)){
		printf("ERROR!\n");
	}
}



int main(int argc, char **argv) {
	
	if (argc != 3){
		printf("Entrada invalida\n" );
		exit(1);
	}

	char *target=argv[2];
	FILE *in;
	
	if ((in= fopen(argv[1], "r"))==NULL) {
		fprintf(stderr, "No se puede leer '%s'\n", argv[1]);
		exit(1);
	}
	char izq[11];
	char der[11];
	char key[21];
	char value[60];

	line_analysis(in,izq,der,key,value);
	
	int condicion=1;
	int next_line=0;
	while(condicion){
		if(strcmp(target,key)==0){
			printf("%s\n",value);
			break;
		}
		if(strcmp(target,key)>0){
			next_line=atoi(der);
			next_line=next_line*100;
		}
		if(strcmp(target,key)<0){
			next_line=atoi(izq);
			next_line=next_line*100;
		}
		if(next_line<0){
			printf("palabra no encontrada\n");
			break;
		}

		fseek(in, next_line, SEEK_SET);
		line_analysis(in,izq,der,key,value);

	}
	fclose(in);

	return 0;
}