/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "operation.h"


Operation::Operation()
{

}

Operation::Operation(int id, QDate date, double value, string typePmt, string description,
          string reference, Magasin magasin, Categorie categorie) : id(id), date(date), value(value),
    typePmt(typePmt), description(description), reference(reference), magasin(magasin), categorie(categorie)
{

}

Operation::~Operation()
{

}

string Operation::toString()
{
    return SEPARATOR+Utilities::nb2string(id)+SEPARATOR+date.toString("dd/MM/yyyy").toStdString()+SEPARATOR+Utilities::nb2string(value)
            +SEPARATOR+typePmt+SEPARATOR+description+SEPARATOR+reference+SEPARATOR+magasin.getNom()
            +SEPARATOR+categorie.getNom()+SEPARATOR+Utilities::nb2string(reste)+"\n";
}

int Operation::getId() const
{
    return id;
}

void Operation::setId(int value)
{
    id = value;
}
QDate Operation::getDate() const
{
    return date;
}

void Operation::setDate(const QDate &value)
{
    date = value;
}
double Operation::getValue() const
{
    return value;
}

void Operation::setValue(double val)
{
    value = val;
}
string Operation::getTypePmt() const
{
    return typePmt;
}

void Operation::setTypePmt(const string &value)
{
    typePmt = value;
}
string Operation::getDescription() const
{
    return description;
}

void Operation::setDescription(const string &value)
{
    description = value;
}
string Operation::getReference() const
{
    return reference;
}

void Operation::setReference(const string &value)
{
    reference = value;
}
Magasin Operation::getMagasin() const
{
    return magasin;
}

void Operation::setMagasin(const Magasin &value)
{
    magasin = value;
}
Categorie Operation::getCategorie() const
{
    return categorie;
}

void Operation::setCategorie(const Categorie &value)
{
    categorie = value;
}
double Operation::getReste() const
{
    return reste;
}

void Operation::setReste(double value)
{
    reste = value;
}

void Operation::setOpChecked(const bool check)
{
    opChecked = check;
}

bool Operation::isOpChecked() const
{
    return opChecked;
}
