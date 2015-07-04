/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "dao.h"
#include "ui_magasins.h"
#include "view_categories.h"
#include "view_accueil.h"
#include "view_favoris.h"
#include "view_magasins.h"
#include "view_comptes.h"

view_Magasins::view_Magasins(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_Magasins )
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size());

    ui->actionAccueil->setObjectName("acc");
    ui->actionFavoris->setObjectName("fav");
    ui->actionComptes->setObjectName("cpt");
    ui->actionCategories->setObjectName("cat");
    ui->actionQuitter->setObjectName("quit");

    connect(ui->actionAccueil,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionComptes,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionFavoris,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionCategories,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(navig()));

    readyForUpdate=false;

    update();
}

view_Magasins::~view_Magasins()
{
    delete ui;
}

void view_Magasins::show()
{
    QMainWindow::show();
    Utilities::setTheme(this,"1");
}

/*
 * LOAD NAVIGATION
*/
void view_Magasins::navig()
{
    if(sender()->objectName()=="acc"){
        view_Accueil *a = new view_Accueil();
        a->show();
    } else if(sender()->objectName()=="cpt"){
        view_Comptes *c = new view_Comptes();
        c->show();
    } else if(sender()->objectName()=="fav"){
        view_Favoris *f = new view_Favoris();
        f->show();
    } else if(sender()->objectName()=="mag"){
        view_Magasins *m = new view_Magasins();
        m->show();
    } else if(sender()->objectName()=="cat"){
        view_Categories *c = new view_Categories();
        c->show();
    } else if(sender()->objectName()=="quit"){
        exit(1);
    }

    this->close();
}


/*
 * FILL TABLEWIDGET
*/
void view_Magasins::remplirTableau(vector<Magasin> magasins)
{
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Libellé"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(""));

    QHeaderView *pHeaderView= ui->tableWidget->horizontalHeader();
    pHeaderView->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(1,300);

    ui->tableWidget->verticalHeader()->hide();

    ui->tableWidget->setRowCount(magasins.size()-1);
    for(int i=0;i<magasins.size();i++){
        if(magasins[i].getId()!=-1){
            QPushButton *del = new QPushButton("X");
            del->setObjectName(QString::number(magasins[i].getId()));
            connect(del, SIGNAL(clicked()), this, SLOT( clicked_del()));

            ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(QString::number(magasins[i].getId())));
            ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(QString::fromStdString(magasins[i].getNom())));
            ui->tableWidget->setCellWidget(i-1,2,del);
        }
    }
}


/*
 * DELETE MAGASIN
*/
void view_Magasins::clicked_del()
{   
    string id = sender()->objectName().toStdString();
    dao.removeMagasin(id);
    update();
}


/*
 * UPDATE LIST
*/
void view_Magasins::update()
{
    readyForUpdate=false;
    ui->tableWidget->clear();
    remplirTableau(dao.getAllMagasins());
    ui->edit_mag->setText("");

    readyForUpdate=true;
}


/*
 * CELL CHANGED
*/
void view_Magasins::on_tableWidget_cellChanged(int row, int column)
{
    if(readyForUpdate){
        string id = ui->tableWidget->item(row,0)->text().toStdString();
        string newName = ui->tableWidget->item(row,column)->text().toStdString();

        if(column == 1){
            dao.updateMagasin(id,newName);
        }
        update();
    }
}


/*
 * ADD MAGASIN
*/
void view_Magasins::on_btn_add_mag_clicked()
{
    if(ui->edit_mag->text().toStdString()==""){
        ui->edit_mag->setStyleSheet("#edit_mag{border:2px solid red;}");
        return;
    } else {
        ui->edit_mag->setStyleSheet("");
    }
    dao.insertMagasin(ui->edit_mag->text().toStdString());
    update();
}
