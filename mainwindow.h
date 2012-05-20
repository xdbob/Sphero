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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(void);

    enum{important, warning, standard, reseau, user};//Priorité (message console)
    void WriteConsole(QString texte, int priority = MainWindow::standard);//Ecrire dans la console
    Ui::MainWindow *getUi();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void CleanConsole(void);
    void Message(QString texte);//Ecrire un message pour l'utilisateur
    void setEcho(bool state);//Défini si une commande est recopiée dans la console
    void setConnected(bool etat);
    void moo(void);

    //Raccourcis => Ecrire console(Signals/slots)
    void WCN(QString texte);
    void WCS(QString texte);
    void WCW(QString texte);
    void WCI(QString texte);

private slots:
    void on_ConsoleInput_returnPressed(void);//Validation d'une commande console
    //Slots appelés lors du lancement et de la capture du JoyStick
    void LJoyStart(void);
    void LJoyStop(void);

    void quit(void);

signals:
    void ConsoleInput(QString);//Commande lancée dans la console
    void Written(QString);//Quelque chose d'écrit dans la console
    void ComJoy(bool);//Commande capture => JoyStick
    void SQuit(void);

private:
    Ui::MainWindow *ui;
    bool echo;
};

#endif
