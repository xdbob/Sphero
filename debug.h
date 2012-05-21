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
#ifndef DEBUG_H
#define DEBUG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QList>
#include "joystick.h"
#include "ui_debug.h"

namespace Ui {
class Debug;
}

class Debug : public QDialog
{
    Q_OBJECT
    
public:
    explicit Debug(void);
    ~Debug(void);
    bool canWrite(void);

public slots:
    void log(QString chaine);//Traitement des sorties pour le log
    //Actualisation des marqueurs widgets de l'interface graphique
    void setJoyX(int value);
    void setJoyY(int value);
    void setJoyC(int value);
    void setJoyAngle(int value);
    void setJoyNorme(int value);
    void setVitesses(QList<int> value);

private:
    Ui::Debug *ui;
    QFile* fichier;
    QTextStream* flux;
    bool writable;
};

#endif
