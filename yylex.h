#ifndef __YYLEX__
#define __YYLEX__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"

int symbolesArray[1024];    //tableau de unitees courantes
char name[1024][64];				//tableau des noms de fonctions / variables 
FILE *file; 
int nameCounter;

void initBuffer(char * buf);
int yylex();
void lex(void);

#endif

