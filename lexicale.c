#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"

int symbolesArray[1024];    //tableau de unitees courantes 
int k=0;
FILE *file; 


/**set buffer array to 0**/
void initBuffer(char * buf){
    int i;
    for(i=0; i<1024; i++)
        buf[i]=0;
}

int yylex(){    //retourne unite courante a partir de tableau
    return symbolesArray[k++];
}

void lex(void){
    int c;
    int  i=0,
         j=0,
         isNumber=0;
	char buffer[1024];
    initBuffer(buffer);
    if (file) {
    while ((c = getc(file)) != EOF){
        if (isalpha(c)){	//adding alpha to buffer
            if(buffer[0]==0)	//if buffer is empty, set isNumber to 0
		isNumber=0;
            buffer[i]=c;
            i++;
	}
	else if (isdigit(c)){
            if(buffer[0]==0)	//buffer not empty, so isNumber is set, or it's not a number
		isNumber=1;
            buffer[i]=c;
            i++;
	}
	else if (c==95 ){	// _	//adding underscore to buffer
            if(buffer[0]==0)	//if buffer is empty, set isNumber to 0
		isNumber=0;
            buffer[i]=c;
            i++;
	}
	else if(c==43){	//	+
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
		if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
		}
		i=0;
		initBuffer(buffer);
            }
            puts("PLUS");
            symbolesArray[j++]=PLUS;
	}
	else if(c==45){	//	-
            if(buffer[0]!=0){
		//printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
		if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
		}
		i=0;
		initBuffer(buffer);
            }
            puts("MOINS");
            symbolesArray[j++]=MOINS;
	}
	else if(c==42){	//	*
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
		if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
		}
		i=0;
		initBuffer(buffer);
            }
            puts("FOIS");
            symbolesArray[j++]=FOIS;
        }
        else if(c==47){	//	/
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("DIVISION");
            symbolesArray[j++]=DIVISE;
        }
        else if(c==60){	//	<
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("INFERIEUR");
            symbolesArray[j++]=INFERIEUR;
        }
        else if(c==61){	//	=
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("EGAL");
            symbolesArray[j++]=EGAL;
        }
        else if(c==38){	//	&
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("ET");
            symbolesArray[j++]=ET;
        }
        else if(c==124){	//	|
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("OU");
            symbolesArray[j++]=OU;
        }
        else if(c==33){	//	!
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("NON");
            symbolesArray[j++]=NON;
        }
        else if(c==123){	//	{
            if(buffer[0]!=0){
                if(!strcmp(buffer, "alors" ) || !strcmp(buffer, "alors " )){
                    puts("ALORS");
                    symbolesArray[j++]=ALORS;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "sinon" ) || !strcmp(buffer, "sinon " )){
                    puts("SINON");
                    symbolesArray[j++]=SINON;
                    i=0;
                    initBuffer(buffer);
                }
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
            }
            puts("ACCOLADE_OUVRANTE");
            symbolesArray[j++]=ACCOLADE_OUVRANTE;
        }
        else if(c==125){	//	}
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("ACCOLADE_FERMANTE");
            symbolesArray[j++]=ACCOLADE_FERMANTE;
        }
        else if(c==59){	//	;
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("POINT_VIRGULE");
            symbolesArray[j++]=POINT_VIRGULE;
        }
        else if(c==44){	//	,
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("VIRGULE");
            symbolesArray[j++]=VIRGULE;
        } 
        else if(c==91){	//	,
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("CROCHET OUVRANT");
            symbolesArray[j++]=CROCHET_OUVRANT;
        } 
        else if(c==93){	//	,
            if(buffer[0]!=0){
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("CROCHET FERMANTE");
            symbolesArray[j++]=CROCHET_FERMANT;
        } 
        else if(c==32){ // espace
            if(buffer[0]!=0){
                if(!strcmp(buffer, "si" )){
                    puts("SI");
                    symbolesArray[j++]=SI;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "entier")){				
                    puts("ENTIER");
                    symbolesArray[j++]=ENTIER;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "retour" )){
                    puts("RETOUR");
                    symbolesArray[j++]=RETOUR;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "tantque" )){
                    puts("TANTQUE");
                    symbolesArray[j++]=TANTQUE;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "faire" )){
                    puts("FAIRE");
                    symbolesArray[j++]=FAIRE;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "alors" ) || !strcmp(buffer, "alors " )){
                    puts("ALORS");
                    symbolesArray[j++]=ALORS;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "sinon" ) || !strcmp(buffer, "sinon " )){
                    puts("SINON");
                    symbolesArray[j++]=SINON;
                    i=0;
                    initBuffer(buffer);
                }
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                i=0;
                initBuffer(buffer);
            }
        }
        else if(c==40){	//	(
            if(buffer[0]!=0){
                puts("ID_FCT");
                symbolesArray[j++]=ID_FCT;
                if( !strcmp(buffer, "lire") || !strcmp(buffer, "lire " )){
                    puts("LIRE");
                    symbolesArray[j++]=LIRE;
                }
                if(!strcmp(buffer, "ecrire" ) || !strcmp(buffer, "ecrire " )){
                    puts("ECRIRE");
                    symbolesArray[j++]=ECRIRE;
                }
                //printf("%s\n", buffer );	DATA STORAGE, FOR LATER USAGE
                i=0;
                initBuffer(buffer);
            }
            puts("PARENTHESE_OUVRANTE");
            symbolesArray[j++]=PARENTHESE_OUVRANTE;
        }
        else if(c==41){  //	)
            if(buffer[0]!=0){
                //printf("%s\n", buffer ); DATA STORAGE, FOR LATER USAGE
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                i=0;
                initBuffer(buffer);
            }
            puts("PARENTHESE_FERMANTE");
            symbolesArray[j++]=PARENTHESE_FERMANTE;
        }
        else if(c==36){ //	$
            if(buffer[0]!=0){
                if(!strcmp(buffer, "entier")){
                    puts("ENTIER");
                    symbolesArray[j++]=ENTIER;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "retour" )){
                    puts("RETOUR");
                    symbolesArray[j++]=RETOUR;
                    i=0;
                    initBuffer(buffer);
                }
                if(!strcmp(buffer, "si" )){
                    puts("SI");
                    symbolesArray[j++]=SI;
                    i=0;
                    initBuffer(buffer);
                }
                if(isNumber){
                    puts("NOMBRE");
                    symbolesArray[j++]=NOMBRE;
                    isNumber=0;
                }
                //printf("%s\n", buffer ); DATA STORAGE, FOR LATER USAGE
                i=0;
                initBuffer(buffer);	
            }
            puts("ID_VAR");
            symbolesArray[j++]=ID_VAR;
        }
    }
    symbolesArray[j++]=FIN;
    puts("FIN");
    fclose(file);
    }
}



int main(void) {
    int uniteCourante;
    file = fopen("max.l", "r");
    lex();  //on remplit le tableau
    do{
        uniteCourante = yylex();  //retourne unite courante
        printf("UniteCourante = %d\n",uniteCourante);
    }while(uniteCourante!=FIN);

    return 0;
}

