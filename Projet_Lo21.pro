QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
CONFIG += c++11

HEADERS += \
    analyseur.h \
    atomes.h \
    litteraux.h \
    operateurs.h \
    operateurs_instances.h \
    pile.h \
    qanalyseur.h

SOURCES += \
    analyseur.cpp \
    atomes.cpp \
    litteraux.cpp \
    main.cpp \
    operateurs.cpp \
    operateurs_instances.cpp \
    pile.cpp \
    qanalyseur.cpp
