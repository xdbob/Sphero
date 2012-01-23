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
    if(!setAutoJoy())//S�lection du premier JoyStick disponible
        id = 25;//Sinon affecter une valeure � l'id du joystick
}

void JoyStick::run(void)
{
    boucle = true;
    if(!sf::Joystick::IsConnected(id))//V�rification de la connection du JoyStick
        return;//Sinon on ne lance pas la thread
    while(boucle)
    {
        //Actualisation en temps r�el des diff�rents Axes
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
    //Remise des valeures � 0 avant de Quitter la thread
    X = 0;
    Y = 0;
    C = 0;
}

bool JoyStick::setAutoJoy(void)
{
    //Parcours des diff�rents JoySticks pouvant �tre connect�s
    for (unsigned short i(0); i < sf::Joystick::Count; i++)
    {
        //S�lection du premier JoyStick disponible
        if(setJoy(i))
            return true;
    }
    return false;
}

bool JoyStick::setJoy(unsigned short ID)
{
    if(sf::Joystick::IsConnected(ID))
    {
        //V�rifier si le JoyStick � suffisament d'axes
        if(sf::Joystick::HasAxis(ID, sf::Joystick::X) || sf::Joystick::HasAxis(ID, sf::Joystick::Y) || sf::Joystick::HasAxis(ID, sf::Joystick::Z))
        id = ID;
        return true;
    }
    return false;
}

void JoyStick::update(void){sf::Joystick::Update();}
bool JoyStick::isConnected(void){return sf::Joystick::IsConnected(id);}

int JoyStick::getAxeX(void){return X;}
int JoyStick::getAxeY(void){return Y;}
int JoyStick::getCurseur(void){return C;}

void JoyStick::stop(void){boucle = false;}
