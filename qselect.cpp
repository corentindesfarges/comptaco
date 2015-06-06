/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "qselect.h"

QSelect::QSelect()
{
}

QSelect::~QSelect()
{
}

bool QSelect::event( QEvent *e )
 {
     if (e->type() == QEvent::Wheel) {
         return false;
     }

     return QComboBox::event(e);
 }

