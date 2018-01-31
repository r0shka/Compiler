e
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"
#define TAILLE 16 // variable globale dont la taille du tableau de caracteres et de noms


/**fonction permettant d'ajouter un caractere et de le relier avec son nom si variable ou fonction
void AddTableau(int * tab){
	int i, j=0;
	tab = (int *) realloc(tab, TAILLE * 2); // modification de la taille du tableau de caractere tout en conservant le contenu initial
	for(i = 0; i< TAILLE ; i++){
		if( tab[i] == 26 || tab[i] == 27 ){
			tab[i] = tabnom[j];
			j++;
		}
	}
}**/

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
file = fopen("L.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF){
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
		/**else if(c==32)
			puts(" ");**/
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
		else if(c==44){	//	,
			if(buffer[0]!=0){
				printf("%s\n", buffer );

				i=0;
				initBuffer(buffer);
			}
			puts("VIRGULE");
		} 
		else if(c==32){ // espace
			if(!strcmp(buffer, "tantque" )){
				puts("TANTQUE");
				i=0;
				initBuffer(buffer);
			}
		}
		else if(c==32){ // espace
			if(!strcmp(buffer, "faire" )){
				puts("FAIRE");
				i=0;
				initBuffer(buffer);
			}
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

