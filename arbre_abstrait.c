#include "arbre_abstrait.h"
#include "tabsymboles.h"

int i=0, j=0;

int portee = P_VARIABLE_GLOBALE;
int adresseLocaleCourante=0;
int adresseArgumentCourant=0;
int nbArgument[100];
int haveArgument=0;
int isGlobal=1;		//detection de variables globale;

void initTab(){		//nombre de argument pour chaque fonction. Max 100 fonctions.
	int k;
	for(k=0; k<100; k++)
		nbArgument[k] = 0;
}



/*******************************OK*******************************************/
n_prog *programme() {

	fp = fopen ("treeAbs.xml", "w+");
	mips = fopen ("a.mips", "w+");
	LL = fopen ("treeLL.xml", "w+");
	initTab();
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	
	n_prog 	*$$ = NULL;
	n_l_dec *$2 = NULL;
	n_l_dec *$4 = NULL;
	
	if(est_premier(uniteCourante, _optDecVariables_) || est_premier(uniteCourante, _listeDecFonctions_) ||
		est_suivant(uniteCourante, _programme_)){
			parcours_prog();
			$2 = optDecVariables();
			parcours_fonc();
			$4 = listeDecFonctions();
			$$ = cree_n_prog( $2, $4 );
			affiche_n_prog($$);
			affiche_balise_fermanteLL(__FUNCTION__,1);
			fclose(fp);
			fclose(mips);
			fclose(LL);
			return $$;
	}
	else{
		printf("Expression mal formée\n");
		fclose(fp);
		exit(-1);
	}
}

/************************************************************************OK*/

n_l_dec *optDecVariables() {  // pas besoin de creer un noeud(voir max.asynt et max.xml)
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	n_l_dec *$$ = NULL;
	if(est_premier(uniteCourante, _listeDecVariables_)){
		$$ = listeDecVariables();
		isGlobal=0;
		if(uniteCourante == POINT_VIRGULE){
			affiche_texteLL(2, "POINT_VIRGULE", 1);
			uniteCourante = yylex();
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
	}
	else if(est_suivant(uniteCourante, _optDecVariables_)){
		isGlobal=0;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formée\n");
		exit(-1);
	}
}

/*************************OK******************************/

n_l_dec *listeDecVariables() {
	n_l_dec *$$ = NULL;
	n_dec *$2 = NULL;
	n_l_dec *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _declarationVariable_)){
		if(haveArgument) nbArgument[j]++;
		$2 = declarationVariable();
		$4 = listeDecVariablesBis();
		$$ = cree_n_l_dec($2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formée\n");
		exit(-1);
	}
}

/**************************OK*****************************************/

n_l_dec *listeDecVariablesBis(){
	n_l_dec *$$ = NULL;
	n_dec *$1 = NULL;
	n_l_dec *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == VIRGULE){
		affiche_texteLL(2, "VIRGULE", 1);
		uniteCourante = yylex();
		if(haveArgument) nbArgument[j]++;
		$1 = declarationVariable();
		$2 = listeDecVariablesBis();
		$$ = cree_n_l_dec($1, $2);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _listeDecVariablesBis_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal fomée\n");
		exit(-1);
	}
}

/************************A REVENIR***************************/

