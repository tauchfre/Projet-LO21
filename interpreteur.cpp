#include "interpreteur.h"
#include <map>



///------------------------ Mapage des operateur biaire---------------------------------------------
/*
std::map<string, unsigned int> map_operateur_binaire;
map_operateur_binaire["+"] = 1;
*/
///--------------------------------- Operateur------------------------------------------------------


using namespace std;
bool estUnOperateurNumerique(string& s){
	if (s=="+") return true;
	if (s=="-") return true;
	if (s=="*") return true;
	if (s=="/") return true;
	if (s=="$") return true;
	if (s=="div") return true;
	if (s=="mod") return true;
	if (s=="pow") return true;
	if (s=="neg") return true;
	if (s=="sin") return true;
	if (s=="cos") return true;
	if (s=="tan") return true;
	if (s=="sqrt") return true;
	if (s=="exp") return true;
	if (s=="ln") return true;
	if (s=="num") return true;
	if (s=="den") return true;
	if (s=="re") return true;
	if (s=="im") return true;
	if (s=="arg") return true;
    if (s=="norm") return true;
	if (s=="arcsin") return true;
	if (s=="arccos") return true;
	if (s=="arctan") return true;
	return false;
    }

bool estUnOperateurLogique(const string& s){
	if (s=="=") return true;
	if (s=="!=") return true;
	if (s=="=<") return true;
	if (s==">=") return true;
	if (s=="<") return true;
	if (s==">") return true;
	if (s=="and") return true;
	if (s=="or") return true;
	if ( s=="not") return true;
	return false;
}

bool estUnOperateurExp(const string& s){
	if (s=="EVAL") return true;
	return false;
}

bool estUnOperateurManipPile(const string& s){
	if (s=="dup") return true;
	if (s=="drop") return true;
	if (s=="swap") return true;
	if (s=="lastop") return true;
	if (s=="lastargs") return true;
	if (s=="undo") return true;
	if (s=="redo") return true;
	if (s=="clear") return true;
	return false;
}

///----------------------------------------Litterale----------------------------------------------
bool estUneLitteraleComplexe(const string& s){
	if ((s.find("$")!=-1)&& s.size()>1) return true;
	return false;
}

bool estUneLitteraleRationnelle(const string& s){
	if ((s.find_first_of("/")!=-1)&& s.size()>1) return true;
	return false;
}
bool estUneLitteraleReel(const string& s){
	if ((s.find_first_of(".")!=-1)&& s.size()>1) return true;
	return false;
}

bool estUneLitteraleEntiere(const string& s){
	int i;
	for(i = 0; i< s.size(); i++)
    {
        if (s[i]>'9'||s[i]<'0') return false;
    }

	return true;
}



///--------------------------------------Interpreteur-------------------------------------------------
int Interpreteur::setType(){
    if(estUnOperateurNumerique(commande)){type = "OperateurNumerique";return 1;}
    if(estUnOperateurLogique(commande)){type = "OperateurLogique";return 1;}
    if(estUnOperateurExp(commande)){type = "OperateurExp";return 1;}
    if(estUnOperateurManipPile(commande)){type = "OperateurManipPile";return 1;}
    if(estUneLitteraleComplexe(commande)){type = "LitteraleComplexe";return 1;}


    if(estUneLitteraleRationnelle(commande)){type = "LitteraleRationelle";return 1;}
    if(estUneLitteraleReel(commande)){type = "LitteraleReel";return 1;}
    if(estUneLitteraleEntiere(commande)){type = "LitteraleEntiere";return 1;}
    return 0;
}

string Interpreteur::estUn() const{

    return type;

}
