#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint insertar_bits(uint x, int pos, uint y, int len) {
  	
	uint mask1=0;
	
	int i;
	for(i=1;i<=pos;i++){
		mask1<<=1;
		mask1=mask1+1;
	}
	uint mask2=~mask1;
	
	uint xa = x&mask2;
	uint xb = x&mask1;

	xa<<=len;
	y<<=pos;
	uint out = xa+y+xb;
	return out;
}


void eliminar_espacios(char *s) {
	char *p= s;

	int size = strlen(p);
	//char *s2=malloc(size*sizeof(char));

	int i;
	int c=0,end=0;
	for(i=0;i<size;i++){
		
		if(*p==' '){

			
			if(c==0){
				*s=*p;

				c++;
				s++;
				p++;
				end++;
			}
			else{
				c++;
				p++;				
			}

		}
		else{
			*s=*p;
			c=0;
			s++;
			p++;
			end++;
		}


	}
	*s='\0';
	for(i=0; i < end; i++){
		s--;
	}
	//s=s2;
  
}
