/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <exception>
#include <fstream>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>
#include <QWidget>
#include <vector>

#include "qselect.h"
#include "ui_comptes.h"
#include "view_accueil.h"
#include "view_categories.h"
#include "view_comptes.h"
#include "view_magasins.h"

using namespace std;

view_Comptes::view_Comptes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view_Comptes)
{
    ui->setupUi(this);

    ui->edit_date->setDate(QDate::currentDate());

    ui->actionAccueil->setObjectName("acc");
    ui->actionCategories->setObjectName("cat");
    ui->actionQuitter->setObjectName("quit");
    ui->actionMagasins->setObjectName("mag");
    ui->actionExporter_la_base_de_donnees->setObjectName("export");
    ui->actionPrint->setObjectName("print");

    connect(ui->actionAccueil,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionCategories,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionMagasins,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionExporter_la_base_de_donnees,SIGNAL(triggered()),this,SLOT(navig()));
    connect(ui->actionPrint,SIGNAL(triggered()),this,SLOT(navig()));

    readyForUpdate=false;
    mod_rest=false;
    load_options();
    update();
}

view_Comptes::~view_Comptes()
{
    delete ui;
}

void view_Comptes::show()
{
    QMainWindow::show();
    Utilities::setTheme(this,"2");
}


void view_Comptes::setTotal(string total)
{
    ui->lb_total->setText("TOTAL : "+QString::fromStdString(total)+" €");
}


void view_Comptes::update()
{
    if(!readyForUpdate)
        return;

    readyForUpdate=false;
    ui->tableWidget->clear();
    remplirTableau(dao.getAllOperations());
    readyForUpdate=true;
    setTotal(dao.getTotalAllOperations());
}


void view_Comptes::update(vector<Operation> operations)
{
    if(!readyForUpdate)
        return;

    readyForUpdate=false;
    ui->tableWidget->clear();
    remplirTableau(operations);
    readyForUpdate=true;
}


void view_Comptes::navig()
{
    bool stay = false;
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
    } else if(sender()->objectName()=="export"){
        exporter();
        stay = true;
    } else if(sender()->objectName()=="print"){
        imprimer(ui->tableWidget,"TEST");
        stay = true;
    }

    if(!stay)
        this->close();
}


void view_Comptes::exporter()
{
    vector<Operation> operations = dao.getAllOperations();
    ofstream fichier("cpt_report", ios::out | ios::trunc);
    for(int i=0;i<operations.size();i++){
        fichier << operations[i].toString();
    }

    fichier.close();

}


void view_Comptes::imprimer(QTableWidget * tableau_a_imprimer, QString titre)
{
    string html="<style>table{border:1px solid gray;}td{border:1px solid gray;}tr{border:1px solid gray;}</style>";
    html +="<link href=':/rc/tab.css' rel='stylesheet' type='text/css' >";
    html += "<table>\n";
    html +=     "\t<tr>\n";
    html +=         "\t\t<td>ID</td>\n";
    html +=         "\t\t<td>Date</td>\n";
    html +=         "\t\t<td>+ / -</td>\n";
    html +=         "\t\t<td>Type</td>\n";
    html +=         "\t\t<td>Description</td>\n";
    html +=         "\t\t<td>Référence</td>\n";
    html +=         "\t\t<td>Magasin</td>\n";
    html +=         "\t\t<td>Catégorie</td>\n";
    html +=         "\t\t<td>Reste</td>\n";
    html +=     "\t</tr>\n";

    for (int row = 0; row < tableau_a_imprimer->rowCount(); row ++)
    {
        html += "\t<tr>\n";
        for (int col = 0; col < tableau_a_imprimer->columnCount()-1; col ++)
        {
            if(col < 3 || (col > 3 && col < 6) || col ==8)
                html += "\t\t<td>"+tableau_a_imprimer->item(row,col)->text().toStdString()+"</td>\n";
            else{
                string value = ((QComboBox*)tableau_a_imprimer->cellWidget(row,col))->currentText().toStdString();
                if(value=="--- Magasins ---" || value=="--- Catégories ---")
                    value = "Autres";
                html += "\t\t<td>"+value+"</td>\n";
            }
        }
        html += "\t</tr>\n";
    }
    html += "</table>";

    html += "<a id='print' href='javascript:document.getElementById(\"print\").style.display=\"none\";window.print();'>Imprimer cette page</a>";

    ofstream fichier("comptes.html", ios::out | ios::trunc);
    fichier << html;
    fichier.close();

    QDesktopServices::openUrl(QUrl("comptes.html"));
}


