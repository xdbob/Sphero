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
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QThread>
#include <QStringList>
#include <SFML/Window/Joystick.hpp>

class JoyStick : public QThread
{
    Q_OBJECT
public:
    explicit JoyStick(QObject *parent = 0);
    int getAxeX();
    int getAxeY();
    int getCurseur();
    bool isConnected();
    
signals:
    void AxeX(int);
    void AxeY(int);
    void Curseur(int);
    
public slots:
    bool setAutoJoy();
    bool setJoy(unsigned short ID);
    void update();

private:
    void run();
    float X;
    float Y;
    float C;
    unsigned short id;
};

#endif // JOYSTICK_H
