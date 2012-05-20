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
    //initialisation et création des différents modules
    joy = new JoyStick;
    d = 0;
    net = new NetWork;
    GUI = new MainWindow;
    GUI->show();
#ifdef QT_DEBUG
    DebugInit();
#endif

    actuPorts(net->actuPort());

    //Connection des signaux et des slots
    QObject::connect(GUI, SIGNAL(ConsoleInput(QString)), SLOT(commande(QString)));
    QObject::connect(joy, SIGNAL(started()), SLOT(CaptureJoy()));
    QObject::connect(joy, SIGNAL(finished()), SLOT(SCaptureJoy()));
    QObject::connect(GUI, SIGNAL(ComJoy(bool)), SLOT(ComJoyStick(bool)));
    QObject::connect(GUI, SIGNAL(SQuit()), SLOT(Quitter()));
    QObject::connect(net, SIGNAL(connected(bool)), GUI, SLOT(setConnected(bool)));
    QObject::connect(GUI->getUi()->commandLinkButton, SIGNAL(clicked()), SLOT(setPort()));
    QObject::connect(joy, SIGNAL(Actu()), SLOT(setMoteursSpeed()));
    QObject::connect(net, SIGNAL(Write(QString)), GUI, SLOT(WCN(QString)));
    QObject::connect(net, SIGNAL(Err(QString)), GUI, SLOT(WCW(QString)));
    QObject::connect(net, SIGNAL(Warning(QString)), GUI, SLOT(WCI(QString)));

    ComJoyStick(true);
}

Core::~Core(void)
{
    joy->stop();
    net->quit();
    delete GUI;
    if(d != 0)
        delete d;
    delete joy;
    delete net;
}

void Core::commande(QString instruction)
{
    if(instruction == "quit" || instruction == "exit")
        Quitter();
    else if(instruction.startsWith("clean "))
    {
        if(instruction.remove(0, 6) == "true" || instruction.remove(0, 6) == "1")
            GUI->setEcho(false);//Les commandes ne sont pas répétées dans la console.
        else
            GUI->setEcho(true);
    }
    else if(instruction.startsWith("echo "))
        GUI->WriteConsole(instruction.remove(0, 5));//echo...
    else if(instruction == "debug init")
        DebugInit();
    else if(instruction == "debug -i")
    {
        DebugInit();
        ShowDebug();
    }
    else if(instruction == "debug")
        ShowDebug();
    else if(instruction.startsWith("port list"))
    {
        instruction.remove(0, 9);
        if(instruction == " -v")
            net->echoPorts(true);
        else
            net->echoPorts();
    }
    else if(instruction.startsWith("port set "))
    {
        instruction.remove(0, 9);
        net->setPort(instruction);
    }
    else if(instruction.startsWith("blink "))
    {
        instruction.remove(0, 6);
        bool ok;
        int temp(instruction.toInt(&ok, 10));
        if(!ok)
            GUI->WriteConsole(instruction + tr(" n'est pas un nombre"));
        else if(temp < 0 || temp > 255)
            GUI->WriteConsole(instruction + tr(" n'est pas compris entre 0 et 255"));
        else
        {
            QList<unsigned char> l;
            l.append(static_cast<unsigned char>(temp));
            net->sendMessage(NetWork::blink, l);
        }
    }
    else if(instruction == "joy start")
        ComJoyStick(true);
    else if(instruction == "joy stop")
        ComJoyStick(false);
    else if(instruction == "joy list")
        getJoyState();
    else if(instruction.startsWith("joy set "))
    {
        instruction.remove(0, 8);
        bool ok;
        int temp(instruction.toInt(&ok, 10));
        if(!ok)
            GUI->WriteConsole(instruction + tr(" n'est pas un nombre"));
        else if(joy->setJoy(temp))
            GUI->WriteConsole(tr("Joystick n°") + instruction + tr(" bien connecté"));
        else
            GUI->WriteConsole(tr("Impossible de connecter le joystick n°") + instruction, MainWindow::warning);
    }
    else if(instruction == "moo" || instruction == "apt-get moo")
        GUI->moo();
    else
        GUI->WriteConsole(tr("instruction non comprise ..."));
}


void Core::Quitter(void)
{
    GUI->WriteConsole(tr("Quitter..."), MainWindow::important);
    qApp->quit();
}

void Core::DebugInit(void)
{
    if(d == 0)
    {
        d = new Debug;
        QObject::connect(GUI, SIGNAL(Written(QString)), d, SLOT(log(QString)));
        GUI->WriteConsole(tr("Création du module de debug"), MainWindow::important);
        QObject::connect(joy, SIGNAL(AxeX(int)), d, SLOT(setJoyX(int)));
        QObject::connect(joy, SIGNAL(AxeY(int)), d, SLOT(setJoyY(int)));
        QObject::connect(joy, SIGNAL(Curseur(int)), d, SLOT(setJoyC(int)));
        QObject::connect(joy, SIGNAL(Angle(int)), d, SLOT(setJoyAngle(int)));
        QObject::connect(joy, SIGNAL(Norme(int)), d, SLOT(setJoyNorme(int)));
        QObject::connect(net, SIGNAL(log(QString)), d, SLOT(log(QString)));
    }
    else
        GUI->WriteConsole(tr("Module de debug déjà créé"), MainWindow::warning);
}

