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
    if(!setAutoJoy())//Sélection du premier JoyStick disponible
        id = 25;//Sinon affecter une valeure à l'id du joystick

    running = false;
    QObject::connect(this, SIGNAL(AxeX(int)), SLOT(updatePolaire()));
    QObject::connect(this, SIGNAL(AxeY(int)), SLOT(updatePolaire()));
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
        update();
        if(sf::Joystick::GetAxisPosition(id, sf::Joystick::X) != X)
        {
            X = sf::Joystick::GetAxisPosition(id, sf::Joystick::X);
            emit AxeX(X);
        }
        if(sf::Joystick::GetAxisPosition(id, sf::Joystick::Y) != Y)
        {
            Y = sf::Joystick::GetAxisPosition(id, sf::Joystick::Y);
            emit AxeY(Y);
        }
        if(sf::Joystick::GetAxisPosition(id, sf::Joystick::Z) != C)
        {
            C = sf::Joystick::GetAxisPosition(id, sf::Joystick::Z);
            emit Curseur(C);
        }
    }
    //Remise des valeures à 0 avant de Quitter la thread
    X = 0;
    Y = 0;
    C = 0;
}

bool JoyStick::setAutoJoy(void)
{
    //Parcours des différents JoySticks pouvant être connectés
    for (unsigned short i(0); i < sf::Joystick::Count; i++)
    {
        //Sélection du premier JoyStick disponible
        if(setJoy(i))
            return true;
    }
    return false;
}

bool JoyStick::setJoy(unsigned short ID)
{
    if(sf::Joystick::IsConnected(ID))
    {
        //Vérifier si le JoyStick à suffisament d'axes
        if(sf::Joystick::HasAxis(ID, sf::Joystick::X) || sf::Joystick::HasAxis(ID, sf::Joystick::Y) || sf::Joystick::HasAxis(ID, sf::Joystick::Z))
        id = ID;
        return true;
    }
    return false;
}

void JoyStick::updatePolaire(void)
{
    if(!running)
        return;
    running = true;
    const double pi(4.0 * atan(1.0));
    vitesse = static_cast<int>(sqrt(Y*Y + X*X ));
    angle = static_cast<int>(((2*atan((-Y)/(X+sqrt(Y*Y+X*X))))+pi/2)*180/pi);
    running = false;
}

void JoyStick::update(void){sf::Joystick::Update();}
bool JoyStick::isConnected(void){return sf::Joystick::IsConnected(id);}

int JoyStick::getAxeX(void){return X;}
int JoyStick::getAxeY(void){return Y;}
int JoyStick::getCurseur(void){return C;}
int JoyStick::getVitesseAbs(void){return vitesse;}
int JoyStick::getAngle(void){return angle;}

void JoyStick::stop(void){boucle = false;}
