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
    update();
    if(!setAutoJoy())
        id = 25;
}

void JoyStick::run()
{
    if(!sf::Joystick::IsConnected(id))
        return;
    while(1)
    {
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
}

bool JoyStick::setAutoJoy()
{
    for (unsigned short i(0); i < sf::Joystick::Count; i++)
    {
        if(sf::Joystick::IsConnected(i))
        {
            id = i;
            return true;
        }
    }
    return false;
}

bool JoyStick::setJoy(unsigned short ID)
{
    if(sf::Joystick::IsConnected(ID))
    {
        if(sf::Joystick::HasAxis(ID, sf::Joystick::X))// || sf::Joystick::HasAxis(ID, sf::Joystick::HasAxis(ID, sf::Joystick::Y)))
        id = ID;
        return true;
    }
    return false;
}

void JoyStick::update(){sf::Joystick::Update();}
bool JoyStick::isConnected(){return sf::Joystick::IsConnected(id);}

int JoyStick::getAxeX(){return X;}
int JoyStick::getAxeY(){return Y;}
int JoyStick::getCurseur(){return C;}
