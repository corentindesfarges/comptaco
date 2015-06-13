/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef VIEW_ADDBOX_H
#define VIEW_ADDBOX_H

#include <QMainWindow>

#include "view_comptes.h"
#include "utilities.h"

namespace Ui {
class view_addbox;
}

class view_addbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit view_addbox(view_Comptes *vc, string type, QWidget *parent = 0);
    ~view_addbox();

    void show();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_add_clicked();

private:
    Ui::view_addbox *ui;
    string type;
    view_Comptes *v_comptes;

};

#endif // VIEW_ADDBOX_H