vector<string> view_Comptes::split(const string &src, const char delim)
{
    vector<string> v;
    string::const_iterator p = src.begin ();
    string::const_iterator q =
            std::find (p, src.end (), delim);
    while (q != src.end ())
    {
        v.push_back (string (p, q));
        p = q;
        q = std::find (++p, src.end (), delim);
    }
    if (p != src.end ())
        v.push_back (string (p, src.end ()));
    return v;
}


int toPercent(int pct, int max)
{
    return max*pct/100;
}


void view_Comptes::resizeEvent( QResizeEvent *e )
{
    QMainWindow::resizeEvent(e);
    resizeWindow();
}


void view_Comptes::resizeWindow()
{
    int w = this->width()-300;

    ui->tableWidget->setColumnWidth(0,toPercent(w,5));
    ui->tableWidget->setColumnWidth(1,toPercent(w,8));
    ui->tableWidget->setColumnWidth(2,toPercent(w,6));
    ui->tableWidget->setColumnWidth(3,toPercent(w,7));
    ui->tableWidget->setColumnWidth(4,toPercent(w,20));
    ui->tableWidget->setColumnWidth(5,toPercent(w,16));
    ui->tableWidget->setColumnWidth(6,toPercent(w,14));
    ui->tableWidget->setColumnWidth(7,toPercent(w,14));
    ui->tableWidget->setColumnWidth(8,toPercent(w,7));
    ui->tableWidget->setColumnWidth(9,toPercent(w,3));
}


void view_Comptes::remplirTableau(vector<Operation> operations)
{
    ui->tableWidget->verticalHeader()->hide();

    QHeaderView *pHeaderView= ui->tableWidget->horizontalHeader();
    pHeaderView->setStretchLastSection(true);

    resizeWindow();

    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Date"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("+ / -"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Type"));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Description"));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Référence"));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Magasin"));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Catégorie"));
    ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem("Reste"));
    ui->tableWidget->setHorizontalHeaderItem(9,new QTableWidgetItem(""));

    ui->tableWidget->setRowCount(operations.size());

    vector<Categorie> categories = dao.getAllCategories();
    vector<Magasin> magasins = dao.getAllMagasins();

    int no_line=0;

    foreach (Operation operation, operations) {
        QSelect *list_type = new QSelect();
        list_type->addItem("CB");
        list_type->addItem("Chèque");
        list_type->addItem("Espèce");

        QPushButton *del = new QPushButton("X");
        del->setMaximumWidth(30);
        del->setObjectName(QString::number(operation.getId()));
        connect(del, SIGNAL(clicked()), this, SLOT( clicked_del()));

        QSelect *list_cat = new QSelect();
        QSelect *list_mag = new QSelect();

        int idxCat = -1;
        int cpt_index = 0;

        foreach (Categorie categorie, categories) {
            list_cat->addItem(QString::fromStdString(categorie.getNom()));
            if(categorie.getId()==operation.getCategorie().getId())
            {
                idxCat = cpt_index;
            }
            cpt_index++;
        }

        int idxMag = -1;
        cpt_index = 0;
        foreach (Magasin magasin, magasins) {
            list_mag->addItem(QString::fromStdString(magasin.getNom()));
            if(magasin.getId()==operation.getMagasin().getId()){
                idxMag = cpt_index;
            }
            cpt_index++;
        }

        int idxType = -1;
        if(operation.getTypePmt()=="CB")
            idxType = 0;
        else if(operation.getTypePmt()=="Chèque")
            idxType = 1;
        else if(operation.getTypePmt()=="Espèce")
            idxType = 2;

        ui->tableWidget->setItem(no_line,0,new QTableWidgetItem(QString::number(operation.getId())));
        ui->tableWidget->setItem(no_line,1,new QTableWidgetItem(operation.getDate().toString("dd/MM/yyyy")));
        ui->tableWidget->setItem(no_line,2,new QTableWidgetItem(QString::number(operation.getValue())));
        ui->tableWidget->setCellWidget(no_line,3,list_type);
        ui->tableWidget->setItem(no_line,4,new QTableWidgetItem((QString::fromStdString(operation.getDescription()))));
        ui->tableWidget->setItem(no_line,5,new QTableWidgetItem(QString::fromStdString(operation.getReference())));
        ui->tableWidget->setCellWidget(no_line,6,list_mag);
        ui->tableWidget->setCellWidget(no_line,7,list_cat);
        ui->tableWidget->setItem(no_line,8,new QTableWidgetItem(QString::number(operation.getReste())));
        ui->tableWidget->setCellWidget(no_line,9,del);

        list_type->setCurrentIndex(idxType);
        list_mag->setCurrentIndex(idxMag);
        list_cat->setCurrentIndex(idxCat);

        QString stype = "TYPE_"+QString::number(operation.getId());
        QString smag = "MAG_"+QString::number(operation.getId());
        QString scat = "CAT_"+QString::number(operation.getId());
        list_type->setObjectName(stype);
        list_cat->setObjectName(scat);
        list_mag->setObjectName(smag);

        connect(list_type, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));
        connect(list_cat, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));
        connect(list_mag, SIGNAL(currentIndexChanged(int)), this, SLOT( currentIndexChanged(int)));

        no_line++;
    }
}


