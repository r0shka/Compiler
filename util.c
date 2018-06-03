#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboles.h"
#include "util.h"
//#include "ll1.h"
#include "arbre_abstrait.h"
#include "affiche_arbre_abstrait.h"

/*fonction pour mips*/
void parcours_dec(char *variable){
	fprintf (mips, "%s .space 4\n", variable);
}

void parcours_fonc(){
	fprintf (mips, ".text\n");
	fprintf (mips, "___start:\n");
	fprintf (mips, "jal	f_main\n");
	fprintf (mips, "li	$v0, 10\n");
	fprintf (mips, "syscall\n");		
}

void parcours_decFonc(char *variable){
	fprintf (mips, "f_%s:\n", variable);
	
}

void parcours_instr();

void parcours_prog(){
	fprintf (mips, ".data\n");
}

int parcours_exp(); 

//int yylex();

/*extern char *yytext;   // déclaré dans analyseur_lexical
extern int  yylineno;  // déclaré dans analyseur_lexical*/
int indent_xml = 0;
int indent_xmlLL = 0;
int indent_step = 1; // mettre à 0 pour ne pas indenter

/*******************************************************************************
 * Affiche le message d'alerte donné en paramètre, avec le numéro de ligne 
 *****************************************************************************
void warning(char *message) {
  fprintf (stderr, "WARNING ligne %d : ", yylineno);
  fprintf (stderr, "%s\n", message);
}
*/
/*******************************************************************************
 * Affiche le message d'erreur donné en paramètre, avec le numéro de ligne 
 *****************************************************************************
void erreur(char *message) {
  fprintf (stderr, "ERREUR ligne %d : ", yylineno);
  fprintf (stderr, "%s\n", message);
  exit(1);
}
*/
/*******************************************************************************
 * Affiche le message d'alerte donné en paramètre, avec le numéro de ligne.
 * Le message d'alerte peut contenir un %s variable, qui sera donné en 
 * argument
 *****************************************************************************
void warning_1s(char *message, char *s) {
  fprintf (stderr, "WARNING ligne %d : ", yylineno);
  fprintf( stderr, message, s );
  fprintf( stderr, "\n" );
}
*/
/*******************************************************************************
 * Affiche le message d'erreur donné en paramètre, avec le numéro de ligne.
 * Le message d'erreur peut contenir un %s variable, qui sera donné en 
 * argument s
 *****************************************************************************
void erreur_1s(char *message, char *s) {
  fprintf( stderr, "Ligne %d : ", yylineno );
  fprintf( stderr, message, s );
  fprintf( stderr, "\n" );
  exit(1);
}
*/
/** Arbre syntaxique fonctions**/

void indentLL() {
    int i;
    for( i = 0; i < indent_xmlLL; i++ ) {
      fprintf(LL, "  " );
    }    
}

void affiche_balise_ouvranteLL(const char *fct_, int trace_xml) {
  if( trace_xml ) {
    indentLL();
    indent_xmlLL += indent_step ;
	  fprintf (LL, "<%s>\n", fct_);
	}  
}

/*******************************************************************************
 * 
 ******************************************************************************/
void affiche_balise_fermanteLL(const char *fct_, int trace_xml) {
  if(trace_xml) {
    indent_xmlLL -= indent_step ;
    indentLL();
    fprintf (LL, "</%s>\n", fct_);
  }
}

void affiche_texteLL(int type, char *texte_, int trace_xml) {
  if(trace_xml) {
    indentLL();
    if(type==1)
    	fprintf (LL, "<id_fonction>%s</id_fonction>\n", texte_);
    if(type==2)
    	fprintf (LL, "<symbole>%s</symbole>\n", texte_);
    if(type==3)
    	fprintf (LL, "<mot_clef>%s</mot_clef>\n", texte_);
    if(type==4)
    	fprintf (LL, "<id_variable>$%s</id_variable>\n", texte_);
    if(type==5)
    	fprintf (LL, "<nombre>%s</nombre>\n", texte_);
  }
}




/*******************************************************************************
 * 
 ******************************************************************************/
char *duplique_chaine(char *src) {
  char *dest = malloc(sizeof(char) * strlen(src));
  strcpy(dest, src);
  return dest;
}

/*******************************************************************************
 * 
 ******************************************************************************/
void indent() {
    int i;
    for( i = 0; i < indent_xml; i++ ) {
      fprintf(fp, "  " );
    }    
}
/*******************************************************************************
 * 
 ******************************************************************************/
void affiche_balise_ouvrante(const char *fct_, int trace_xml) {
  if( trace_xml ) {
    indent();
    indent_xml += indent_step ;
	  fprintf (fp, "<%s>\n", fct_);
	}  
}

/*******************************************************************************
 * 
 ******************************************************************************/
void affiche_balise_fermante(const char *fct_, int trace_xml) {
  if(trace_xml) {
    indent_xml -= indent_step ;
    indent();
    fprintf (fp, "</%s>\n", fct_);
  }
}

