#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    GUI = new MainWindow;
    GUI->show();

    joy = new JoyStick;

    d = 0;

    QObject::connect(GUI, SIGNAL(ConsoleInput(QString)), this, SLOT(commande(QString)));
}

Core::~Core()
{
    delete GUI;
    if(d != 0)
        delete d;
    delete joy;
}

void Core::commande(QString instruction)
{
    if(instruction == "quit" || instruction == "exit")
    {
        GUI->WriteConsole("Quitter...");
        qApp->quit();
    }
    else if(instruction[0] == 'e' && instruction[1] == 'c' && instruction[2] == 'h' && instruction[3] == 'o' && instruction[4] == ' ')
    {
        GUI->WriteConsole(instruction.remove(0, 5));
    }
    else if(instruction == "debug init")
    {
        d = new Debug;
        GUI->WriteConsole("Création du module de debug");
    }
    else if(instruction == "debug")
    {
        if(d != 0)
        {
            GUI->WriteConsole("Ouverture de la fenêtre de Debug");
            d->show();
        }
        else
        {
            GUI->WriteConsole("Erreur lors de l'ouverture de la fenêtre de Debug.");
            GUI->WriteConsole("Le module Debug n'est pas initialisé");
        }
    }
    else if(instruction[0] == 'c' && instruction[1] == 'l' && instruction[2] == 'e' && instruction[3] == 'a' && instruction[4] == 'n' && instruction[5] == ' ')
    {
        if(instruction.remove(0, 6) == "true" || instruction.remove(0, 6) == "1")
            GUI->setEcho(true);
        else
            GUI->setEcho(false);
    }
    else
    {
        GUI->WriteConsole("instruction non comprise ...");
    }
}
