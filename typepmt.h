/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef TYPEPMT_H
#define TYPEPMT_H

#include "utilities.h"

using namespace std;

class TypePmt
{
public:
    TypePmt();
    TypePmt(int id);
    ~TypePmt();
    string toString();

private:
    string libelle;
};

#endif // TYPEPMT_H
