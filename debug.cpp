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

Debug::Debug(void) :
    ui(new Ui::Debug)
{
    ui->setupUi(this);

    fichier = new QFile("debug.log");
    flux = new QTextStream(fichier);
    if(fichier->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))//ouverture de debug.log
    {
        writable = true;
        flux->setAutoDetectUnicode(true);
        flux->setCodec("utf-8");
        *flux << "\n" << "##### Nouvelle instance le - " << QDateTime().currentDateTime().toString() << " #####\n";
    }
    else
    {
        writable = false;
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier debug.log");
    }
}

Debug::~Debug(void)
{
    fichier->close();
    delete ui;
    delete fichier;
    delete flux;
}

bool Debug::canWrite(void){return writable;}

void Debug::log(QString chaine)
{
    *flux << QTime::currentTime().toString() << " - " << chaine << "\n";
}

void Debug::setJoyX(int value)
{
    ui->AxeX->display(value);
    ui->progressX->setValue(value);
}

void Debug::setJoyY(int value)
{
    ui->AxeY->display(value);
    ui->progressY->setValue(value);
}

void Debug::setJoyC(int value)
{
    ui->Curseur->display(value);
    ui->progressCurseur->setValue(value);
}

void Debug::setJoyAngle(int value)
{
    ui->Angle->display(value);
    ui->progressA->setValue(value);
}

void Debug::setJoyNorme(int value)
{
    ui->Norme->display(value);
    ui->progressN->setValue(value);
}
