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
        map<QString,Litteral_calculable&> variables;
        map<QString,Litteral_programme&> programmes;
    public:
        TypeAtome atomeExiste(QString str);
        Litteral& traduireAtome(QString str);
        void ajouterAtome(QString key, const Litteral& L);
        ConteneurOperande** interpreter(QString str);
};
#endif // ATOMES_H_INCLUDED
