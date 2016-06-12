#include "qanalyseur.h"
#include "analyseur.h"

QComputer::QComputer(QWidget* parent): QWidget(parent)
{

    // Create the object pointed by the class attributes
    //pile = new Pile;
    menu = new QMenuBar(this);

    parametre = new QAction(menu);
    quitter = new QAction;
    variable = new QAction;
    programme = new QAction;


    menu->connect(parametre, SIGNAL(triggered(bool)), this , SLOT(open_parametre()));
    menu->addMenu("Paramètres")->addAction(parametre);

    menu->connect(variable, SIGNAL(triggered(bool)), this , SLOT(open_variable()));
    menu->addMenu("Gestion des Variables")->addAction(variable);

    menu->connect(programme, SIGNAL(triggered(bool)), this , SLOT(open_programme()));
    menu->addMenu("Gestion des Programme")->addAction(programme);

    menu->connect(quitter, SIGNAL(triggered(bool)), this , SLOT(quit()));
    menu->addMenu("Quitter")->addAction(quitter);



    computer = new Computer;

    computer->setNbAfficher(10);
    message=new QLineEdit(this);
    vuePile=new QTableWidget(computer->getNbAfficher(),1,this); // 1 colonne
    commande=new QLineEdit(this);
    couche = new QGridLayout(this);
    couche2 = new QGridLayout(this);
    grille1 = new QVBoxLayout(this);
    grille2 = new QVBoxLayout(this);
    grille3 = new QVBoxLayout(this);
    grille4 = new QVBoxLayout(this);

    b1 = new  QPushButton("1", this);
    b2 = new  QPushButton("2", this);
    b3 = new  QPushButton("3", this);
    b4 = new  QPushButton("4", this);
    b5 = new  QPushButton("5", this);
    b6 = new  QPushButton("6", this);
    b7 = new  QPushButton("7", this);
    b8 = new  QPushButton("8", this);
    b9 = new  QPushButton("9", this);
    b0 = new  QPushButton("0", this);
    additionner = new  QPushButton("+", this);
    soustraire = new  QPushButton("-", this);
    multiplier = new  QPushButton("*", this);
    diviser = new  QPushButton("/", this);
    point = new  QPushButton(".", this);
    dollar = new  QPushButton("$", this);
    entree = new QPushButton("Enter", this);



    // On positionne les objets dans la fenetre.
	
    grille1->addWidget(b7);
    grille1->addWidget(b4);
    grille1->addWidget(b1);
    grille1->addWidget(dollar);
    setLayout(grille1);

    grille2->addWidget(b8);
    grille2->addWidget(b5);
    grille2->addWidget(b2);
    grille2->addWidget(b0);
    setLayout(grille2);

    grille3->addWidget(b9);
    grille3->addWidget(b6);
    grille3->addWidget(b3);
    grille3->addWidget(point);
    setLayout(grille3);

    grille4->addWidget(additionner);
    grille4->addWidget(soustraire);
    grille4->addWidget(multiplier);
    grille4->addWidget(diviser);
    setLayout(grille4);

    couche->addWidget(menu,0,0);
    couche->addWidget(message,1,0);
    couche->addWidget(vuePile,2,0);
    couche->addWidget(commande,3,0) ;
    couche->addLayout(couche2,4,0);
    couche2->addWidget(entree,5,0,1,4);

    setLayout(couche);

    couche2->addLayout(grille1,0,0);
    couche2->addLayout(grille2,0,1);
    couche2->addLayout(grille3,0,2);
    couche2->addLayout(grille4,0,3);

    setLayout(couche2);


    // On ajoute le titre de la fenetre 
    this->setWindowTitle(QString("UTComputer"));
	
    // On definit la couleur des messages 
	
    message->setStyleSheet("background: white; color: black");
    message->setReadOnly(true);
    // Finish up the appearance of the object pointed by vuePile.
    // background
    vuePile->setStyleSheet("background: white; color: black");
    // foreground
    vuePile->verticalHeader()->setStyleSheet("color: black");
    // inhibit modification
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // make invisible the column table.
    vuePile->horizontalHeader()->setVisible(false);
    // adjust automatically the window's width.
    vuePile->horizontalHeader()->setStretchLastSection(true);

    //  create a list of tables "i:" for each line
    // and the items of each list.
    QStringList numberList;
  for(unsigned int i=computer->getNbAfficher(); i>0; i--) {
        QString str= QString::number(i);
        str+=" :";
        numberList<<str;
        // creation of the item of each line initialized with an empty chain (chaine vide).
        vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
    }
    // print the label list on a vertial header.
    vuePile->setVerticalHeaderLabels(numberList);
    // fixed width as a function of the number of items to print
    vuePile->setFixedHeight(computer->getNbAfficher()*vuePile->rowHeight(0)+2);
	


    // connections
    connect(computer,SIGNAL(modificationEtat()),this,SLOT(rafraichir()));
    connect(commande,SIGNAL(returnPressed()),this,SLOT(CommandeSuivante()));
    connect(b0,SIGNAL(clicked(bool)),this,SLOT(clicked_b0()));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(clicked_b1()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(clicked_b2()));
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(clicked_b3()));
    connect(b4,SIGNAL(clicked(bool)),this,SLOT(clicked_b4()));
    connect(b5,SIGNAL(clicked(bool)),this,SLOT(clicked_b5()));
    connect(b6,SIGNAL(clicked(bool)),this,SLOT(clicked_b6()));
    connect(b7,SIGNAL(clicked(bool)),this,SLOT(clicked_b7()));
    connect(b8,SIGNAL(clicked(bool)),this,SLOT(clicked_b8()));
    connect(b9,SIGNAL(clicked(bool)),this,SLOT(clicked_b9()));
    connect(additionner,SIGNAL(clicked(bool)),this,SLOT(clicked_add()));
    connect(soustraire,SIGNAL(clicked(bool)),this,SLOT(clicked_sous()));
    connect(diviser,SIGNAL(clicked(bool)),this,SLOT(clicked_div()));
    connect(multiplier,SIGNAL(clicked(bool)),this,SLOT(clicked_mult()));
    connect(point,SIGNAL(clicked(bool)),this,SLOT(clicked_point()));
    connect(dollar,SIGNAL(clicked(bool)),this,SLOT(clicked_doll()));
    connect(entree,SIGNAL(clicked(bool)),this,SLOT(clicked_entree()));
	
    // Premier message 
    computer->getAnalyseur().setMessage("Bienvenue dans l'application UTComputer!");
    message->setText(computer->getAnalyseur().getMessage());
    // Give the command bar some focus.
    commande->setFocus(Qt::OtherFocusReason);
}
void QComputer::rafraichir(){
    // the message

    message->setText(computer->getAnalyseur().getMessage());
    int nb=0;
    // On vide la Pile de Qt
    for( int i=0; i<computer->getNbAfficher(); i++)
    {
        vuePile->item(i,0)->setText("");

    }
    // Puis on la met à jour avec la Pile Actuelle

    ostringstream os;
    QString qs;
      for(Pile::iterator it=computer->getPileActuelle().begin(); it!=computer->getPileActuelle().end() && nb<computer->getNbAfficher(); ++it, nb++)
    {
        os<<(*it);
        qs = QString::fromStdString((os.str()));
        os.str("");
        os.clear();
        vuePile->item(computer->getNbAfficher()-1-nb,0)->setText(qs);

    }

}

