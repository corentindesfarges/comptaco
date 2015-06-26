#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T19:22:25
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += printsupport

TARGET = ComptaCo
TEMPLATE = app

CONFIG += c++11

unix{
LIBS += -ldl
}

SOURCES += main.cpp\
    sqlite3.c \
    qselect.cpp \
    view_categories.cpp \
    view_comptes.cpp \
    view_magasins.cpp \
    view_accueil.cpp \
    operation.cpp \
    typepmt.cpp \
    categorie.cpp \
    magasin.cpp \
    dao.cpp \
    utilities.cpp \
    view_addbox.cpp

HEADERS  += \
    sqlite3.h \
    qselect.h \
    view_categories.h \
    view_comptes.h \
    view_magasins.h \
    view_accueil.h \
    operation.h \
    typepmt.h \
    categorie.h \
    magasin.h \
    dao.h \
    utilities.h \
    view_addbox.h

FORMS    += accueil.ui \
    magasins.ui \
    comptes.ui \
    categories.ui \
    addbox.ui

DISTFILES += \
    tab.css \
    bdd.db \

RESOURCES += \
    resources.qrc
