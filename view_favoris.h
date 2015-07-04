/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef FAVORIS_H
#define FAVORIS_H

#include <QMainWindow>

#include "dao.h"
#include "favori.h"
#include "utilities.h"

using namespace std;

namespace Ui {
class view_Favoris;
}

class view_Favoris : public QMainWindow
{
    Q_OBJECT

public:
    explicit view_Favoris(QWidget *parent = 0);
    ~view_Favoris();

    void show();
    void load_options(string newMag="", string newCat="");

private slots:
    void clicked_del();
    void currentIndexChanged(int);

    void on_list_categories_currentIndexChanged(const QString &arg1);

    void on_list_magasins_currentIndexChanged(const QString &arg1);

    void on_btn_add_clicked();

    void navig();

    void on_tableWidget_cellChanged(int row, int column);

private:
    void resizeWindow();
    void update();
    void remplirTableau(vector<Favori> favoris);

    DAO dao;
    Ui::view_Favoris *ui;
    bool readyForUpdate;
};

#endif // FAVORIS_H