void QComputer::CommandeSuivante(){
    // On recupere le texte de la barre de commande 
    QString c=commande->text();

    QTextStream stream(&c);
    QString com;
    do {
        stream>>com; // element extraction
        // send the command to the controller
        if (com!="") computer->effectuer(com);
    }while (com!="");
	// On effectue la commande
    // computer->effectuer(c);


    // On vide la barre de commande
    commande->clear();  
}

void QComputer::clicked_b1(){
   QString c=commande->text();
   c = c + "1";
   commande->setText(c);
}

void QComputer::clicked_b2(){

    QString c=commande->text();
    c = c + "2";
    commande->setText(c);
}

void QComputer::clicked_b3(){

    QString c=commande->text();
    c = c + "3";
    commande->setText(c);
}

void QComputer::clicked_b4(){

    QString c=commande->text();
    c = c + "4";
    commande->setText(c);
}

void QComputer::clicked_b5(){

    QString c=commande->text();
    c = c + "5";
    commande->setText(c);
}

void QComputer::clicked_b6(){

    QString c=commande->text();
    c = c + "6";
    commande->setText(c);
}

void QComputer::clicked_b7(){

    QString c=commande->text();
    c = c + "7";
    commande->setText(c);
}

void QComputer::clicked_b8(){

    QString c=commande->text();
    c = c + "8";
    commande->setText(c);
}

void QComputer::clicked_b9(){

    QString c=commande->text();
    c = c + "9";
    commande->setText(c);
}

void QComputer::clicked_b0(){

    QString c=commande->text();
    c = c + "0";
    commande->setText(c);
}

void QComputer::clicked_add(){
    QString c=commande->text();
    c = c + " +";
    commande->setText(c);
    CommandeSuivante();

}

void QComputer::clicked_sous(){
    QString c=commande->text();
    c = c + " -";
    commande->setText(c);
    CommandeSuivante();
}

void QComputer::clicked_mult(){
    QString c=commande->text();
    c = c + " *";
    commande->setText(c);
    CommandeSuivante();
}

void QComputer::clicked_div(){
    QString c=commande->text();
    c = c + " /";
    commande->setText(c);
    CommandeSuivante();
}

