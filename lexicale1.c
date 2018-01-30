#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"
#define Taille // variable globale dont la taille du tableau de caracteres et de noms


// fonction permettant d'ajouter un caractere et de le relier avec son nom si variable ou fonction
void AddTableau( int tab[Taille]){
	int tabnom[Taille]; // tableau de noms de variables et de fonctions codées soit par 26 soit par 27
	int i, j=0;
	tab = (int *) realloc(tab, 1024); // modification de la taille du tableau de caractere tout en conservant le contenu initial
	for(i = 0; i< Taille ; i++){
		if( tab[i] == 26 || tab[i] == 27 ){
			tab[i] = tabnom[j];
			j++;
		}
	}
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
file = fopen("L.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF){
	    // appel à la fonction AddTbleau
	    if(i < Taille ){
			AddTableau(// j'ai un souci avec le type int du parametre??
		}
        if (isalpha(c)){
			puts("it's a letter(to buffer)");
			buffer[i]=c;
			i++;
		}
		else if (isdigit(c))
			puts("ENTIER");
		else if(c==32)
			puts("SPACE");
		else if(c==40){	//(
			printf("%s\n", buffer );
			puts("PARENTHESE_OUVRANTE");
			i=0;
			initBuffer(buffer);
		}
		else if(c==41){  //)
			printf("%s\n", buffer );
			i=0;
			initBuffer(buffer);
			puts("PARENTHESE_FERMANTE");
		}
		else if(c==36){ //$
			printf("%s\n", buffer );
			i=0;
			initBuffer(buffer);	
		}	
		else
			puts("Unknown character");
	}
    fclose(file);
}
return 0;
}
