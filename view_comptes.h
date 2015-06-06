/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef COMPTES_H
#define COMPTES_H

#include <QComboBox>
#include <QMainWindow>
#include <QTableWidget>

#include "dao.h"
#include "operation.h"
#include "utilities.h"

using namespace std;

namespace Ui {
class view_Comptes;
}

class view_Comptes : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit view_Comptes(QWidget *parent = 0);
    vector<string> static split(const string &src, const char delim);

    ~view_Comptes();

    void show();
    
private slots:

    void on_tableWidget_cellChanged(int row, int column);

    void imprimer(QTableWidget * tableau_a_imprimer, QString titre);

    void currentIndexChanged(int idx);

    void navig();

    void clicked_del();

    void on_btn_add_clicked();

    void on_edit_date_begin_dateChanged(const QDate &date);

    void on_edit_date_end_dateChanged(const QDate &date);

    void on_rad_mois_clicked();

    void on_rad_entre_clicked();

    void on_check_date_toggled(bool checked);

    void on_check_categories_toggled(bool checked);

    void on_check_magasins_toggled(bool checked);

    void on_check_pmt_toggled(bool checked);

    void on_list_pmt_2_currentIndexChanged(int index);

    void on_list_magasins_2_currentIndexChanged(int index);

    void on_list_categories_2_currentIndexChanged(int index);

    void on_list_mois_currentIndexChanged(int index);

    void on_list_annee_currentIndexChanged(int index);

    void on_check_afficher_tout_toggled(bool checked);

    void resizeEvent( QResizeEvent *e );

private:
    Ui::view_Comptes *ui;
    DAO dao;
    void resizeWindow();
    bool readyForUpdate;
    bool mod_rest;
    void setTotal(string total);
    void update();
    void update(vector<Operation> operations);
    void adapteScreen();
    void exporter();
    vector<Operation> loadSearch();
    void maj_restes(string id, string diff);
    void remplirTableau(vector<Operation> operations);
    void load_options();
};

#endif // COMPTES_H
