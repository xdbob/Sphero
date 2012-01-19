#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void WriteConsole(QString texte);
    void CleanConsole(void);
    void Message(QString texte);
    void setEcho(bool state);

private slots:
    void on_ConsoleInput_returnPressed();

signals:
    void ConsoleInput(QString);

private:
    Ui::MainWindow *ui;
    bool echo;
};

#endif // MAINWINDOW_H
