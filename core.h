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
#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QApplication>
#include <cmath>
#include <QList>
#include <QStringList>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"
#include "joystick.h"
#include "network.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    ~Core(void);
signals:

public slots:

private slots:

    void commande(QString instruction);//Traitement des commandes (console)
    void CaptureJoy(void);//Début de la capture de la position du JoyStick
    void SCaptureJoy(void);//Fin de la capture de la position du JoyStick

    void Quitter(void);

    void DebugInit(void);
    void ShowDebug(void);

    void ComJoyStick(bool etat);//Lancement/Arrêt de la capture du JoyStick
    void getJoyState(void);

    void setPort(void);

    void setMoteursSpeed(void);


private:
    MainWindow* GUI;
    Debug* d;
    JoyStick* joy;
    NetWork* net;
};

#endif
