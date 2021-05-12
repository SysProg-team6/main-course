#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>

#include "gameservices.h"
#include "playedgamesservices.h"
#include "playerservices.h"

#include "formmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr, PlayerServices *ps = nullptr, PlayedGamesServices *pgs = nullptr, GameServices *gs = nullptr);
    ~MainWindow();
private slots:
    void handleButton();
private:
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *confirmPassword;
    QRadioButton *newAcc;
    QPalette *palette;

    FormMenu *_menu;

    PlayerServices *_ps;
    GameServices *_gs;
    PlayedGamesServices *_pgs;

};
#endif // MAINWINDOW_H


