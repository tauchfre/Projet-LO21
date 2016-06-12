#ifndef QANALYSEUR
#define QANALYSEUR

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "analyseur.h"
#include "pile.h"
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include<QDialog>
#include<QEvent>
#include<QCheckBox>




class fenetreVariable : public QWidget{

    Q_OBJECT

    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QGridLayout* couche;
    QHBoxLayout* couche2;
    QPushButton *modifie;
    QPushButton *supprimer;


public:
    explicit fenetreVariable(QWidget *parent = 0);

public slots:
    void var_suppression();
    void var_modification();
    void quit();
};




class fenetreProgramme : public QWidget{

    Q_OBJECT

    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QGridLayout* couche;
    QHBoxLayout* couche2;
    QPushButton *modifie;
    QPushButton *supprimer;


public:
    explicit fenetreProgramme(QWidget *parent = 0);

public slots:

    void var_suppression();
    void var_modification();
    void quit();
};



class fenetreParametre : public QWidget{

    Q_OBJECT
    QCheckBox* cb1;
    QCheckBox* cb2;
    QVBoxLayout* couche;
    QPushButton* annuler;
    QPushButton* valider;
    bool *bip;
    bool *clavier;


public:
    explicit fenetreParametre(QWidget *parent = 0);

public slots:

    void quit();
};



class QComputer : public QWidget{

    Q_OBJECT
    QEvent *clavier;
    QMenuBar *menu;
    QAction *parametre;
    QAction *quitter;
    QAction *variable;
    QAction *programme;

    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QGridLayout* couche;
    QGridLayout* couche2;
    QVBoxLayout* grille1;
    QVBoxLayout* grille2;
    QVBoxLayout* grille3;
    QVBoxLayout* grille4;
    fenetreParametre* fenParametre;
    fenetreVariable* fenVariable;
    fenetreProgramme* fenProgramme;

    Computer* computer;
    QPushButton* b1;
    QPushButton* b2;
    QPushButton* b3;
    QPushButton* b4;
    QPushButton* b5;
    QPushButton* b6;
    QPushButton* b7;
    QPushButton* b8;
    QPushButton* b9;
    QPushButton* b0;
    QPushButton* additionner;
    QPushButton* soustraire;
    QPushButton* multiplier;
    QPushButton* diviser;
    QPushButton* point;
    QPushButton* dollar;
    QPushButton* entree;




public:
    explicit QComputer(QWidget *parent = 0);

public slots:
    void rafraichir();
    void CommandeSuivante();
    void clicked_b1();
    void clicked_b2();
    void clicked_b3();
    void clicked_b4();
    void clicked_b5();
    void clicked_b6();
    void clicked_b7();
    void clicked_b8();
    void clicked_b9();
    void clicked_b0();
    void clicked_add();
    void clicked_sous();
    void clicked_mult();
    void clicked_div();
    void clicked_doll();
    void clicked_point();
    void clicked_entree();
    void open_parametre();
    void open_programme();
    void open_variable();
    void quit();
};








#endif // QANALYSEUR

