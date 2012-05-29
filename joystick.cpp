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
    if(!sf::Joystick::isConnected(id) || id == 25)//Vérification de la connection du JoyStick
        return;//Sinon on ne lance pas la thread
    while(boucle)
    {
        //Actualisation en temps réel des différents Axes
        //Envoi du signal correspondant en cas de changement
        msleep(50);
        update();
        emit AxeX(getAxeX());
        emit AxeY(getAxeY());
        emit Curseur(getCurseur());
        emit Norme(norme());
        emit Angle(angle());
        emit Actu();
    }
}

bool JoyStick::setAutoJoy(void)
{
    //Parcours des différents JoySticks pouvant être connectés
    for (unsigned int i(0); i < nbJoyStickMax(); i++)
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
    if(sf::Joystick::isConnected(ID))
    {
        //Vérifier si le JoyStick à suffisament d'axes
        if(sf::Joystick::hasAxis(ID, sf::Joystick::X) || sf::Joystick::hasAxis(ID, sf::Joystick::Y) || sf::Joystick::hasAxis(ID, sf::Joystick::Z))
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

void JoyStick::update(void){sf::Joystick::update();}
bool JoyStick::isConnected(void){return sf::Joystick::isConnected(id);}

int JoyStick::getAxeX(void){return sf::Joystick::getAxisPosition(id, sf::Joystick::X);}
int JoyStick::getAxeY(void){return sf::Joystick::getAxisPosition(id, sf::Joystick::Y);}
int JoyStick::getCurseur(void){return -sf::Joystick::getAxisPosition(id, sf::Joystick::Z);}

//Voir http://bit.ly/y1jdFM
int JoyStick::getVitesseAbs(void)
{
    int X(getAxeX()), Y(getAxeY());
    return static_cast<int>(sqrt(Y*Y + X*X ));
}
int JoyStick::getAngle(void){return angle();}

void JoyStick::stop(void)
{
    boucle = false;
    msleep(60);
}

bool* JoyStick::getJoyStick(void)
{
    bool* joys = new bool[nbJoyStickMax()];
    unsigned int jm(nbJoyStickMax());
    for (unsigned short i(0); i < jm; i++)
    {
        if(sf::Joystick::isConnected(i))
        {
            if(sf::Joystick::hasAxis(i, sf::Joystick::X) || sf::Joystick::hasAxis(i, sf::Joystick::Y) || sf::Joystick::hasAxis(i, sf::Joystick::Z))
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

double JoyStick::getPI(void)
{
    return pi;
}
