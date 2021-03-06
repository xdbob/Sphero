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
    setConnected(false);

    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), SLOT(quit()));
    QObject::connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(ui->actionLancer_la_capture, SIGNAL(triggered()), SLOT(LJoyStart()));
    QObject::connect(ui->actionStopper_la_capture, SIGNAL(triggered()), SLOT(LJoyStop()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), SLOT(co()));
}

MainWindow::~MainWindow(void)
{
    delete ui;
}

void MainWindow::on_ConsoleInput_returnPressed(void)
{
    if(ui->ConsoleInput->text() != QString())
    {
        WriteConsole(ui->ConsoleInput->text(), MainWindow::user);
        emit ConsoleInput(ui->ConsoleInput->text());
        ui->ConsoleInput->clear();
    }
}

void MainWindow::WriteConsole(QString texte, int priority)
{
    if(priority == MainWindow::user)
    {
        if(echo)
            ui->Console->append("<span style=\"color: lime;\"><strong>" + texte + "</strong></span>");
        texte = "User : " + texte;
        emit Written(texte);
        return;
    }
    else if(priority == MainWindow::important)
    {
        ui->Console->append("<span style=\"color: orange;\">" + texte + "</span>");
        texte = "#Important# " + texte + " #Important#";
    }
    else if(priority == MainWindow::warning)
    {
        ui->Console->append("<span style=\"color: red;\">" + texte + "</span>");
        texte = "#Warning# " + texte + " #Waring#";
    }
    else if(priority == MainWindow::reseau)
    {
        ui->Console->append("<span style=\"color: white;\">" + texte + "</span>");
        texte = "#Network# " + texte + " #Network#";
    }
    else
        ui->Console->append("<span style=\"color: lime;\">" + texte + "</span>");
    texte = "Console : " + texte;
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

void MainWindow::setConnected(bool etat)
{
    if(etat)
    {
        Message(tr("Connecté"));
        ui->commandLinkButton->setText(tr("Déconnecter"));
    }
    else
    {
        Message(tr("Déconnecté"));
        ui->commandLinkButton->setText(tr("Connecter"));
    }

    ui->comboBox->setEnabled(!etat);
    ui->VitesseM1->setEnabled(etat);
    ui->VitesseM2->setEnabled(etat);
    ui->VitesseM3->setEnabled(etat);
    ui->Batterie->setEnabled(etat);
}

void MainWindow::quit(void){emit SQuit();}

void MainWindow::LJoyStart(void){emit ComJoy(true);}
void MainWindow::LJoyStop(void){emit ComJoy(false);}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit SQuit();
}

void MainWindow::moo()
{
    QMessageBox::information(this, "Easter Egg", "              (___)\n              (oo)\n    /------\\/\n  / |          ||\n*  /\\-----/\\\n   ~~      ~~\n...\"Have you mooed today?\"...");
}

void MainWindow::actuPorts(QStringList ports)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(ports);
}

bool MainWindow::isCurseur(void){return ui->actionCurseur->isChecked();}
bool MainWindow::isSimulating(void){return ui->actionSimulation->isChecked();}

void MainWindow::WCI(QString texte){WriteConsole(texte, MainWindow::important);}
void MainWindow::WCN(QString texte){WriteConsole(texte, MainWindow::reseau);}
void MainWindow::WCS(QString texte){WriteConsole(texte);}
void MainWindow::WCW(QString texte){WriteConsole(texte, MainWindow::warning);}
void MainWindow::co(void){emit connect();}

QString MainWindow::CurrentSelectedPort(void){return ui->comboBox->currentText();}

void MainWindow::echoVitesses(QList<double> liste)
{

    if(liste.size() != 3)
        return;
    ui->VitesseM1->display(liste[0]);
    ui->VitesseM2->display(liste[1]);
    ui->VitesseM3->display(liste[2]);

}
