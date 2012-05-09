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
#include <SFML/Window/Joystick.hpp>
#include <cmath>

class JoyStick : public QThread
{
    Q_OBJECT
public:
    explicit JoyStick(QObject *parent = 0);
    static bool* getJoyStick(void);
    static unsigned int nbJoyStickMax(void);
    int getAxeX(void);
    int getAxeY(void);
    int getCurseur(void);
    bool isConnected(void);
    double getPI(void);
    
signals:
    void AxeX(int);
    void AxeY(int);
    void Curseur(int);
    void Angle(int);
    void Norme(int);
    void Actu(void);
    
public slots:
    bool setAutoJoy(void);//Sélection du premier JoyStick disponible
    bool setJoy(unsigned int ID);//Sélection manuelle d'un JoyStick
    void update(void);//Actualisation
    void stop(void);//Arrêt de la thread
    int getVitesseAbs(void);//Récupération de la vitesse absolue
    int getAngle(void);//Récupération de l'angle des coordonées polaires(°)

private:
    void run(void);//Thread de capture du JoyStick sélectionné
    inline int norme(void);
    inline int angle(void);
    unsigned short id;
    bool boucle;
    double pi;
};

#endif
