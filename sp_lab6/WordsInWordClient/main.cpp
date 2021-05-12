#include "mainwindow.h"
#include "client.h"

#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client* client = new Client();
    MainWindow *w = new MainWindow(client);
    w->show();

    int code = a.exec();

    delete(w);

    return code;
}
