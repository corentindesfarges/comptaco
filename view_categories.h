/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QMainWindow>

#include "categorie.h"
#include "dao.h"
#include "utilities.h"

using namespace std;

namespace Ui {
class view_Categories;
}

class view_Categories : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit view_Categories(QWidget *parent = 0);
    ~view_Categories();

    void show();
    
private slots:

    void navig();

    void on_tableWidget_cellChanged(int row, int column);

    void clicked_del();

    void on_btn_add_cat_clicked();

private:
    Ui::view_Categories *ui;
    DAO dao;
    bool readyForUpdate;
    void remplirTableau(vector<Categorie> categories);
    void remplirCombobox(vector<vector<string> > v);
    void update();
};

#endif // CATEGORIES_H
