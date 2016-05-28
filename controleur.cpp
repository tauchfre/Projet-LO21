#include "controleur.h"
/*
bool estUnOperateurNumerique(const string& s){
	if (s=="+") return true;
	if (s=="-") return true;
	if (s=="*") return true;
	if (s=="/") return true;
	if (s=="$") return true;

	if (s=="DIV"||s="div") return true;
	if (s=="MOD"||s="mod") return true;
	if (s=="POW"||s="pow") return true;
	if (s=="NEG"||s="neg") return true;
	if (s=="SIN"||s="sin") return true;
	if (s=="COS"||s="cos") return true;
	if (s=="TAN"||s="tan") return true;
	if (s=="SQRT"||s="sqrt") return true;
	if (s=="EXP"||s="exp") return true;
	if (s=="LN"||s="ln") return true;
	if (s=="NUM"||s="num") return true;
	if (s=="DEN"||s="den") return true;
	if (s=="RE"||s="re") return true;
	if (s=="IM"||s="im") return true;
	if (s=="ARG"||s="arg") return true;
    if (s=="NORM"||s="norm") return true;
	if (s=="ARCSIN"||s="arcsin") return true;
	if (s=="ARCCOS"||s="arccos") return true;
	if (s=="ARCTAN"||s="arctan") return true;
	return false;
}

bool estUnOperateurLogique(const string& s){
	if (s=="=") return true;
	if (s=="!=") return true;
	if (s=="=<") return true;
	if (s==">=") return true;
	if (s=="<") return true;
	if (s==">") return true;
	if (s=="AND"||s=="and") return true;
	if (s=="OR"||s=="or") return true;
	if (s=="NOT"|| s=="not") return true;
	return false;
}

bool estUneLitteraleNumerique(const string& s){
	if (s=="+") return true;
	return false;
}
bool estUneLiteraleComplexe(const string& s){
	if (s=="+") return true;
	return false;
}

bool estUnNombre(const string& s){
	unsigned int i=0;
	//for(i=0; i<s.size(); i++)
		//if (s[i]<'0' || s[i]>'9') return false;
	for(string::const_iterator it=s.begin(); it!=s.end(); ++it)
		if (*it<'0' || *it>'9') return false;
	return true;
}

bool estUneLitteraleAtome(const string& s){
	if (s=="+") return true;
	return false;
}
bool estUneLitteraleExpression(const string& s){
	if (s=="+") return true;
	return false;
}

bool estUneLitteraleProgramme(const string& s){
	if (s=="+") return true;
	return false;
}

bool estUnNombre(const string& s){
	unsigned int i=0;
	//for(i=0; i<s.size(); i++)
		//if (s[i]<'0' || s[i]>'9') return false;
	for(string::const_iterator it=s.begin(); it!=s.end(); ++it)
		if (*it<'0' || *it>'9') return false;
	return true;
}


void Controleur::commande(const string& c){
	if (estUneLitteraleNumerique(c)){
		pileAff.push(pileMng.addLitteral(atoi(c.c_str())));
	}else{

		if (estUnOperateurNumerique(c)){
			if (labAff.taille()>=2) {
				int v2=labAff.top().getValue();
				labMng.removeLabel(labAff.top());
				labAff.pop();
				int v1=labAff.top().getValue();
				labMng.removeLabel(labAff.top());
				labAff.pop();

				int res;
				if (c=="+") res=v1+v2;
				if (c=="-") res=v1-v2;
				if (c=="*") res=v1*v2;
				if (c=="/") {
					if (v2!=0) 	res=v1/v2;
					else{
						labAff.setMessage("Erreur : division par zero");
						// restauration de la pile
						pileAff.push(pileMng.addLabel(v1));
						res=v2;
					}
				}
				Label& e=labMng.addLabel(res);
				labAff.push(e);
			}else{
				labAff.setMessage("Erreur : pas assez d'arguments");
			}
		}else labAff.setMessage("Erreur : commande inconnue");
	}
}

void Controleur::executer(){
	string c;
	do {
		pileAff.affiche();
		cout<<"?-";
		cin>>c;
		if (c!="Q") commande(c);
	}while(c!="Q");
}
*/
