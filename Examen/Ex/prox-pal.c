#include <stdio.h>
#include <stdlib.h>

#include "prox-pal.h"

char *prox_pal(char **pfrase) {
  
  char *s = *pfrase;
  char *pal =s;
  
  if(*s=='\0'){
  	return NULL;
  }

  while(*s==' '){
  	pal++;
  	s++;
  }
  //printf("%c\n",*s );

  while(1){
  	//break;
  	if(*s=='\0'){
  		*pfrase = s;	
  		return pal;
  	}
  	if(*s!=' '){
  		s++;
  	}
  	else{
  		
  		*s='\0';
  		s++;
  		*pfrase = s;
  		return pal;
  	}
  }
  //*pfrase = s;
  return NULL;
}
