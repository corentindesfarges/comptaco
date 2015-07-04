/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QFile>
#include <QSettings>

#include "ui_categories.h"
#include "view_accueil.h"
#include "view_categories.h"
#include "view_comptes.h"
#include "view_favoris.h"
#include "view_magasins.h"

view_Categories::view_Categories(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_Categories)
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size());

    ui->actionAccueil->setObjectName("acc");
    ui->actionFavoris->setObjectName("fav");
    ui->actionComptes->setObjectName("cpt");
    ui->actionQuitter->setObjectName("quit");
    ui->actionMagasins->setObjectName("mag");

    connect(ui->actionAccueil,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionComptes,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionFavoris,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionMagasins,SIGNAL(triggered()),this,SLOT(navig()));

    readyForUpdate=false;

    update();
}

view_Categories::~view_Categories()
{
    delete ui;
}

void view_Categories::show()
{
    QMainWindow::show();
    Utilities::setTheme(this,"1");
}


void view_Categories::navig()
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

void view_Categories::remplirTableau(vector<Categorie> categories)
{
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Libellé"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(""));

    QHeaderView *pHeaderView= ui->tableWidget->horizontalHeader();
    pHeaderView->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(1,300);

    ui->tableWidget->verticalHeader()->hide();

    ui->tableWidget->setRowCount(categories.size()-1);
    for(int i=0;i<categories.size();i++){
        if(categories[i].getId()!=-1){
            QPushButton *del = new QPushButton("X");
            del->setObjectName(QString::number(categories[i].getId()));
            connect(del, SIGNAL(clicked()), this, SLOT( clicked_del()));

            ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(QString::number(categories[i].getId())));
            ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(QString::fromStdString(categories[i].getNom())));
            ui->tableWidget->setCellWidget(i-1,2,del);
        }

    }
}

void view_Categories::clicked_del()
{
    string id = sender()->objectName().toStdString();
    dao.removeCategorie(id);
    update();
}

/*Met a jour le tableau et la liste*/
void view_Categories::update()
{
    readyForUpdate=false;
    ui->tableWidget->clear();
    remplirTableau(dao.getAllCategories());
    ui->edit_nom_cat->setText("");
    readyForUpdate=true;
}


void view_Categories::on_tableWidget_cellChanged(int row, int column)
{
    if(readyForUpdate){
        string id = ui->tableWidget->item(row,0)->text().toStdString();
        string newName = ui->tableWidget->item(row,column)->text().toStdString();

        if(column == 1){
            dao.updateCategorie(id,newName);
        }
        update();
    }
}

void view_Categories::on_btn_add_cat_clicked()
{
    if(ui->edit_nom_cat->text().toStdString()==""){
        ui->edit_nom_cat->setStyleSheet("#edit_nom_cat{border:2px solid red;}");
        return;
    } else {
        ui->edit_nom_cat->setStyleSheet("");
    }
    dao.insertCategorie(ui->edit_nom_cat->text().toStdString());
    update();
}
