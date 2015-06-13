/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef DAO_H
#define DAO_H

#include <QFile>
#include <sqlite3.h>
#include <vector>

#include "categorie.h"
#include "magasin.h"
#include "operation.h"
#include "typepmt.h"

#include "utilities.h"

using namespace std;

class DAO
{
public:
    DAO();
    ~DAO();
    void open();
    void close();

    void loadSchema();

    void execute(string req);
    void execute(char* req);

    Operation getOperation(string knewColName, string knewValue);
    Categorie getCategorie(string knewColName, string knewValue);
    Magasin getMagasin(string knewColName, string knewValue);

    vector<Operation> getOperationsSelected(QDate d1, QDate d2, string nomMag, string nomCat, string typePmt);

    string getTotalAllOperations();
    string getTotalOperationsSelected(QDate d1, QDate d2, string nomMag, string nomCat, string typePmt);

    vector<Operation> getAllOperations();
    vector<Categorie> getAllCategories();
    vector<Magasin> getAllMagasins();

    double getReste();
    string orderBy(string col);

    void removeOperation(string id);
    void removeMagasin(string id);
    void removeCategorie(string id);

    void insertOperation(string date, string value, string typePmt, string description,
                         string reference, string magasin, string categorie, string reste);
    void insertMagasin(string id);
    void insertCategorie(string id);

    void updateOperation(string id, string date, string value, string description,
                         string reference, string reste);
    void updateOperation(string id, string col, string value);
    void updateOperations(string idBase, string diff);
    void updateMagasin(string id, string nom);
    void updateCategorie(string id, string nom);


private:

    sqlite3 *db;
    int conn;
    char *zErrMsg;
    int  rc;
    const char *sql;
    const char* data;

};

#endif // DAO_H
