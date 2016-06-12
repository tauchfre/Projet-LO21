#include "atomes.h"
#include "operateurs_instances.h"
#include <sstream>
#include <typeinfo>
void ListeAtomes::ajouterAtome(string key, const Litteral& L)
{
        ostringstream os;
        os << L;
        if(os.str()[0] == '[')
        {
            try{
            Litteral_programme& L_prog = dynamic_cast<Litteral_programme &>(L.copie());
            programmes.insert(  pair<string,Litteral_programme&>(key,L_prog));
            } catch(bad_cast& e) { throw ExceptionLitteral("Ajout dans un atome d'un litteral mal construit."); }
        }
        else
        {
            try{
            Litteral_calculable& L_calc = dynamic_cast<Litteral_calculable &>(L.copie());
            variables.insert(  pair<string,Litteral_calculable&>(key,L_calc));
            } catch(bad_cast& e) { throw ExceptionLitteral("Ajout dans un atome d'un litteral mal construit."); }
        }
}
TypeAtome ListeAtomes::atomeExiste(string key)
{
    if(programmes.find(key) != programmes.end())
        return progg;

    else if (variables.find(key) != variables.end())
        return var;

    else
        return NIL;
}
Litteral& ListeAtomes::traduireAtome(string str)
{
    TypeAtome existenceAtome = atomeExiste(str);
    if(existenceAtome == progg)
    {   Litteral_programme& P = programmes.find(str)->second;
        return P; }
    else if(existenceAtome == var)
    {
        Litteral_calculable& C = variables.find(str)->second;
        return C; }
    else
        return * new Litteral_expression(str);
}
ConteneurOperande* ListeAtomes::interpreter(string str)
{
    Litteral& L = traduireAtome(str);
    ConteneurOperande* res = new ConteneurOperande(L);
    return res;
}
