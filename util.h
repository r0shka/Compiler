#ifndef __UTIL__
#define __UTIL__

/*fonction pour mips*/
void parcours_dec();
void parcours_instr();
void parcours_prog();
void parcours_fonc();
void parcours_decFonc();
int parcours_exp(); 

/**arbre syntaxique**/
void indentLL();
void affiche_balise_ouvranteLL(const char *fct_, int trace_xml);
void affiche_balise_fermanteLL(const char *fct_, int trace_xml);
void affiche_texteLL(int type, char *texte_, int trace_xml);

char *duplique_chaine(char *s);
void warning(char *message);
void erreur(char *message);
void warning_1s(char *message, char *s);
void erreur_1s(char *message, char *s);
void affiche_balise_ouvrante(const char *fct_, int trace_xml);
void affiche_balise_fermante(const char *fct_, int trace_xml);
void affiche_element(char *fct_, char *texte_, int trace_xml);
//void affiche_texte(int type, char *texte_, int trace_xml);
void affiche_texte(char *texte_, int trace_abs);
void test_yylex_internal(FILE *yyin);
void nom_token( int token, char *nom, char *valeur );

#endif
