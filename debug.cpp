/****************************************************************************
*  Copyright (C) 2012 DAMHET Antoine                                        *
*                                                                           *
*  This program is free software; you can redistribute it and/or modify     *
*  it under the terms of the GNU General Public License as published by     *
*  the Free Software Foundation; either version 2 of the License, or        *
*  (at your option) any later version.                                      *
*                                                                           *
*  This program is distributed in the hope that it will be useful,          *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
*  GNU General Public License for more details.                             *
*                                                                           *
*  You should have received a copy of the GNU General Public License along  *
*  with this program; if not, write to the Free Software Foundation, Inc.,  *
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
****************************************************************************/
#include "debug.h"
#include "ui_debug.h"

Debug::Debug(JoyStick *t, MainWindow *c) :
    ui(new Ui::Debug)
{
    ui->setupUi(this);

    //Connection des signaux et des slots
    QObject::connect(t, SIGNAL(AxeX(int)), ui->AxeX, SLOT(display(int)));
    QObject::connect(t, SIGNAL(AxeY(int)), ui->AxeY, SLOT(display(int)));
    QObject::connect(t, SIGNAL(Curseur(int)), ui->Curseur, SLOT(display(int)));
    /*
    QObject::connect(c, SIGNAL(Written(QString)), this, SLOT(log(QString)));
    QObject::connect(c, SIGNAL(ConsoleInput(QString)), this, SLOT(logInput(QString)));
    */
}

Debug::~Debug(void)
{
    delete ui;
}

void Debug::log(QString chaine)
{
    //en attente d'implémentation
}

void Debug::logInput(QString chaine){log("User : " + chaine);}
