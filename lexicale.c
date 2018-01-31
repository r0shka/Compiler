#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"

/**set buffer array to 0**/
void initBuffer(char * buf){
	int i;
	for(i=0; i<64; i++)
		buf[i]=0;
}

 
int main( void )
{
int c, 
	i=0;
	
char buffer[64];
initBuffer(buffer);
FILE *file;
file = fopen("max.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF){
	  
        if (isalpha(c)){
			buffer[i]=c;
			i++;
		}
		else if (c==95 ){
			buffer[i]=c;
			i++;
		}
		else if (isdigit(c)){
			buffer[i]=c;
			i++;
			puts("NOMBRE");
		}
		else if(c==43){	//	+
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("PLUS");
		}
		else if(c==45){	//	-
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("MOINS");
		}
		else if(c==42){	//	*
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("FOIS");
		}
		else if(c==47){	//	/
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("DIVISION");
		}
		else if(c==60){	//	<
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("INFERIEUR");
		}
		else if(c==61){	//	=
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("EGALE");
		}
		else if(c==38){	//	&
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("ET");
		}
		else if(c==124){	//	|
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("OU");
		}
		else if(c==33){	//	!
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("NON");
		}
		else if(c==123){	//	{
			if(buffer[0]!=0){
				if(!strcmp(buffer, "alors" ) || !strcmp(buffer, "alors " )){
					puts("ALORS");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "sinon" ) || !strcmp(buffer, "sinon " )){
					puts("SINON");
					i=0;
					initBuffer(buffer);
				}
			}
			puts("ACCOLADE_OUVRANTE");
		}
		else if(c==125){	//	}
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("ACCOLADE_FERMANTE");
		}
		else if(c==59){	//	;
			if(buffer[0]!=0){
				printf("%s\n", buffer );

				i=0;
				initBuffer(buffer);
			}
			puts("POINT_VIRGULE");
		}
		else if(c==44){	//	,
			if(buffer[0]!=0){
				printf("%s\n", buffer );

				i=0;
				initBuffer(buffer);
			}
			puts("VIRGULE");
		} 
		else if(c==91){	//	,
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("CROCHET OUVRANTE");
		} 
		else if(c==93){	//	,
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("CROCHET FERMANTE");
		} 
		else if(c==32){ // espace
			if(buffer[0]!=0){
				if(!strcmp(buffer, "si" )){
					puts("SI");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "entier")){				
					puts("ENTIER");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "retour" )){
					puts("RETOUR");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "tantque" )){
					puts("TANTQUE");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "faire" )){
					puts("FAIRE");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "alors" ) || !strcmp(buffer, "alors " )){
					puts("ALORS");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "sinon" ) || !strcmp(buffer, "sinon " )){
					puts("SINON");
					i=0;
					initBuffer(buffer);
				}
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
		}
		else if(c==40){	//	(
			if(buffer[0]!=0){
				puts("ID_FCT");
				if( !strcmp(buffer, "lire") || !strcmp(buffer, "lire " ))
					puts("LIRE");
				if(!strcmp(buffer, "ecrire" ) || !strcmp(buffer, "ecrire " ))
					puts("ECRIRE");
				//printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
				
			}
			puts("PARENTHESE_OUVRANTE");
		}
		else if(c==41){  //	)
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("PARENTHESE_FERMANTE");
		}
		else if(c==36){ //	$
			if(buffer[0]!=0){
				if(!strcmp(buffer, "entier")){
					puts("ENTIER");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "retour" )){
					puts("RETOUR");
					i=0;
					initBuffer(buffer);
				}
				if(!strcmp(buffer, "si" )){
					puts("SI");
					i=0;
					initBuffer(buffer);
				}
				//printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);	
			}
			puts("ID_VAR");
		}	
		/**else
			puts(" ");**/
	}
    fclose(file);
}
return 0;
}

