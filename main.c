#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symboles.h"
#include "yylex.h"
#include "premiers.h"
#include "suivants.h"
#include "util.h"
#include "affiche_arbre_abstrait.h"
#include "arbre_abstrait.h"

int main(void) {
    file = fopen("test/max.l", "r");
    lex();  	//on remplit le tableau des symboles
    initialise_premiers();
    initialise_suivants();
	uniteCourante = yylex();	//recuperer le premier symboles pour commencer l'analyse
	programme();
  return 0;
}
