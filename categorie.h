/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef CATEGORIE_H
#define CATEGORIE_H

#include "utilities.h"

using namespace std;

class Categorie
{
public:
    Categorie();
    Categorie(const int id, const string nom);
    ~Categorie();

    int getId() const;
    void setId(int value);

    string getNom() const;
    void setNom(const string &value);

private:
    int id;
    string nom;
};

#endif // CATEGORIE_H
