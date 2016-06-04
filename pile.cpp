#include "pile.h"
#include "litteraux.h"



void Pile::agrandissement(){
    Litteral **newtab = new Litteral*[(tailleMax +1)*2];
    std::memcpy(newtab,litteraux,taille*sizeof(Litteral*));
	Litteral**  old=litteraux;
	litteraux=newtab;
	tailleMax=(tailleMax+1)*2;
	delete old;

}


void Pile::afficher()const{
	//system("cls");
	cout<<"********************************************* \n";
	//cout<<"M : "<<message<<"\n";
	cout <<"\n";
	cout<<"            Entrez votre commande" <<"\n \n";
	cout<<"---------------------------------------------\n";
	if(taille >0){
	for(int i = taille-1; i>=0; i--) {

    cout << *litteraux[i]<<"\n";
	}
	}
	cout<<"---------------------------------------------\n";
}

// METHODES DE LA CLASSE PILE
/*
void Pile::afficher() const
{
    if(taille > 0)
    {
        cout << "Pile :" << endl;
        for(int i = taille-1; i>=0; i--) // On affiche à l'envers !
        {
            cout << ">" << *litteraux[i];
            cout << endl;
        }
    }
}
*/

void Pile::push(Litteral& L)
{

    if(taille < tailleMax)
    {
        //litteraux[taille] = &(L.copie());
        litteraux[taille] = &(L.copie());
        taille++;

    }
    else

        agrandissement();
}
Litteral& Pile::pop()
{
    if(taille>0)
    {
        taille--;
        return *litteraux[taille];
    }
    else
        throw ExceptionPile("Pas d'élement à dépiler");

}
Pile::Pile(const Pile& P) : litteraux(new Litteral*[P.getTailleMax()]),tailleMax(P.getTailleMax()),taille(0)
{
    P.copierDans(*this);
}
void Pile::copierDans(Pile& P) const
{
    for(int i = 0; i<taille; i++) // On parcours dans l'ordre d'ajout du plus vieux au plus récent
    {
        P.push(*litteraux[i]);
    }
}
