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

class QComputer : public QWidget{
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
    Computer* computer;
public:
    explicit QComputer(QWidget *parent = 0);

public slots:
    void rafraichir();
    void CommandeSuivante();
};

#endif // QANALYSEUR