void Core::ShowDebug(void)
{
    if(d != 0)
    {
        GUI->WriteConsole(tr("Ouverture de la fenêtre de Debug"));
        d->show();
    }
    else
    {
        GUI->WriteConsole(tr("Erreur lors de l'ouverture de la fenêtre de Debug : "), MainWindow::warning);
        GUI->WriteConsole(tr("Le module Debug n'est pas initialisé"), MainWindow::warning);
    }
}

void Core::ComJoyStick(bool etat)
{
    if(etat)
    {
        if(joy->isRunning())
        {
            GUI->WriteConsole(tr("Impossible de lancer la capture : capture en cours d'exécution"), MainWindow::warning);
        }
        else
        {
            GUI->WriteConsole(tr("Lancement de la capture du JoyStick"));
            joy->start();
        }
    }
    else
    {
        if(joy->isRunning())
        {
            GUI->WriteConsole(tr("Arrêt de la capture"));
            joy->stop();
        }
        else
            GUI->WriteConsole(tr("Impossible de stopper la capture : capture non lancée"), MainWindow::warning);
    }
}

void Core::getJoyState(void)
{
    bool* j = joy->getJoyStick();
    unsigned int jm(joy->nbJoyStickMax());
    for(unsigned int i(0);i<jm;i++)
    {
        GUI->WriteConsole(tr("Joystick ID n°") + QString::number(i), MainWindow::warning);
        if(j[i])
            GUI->WriteConsole(tr("Connecté"));
        else
            GUI->WriteConsole(tr("Déconnecté"), MainWindow::important);
    }
    delete j;
}

void Core::CaptureJoy(void){GUI->WriteConsole(tr("Capture du Joystick Lancée"), MainWindow::important);}
void Core::SCaptureJoy(void){GUI->WriteConsole(tr("Capture du Joystick Stoppée"), MainWindow::important);}

void Core::actuPorts(QStringList prts)
{
    GUI->getUi()->comboBox->clear();
    GUI->getUi()->comboBox->addItems(prts);
}

void Core::setPort(void)
{
    if(net->isConnected())
    {
        net->deco();
        if(!net->isConnected())
        {
            GUI->getUi()->comboBox->setEnabled(true);
            GUI->getUi()->commandLinkButton->setText(tr("Connecter"));
        }
    }
    else
    {
        net->setPort(GUI->getUi()->comboBox->currentText());
        if(net->isConnected())
        {
            GUI->getUi()->comboBox->setEnabled(false);
            GUI->getUi()->commandLinkButton->setText(tr("Déonnecter"));
        }
    }
}

void Core::setMoteursSpeed(void)
{
    //Redressement de la vitesse absolue
    int temp(joy->getVitesseAbs());
    if(temp > 100)
        temp = 100;
    //Conversion des variables (int => double) & création de variables temporaires
    double vitesse(static_cast<double>(temp)), angle(static_cast<double>(joy->getAngle()));

    QList<double> value;
    QList<unsigned char> sortie;
    QList<unsigned char> srt2;
    value.push_back(vitesse * cos(joy->getPI() * (angle + 30.0) / 180.0));
    value.push_back(vitesse * cos(joy->getPI() * (angle + 150.0) / 180.0));
    value.push_back(vitesse * cos(joy->getPI() *(angle + 270.0) / 180.0));
    if(GUI->getUi()->actionCurseur->isChecked())
    {
        for(int i(0);i<3;i++)
        {
            double tmp(static_cast<double>(joy->getCurseur()));
            tmp += 100.0;
            tmp /= 200.0;
            value[i] = value[i] * tmp;
        }
    }
    GUI->getUi()->VitesseM1->display(value[0]);
    GUI->getUi()->VitesseM2->display(value[1]);
    GUI->getUi()->VitesseM3->display(value[2]);
    if(d != 0)
    {
        QList<int> tmp;
        for(int i(0);i<3;i++)
            tmp.push_back(static_cast<int>(fabs(value[i])));
        d->setVitesses(tmp);
    }
    for(int i(0);i<3;i++)
    {
        int tmp(static_cast<int>(value[i] * 2.5));
        if(tmp < 0)
        {
            tmp = 0-tmp;
            srt2.push_back(0b11111111);
        }
        else
            srt2.push_back(0b00000000);
        sortie.push_back(static_cast<unsigned char>(tmp));
    }
    if(net->isConnected())
        net->sendMessage(NetWork::moteur, sortie, srt2);
}
