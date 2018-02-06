#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include "symboles.h"
#include "syntaxe.h"
int uniteCourante ; //variable globale 

int yylex(void);
extern char *yytext;

void EE(){
	if(uniteCourante == 2 ){
		uniteCourante = yylex() ; // fonction à trouver
		E();
	}
	else {
		if(uniteCourante == 0) {
			uniteCourante = yylex();
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
}

void T(){
	F();
	TT();
}
void E(){
	T();
	EE();
}

void TT(){
	if(uniteCourante == 2 ) {
		uniteCourante = yylex() ; // fonction à trouver
		T();
	}
	else {
		if(uniteCourante == 0) {
			uniteCourante = yylex();
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
}

void F(){
	if(uniteCourante == 6 ) {
		uniteCourante = yylex() ; // fonction à trouver
		E();
		
		if(uniteCourante == 7 ){
			uniteCourante = yylex() ; // fonction à trouver
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
	else {
		if(uniteCourante == 28) {
			uniteCourante = yylex();
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
}
 
int main() {  
  FILE *file;
  file = fopen("yyin.txt", "r");
  if(file == NULL){
    printf("impossible d'ouvrir le fichier");
    exit(1);
  }
  do {
    uniteCourante = yylex();  
    F();
  } while (uniteCourante != FIN);
  
  return 0;
}

