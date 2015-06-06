/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef MAGASINS_H
#define MAGASINS_H

#include <QMainWindow>

#include "dao.h"
#include "magasin.h"
#include "utilities.h"

using namespace std;

namespace Ui {
class view_Magasins ;
}

class view_Magasins : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit view_Magasins(QWidget *parent = 0);
    ~view_Magasins();
    
    void show();

private slots:

    void navig();

    void on_tableWidget_cellChanged(int row, int column);

    void clicked_del();

    void on_btn_add_mag_clicked();


private:
    Ui::view_Magasins  *ui;
    DAO dao;
    bool readyForUpdate;
    void remplirTableau(vector<Magasin> magasins);
    void remplirCombobox(vector<vector<string> > v);
    void update();
};

#endif // MAGASINS_H
