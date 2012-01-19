#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    echo = true;
    Message("Déconnecté");
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConsoleInput_returnPressed()
{
    if(ui->ConsoleInput->text() != QString())
    {
        if(echo)
            WriteConsole("<strong>" + ui->ConsoleInput->text() + "</strong>");
        emit ConsoleInput(ui->ConsoleInput->text());
        ui->ConsoleInput->clear();
    }
}

void MainWindow::WriteConsole(QString texte)
{
    ui->Console->append("<span style=\"color: lime;\">" + texte + "</span>");
}

void MainWindow::CleanConsole(){ui->Console->clear();}

void MainWindow::Message(QString texte)
{
    ui->statusbar->showMessage(texte);
}

void MainWindow::setEcho(bool state)
{
    echo = state;
}
