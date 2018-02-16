#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include "symboles.h"
#include "syntaxe.h"
#include "lexicale.c"
int uniteCourante ; //variable globale 
int compteur = 0;

void EE(){
	if(uniteCourante == PLUS ){
		uniteCourante = symbolesArray ; // fonction à trouver
		E();
	}
	else {
		if(uniteCourante == EPSILON) {
			//uniteCourante = yylex();
			return;
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
	if(uniteCourante == FOIS) {
		uniteCourante = yylex() ; // fonction à trouver
		T();
	}
	else {
		if(uniteCourante == EPSILON) {
			//uniteCourante = yylex();
			return;
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
}

void F(){
	if(uniteCourante == PARENTHESE_OUVRANTE) {
		uniteCourante = symbolesArray[compteur++]; // fonction à trouver
		E();
		if(uniteCourante == PARENTHESE_FERMANTE ){
			uniteCourante = symbolesArray[compteur] ; // fonction à trouver
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
	else {
		if(uniteCourante == NOMBRE) {
			uniteCourante = symbolesArray[compteur];
		}
		else {
			printf("Erreur de syntaxe");
			exit(-1);
		}
	}
	compteur++;
}
 
int main() {  
 // initBuffer(symbolesArray);
  FILE *file;
  file = fopen("yyin.txt", "r");
  if(file == NULL){
    printf("impossible d'ouvrir le fichier");
    exit(1);
  }
  lexical(file);
  do {
    uniteCourante = symbolesArray[compteur++];  
    F();
  } while (uniteCourante != 0 );

  printf("succes\n");
  
  return 0;
}