void view_Comptes::clicked_del()
{
    string id = sender()->objectName().toStdString();
    string value = Utilities::nb2string(dao.getOperation("IDOP",id).getValue());
    dao.removeOperation(id);
    maj_restes(id,value);
    update();
}


void view_Comptes::currentIndexChanged(int idx)
{
    QComboBox *cb = (QComboBox*)sender();

    string s = sender()->objectName().toStdString();
    vector<string> sp = split(s,'_');

    string id = sp[1];
    string column = sp[0];
    string value = cb->currentText().toStdString();

    if(column=="MAG"){
        value = Utilities::nb2string(dao.getMagasin("NOMMAG",value).getId());
    } else if(column=="CAT"){
        value = Utilities::nb2string(dao.getCategorie("NOMCAT",value).getId());
    }
    dao.updateOperation(id, column, value);
}


void view_Comptes::load_options()
{
    readyForUpdate=false;
    ui->list_pmt->addItem("CB");
    ui->list_pmt->addItem("Chèque");
    ui->list_pmt->addItem("Espèce");

    ui->list_pmt_2->addItem("CB");
    ui->list_pmt_2->addItem("Chèque");
    ui->list_pmt_2->addItem("Espèce");

    vector<Categorie> categories = dao.getAllCategories();
    for(int i=0;i<categories.size();i++){
        ui->list_categories->addItem(QString::fromStdString(categories[i].getNom()));
        ui->list_categories_2->addItem(QString::fromStdString(categories[i].getNom()));
    }

    vector<Magasin> magasins= dao.getAllMagasins();
    for(int i=0;i<magasins.size();i++){
        ui->list_magasins->addItem(QString::fromStdString(magasins[i].getNom()));
        ui->list_magasins_2->addItem(QString::fromStdString(magasins[i].getNom()));
    }

    QDate date = date.currentDate();
    for(int i = 0;i<ui->list_annee->count();i++){
        if(ui->list_annee->itemText(i)==date.toString("yyyy"))
            ui->list_annee->setCurrentIndex(i);
    }
    for(int i = 0;i<ui->list_mois->count();i++){
        if(ui->list_mois->itemText(i).toLower()==date.toString("MMMM"))
            ui->list_mois->setCurrentIndex(i);
    }

    ui->edit_date_begin->setDate(date.addDays(-1));
    ui->edit_date_end->setDate(date.addDays(1));

    ui->check_date->setChecked(false);
    ui->check_magasins->setChecked(false);
    ui->check_categories->setChecked(false);
    ui->check_pmt->setChecked(false);
    readyForUpdate=true;
}


