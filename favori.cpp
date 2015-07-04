/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "favori.h"

Favori::Favori()
{

}

Favori::Favori(int id, double value, string typePmt, string description, string reference, Magasin magasin, Categorie categorie) :
    id(id), value(value), typePmt(typePmt), description(description), reference(reference), magasin(magasin), categorie(categorie)
{

}

Favori::~Favori()
{

}

string Favori::toString()
{
    return SEPARATOR+Utilities::nb2string(id)+SEPARATOR+Utilities::nb2string(value)+SEPARATOR+typePmt+SEPARATOR+description+SEPARATOR+reference+SEPARATOR+magasin.getNom()
            +SEPARATOR+categorie.getNom()+"\n";
}
