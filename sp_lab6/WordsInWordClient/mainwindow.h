#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>

#include "formmenu.h"
#include "client.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(Client *client, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleButton();
    void connected();
    void loggedIn(Player p);
    void disconnected();
    void tryConnect();
private:
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *confirmPassword;
    QRadioButton *newAcc;
    QPalette *palette;

    FormMenu *_menu;

    Client *_client;
};
#endif // MAINWINDOW_H
