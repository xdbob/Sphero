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
#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QStringList>
#include <QList>
#include <QTimer>
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "mainwindow.h"

class NetWork : public QThread
{
    Q_OBJECT

public:
    explicit NetWork(QObject *parent = 0);
    ~NetWork();
    bool isConnected(void);
    QStringList actuPort(void);//Retourne tous les ports série (virtuels et réels) de l'ordinateur
    enum {moteur, getGyro, getAccelero, ping, stopall, blink};
    
signals:
    void connected(bool);
    void Gyroscope(QList<int>);
    void Acceleroscope(QList<int>);
    void Pong(void);
    void Write(QString);
    void Err(QString);
    void Warning(QString);
    void log(QString);
    
public slots:
    void echoPorts(bool verbose = false);//Affiche tous les ports série
    void setPort(QString name);//Sélectionner && se connecter au port "name"
    void deco(void);//Se déconnecter
    //Envoyer un message au module
    void sendMessage(int commande = NetWork::ping, QList<unsigned char> var = QList<unsigned char>(), QList<unsigned char> var2 = QList<unsigned char>());

private slots:
    void getMessage(void);
    void closed(bool y);
    void pingpong(void);
    void timeout(void);

private:
    QextSerialPort* port;
    bool connect;
    QByteArray bytesReceived;
    inline void gyro(QByteArray datas);
    inline void accelero(QByteArray datas);
    bool logging;
    QTimer* time;
    bool init;
    bool retry;
};

#endif // NETWORK_H
