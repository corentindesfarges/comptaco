/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef VIEW_ADDBOX_H
#define VIEW_ADDBOX_H

#include <QMainWindow>

#include "utilities.h"
#include "view_comptes.h"
#include "view_favoris.h"

namespace Ui {
class view_addbox;
}

class view_addbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit view_addbox(view_Comptes *view, string type, QWidget *parent = 0);
    explicit view_addbox(view_Favoris *view, string type, QWidget *parent = 0);
    ~view_addbox();

    void show();
    void load_options(const string& newMag="", const string& newCat="");

private slots:
    void on_btn_cancel_clicked();

    void on_btn_add_clicked();

private:
    Ui::view_addbox *ui;
    string type;
    view_Comptes *m_viewComptes;
    view_Favoris *m_viewFavoris;

};

#endif // VIEW_ADDBOX_H
