/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef FAVORI_H
#define FAVORI_H

#include "operation.h"

//using namespace std;

class Favori : public Operation
{
public:
    Favori();
    Favori(int id, double value, string typePmt, string description, string reference, Magasin magasin, Categorie categorie);
    ~Favori();

    string toString();

private:
    int id;
    double value;
    string typePmt;
    string description;
    string reference;
    Magasin magasin;
    Categorie categorie;
};

#endif // FAVORI_H
