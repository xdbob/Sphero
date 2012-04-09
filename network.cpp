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
}

NetWork::~NetWork()
{
    if(port != 0)
        delete port;
}

void NetWork::setGUI(MainWindow *interface)
{
    GUI = interface;
}

void NetWork::echoPorts(bool verbose)
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    GUI->WriteConsole(tr("Liste des ports"));
    for (int i = 0; i < ports.size(); i++)
    {
        if(verbose)
            GUI->WriteConsole(tr("Nom du port :") + ports.at(i).portName, MainWindow::reseau);
        GUI->WriteConsole(tr("Nom du port (friendName) : ") + ports.at(i).friendName, MainWindow::reseau);
        if(verbose)
            GUI->WriteConsole(tr("Adresse physique : ") + ports.at(i).physName, MainWindow::reseau);
        GUI->WriteConsole(tr("Type : ") + ports.at(i).enumName, MainWindow::reseau);
        if(verbose)
        {
            GUI->WriteConsole("vendor ID:" + QString::number(ports.at(i).vendorID, 16), MainWindow::reseau);
            GUI->WriteConsole("product ID:" + QString::number(ports.at(i).productID, 16), MainWindow::reseau);
        }
        GUI->WriteConsole("===================================");
    }
}

void NetWork::setPort(QString name)
{
    port = new QextSerialPort(name);
    port->setBaudRate(BAUD115200);
    port->setParity(PAR_NONE);
    port->setFlowControl(FLOW_OFF);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    connect = port->open(QIODevice::ReadWrite);
    emit connected(connect);
    if(!connect)
        GUI->WriteConsole(tr("Impossible de se connecter au port ") + name, MainWindow::warning);
    else
    {
        QObject::connect(port, SIGNAL(readyRead()), SLOT(getMessage()));
        QObject::connect(port, SIGNAL(dsrChanged(bool)), SLOT(closed(bool)));
        GUI->WriteConsole(tr("Connection avec le port ") + name + tr(" effectuée"), MainWindow::reseau);
    }

}

void NetWork::closed(bool y)
{
    if(y == false)
    {
        connect = false;
        emit connected(false);
        delete port;
        port = 0;
        GUI->WriteConsole(tr("Fin de la connection"), MainWindow::reseau);
    }
}

bool NetWork::isConnected(void){return connect;}

void NetWork::getMessage(void)
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    port->read(bytes.data(), bytes.size());
    //qDebug() << "bytes read:" << bytes.size();

    bytesReceived.append(bytes);

    // only do input if all of it has been received.
    // without this the serial port transports line of messages
    // with only 3 or 4 bytes at a time
    if(bytes.contains('\n'))
    {
        GUI->WriteConsole(QString::fromAscii(bytesReceived), MainWindow::reseau);
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
