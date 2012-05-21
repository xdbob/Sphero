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
#include "network.h"

NetWork::NetWork(QObject *parent) :
    QThread(parent)
{
    port = 0;
    connect = false;
    logging = false;
    time = new QTimer(this);
    init = false;
    retry = false;
    QObject::connect(time, SIGNAL(timeout()), SLOT(timeout()));
}

NetWork::~NetWork()
{
    if(port != 0)
        delete port;
    delete time;
}

void NetWork::echoPorts(bool verbose)
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    emit Write(tr("Liste des ports"));
    for (int i = 0; i < ports.size(); i++)
    {
        if(verbose)
            emit Write(tr("Nom du port : ") + ports.at(i).portName);
        emit Write(tr("Nom du port (friendName) : ") + ports.at(i).friendName);
        if(verbose)
            emit Write(tr("Adresse physique : ") + ports.at(i).physName);
        emit Write(tr("Type : ") + ports.at(i).enumName);
        if(verbose)
        {
            emit Write("vendor ID:" + QString::number(ports.at(i).vendorID, 16));
            emit Write("product ID:" + QString::number(ports.at(i).productID, 16));
        }
        emit Write("===================================");
    }
}

void NetWork::setPort(QString name)
{
    //Définition des propiétés du port série
    port = new QextSerialPort(name);
    //Vitesse (115200 bits par seconde)
    port->setBaudRate(BAUD115200);
    //Pas de parité
    port->setParity(PAR_NONE);
    //Pas de controle du flux
    port->setFlowControl(FLOW_OFF);
    //8 bits par trame
    port->setDataBits(DATA_8);
    //2 bits pour signaler la fin de la trame
    port->setStopBits(STOP_2);
    //Port en lecture/écriture
    connect = port->open(QIODevice::ReadWrite);
    emit connected(connect);
    if(!connect)
        emit Err(tr("Impossible de se connecter au port ") + name);
    else
    {
        QObject::connect(port, SIGNAL(readyRead()), SLOT(getMessage()));
        QObject::connect(port, SIGNAL(dsrChanged(bool)), SLOT(closed(bool)));
        emit Write(tr("Connection avec le port ") + name + tr(" en cours ..."));
        sendMessage();
    }

}

void NetWork::closed(bool y)
{
    //Si y = false, on déconnecte le port
    if(y == false)
    {
        connect = false;
        emit connected(false);
        delete port;
        port = 0;
        emit Write(tr("Fin de la connection"));
        init = false;
    }
}

bool NetWork::isConnected(void){return connect;}

void NetWork::getMessage(void)
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    port->read(bytes.data(), bytes.size());

    bytesReceived.append(bytes);


    if(bytesReceived.endsWith('\n'))
    {
        if(!bytesReceived.startsWith(0b01011000))
        {
            if(init)
            {
                emit Warning(tr("bug"));
                emit Warning(QString::fromAscii(bytesReceived));
            }
            bytesReceived.clear();
            return;
        }
        bytesReceived.remove(0, 1);
        bytesReceived.remove(bytesReceived.size() - 1, 1);
        if(bytesReceived.startsWith(0b11001100))
        {
            emit Pong();
            time->stop();
            if(!init)
            {
                init = true;
                emit Write(tr("Connection accomplie"));
            }
        }
        else if(bytesReceived.startsWith(0b01101101))
            accelero(bytesReceived);
        else if(bytesReceived.startsWith(0b01101101))
            gyro(bytesReceived);
        if(logging)
            emit log("#LOG NET#" + QString::fromAscii(bytesReceived) + "#LOG NET#");
        bytesReceived.clear();
    }
}

QStringList NetWork::actuPort(void)
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    QStringList liste;
    for (int i = 0; i < ports.size(); i++)
        liste << ports.at(i).portName;
    return liste;
}

void NetWork::deco()
{
    if(isConnected())
    {
        closed(false);
    }
}

void NetWork::sendMessage(int commande, QList<unsigned char> var, QList<unsigned char> var2)
{
    if(!isConnected())
    {
        emit Err(tr("Impossible d'envoyer le message, le module n'est pas connecté"));
        return;
    }
    QByteArray message;
    unsigned char octet(0b01010010);
    message.append(octet);
    switch(commande)
    {
    case NetWork::ping:
        octet = 0b11001100;
        message.append(octet);
        time->start(500);
        break;
    case NetWork::getAccelero:
        octet = 0b10110110;
        message.append(octet);
        break;
    case NetWork::getGyro:
        octet = 0b01101101;
        message.append(octet);
        break;
    case NetWork::moteur:
        octet = 0b10101010;
        message.append(octet);
        if(var.size() != 3 || var2.size() != 3)
        {
            emit Err(tr("Erreur commande moteur : arguments"));
            return;
        }
        else if((var2[0] != 0b00000000 && var2[0] != 0b11111111) ||
                (var2[1] != 0b00000000 && var2[1] != 0b11111111) ||
                (var2[2] != 0b00000000 && var2[2] != 0b11111111))
        {
            emit Err(tr("Erreur commande moteur : arguments"));
            return;
        }
        else
        {
            message.append(var[0]);
            message.append(var2[0]);
            message.append(var[1]);
            message.append(var2[1]);
            message.append(var[2]);
            message.append(var2[2]);
        }
        break;
    case NetWork::stopall:
        octet = 0b01110111;
        message.append(octet);
        break;
    case NetWork::blink:
        octet = 0b01010101;
        if(var.size() != 1)
        {
            emit Err(tr("Erreur Blink : arguments"));
            return;
        }
        message.append(octet);
        message.append(var[0]);
        break;
    default:
        emit Warning(tr("Réseau : Commande inconnue"));
        return;
        break;
    }
    message.append('\n');
    port->write(message);
}

void NetWork::accelero(QByteArray datas)
{
    //not implemented yet
}

void NetWork::gyro(QByteArray datas)
{
    //not implemented yet
}

void NetWork::pingpong(void)
{
    //not implemented yet
}

void NetWork::timeout(void)
{
    emit Err(tr("ping timeout : la connection avec avec le module à échouée"));
    if(!retry)
    {
        emit Warning(tr("Tentative de reconnection"));
        time->stop();
        sendMessage();
    }
    else
    {
        deco();
        time->stop();
    }
}
