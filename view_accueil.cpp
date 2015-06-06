/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QLayout>
#include <QSettings>
#include <stdio.h>

#include "ui_accueil.h"
#include "view_accueil.h"
#include "view_categories.h"
#include "view_comptes.h"
#include "view_magasins.h"

view_Accueil::view_Accueil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_Accueil)
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size());

}

view_Accueil::~view_Accueil()
{
    delete ui;
}

void view_Accueil::showLabels()
{
    QSettings settings("Dev", "ComptaCool");
    bool momFest = (settings.value("theme")=="b");
    ui->lb_titre_1->setVisible(momFest);
    ui->lb_stitre_1->setVisible(momFest);
    ui->lb_titre_2->setVisible(!momFest);
    ui->lb_stitre_2->setVisible(!momFest);
}

void view_Accueil::show()
{
    QMainWindow::show();
    showLabels();
    Utilities::setTheme(this,"1");
}

void view_Accueil::on_pushButton_2_clicked()
{
    view_Categories *c = new view_Categories();
    c->show();
    this->close();
}

void view_Accueil::on_pushButton_3_clicked()
{
    view_Magasins *m = new view_Magasins();
    m->show();
    this->close();
}

void view_Accueil::on_pushButton_4_clicked()
{
    view_Comptes *c = new view_Comptes();
    c->show();
    this->close();
}

void view_Accueil::on_btn_theme_classic_clicked()
{
    QSettings settings("Dev", "ComptaCool");
    settings.setValue("theme","n");
    showLabels();
    Utilities::setTheme(this,"1");
}

void view_Accueil::on_btn_theme_chic_clicked()
{
    QSettings settings("Dev", "ComptaCool");
    settings.setValue("theme","c");
    showLabels();
    Utilities::setTheme(this,"1");
}

void view_Accueil::on_btn_theme_mother_fest_clicked()
{
    QSettings settings("Dev", "ComptaCool");
    settings.setValue("theme","b");
    showLabels();
    Utilities::setTheme(this,"1");
}
