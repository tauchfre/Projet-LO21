#include "qanalyseur.h"
#include "analyseur.h"

QComputer::QComputer(QWidget* parent): QWidget(parent)
{

    // Create the object pointed by the class attributes
    //pile = new Pile;
    computer = new Computer;
    computer->setNbAfficher(10);
    message=new QLineEdit(this);
    vuePile=new QTableWidget(computer->getNbAfficher(),1,this); // 1 colonne
    commande=new QLineEdit(this);
    couche = new QVBoxLayout(this);



    // On positionne les objets dans la fenetre.
	
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    setLayout(couche);

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
	
    // Premier message 
    computer->getAnalyseur().setMessage("Bienvenue dans l'application UTComputer!");
	
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
        //vuePile->item(nb,0)->setText((*it).toStr());
        vuePile->item(computer->getNbAfficher()-1-nb,0)->setText(qs);







       // vuePile->item(computer->getNbAfficher()-1-nb,0)->setText("aaa");


    }

   /* for( int i=0; i<computer->getNbAfficher(); i++)
    {
        if(i<computer->getPileActuelle().getTaille()){
            vuePile->item(i,0)->setText((computer->getPileActuelle().top()).toStr());

        }
        else vuePile->item(i,0)->setText("1");

    }*/


}

void QComputer::CommandeSuivante(){
    // On recupere le texte de la barre de commande 
    QString c=commande->text();


	// On effectue la commande
     computer->effectuer(c);


    // On vide la barre de commande
    commande->clear();  
}


