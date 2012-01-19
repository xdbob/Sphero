#ifndef CORE_H
#define CORE_H

#include <QtGui>
#include "mainwindow.h"
#include "debug.h"
#include "joystick.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    ~Core();
signals:

public slots:

private slots:
    void commande(QString instruction);

private:
    MainWindow* GUI;
    Debug* d;
    JoyStick* joy;
};

#endif // CORE_H
