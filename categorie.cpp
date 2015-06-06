/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "categorie.h"

Categorie::Categorie()
{
}

Categorie::Categorie(const int id, const string nom)
{
    this->setId(id);
    this->setNom(nom);
}

Categorie::~Categorie()
{
}

int Categorie::getId() const
{
    return id;
}

void Categorie::setId(int value)
{
    id = value;
}
string Categorie::getNom() const
{
    return nom;
}

void Categorie::setNom(const string &value)
{
    nom = value;
}



