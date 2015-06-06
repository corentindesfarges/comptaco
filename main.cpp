/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QApplication>

#include "dao.h"
#include "view_accueil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DAO dao;
    dao.loadSchema();

    view_Accueil accueil;
    accueil.show();
    
    return a.exec();
}
