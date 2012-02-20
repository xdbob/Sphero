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
#include "joystick.h"

JoyStick::JoyStick(QObject *parent) :
    QThread(parent)
{
    update();//Actualiation des JoySticks
    pi = (4.0 * atan(1.0));
    if(!setAutoJoy())//Sélection du premier JoyStick disponible
        id = 25;//Sinon affecter une valeure à l'id du joystick
}

void JoyStick::run(void)
{
    boucle = true;
    if(!sf::Joystick::IsConnected(id))//Vérification de la connection du JoyStick
        return;//Sinon on ne lance pas la thread
    while(boucle)
    {
        //Actualisation en temps réel des différents Axes
        //Envoi du signal correspondant en cas de changement
        QTest::qSleep(10);
        update();
        emit AxeX(sf::Joystick::GetAxisPosition(id, sf::Joystick::X));
        emit AxeY(sf::Joystick::GetAxisPosition(id, sf::Joystick::Y));
        emit Curseur(-sf::Joystick::GetAxisPosition(id, sf::Joystick::Z));
        emit Norme(norme());
        emit Angle(angle());
    }
    //Remise des valeures à 0 avant de Quitter la thread
}

bool JoyStick::setAutoJoy(void)
{
    //Parcours des différents JoySticks pouvant être connectés
    for (unsigned int i(0); i < sf::Joystick::Count; i++)
    {
        //Sélection du premier JoyStick disponible
        if(setJoy(i))
            return true;
    }
    return false;
}

bool JoyStick::setJoy(unsigned int ID)
{
    if(isRunning())
        stop();
    if(sf::Joystick::IsConnected(ID))
    {
        //Vérifier si le JoyStick à suffisament d'axes
        if(sf::Joystick::HasAxis(ID, sf::Joystick::X) || sf::Joystick::HasAxis(ID, sf::Joystick::Y) || sf::Joystick::HasAxis(ID, sf::Joystick::Z))
        id = ID;
        return true;
    }
    return false;
}

int JoyStick::norme(void)
{
    int X(getAxeX()), Y(getAxeY());
    return static_cast<int>(sqrt(Y*Y + X*X ));
}
int JoyStick::angle(void)
{
    int X(getAxeX()), Y(getAxeY());
    if(Y == 0 && X == 0)
        return 0;
    else
    {
        double i((2*atan((-Y)/(X+sqrt(Y*Y+X*X))))*180/pi);
        i -= 90.0;
        if (i < -180.0)
            i += 360.0;
        return static_cast<int>(i);
    }
}

void JoyStick::update(void){sf::Joystick::Update();}
bool JoyStick::isConnected(void){return sf::Joystick::IsConnected(id);}

int JoyStick::getAxeX(void){return sf::Joystick::GetAxisPosition(id, sf::Joystick::X);}
int JoyStick::getAxeY(void){return sf::Joystick::GetAxisPosition(id, sf::Joystick::Y);}
int JoyStick::getCurseur(void){return -sf::Joystick::GetAxisPosition(id, sf::Joystick::Z);}

//Voir http://bit.ly/y1jdFM
int JoyStick::getVitesseAbs(void)
{
    int X(getAxeX()), Y(getAxeY());
    return static_cast<int>(sqrt(Y*Y + X*X ));
}
int JoyStick::getAngle(void)
{
    int X(getAxeX()), Y(getAxeY());
    return static_cast<int>(((2*atan((-Y)/(X+sqrt(Y*Y+X*X))))+pi/2)*180/pi);
}

void JoyStick::stop(void){boucle = false;}

bool* JoyStick::getJoyStick(void)
{
    bool* joys = new bool[nbJoyStickMax()];
    unsigned int jm(nbJoyStickMax());
    for (unsigned short i(0); i < jm; i++)
    {
        if(sf::Joystick::IsConnected(i))
        {
            if(sf::Joystick::HasAxis(i, sf::Joystick::X) || sf::Joystick::HasAxis(i, sf::Joystick::Y) || sf::Joystick::HasAxis(i, sf::Joystick::Z))
                joys[i] = true;
        }
        else
            joys[i] = false;
    }
    return joys;
}

unsigned int JoyStick::nbJoyStickMax(void)
{
    return sf::Joystick::Count;
}
