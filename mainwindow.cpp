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
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    echo = true;
    Message("Déconnecté");
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow(void)
{
    delete ui;
}

void MainWindow::on_ConsoleInput_returnPressed(void)
{
    if(ui->ConsoleInput->text() != QString())
    {
        if(echo)
            WriteConsole("<strong>" + ui->ConsoleInput->text() + "</strong>");
        emit ConsoleInput(ui->ConsoleInput->text());
        ui->ConsoleInput->clear();
    }
}

void MainWindow::WriteConsole(QString texte)
{
    ui->Console->append("<span style=\"color: lime;\">" + texte + "</span>");
    texte = "User : " + texte;
    emit Written(texte);
}

void MainWindow::CleanConsole(){ui->Console->clear();}

void MainWindow::Message(QString texte)
{
    ui->statusbar->showMessage(texte);
}

void MainWindow::setEcho(bool state)
{
    echo = state;
}
