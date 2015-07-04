/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QMainWindow>

#include "utilities.h"

using namespace std;

namespace Ui {
class view_Accueil;
}

class view_Accueil : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit view_Accueil(QWidget *parent = 0);
    ~view_Accueil();
    void setTheme();

    void show();
    void showLabels();
    
private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_btn_theme_classic_clicked();

    void on_btn_theme_chic_clicked();

    void on_btn_theme_mother_fest_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::view_Accueil *ui;
};

#endif // ACCUEIL_H