void QComputer::clicked_doll(){
    QString c=commande->text();
    c = c + " $";
    commande->setText(c);
    CommandeSuivante();
}

 void QComputer::clicked_point(){
     QString c=commande->text();
     c = c + ".";
     commande->setText(c);
 }

  void QComputer::clicked_entree(){

      QString c=commande->text();
      computer->effectuer(c);
      commande->clear();
  }


    void QComputer::open_parametre()
    {
        fenParametre = new fenetreParametre;
        fenParametre->show();
    }

    void QComputer::open_programme()
    {
        fenProgramme = new fenetreProgramme;
        fenProgramme->show();
    }

    void QComputer::open_variable()
    {
        fenVariable = new fenetreVariable;
        fenVariable->show();
    }
    void QComputer::quit(){
        this->close();

    }

    fenetreVariable::fenetreVariable(QWidget* parent): QWidget(parent)
    {

        vuePile=new QTableWidget(10,1,this); // 1 colonne
        commande=new QLineEdit(this);
        couche = new QGridLayout(this);
        supprimer = new QPushButton("Supprimer", this);
        modifie = new QPushButton("Modifier", this);
        couche2 = new QHBoxLayout(this);
        connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(var_suppression()));
        connect(modifie, SIGNAL(clicked(bool)), this, SLOT(var_modification()));

        couche2->addWidget(modifie);
        couche2->addWidget(supprimer);
        setLayout(couche2);
        couche->addWidget(vuePile,0,0);
        couche->addWidget(commande, 1,0);
        couche->addLayout(couche2,2,0);
        setLayout(couche);




        // On ajoute le titre de la fenetre
        this->setWindowTitle(QString("Edition variable"));

        // On definit la couleur des messages

        // Finish up the appearance of the object pointed by vuePile.
        // background
        vuePile->setStyleSheet("background: white; color: black");
        // foreground
        vuePile->verticalHeader()->setStyleSheet("color: black");
        // inhibit modification
        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // make invisible the column table.
        vuePile->horizontalHeader()->setVisible(false);
        // adjust automatically the window's width.
        vuePile->horizontalHeader()->setStretchLastSection(true);

        //  create a list of tables "i:" for each line
        // and the items of each list.
        QStringList numberList;
      for(unsigned int i=10; i>0; i--) {
            QString str= QString::number(i);
            str+=" ";
            numberList<<str;
            // creation of the item of each line initialized with an empty chain (chaine vide).
            vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
        }
        // print the label list on a vertial header.
        vuePile->setVerticalHeaderLabels(numberList);
        // fixed width as a function of the number of items to print
        vuePile->setFixedHeight(10*vuePile->rowHeight(0)+2);



    }


    void fenetreVariable::quit(){
        this->close();
    }

    void fenetreVariable::var_suppression(){

    }

    void fenetreVariable::var_modification(){

    }


    fenetreProgramme::fenetreProgramme(QWidget* parent): QWidget(parent)
    {

        vuePile=new QTableWidget(10,1,this); // 1 colonne
        commande=new QLineEdit(this);
        couche = new QGridLayout(this);
        supprimer = new QPushButton("Supprimer", this);
        modifie = new QPushButton("Modifier", this);
        couche2 = new QHBoxLayout(this);
        connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(var_suppression()));
        connect(modifie, SIGNAL(clicked(bool)), this, SLOT(var_modification()));

        couche2->addWidget(modifie);
        couche2->addWidget(supprimer);
        setLayout(couche2);
        couche->addWidget(vuePile,0,0);
        couche->addWidget(commande, 1,0);
        couche->addLayout(couche2,2,0);
        setLayout(couche);




        // On ajoute le titre de la fenetre
        this->setWindowTitle(QString("Edition variable"));

        // On definit la couleur des messages

        // Finish up the appearance of the object pointed by vuePile.
        // background
        vuePile->setStyleSheet("background: white; color: black");
        // foreground
        vuePile->verticalHeader()->setStyleSheet("color: black");
        // inhibit modification
        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // make invisible the column table.
        vuePile->horizontalHeader()->setVisible(false);
        // adjust automatically the window's width.
        vuePile->horizontalHeader()->setStretchLastSection(true);

        //  create a list of tables "i:" for each line
        // and the items of each list.
        QStringList numberList;
      for(unsigned int i=10; i>0; i--) {
            QString str= QString::number(i);
            str+=" ";
            numberList<<str;
            // creation of the item of each line initialized with an empty chain (chaine vide).
            vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
        }
        // print the label list on a vertial header.
        vuePile->setVerticalHeaderLabels(numberList);
        // fixed width as a function of the number of items to print
        vuePile->setFixedHeight(10*vuePile->rowHeight(0)+2);



    }
    void fenetreProgramme::quit(){
        this->close();
    }



    void fenetreProgramme::var_suppression(){

    }

    void fenetreProgramme::var_modification(){

    }


    fenetreParametre::fenetreParametre(QWidget* parent): QWidget(parent)
    {
        cb1 = new QCheckBox("Bip Sonore", this);
        cb2 = new QCheckBox("Clavier Cliquable", this);
        couche = new QVBoxLayout(this);
        annuler = new QPushButton("Retour", this);
        valider = new QPushButton("Valider", this);
        couche->addWidget(cb1,0,0);
        couche->addWidget(cb2,1,0);
        couche->addWidget(valider,2,0);
        couche->addWidget(annuler,3,0);
        setLayout(couche);



    }

    void fenetreParametre::quit(){
        this->close();
    }



