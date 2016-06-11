QT += core
QT -= gui
QT += xml

CONFIG += c++11

TARGET = QTXML
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    analyseur.cpp \
    atomes.cpp \
    litteraux.cpp \
    operateurs.cpp \
    operateurs_instances.cpp \
    pile.cpp

DISTFILES += \
    essai1.cbp \
    README.md

HEADERS += \
    analyseur.h \
    atomes.h \
    litteraux.h \
    operateurs.h \
    operateurs_instances.h \
    pile.h
