#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"
#define TAILLE 16 // variable globale dont la taille du tableau de caracteres et de noms


// fonction permettant d'ajouter un caractere et de le relier avec son nom si variable ou fonction
void AddTableau(int * tab){
	//int i, j=0;
	tab = (int *) realloc(tab, TAILLE * 2); // modification de la taille du tableau de caractere tout en conservant le contenu initial
	/**for(i = 0; i< TAILLE ; i++){
		if( tab[i] == 26 || tab[i] == 27 ){
			tab[i] = tabnom[j];
			j++;
		}
	}**/
}

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
file = fopen("L", "r");
if (file) {
    while ((c = getc(file)) != EOF){
		printf("%d\n",c);
	    // appel à la fonction AddTbleau
	    /**if(i > TAILLE-1 ){
			AddTableau(tabID);
		}**/
        if (isalpha(c)){
			//puts("it's a letter(to buffer)");
			buffer[i]=c;
			i++;
		}
		else if (isdigit(c))
			puts("NOMBRE");
		else if(c==32){
			if(!strcmp(buffer, "si " ))
				puts("SI");
		}
		else if(c==43){	//	+
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("PLUS");
		}
		else if(c==61){	//	=
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
			}
			puts("EGALE");
		}
		else if(c==123){	//	{
			if(buffer[0]!=0){
				printf("%s\n", buffer );
				i=0;
				initBuffer(buffer);
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
		else if(c==40){	//	(
			if(buffer[0]!=0){
				puts("ID_FCT");
				printf("%s\n", buffer );
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
				if(!strcmp(buffer, "entier"))
					puts("ENTIER");
				if(!strcmp(buffer, "retour" ))
					puts("RETOUR");
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
