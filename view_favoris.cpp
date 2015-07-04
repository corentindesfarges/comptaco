/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QPushButton>
#include <vector>

#include "qselect.h"
#include "ui_favoris.h"
#include "view_accueil.h"
#include "view_addbox.h"
#include "view_categories.h"
#include "view_comptes.h"
#include "view_favoris.h"
#include "view_magasins.h"

view_Favoris::view_Favoris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_Favoris), readyForUpdate(false)
{
    ui->setupUi(this);

    setMinimumSize(size());
    setMaximumSize(size());

    ui->actionAccueil->setObjectName("acc");
    ui->actionFavoris->setObjectName("fav");
    ui->actionComptes->setObjectName("cpt");
    ui->actionMagasins->setObjectName("mag");
    ui->actionCategories->setObjectName("cat");
    ui->actionQuitter->setObjectName("quit");

    connect(ui->actionAccueil,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionFavoris,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionComptes,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionCategories,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionMagasins,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(navig()));

    resizeWindow();
    load_options();
    update();
}

view_Favoris::~view_Favoris()
{
    delete ui;
}


void view_Favoris::update()
{
    if(!readyForUpdate)
        return;

    readyForUpdate=false;
    ui->tableWidget->clear();
    remplirTableau(dao.getAllFavoris());
    readyForUpdate=true;
}


void view_Favoris::show()
{
    QMainWindow::show();
    Utilities::setTheme(this,"1");
}


void view_Favoris::resizeWindow()
{
    int w = this->width()-300;

    ui->tableWidget->setColumnWidth(0,Utilities::toPercent(w,6));
    ui->tableWidget->setColumnWidth(1,Utilities::toPercent(w,7));
    ui->tableWidget->setColumnWidth(2,Utilities::toPercent(w,10));
    ui->tableWidget->setColumnWidth(3,Utilities::toPercent(w,20));
    ui->tableWidget->setColumnWidth(4,Utilities::toPercent(w,20));
    ui->tableWidget->setColumnWidth(5,Utilities::toPercent(w,17));
    ui->tableWidget->setColumnWidth(6,Utilities::toPercent(w,17));
    ui->tableWidget->setColumnWidth(7,Utilities::toPercent(w,3));
}


void view_Favoris::load_options(string newMag, string newCat)
{
    readyForUpdate=false;

    ui->list_pmt->clear();
    ui->list_pmt->addItem("CB");
    ui->list_pmt->addItem("Chèque");
    ui->list_pmt->addItem("Espèce");
    ui->list_pmt->addItem("Virement");
    ui->list_pmt->addItem("Autre");

    if((newMag=="" && newCat=="") || newMag=="")
    {
        vector<Categorie> categories = dao.getAllCategories();
        ui->list_categories->clear();
        for(int i=0;i<categories.size();i++){
            ui->list_categories->addItem(QString::fromStdString(categories[i].getNom()));
            if(categories[i].getNom()==newCat)
                ui->list_categories->setCurrentIndex(i);
        }
        ui->list_categories->addItem("Ajouter...");
    }

    if((newMag=="" && newCat=="") || newCat=="")
    {
        vector<Magasin> magasins= dao.getAllMagasins();
        ui->list_magasins->clear();
        for(int i=0;i<magasins.size();i++){
            ui->list_magasins->addItem(QString::fromStdString(magasins[i].getNom()));
            if(magasins[i].getNom()==newMag)
                ui->list_magasins->setCurrentIndex(i);
        }
        ui->list_magasins->addItem("Ajouter...");
    }

    readyForUpdate=true;
}


