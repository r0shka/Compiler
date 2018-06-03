#ifndef __ARBRE_ABSTRAIT__
#define __ARBRE_ABSTRAIT__

#include "syntabs.h"
#include <stdio.h>
#include <stdlib.h>
#include "premiers.h"
#include "suivants.h"
#include "symboles.h"
#include "yylex.h"
#include "util.h"
#include "affiche_arbre_abstrait.h"

FILE * fp;
FILE * mips;
FILE * LL;

n_prog  *programme();
n_l_dec *optDecVariables();
n_l_dec *listeDecFonctions();
n_l_dec *listeDecVariables();
n_dec 	*declarationVariable();
n_l_dec *listeDecVariablesBis();
n_exp *optTailleTableau();
n_dec   *declarationFonction();
n_l_dec *listeParam();
n_l_dec *optListeDecVariables();
n_instr *instructionBloc();
n_instr    *instruction();
n_instr    *instructionAffect();
n_instr    *instructionBloc();
n_l_instr  *listeInstructions();
n_instr    *instructionSi();
n_instr    *optSinon();
n_instr   *instructionTantque();
n_instr   *instructionAppel();
n_instr   *instructionRetour();
n_instr  *instructionEcriture();
n_instr  *instructionVide();
n_exp *expression();
n_exp *expressionBis( n_exp *herite );
n_exp *conjonction();
n_exp *conjonctionBis( n_exp *herite );
n_exp *comparaison();
n_exp *comparaisonBis( n_exp *herite );
n_exp *expArith();
n_exp *expArithBis( n_exp *herite );
n_exp *terme();
n_exp *termeBis( n_exp *herite );
n_exp *negation();
n_exp *facteur();
n_var *var();
n_var *optIndice();
n_appel *appelFct();
n_l_exp *listeExpressions();
n_l_exp *listeExpressionsBis();

#endif
