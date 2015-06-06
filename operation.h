/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef OPERATION_H
#define OPERATION_H

#include <QDate>

#include "categorie.h"
#include "magasin.h"
#include "typepmt.h"
#include "utilities.h"

using namespace std;

class Operation
{
public:
    Operation();
    Operation(int id, QDate date, double value, string typePmt, string description,
              string reference, Magasin magasin, Categorie categorie);
    ~Operation();

    const string SEPARATOR = "#&!#";

    string toString();

    int getId() const;
    void setId(int value);

    QDate getDate() const;
    void setDate(const QDate &value);

    double getValue() const;
    void setValue(double val);

    string getTypePmt() const;
    void setTypePmt(const string &value);

    string getDescription() const;
    void setDescription(const string &value);

    string getReference() const;
    void setReference(const string &value);

    Magasin getMagasin() const;
    void setMagasin(const Magasin &value);

    Categorie getCategorie() const;
    void setCategorie(const Categorie &value);

    double getReste() const;
    void setReste(double value);

private:
    int id;
    QDate date;
    double value;
    string typePmt;
    string description;
    string reference;
    Magasin magasin;
    Categorie categorie;
    double reste;
};

#endif // OPERATION_H