void view_Comptes::on_btn_add_clicked()
{
    double reste = dao.getReste();
    reste += ui->edit_value->text().toDouble();
    QDate date = QDate::fromString(ui->edit_date->text().toStdString().c_str(),"dd/MM/yyyy");

    if(!Utilities::checkIsValue(ui->edit_value->text().toStdString())){
        ui->edit_value->setStyleSheet("#edit_value{border:2px solid red;}");
        return;
    } else {
        ui->edit_value->setStyleSheet("");
    }

    if(ui->edit_desc->text().toStdString()==""){
        ui->edit_desc->setStyleSheet("#edit_desc{border:2px solid red;}");
        return;
    } else {
        ui->edit_desc->setStyleSheet("");
    }


    dao.insertOperation(date.toString("yyyy-MM-dd").toStdString(),
               ui->edit_value->text().toStdString(),
               ui->list_pmt->currentText().toStdString(),
               ui->edit_desc->text().toStdString(),
               ui->edit_ref->text().toStdString(),
               ui->list_magasins->currentText().toStdString(),
               ui->list_categories->currentText().toStdString(),
               Utilities::nb2string(reste));

    ui->edit_ref->setText("");
    ui->edit_desc->setText("");
    ui->edit_value->setText("");

    readyForUpdate=false;
    ui->check_categories->setChecked(false);
    ui->check_date->setChecked(false);
    ui->check_magasins->setChecked(false);
    ui->check_pmt->setChecked(false);
    readyForUpdate=true;

    update();
}


void view_Comptes::on_tableWidget_cellChanged(int row, int column)
{
    if(!mod_rest && readyForUpdate){
        string id = ui->tableWidget->item(row,0)->text().toStdString();
        string newval = ui->tableWidget->item(row,column)->text().toStdString();
        double diff;
        QDate date;

        switch(column)
        {
        case 1:
            date = QDate::fromString(newval.c_str(),"dd/MM/yyyy");
            if(date.isValid())
                dao.updateOperation(id,"DATEOP",date.toString("yyyy-MM-dd").toStdString());
            break;
        case 2:
            diff = dao.getOperation("IDOP",id).getValue()-Utilities::string2double(newval);
            dao.updateOperation(id,"VALEUR",newval);
            maj_restes(id,Utilities::nb2string(diff));
            update();
            break;
        case 4: dao.updateOperation(id,"DESCRIPTION",newval);
            break;
        case 5: dao.updateOperation(id,"REFERENCE",newval);
            break;
        }
    }
}


void view_Comptes::maj_restes(string id, string diff)
{
    mod_rest = true;
    dao.updateOperations(id,diff);
    update();
    mod_rest = false;
}


