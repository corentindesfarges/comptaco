/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef QSELECT_H
#define QSELECT_H

#include <QComboBox>
#include <QEvent>

using namespace std;

class QSelect : public QComboBox
{
public:
    QSelect();
    ~QSelect();
protected:
    bool event( QEvent *e );
};

#endif // QSELECT_H