void view_Favoris::navig()
{
    if(sender()->objectName()=="acc"){
        view_Accueil *a = new view_Accueil();
        a->show();
    } else if(sender()->objectName()=="cpt"){
        view_Comptes *c = new view_Comptes();
        c->show();
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


void view_Favoris::remplirTableau(vector<Favori> favoris)
{
    ui->tableWidget->verticalHeader()->hide();

    QHeaderView *pHeaderView= ui->tableWidget->horizontalHeader();
    pHeaderView->setStretchLastSection(true);

    resizeWindow();

    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("+ / -"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Type"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Description"));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Référence"));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Magasin"));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Catégorie"));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem(""));

    ui->tableWidget->setRowCount(favoris.size());

    vector<Categorie> categories = dao.getAllCategories();
    vector<Magasin> magasins = dao.getAllMagasins();

    int no_line=0;

    foreach (Favori favori, favoris) {
        QSelect *list_type = new QSelect();
        list_type->addItem("CB");
        list_type->addItem("Chèque");
        list_type->addItem("Espèce");
        list_type->addItem("Virement");
        list_type->addItem("Autre");

        QPushButton *del = new QPushButton("X");
        del->setMaximumWidth(30);
        del->setObjectName(QString::number(favori.getId()));
        connect(del, SIGNAL(clicked()), this, SLOT( clicked_del()));

        QSelect *list_cat = new QSelect();
        QSelect *list_mag = new QSelect();

        int idxCat = -1;
        int cpt_index = 0;

        foreach (Categorie categorie, categories) {
            list_cat->addItem(QString::fromStdString(categorie.getNom()));
            if(categorie.getId()==favori.getCategorie().getId())
            {
                idxCat = cpt_index;
            }
            cpt_index++;
        }

        int idxMag = -1;
        cpt_index = 0;
        foreach (Magasin magasin, magasins) {
            list_mag->addItem(QString::fromStdString(magasin.getNom()));
            if(magasin.getId()==favori.getMagasin().getId()){
                idxMag = cpt_index;
            }
            cpt_index++;
        }

        int idxType = -1;
        if(favori.getTypePmt()=="CB")
            idxType = 0;
        else if(favori.getTypePmt()=="Chèque")
            idxType = 1;
        else if(favori.getTypePmt()=="Espèce")
            idxType = 2;
        else if(favori.getTypePmt()=="Virement")
            idxType = 3;
        else if(favori.getTypePmt()=="Autre")
            idxType = 4;

        ui->tableWidget->setItem(no_line,0,new QTableWidgetItem(QString::number(favori.getId())));
        ui->tableWidget->setItem(no_line,1,new QTableWidgetItem(QString::number(favori.getValue())));
        ui->tableWidget->setCellWidget(no_line,2,list_type);
        ui->tableWidget->setItem(no_line,3,new QTableWidgetItem((QString::fromStdString(favori.getDescription()))));
        ui->tableWidget->setItem(no_line,4,new QTableWidgetItem(QString::fromStdString(favori.getReference())));
        ui->tableWidget->setCellWidget(no_line,5,list_mag);
        ui->tableWidget->setCellWidget(no_line,6,list_cat);
        ui->tableWidget->setCellWidget(no_line,7,del);

        list_type->setCurrentIndex(idxType);
        list_mag->setCurrentIndex(idxMag);
        list_cat->setCurrentIndex(idxCat);

        QString stype = "TYPE_"+QString::number(favori.getId());
        QString smag = "MAG_"+QString::number(favori.getId());
        QString scat = "CAT_"+QString::number(favori.getId());
        list_type->setObjectName(stype);
        list_cat->setObjectName(scat);
        list_mag->setObjectName(smag);

        connect(list_type, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));
        connect(list_cat, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));
        connect(list_mag, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));

        no_line++;
    }
}


void view_Favoris::clicked_del()
{
    string id = sender()->objectName().toStdString();
    dao.removeFavori(id);
    update();
}


void view_Favoris::currentIndexChanged(int idx)
{
    QComboBox *cb = (QComboBox*)sender();

    string s = sender()->objectName().toStdString();
    vector<string> sp = Utilities::split(s,'_');

    string id = sp[1];
    string column = sp[0];
    string value = cb->currentText().toStdString();

    if(column=="MAG"){
        value = Utilities::nb2string(dao.getMagasin("NOMMAG",value).getId());
    } else if(column=="CAT"){
        value = Utilities::nb2string(dao.getCategorie("NOMCAT",value).getId());
    }
    dao.updateFavori(id, column, value);
}

void view_Favoris::on_list_categories_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Ajouter...")
    {
        view_addbox *addbox = new view_addbox(this, "cat");
        addbox->setWindowModality(Qt::ApplicationModal);
        addbox->show();
    }
}

void view_Favoris::on_list_magasins_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Ajouter...")
    {
        view_addbox *addbox = new view_addbox(this, "mag");
        addbox->setWindowModality(Qt::ApplicationModal);
        addbox->show();
    }
}

void view_Favoris::on_btn_add_clicked()
{
    if(!Utilities::checkIsValue(ui->edit_value->text().toStdString()))
    {
        ui->edit_value->setStyleSheet("#edit_value{border:2px solid red;}");
        return;
    }
    else
    {
        ui->edit_value->setStyleSheet("");
    }

    dao.insertFavori(ui->edit_value->text().toStdString(),
           ui->list_pmt->currentText().toStdString(),
           ui->edit_desc->text().toStdString(),
           ui->edit_ref->text().toStdString(),
           ui->list_magasins->currentText().toStdString(),
           ui->list_categories->currentText().toStdString());

    ui->edit_ref->setText("");
    ui->edit_desc->setText("");
    ui->edit_value->setText("");
    ui->list_pmt->setCurrentIndex(0);
    ui->list_magasins->setCurrentIndex(0);
    ui->list_categories->setCurrentIndex(0);

    update();
}

void view_Favoris::on_tableWidget_cellChanged(int row, int column)
{
    if(readyForUpdate){
        string id = ui->tableWidget->item(row,0)->text().toStdString();
        string newval = ui->tableWidget->item(row,column)->text().toStdString();


        switch(column)
        {
        case 1:
            dao.updateFavori(id,"VALEUR",newval);
            break;
        case 3: dao.updateFavori(id,"DESCRIPTION",newval);
            break;
        case 4: dao.updateFavori(id,"REFERENCE",newval);
            break;
        }
    }
}