/*******************************************************************************
 * 
 *****************************************************************************
void affiche_texte(int type, char *texte_, int trace_xml) {
  if(trace_xml) {
    indent();
    if(type==1)
    	fprintf (fp, "<id_fonction>%s</id_fonction>\n", texte_);
    if(type==2)
    	fprintf (fp, "<symbole>%s</symbole>\n", texte_);
    if(type==3)
    	fprintf (fp, "<mot_clef>%s</mot_clef>\n", texte_);
    if(type==4)
    	fprintf (fp, "<id_variable>%s</id_variable>\n", texte_);
  }
}
*/

void affiche_texte(char *texte_, int trace_abs){
	indent();
	if(trace_abs){
		fprintf(fp, "%s\n", texte_);
	}
}

/*******************************************************************************
 * 
 ******************************************************************************/
void affiche_xml_texte( char *texte_ ) {
  int i = 0;
  while( texte_[ i ] != '\0' ) {
    if( texte_[ i ] == '<' ) {
      fprintf( fp, "&lt;" );
    }
    else if( texte_[ i ] == '>' ) {
      fprintf( fp, "&gt;" );
    }
    else if( texte_[ i ] == '&' ) {
      fprintf( fp, "&amp;" );
    }
    else {
      //putchar( texte_[i] );
		fprintf (fp, "$%s", texte_);
		return;
    }
    i++;
  }
}

/*******************************************************************************
 * 
 ******************************************************************************/
void affiche_element(char *fct_, char *texte_, int trace_xml) {
  if(trace_xml) {
    indent();
    fprintf (fp, "<%s>", fct_ );
    affiche_xml_texte( texte_ );
    fprintf (fp, "</%s>\n", fct_ );
  }
}

/*******************************************************************************
 * Fonction auxiliaire appelée par l'analyseur syntaxique tout simplement pour 
 * afficher des messages d'erreur et l'arbre XML 
 *****************************************************************************
void nom_token( int token, char *nom, char *valeur ) {
  int i;    
  char *tableMotsClefs[] = {"si", "alors", "sinon", "tantque", "faire", "entier", "retour", "lire", "ecrire"};
  int codeMotClefs[] = {SI, ALORS, SINON, TANTQUE, FAIRE, ENTIER, RETOUR, LIRE, ECRIRE};
  int nbMotsClefs = 9;
  
  strcpy( nom, "symbole" );
  if(token == POINT_VIRGULE) strcpy( valeur, "POINT_VIRGULE");
  else if(token == PLUS) strcpy(valeur, "PLUS");
  else if(token == MOINS) strcpy(valeur, "MOINS");
  else if(token == FOIS) strcpy(valeur, "FOIS");
  else if(token == DIVISE) strcpy(valeur, "DIVISE");
  else if(token == PARENTHESE_OUVRANTE) strcpy(valeur, "PARENTHESE_OUVRANTE");
  else if(token == PARENTHESE_FERMANTE) strcpy(valeur, "PARENTHESE_FERMANTE");
  else if(token == CROCHET_OUVRANT) strcpy(valeur, "CROCHET_OUVRANT");
  else if(token == CROCHET_FERMANT) strcpy(valeur, "CROCHET_FERMANT");
  else if(token == ACCOLADE_OUVRANTE) strcpy(valeur, "ACCOLADE_OUVRANTE");
  else if(token == ACCOLADE_FERMANTE) strcpy(valeur, "ACCOLADE_FERMANTE");
  else if(token == EGAL) strcpy(valeur, "EGAL");
  else if(token == INFERIEUR) strcpy(valeur, "INFERIEUR");
  else if(token == ET) strcpy(valeur, "ET");
  else if(token == OU) strcpy(valeur, "OU");
  else if(token == NON) strcpy(valeur, "NON"); 
  else if(token == FIN) strcpy(valeur, "FIN");
  else if(token == VIRGULE) strcpy(valeur, "VIRGULE");

  else if( token == ID_VAR ) {
    strcpy( nom, "id_variable" );  
    strcpy( valeur, yytext );        
  }
  else if( token == ID_FCT ) {
    strcpy( nom, "id_fonction" );    
    strcpy( valeur, yytext );    
  }
  else if( token == NOMBRE ) {
    strcpy( nom, "nombre" );
    strcpy( valeur, yytext ); 
  }
  else {
    strcpy( nom, "mot_clef" );
    for(i=0; i < nbMotsClefs; i++){
      if( token ==  codeMotClefs[i] ){
        strcpy( valeur, tableMotsClefs[i] );
        break;
      }
    }
  }  
}
*/
/*******************************************************************************
 * Fonction auxiliaire appelée par le compilo en mode -l, pour tester l'analyseur
 * lexical et, étant donné un programme en entrée, afficher la liste des tokens.
 *****************************************************************************
void test_yylex_internal(FILE *yyin) {
  int uniteCourante;
  char nom[100];
  char valeur[100];  
  do {
    uniteCourante = yylex();  
    nom_token( uniteCourante, nom, valeur );
    printf("%s\t%s\t%s\n", yytext, nom, valeur);
  } while (uniteCourante != FIN);
}
*/
