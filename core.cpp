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
#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    GUI = new MainWindow;
    GUI->show();

    joy = new JoyStick;

    d = 0;

    QObject::connect(GUI, SIGNAL(ConsoleInput(QString)), this, SLOT(commande(QString)));
    QObject::connect(joy, SIGNAL(started()), this, SLOT(CaptureJoy()));
    QObject::connect(joy, SIGNAL(finished()), this, SLOT(SCaptureJoy()));
}

Core::~Core()
{
    delete GUI;
    if(d != 0)
        delete d;
    delete joy;
}

void Core::commande(QString instruction)
{
    if(instruction == "quit" || instruction == "exit")
    {
        GUI->WriteConsole("Quitter...");
        qApp->quit();
    }
    else if(instruction[0] == 'e' && instruction[1] == 'c' && instruction[2] == 'h' && instruction[3] == 'o' && instruction[4] == ' ')
    {
        GUI->WriteConsole(instruction.remove(0, 5));
    }
    else if(instruction == "debug init")
    {
        d = new Debug(joy, GUI);
        GUI->WriteConsole("Création du module de debug");
    }
    else if(instruction == "debug")
    {
        if(d != 0)
        {
            GUI->WriteConsole("Ouverture de la fenêtre de Debug");
            d->show();
        }
        else
        {
            GUI->WriteConsole("Erreur lors de l'ouverture de la fenêtre de Debug.");
            GUI->WriteConsole("Le module Debug n'est pas initialisé");
        }
    }
    else if(instruction[0] == 'c' && instruction[1] == 'l' && instruction[2] == 'e' && instruction[3] == 'a' && instruction[4] == 'n' && instruction[5] == ' ')
    {
        if(instruction.remove(0, 6) == "true" || instruction.remove(0, 6) == "1")
            GUI->setEcho(true);
        else
            GUI->setEcho(false);
    }
    else if(instruction == "joy start")
    {
        if(joy->isConnected())
        {
            GUI->WriteConsole("Lancement de la capture du JoyStick");
            joy->start();
        }
        else
        {
            GUI->WriteConsole("Erreur lors du lancement de la capture :");
            GUI->WriteConsole("<span style=\"color: red;\">Pas de JoyStick Connecté</span>");
        }
    }
    else
    {
        GUI->WriteConsole("instruction non comprise ...");
    }
}

void Core::CaptureJoy()
{
    GUI->WriteConsole("<span style=\"color: red;\">Capture du Joystick Lancée</span>");
}

void Core::SCaptureJoy()
{
    GUI->WriteConsole("<span style=\"color: red;\">Capture du Joystick Stoppée</span>");
}