vector<Operation> view_Comptes::loadSearch()
{
    if(!readyForUpdate)
        return vector<Operation>();

    readyForUpdate = false;
    QDate d1 = QDate::fromString("1000-01-01","yyyy-MM-dd");
    QDate d2 = QDate::fromString("3000-12-31","yyyy-MM-dd");;
    string nomMag = "";
    string nomCat = "";
    string typePmt = "";

    if(ui->check_date->isChecked()){
        if(ui->rad_entre->isChecked()){
            d1 = ui->edit_date_begin->date();
            d2 = ui->edit_date_end->date();
        } else if(ui->rad_mois->isChecked()){
            map<string,string> mois;
            mois["Janvier"] = "01";
            mois["Février"] = "02";
            mois["Mars"] = "03";
            mois["Avril"] = "04";
            mois["Mai"] = "05";
            mois["Juin"] = "06";
            mois["Juillet"] = "07";
            mois["Août"] = "08";
            mois["Septembre"] = "09";
            mois["Octobre"] = "10";
            mois["Novembre"] = "11";
            mois["Décembre"] = "12";

            string m = ui->list_mois->currentText().toStdString();
            string annee = ui->list_annee->currentText().toStdString();

            d1 = QDate::fromString((annee+"-"+mois[m]+"-01").c_str(),"yyyy-MM-dd");
            d2 = QDate::fromString((annee+"-"+mois[m]+"-31").c_str(),"yyyy-MM-dd");
            if(!d2.isValid()){
                d2 = QDate::fromString((annee+"-"+mois[m]+"-30").c_str(),"yyyy-MM-dd");
                if(!d2.isValid()){
                    d2 = QDate::fromString((annee+"-"+mois[m]+"-29").c_str(),"yyyy-MM-dd");
                    if(!d2.isValid()){
                        d2 = QDate::fromString((annee+"-"+mois[m]+"-28").c_str(),"yyyy-MM-dd");
                    }
                }
            }
        }
    }
    if(ui->check_magasins->isChecked()){
        Magasin magasin = dao.getMagasin("NOMMAG",ui->list_magasins_2->currentText().toStdString());
        if(magasin.getId()!=-1)
            nomMag = magasin.getNom();
    }

    if(ui->check_categories->isChecked()){
        Categorie categorie = dao.getCategorie("NOMCAT",ui->list_categories_2->currentText().toStdString());
        if(categorie.getId()!=-1)
            nomCat = categorie.getNom();
    }

    if(ui->check_pmt->isChecked()){
        typePmt = ui->list_pmt_2->currentText().toStdString();
    }

    vector<Operation> operations = dao.getOperationsSelected(d1, d2, nomMag, nomCat, typePmt);
    this->setTotal(dao.getTotalOperationsSelected(d1, d2, nomMag, nomCat, typePmt));
    readyForUpdate = true;

    return operations;
}


void view_Comptes::on_edit_date_begin_dateChanged(const QDate &date)
{
    ui->rad_entre->setChecked(true);
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_edit_date_end_dateChanged(const QDate &date)
{
    ui->rad_entre->setChecked(true);
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_rad_mois_clicked()
{
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_rad_entre_clicked()
{
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_check_date_toggled(bool checked)
{
    update(loadSearch());
}


void view_Comptes::on_list_mois_currentIndexChanged(int index)
{
    ui->rad_mois->setChecked(true);
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_list_annee_currentIndexChanged(int index)
{
    ui->rad_mois->setChecked(true);
    ui->check_date->setChecked(true);
    update(loadSearch());
}


void view_Comptes::on_check_categories_toggled(bool checked)
{
    update(loadSearch());
}


void view_Comptes::on_check_magasins_toggled(bool checked)
{
    update(loadSearch());
}


void view_Comptes::on_check_pmt_toggled(bool checked)
{
    update(loadSearch());
}


void view_Comptes::on_list_pmt_2_currentIndexChanged(int index)
{
    update(loadSearch());
    ui->check_pmt->setChecked(true);
}


void view_Comptes::on_list_magasins_2_currentIndexChanged(int index)
{
    update(loadSearch());
    ui->check_magasins->setChecked(true);
}


void view_Comptes::on_list_categories_2_currentIndexChanged(int index)
{
    update(loadSearch());
    ui->check_categories->setChecked(true);
}


void view_Comptes::on_check_afficher_tout_toggled(bool checked)
{
    ui->check_categories->setEnabled(!checked);
    ui->check_date->setEnabled(!checked);
    ui->check_magasins->setEnabled(!checked);
    ui->check_pmt->setEnabled(!checked);
    ui->list_categories_2->setEnabled(!checked);
    ui->list_magasins_2->setEnabled(!checked);
    ui->list_pmt_2->setEnabled(!checked);
    ui->list_mois->setEnabled(!checked);
    ui->list_annee->setEnabled(!checked);
    ui->edit_date_begin->setEnabled(!checked);
    ui->edit_date_end->setEnabled(!checked);
    ui->rad_entre->setEnabled(!checked);
    ui->rad_mois->setEnabled(!checked);

    if(checked)
        update();
    else
        update(loadSearch());
}