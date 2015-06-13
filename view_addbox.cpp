/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "dao.h"
#include "view_addbox.h"
#include "ui_addbox.h"

view_addbox::view_addbox(view_Comptes *vc, string type, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_addbox), v_comptes(vc)
{
    ui->setupUi(this);

    setMinimumSize(size());
    setMaximumSize(size());
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->type = type;
    if(type=="cat")
    {
        ui->lb_titre_1->setText("Nouvelle Catégorie");
    }
    else if(type=="mag")
    {
        ui->lb_titre_1->setText("Nouveau Magasin");
    }
}

view_addbox::~view_addbox()
{
    delete ui;
}


void view_addbox::show()
{
    QMainWindow::show();
    Utilities::setTheme(this,"1");
}

void view_addbox::on_btn_cancel_clicked()
{
    if(type=="cat")
    {
        v_comptes->load_options("",";operation/canceled°;");
    }
    else if (type=="mag")
    {
        v_comptes->load_options(";operation/canceled°;","");
    }
    this->close();
}

void view_addbox::on_btn_add_clicked()
{
    string nom = ui->edit_nom->text().toStdString();
    if(nom=="")
    {
        ui->edit_nom->setStyleSheet("#edit_nom{border:2px solid red;}");
        return;
    }
    else
    {
        ui->edit_nom->setStyleSheet("");
    }


    DAO dao;
    if(type=="cat")
    {
        dao.insertCategorie(nom);
        v_comptes->load_options("",nom);
    }
    else if (type=="mag")
    {
        dao.insertMagasin(nom);
        v_comptes->load_options(nom,"");
    }

    this->close();
}