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
    //initialisatio et création des différents modules
    GUI = new MainWindow;
    GUI->show();
    joy = new JoyStick;
    d = 0;

    //Connection des signaux et des slots
    QObject::connect(GUI, SIGNAL(ConsoleInput(QString)), this, SLOT(commande(QString)));
    QObject::connect(joy, SIGNAL(started()), this, SLOT(CaptureJoy()));
    QObject::connect(joy, SIGNAL(finished()), this, SLOT(SCaptureJoy()));
    QObject::connect(joy, SIGNAL(terminated()), this, SLOT(SCaptureJoy()));
    QObject::connect(GUI, SIGNAL(ComJoy(bool)), this, SLOT(ComJoyStick(bool)));
}

Core::~Core(void)
{
    delete GUI;
    if(d != 0)
        delete d;
    delete joy;
}

void Core::commande(QString instruction)
{
    if(instruction == "quit" || instruction == "exit")
        Quitter();
    else if(instruction[0] == 'c' && instruction[1] == 'l' && instruction[2] == 'e' && instruction[3] == 'a' && instruction[4] == 'n' && instruction[5] == ' ')
    {
        if(instruction.remove(0, 6) == "true" || instruction.remove(0, 6) == "1")
            GUI->setEcho(true);
        else
            GUI->setEcho(false);
    }
    else if(instruction[0] == 'e' && instruction[1] == 'c' && instruction[2] == 'h' && instruction[3] == 'o' && instruction[4] == ' ')
        GUI->WriteConsole(instruction.remove(0, 5));
    else if(instruction == "debug init")
        DebugInit();
    else if(instruction == "debug")
        ShowDebug();
    else if(instruction == "joy start")
        ComJoyStick(true);
    else if(instruction == "joy stop")
        ComJoyStick(false);
    else
    {
        GUI->WriteConsole("instruction non comprise ...");
    }
}


void Core::Quitter(void)
{
    GUI->WriteConsole("Quitter...");
    qApp->quit();
}

void Core::DebugInit(void)
{
    if(d == 0)
    {
        d = new Debug(joy, GUI);
        GUI->WriteConsole("Création du module de debug");
    }
    else
        GUI->WriteConsole("Module de debug déjà créé");
}

void Core::ShowDebug(void)
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

void Core::ComJoyStick(bool etat)
{
    if(etat)
    {
        GUI->WriteConsole("Lancement de la capture du JoyStick");
        joy->start();
    }
    else
    {
        if(joy->isRunning())
        {
            GUI->WriteConsole("Arrêt de la capture");
            joy->terminate();
        }
        else
            GUI->WriteConsole("Impossible de stopper la capture : capture non lancée");
    }
}

void Core::CaptureJoy(void){GUI->WriteConsole("<span style=\"color: red;\">Capture du Joystick Lancée</span>");}
void Core::SCaptureJoy(void){GUI->WriteConsole("<span style=\"color: red;\">Capture du Joystick Stoppée</span>");}
