#ifndef INTERPRETEUR_H_INCLUDED
#define INTERPRETEUR_H_INCLUDED
#include <cstring>
#include <iostream>

using namespace std;
class Interpreteur {
    string commande;
    string type;
public:
    void setCommande(string com){commande = com;}
    int setType();
    string estUn()const;

};

#endif // INTERPRETEUR_H_INCLUDED
