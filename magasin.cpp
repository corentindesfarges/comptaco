/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "magasin.h"

Magasin::Magasin()
{

}

Magasin::Magasin(const int id, const string nom)
{
    this->setId(id);
    this->setNom(nom);
}

Magasin::~Magasin()
{

}

int Magasin::getId() const
{
    return id;
}

void Magasin::setId(int value)
{
    id = value;
}
string Magasin::getNom() const
{
    return nom;
}

void Magasin::setNom(const string &value)
{
    nom = value;
}
