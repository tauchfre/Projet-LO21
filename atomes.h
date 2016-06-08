#ifndef ATOMES_H_INCLUDED
#define ATOMES_H_INCLUDED
#include "operateurs.h"
#include "litteraux.h"
#include <map>
using namespace std;

enum TypeAtome{var,prog,NIL};
class ListeAtomes
{
    private:
        map<string,Litteral_calculable&> variables;
        map<string,Litteral_programme&> programmes;
    public:
        TypeAtome atomeExiste(string str);
        Litteral& traduireAtome(string str);
        void ajouterAtome(string key, const Litteral& L);
        ConteneurOperande** interpreter(string str);
};
#endif // ATOMES_H_INCLUDED