n_dec *declarationVariable(){ // fonction creant un noeud pour afficher la variable
	n_dec *$$ = NULL;
	n_exp *$2 = NULL;  //pour type de optTailleTableau
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == ENTIER){
		affiche_texteLL(3, "entier", 1);
		uniteCourante = yylex();
		if(uniteCourante == ID_VAR){
			char *variable = name[i++];
			affiche_texteLL(4, variable, 1);
			if(isGlobal){
				parcours_dec(variable);
			}
			uniteCourante = yylex();
			if(haveArgument){	// ajout d'argument a la table des symboles
				ajouteIdentificateur(variable, P_ARGUMENT, T_ENTIER, adresseArgumentCourant, 1);
				adresseArgumentCourant+=4;
			}
			else{	// ajout de variable a la table des symboles
				ajouteIdentificateur(variable, portee, T_ENTIER, adresseLocaleCourante, 1);
				adresseLocaleCourante+=4;
			}
			$2 = optTailleTableau(); 
			if( $2==NULL ){
				$$ = cree_n_dec_var( variable ); //affiche la variable en appelant le tableau name
			}
			else{
				$$ = cree_n_dec_tab(variable , $2->u.entier); // à revoir 
			}
			affiche_balise_fermanteLL(__FUNCTION__,1);
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
	return $$;
}

/*******************************TYPE A REVOIR ******************/

n_exp *optTailleTableau(){  //affiche probleme de type de optTailleTableu, mais pas besoin de creer un noeud
	n_exp *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == CROCHET_OUVRANT){
		affiche_texteLL(2, "CROCHET_OUVRANT", 1);
		uniteCourante = yylex();
		if(uniteCourante == NOMBRE){
			affiche_texteLL(5, name[i++], 1);	
			uniteCourante = yylex();
			if(	uniteCourante == CROCHET_FERMANT){
				affiche_texteLL(2, "CROCHET_FERMANT", 1);
				uniteCourante = yylex();
				affiche_balise_fermanteLL(__FUNCTION__,1);
				return $$;
			}
			else{
				exit(-1);
			}
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else if(est_suivant(uniteCourante, _optTailleTableau_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/***************************************************************OK**/

n_l_dec *listeDecFonctions(){
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	n_l_dec *$$ = NULL;
	n_dec *$2 = NULL;
	n_l_dec *$4 = NULL;
	if(est_premier(uniteCourante, _declarationFonction_)){
		$2 = declarationFonction();
		$4 = listeDecFonctions();
		$$ = cree_n_l_dec($2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(est_suivant(uniteCourante, _listeDecFonctions_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/*********************************************************************OK*/

n_dec *declarationFonction(){
	n_dec *$$  = NULL;
	n_l_dec *$2  = NULL;
	n_l_dec *$4 = NULL;
	n_instr *$5 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	char *fonction ; 	
	if(uniteCourante == ID_FCT){
		fonction = name[i++]; // name appelé pour donner le nom de la fonction
		affiche_texteLL(1, fonction, 1);
		/*if( rechercheDeclarative(fonction) >= 0 ) {	//teste la presence de la fonction avec le meme nom
			puts("ERROR : NAME ALREADY DECLARED");
			exit(-1);
		}*/
		entreeFonction();
		uniteCourante = yylex();
		ajouteIdentificateur(fonction, P_VARIABLE_GLOBALE, T_FONCTION, 0, 0);
		parcours_decFonc(fonction);
		$2 = listeParam();
		$4 = optDecVariables();
		$5 = instructionBloc();
		tabsymboles.base++;
		/*-on parcour la table sym, et ajoute le nombre de parametres a chaque fonction-*/
		for(int m = 0; m < tabsymboles.sommet; m++){		
			if(tabsymboles.tab[m].type == T_FONCTION)
				tabsymboles.tab[m].complement = nbArgument[m];
		}
		j++;
		affiche_balise_fermanteLL(__FUNCTION__,1);
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
	$$ = cree_n_dec_fonc( fonction, $2, $4, $5);
	afficheTabsymboles();
	adresseLocaleCourante=0;
	adresseArgumentCourant=0;
	sortieFonction();		
	return $$;
}

/********************************OK**************************************/

n_l_dec *listeParam(){ // ne cree pas de noeud
	n_l_dec *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == PARENTHESE_OUVRANTE){
		affiche_texteLL(2, "PARENTHESE_OUVRANTE", 1);
		uniteCourante = yylex();
		haveArgument = 1;
		$$ = optListeDecVariables();
		if(uniteCourante == PARENTHESE_FERMANTE){
			affiche_texteLL(2, "PARENTHESE_FERMANTE", 1);
			uniteCourante = yylex();
			haveArgument = 0;
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else {
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/**********************************OK****************************************/

n_l_dec *optListeDecVariables(){ // cree pas de noeud
	n_l_dec *$$ = NULL;
	//n_l_dec *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _listeDecVariables_)){
		$$ = listeDecVariables();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;	
	}
	else if(est_suivant(uniteCourante, _optListeDecVariables_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
	}
}

/****************************ok*****************************************/

n_instr *instruction(){ // pas besoin de creer un noeud
	n_instr *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _instructionAffect_)){
		$$ = instructionAffect();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionBloc_)){
		$$ = instructionBloc();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionSi_)){
		$$ = instructionSi();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionTantque_)){
		$$ = instructionTantque();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionAppel_)){
		$$ = instructionAppel();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionRetour_)){
		$$ = instructionRetour();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionEcriture_)){
		$$ = instructionEcriture();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_premier(uniteCourante, _instructionVide_)){
		$$ = instructionVide();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/*******************************ok****************************************/

n_instr *instructionAffect(){
	n_var *$2 = NULL;
	n_exp *$4 = NULL;
	n_instr *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _var_)){
		$2 = var();
		if(uniteCourante == EGAL){
			affiche_texteLL(2, "EGAL", 1);
			uniteCourante = yylex();
			$4 = expression();
			if(uniteCourante == POINT_VIRGULE){
				affiche_texteLL(2, "POINT_VIRGULE", 1);
				uniteCourante = yylex();
				$$ = cree_n_instr_affect($2, $4);
				affiche_balise_fermanteLL(__FUNCTION__,1);
				return $$;
			}
			else{
				printf("Expression mal formé");
				exit(-1);
			}
		}
		else{
			printf("Expression mal formé");
			exit(-1);
			}
	}
	else {
		printf("Expression mal formé17");
		exit(-1);
	}
}

/********************************ok**************************************/

n_instr *instructionBloc(){ // pas besoin de creer un noeud return la liste d'instructions
	n_instr *$$ = NULL;
	n_l_instr *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == ACCOLADE_OUVRANTE){
		affiche_texteLL(2, "ACCOLADE_OUVRANTE", 1);
		uniteCourante = yylex();
		$2 = listeInstructions();
		if(uniteCourante == ACCOLADE_FERMANTE){
			affiche_texteLL(2, "ACCOLADE_FERMANTE", 1);
			uniteCourante = yylex();
			$$ = cree_n_instr_bloc($2); // pas forcer à revoir
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/***********************************ok**************************/

n_l_instr *listeInstructions(){
	n_l_instr *$$ = NULL;
	n_instr *$2 = NULL;
	n_l_instr *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _instruction_)){
		$2 = instruction();
		$4 = listeInstructions();
		$$ = cree_n_l_instr($2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _listeInstructions_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé");
		exit(-1);
	}
}

/*****************************ok***************************************/

n_instr *instructionSi() {
	n_instr *$$ = NULL;
	n_exp *$2 = NULL;
	n_instr *$4 = NULL;
	n_instr *$5 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == SI){
		affiche_texteLL(3, "si", 1);
		uniteCourante = yylex(); //affiche consommer(SI);
		$2 = expression();
		if(uniteCourante == ALORS){
			affiche_texteLL(3, "alors", 1);
			uniteCourante = yylex(); //afficheconsommer( ALORS );
			$4 = instructionBloc();
			$5 = optSinon();
			$$ = cree_n_instr_si($2, $4, $5);
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
			printf("Expression mal formé\n");
			exit(-1);
	}
}

/*********************************************ok**********************/

n_instr *optSinon(){ // pas besoin de creer un noeud return just l'instrucionBloc
	n_instr *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante== SINON){
		affiche_texteLL(3, "sinon", 1);
		uniteCourante = yylex();
		$$ = instructionBloc();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _optSinon_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
			printf("Expression mal formé\n");
			exit(-1);
	}
}

/*********************************ok**************************************/

n_instr *instructionTantque(){
	n_instr *$$ = NULL;
	n_exp *$2 = NULL;
	n_instr *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == TANTQUE){
		affiche_texteLL(3, "tantque", 1);
		uniteCourante = yylex();
		$2 = expression();
		if(uniteCourante == FAIRE){ 
			affiche_texteLL(3, "faire", 1);
			uniteCourante = yylex();
			$4 = instructionBloc();
			$$ = cree_n_instr_tantque($2, $4);
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/***************************************ok****************************/

n_instr *instructionAppel(){
	n_instr *$$ =  NULL;
	n_appel *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _appelFct_)){
		$2 = appelFct();
		if(uniteCourante == POINT_VIRGULE){
			affiche_texteLL(2, "POINT_VIRGULE", 1);
			uniteCourante = yylex();
			$$ = cree_n_instr_appel( $2 );
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/*******************************ok*********************************/

n_instr *instructionRetour(){
	n_instr *$$ = NULL;
	n_exp *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == RETOUR){
		affiche_texteLL(3, "retour", 1);
		uniteCourante = yylex();
		$2 = expression();
		if(uniteCourante == POINT_VIRGULE){
			affiche_texteLL(2, "POINT_VIRGULE", 1);
			uniteCourante = yylex();
			$$ = cree_n_instr_retour( $2 );
			affiche_balise_fermanteLL(__FUNCTION__,1);
			//affiche_instr_retour($$);
			return $$;
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/*********************************ok******************************************/

n_instr *instructionEcriture(){
		n_instr *$$ = NULL;
		n_exp *$2 = NULL;
		affiche_balise_ouvranteLL(__FUNCTION__,1);
		if(uniteCourante == ECRIRE){
			affiche_texteLL(3, "ecrire", 1);
			uniteCourante = yylex();
			if(uniteCourante==PARENTHESE_OUVRANTE){
				affiche_texteLL(2, "PARENTHESE_OUVRANTE", 1);
				uniteCourante = yylex();
				$2 = expression();
				if(uniteCourante == PARENTHESE_FERMANTE){
					affiche_texteLL(2, "PARENTHESE_FERMANTE", 1);
					uniteCourante = yylex();
					if(uniteCourante == POINT_VIRGULE){
						affiche_texteLL(2, "POINT_VIRGULE", 1);
						uniteCourante = yylex();
						$$ = cree_n_instr_ecrire( $2 );
						affiche_balise_fermanteLL(__FUNCTION__,1);
						//affiche_instr_ecrire($$);
						return $$;
					}
					else{
						printf("Expression mal formé\n");
						exit(-1);
					}
				}
				else{
					printf("Expression mal formé\n");
					exit(-1);
				}
			}
			else{
				printf("Expression mal formé\n");
				exit(-1);
			}
		}
		else{
			printf("Expression mal formé\n");
			exit(-1);
		}
}

/****************************ok*******************************************/

n_instr *instructionVide(){ // pas besoin de creer un noeud d'autant plus que c vide
	n_instr *$$ = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == POINT_VIRGULE){
		affiche_texteLL(2, "POINT_VIRGULE", 1);
		uniteCourante = yylex();
		$$ = cree_n_instr_vide();
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/************************************ok**********************/

n_exp *expression(){
	n_exp *$$ = NULL;
	n_exp *fils = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _conjonction_)){
		fils = conjonction();
		$$ = expressionBis( fils );
		//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation"OU"
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf("Expression mal formé\n");
		exit(-1);
	}
}

/*******************************ok***************************************/

n_exp *expressionBis( n_exp *herite ){
	n_exp *$2 = NULL ;
	n_exp *$$ = NULL ;
	n_exp *herite_fils = NULL ;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == OU){
		affiche_texteLL(3, "ou", 1);
		uniteCourante = yylex();
		$2 = conjonction();
		herite_fils = cree_n_exp_op(ou, herite, $2);
		$$ = expressionBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _expressionBis_)){
		$$ = herite;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}

/******************************OK*************************************/

n_exp *conjonction(){ // pas besoin de creer un noeud, mais j'en doute donc cree pour l'instant 
	n_exp *$$ = NULL;
	n_exp *fils = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _comparaison_)){
		fils = comparaison();
		$$ = conjonctionBis( fils );
		//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation"ET"
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}

/*************************ok*****************************************/

n_exp *conjonctionBis( n_exp *herite ){
	n_exp *$2 = NULL;
	n_exp *$$ = NULL;
	n_exp *herite_fils = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == ET){
		affiche_texteLL(3, "et", 1);
		uniteCourante = yylex();
		$2 = comparaison();
		herite_fils = cree_n_exp_op(et, herite, $2);
		$$ = conjonctionBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _conjonctionBis_)){
		$$ = herite;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}

/*****************************ok***********************************/

n_exp *comparaison(){
	n_exp *$$ = NULL;
	n_exp *fils = NULL;
	//n_exp *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _expArith_)){
		fils = expArith();
		$$ = comparaisonBis(fils);
		//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation no defini
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/**************************ok***************************************/
n_exp *comparaisonBis( n_exp *herite ){
	n_exp *$2 = NULL;
	n_exp *$$ = NULL;
	n_exp *herite_fils = NULL;

	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == EGAL){
		affiche_texteLL(2, "EGAL", 1);
		uniteCourante = yylex();
		$2 = expArith();
		herite_fils = cree_n_exp_op(egal, herite, $2);
		$$ = comparaisonBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(uniteCourante == INFERIEUR){
		affiche_texteLL(2, "INFERIEUR", 1);
		uniteCourante = yylex();
		$2 = expArith();
		herite_fils = cree_n_exp_op(inf, herite, $2);
		$$ = comparaisonBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _comparaisonBis_)){
		$$ = herite;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*******************************OK**************************************/
n_exp *expArith(){
	n_exp *$$ = NULL;
	n_exp *fils = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _terme_)){
		fils = terme();
		$$ = expArithBis(fils);
		//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation no defini, peut generer une erreur
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/***********************************ok********************************/
n_exp *expArithBis( n_exp *herite ){
	n_exp *$2 = NULL ;
	n_exp *$$ = NULL ;
	n_exp *herite_fils = NULL ;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == PLUS){
		affiche_texteLL(2, "PLUS", 1);
		uniteCourante = yylex();
		$2 = terme();
		herite_fils = cree_n_exp_op(plus, herite, $2);
		$$ = expArithBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(uniteCourante == MOINS){
		affiche_texteLL(2, "MOINS", 1);
		uniteCourante = yylex();
		$2 = terme();
		herite_fils = cree_n_exp_op(moins, herite, $2);
		$$ = expArithBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _expArithBis_)){
		$$ = herite;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée42\n" );
		exit(-1);
	}
}
/****************************OK*************************************/
n_exp *terme(){
	n_exp *$$ = NULL;
	n_exp *fils = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _negation_)){
		fils = negation();
		$$ = termeBis(fils);
		//$$ = cree_n_exp_op(opExp, $2, $4);  //affiche operation no defini, peut generer une erreur
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*************************ok************************************************/
n_exp *termeBis( n_exp *herite ){
	n_exp *$2 = NULL;
	n_exp *$$ = NULL;
	n_exp *herite_fils = NULL ;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == FOIS){
		affiche_texteLL(2, "FOIS", 1);
		uniteCourante = yylex();
		$2 = negation();
		herite_fils = cree_n_exp_op(fois, herite, $2);
		$$ = termeBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(uniteCourante == DIVISE){
		affiche_texteLL(2, "DIVISE", 1);
		uniteCourante = yylex();
		$2 = negation();
		herite_fils = cree_n_exp_op(divise, herite, $2);
		$$ = termeBis( herite_fils );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _termeBis_)){
		$$ = herite;
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*************************A REVENIR GENERE UNE ERREUR DE SEGMENTATION************************************/
n_exp *negation(){
	n_exp *$$ = NULL;
	//n_exp *$2 = NULL;
	//n_exp *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == NON){
		affiche_texteLL(3, "non", 1);
		uniteCourante = yylex();
		$$ = negation();
		//$$ = cree_n_exp_op(non, $2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(est_premier(uniteCourante, _facteur_)){
		$$ = facteur();
		//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation no defini, peut generer une erreur
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else{
		printf( "Expression mal formée\n" );
	}
}/*******************************************************OK**************/
n_exp *facteur(){ 
	n_exp *$$ = NULL;
	n_appel *$2 = NULL;
	n_var *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == PARENTHESE_OUVRANTE){
		affiche_texteLL(2, "PARENTHESE_OUVRANTE", 1);
		uniteCourante = yylex();
		$$ = expression();
		if(uniteCourante == PARENTHESE_FERMANTE){
			affiche_texteLL(2, "PARENTHESE_FERMANTE", 1);
			uniteCourante = yylex();
			//$$ = cree_n_exp_op(opExp, $2, $4); //affiche operation no defini, peut generer une erreur
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			printf( "Expression mal formée\n" );
			exit(-1);
		}
	}
	else if(uniteCourante == NOMBRE){
		char *nombre = name[i++];
		int nb = atoi( nombre );
		affiche_texteLL(5, nombre, 1);
		uniteCourante = yylex();
		$$ = cree_n_exp_entier( nb ); //affiche NOMBRE en entier
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(est_premier(uniteCourante, _appelFct_)){
		$2 = appelFct();
		$$ = cree_n_exp_appel( $2 );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(est_premier(uniteCourante, _var_)){
		$4 = var();
		$$ = cree_n_exp_var( $4 );
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	if(uniteCourante == LIRE){ 
		affiche_texteLL(3, "lire", 1);
		uniteCourante = yylex();
		if(uniteCourante == PARENTHESE_OUVRANTE){
			affiche_texteLL(2, "PARENTHESE_OUVRANTE", 1);
			uniteCourante = yylex();
			if(uniteCourante == PARENTHESE_FERMANTE){
				affiche_texteLL(2, "PARENTHESE_FERMANTE", 1);
				uniteCourante = yylex();
				$$ = cree_n_exp_lire();
				affiche_balise_fermanteLL(__FUNCTION__,1);
				return $$;
			}
			else {
				printf( "Expression mal formée\n" );
				exit(-1);
			}
		}
		else {
			printf( "Expression mal formée\n" );
			exit(-1);
		}
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/**************************A REVENIR AU ELSE ***********************************/
n_var *var(){
	n_var *$$ = NULL;
	n_var *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == ID_VAR){
		char *variable = name[i++];
		affiche_texteLL(4, variable, 1);
		uniteCourante = yylex();
		$2 = optIndice();
		if( $2 == NULL ){
			$$ = cree_n_var_simple( variable );
			/***probleme de nom, donc ne marche pas***/
			/*printf("variable %s,i=%d,\n", variable,i);
			if( rechercheExecutable(variable ) < 0 ){
				printf("ERROR: VARIABLE %s NOT DECLARED, i=%d,\n", variable,i);
				exit(-1);
			}*/
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $2;
		}
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*************** A REVENIR SI TT MARCHE PAS BIEN car "variable" ********************/
n_var *optIndice(){ // pas besoin de creer un noeud
	n_var *$$ = NULL;
	n_exp *$2 = NULL;
	char *variable ;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == CROCHET_OUVRANT){
		affiche_texteLL(2, "CROCHET_OUVRANT", 1);
		uniteCourante = yylex();
		$2 = expression();
		$$ = cree_n_var_indicee(variable, $2);

		if(uniteCourante == CROCHET_FERMANT){
			affiche_texteLL(2, "CROCHET_FERMANT", 1);
			uniteCourante = yylex();
			affiche_balise_fermanteLL(__FUNCTION__,1);
			return $$;
		}
		else{
			//printf( "Expression mal formée\n" );
			exit(-1);
		}
	}
	else if(est_suivant(uniteCourante, _optIndice_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*********************ok********************************************/
n_appel *appelFct(){
	n_appel *$$ = NULL;
	n_l_exp *$2 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == ID_FCT){
		char *fonction = name[i++];
		affiche_texteLL(1, fonction, 1);
		uniteCourante = yylex();
		if(uniteCourante == PARENTHESE_OUVRANTE){
			affiche_texteLL(2, "PARENTHESE_OUVRANTE", 1);
			uniteCourante = yylex();
			$2 = listeExpressions();
			if(uniteCourante == PARENTHESE_FERMANTE){
				affiche_texteLL(2, "PARENTHESE_FERMANTE", 1);
				uniteCourante = yylex();
				/***probleme de nom, donc ne marche pas***/

				/*printf("variable %s,i=%d,\n", fonction,i);
				if( rechercheExecutable( fonction ) < 0 ){
					printf("ERROR: FUNCTION %s NOT DECLARED\n", fonction);
					exit(-1);
				}*/

				$$ = cree_n_appel(fonction, $2);
				affiche_balise_fermanteLL(__FUNCTION__,1);
				return $$;
			}
			else {
				printf( "Expression mal formée\n" );
				exit(-1);
			}
		}
		else {
			printf( "Expression mal formée\n" );
			exit(-1);
		}
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*************************ok*********************************/
n_l_exp *listeExpressions(){
	n_l_exp *$$ = NULL;
	n_exp *$2 = NULL;
	n_l_exp *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(est_premier(uniteCourante, _expression_)){
		$2 = expression();
		$4 = listeExpressionsBis();
		$$ = cree_n_l_exp( $2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _listeExpressions_)){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
/*****************************ok**************************************/
n_l_exp *listeExpressionsBis(){
	n_l_exp *$$ = NULL;
	n_exp *$2 = NULL ;
	n_l_exp *$4 = NULL;
	affiche_balise_ouvranteLL(__FUNCTION__,1);
	if(uniteCourante == VIRGULE){
		affiche_texteLL(2, "VIRGULE", 1);
		uniteCourante = yylex();
		$2 = expression();
		$4 = listeExpressionsBis();
		$$ = cree_n_l_exp( $2, $4);
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else if(est_suivant(uniteCourante, _listeExpressionsBis_ )){
		affiche_balise_fermanteLL(__FUNCTION__,1);
		return $$;
	}
	else {
		printf( "Expression mal formée\n" );
		exit(-1);
	}
}
