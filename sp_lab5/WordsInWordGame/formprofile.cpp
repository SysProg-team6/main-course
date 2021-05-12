#include "formprofile.h"
#include "player.h"
#include "playerservices.h"
#include "playersrepository.h"

#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QListWidget>
#include<QMessageBox>


FormProfile::FormProfile(Player &player, QWidget *parent, PlayerServices *ps) : QWidget(parent)
{
    _ps = ps;
    _player = player;


    setWindowTitle("Profile");
    setGeometry(100, 100, 800, 600);

    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);


    QString logstr = QString::fromStdString("Login: " + _player.getName());
    QString passstr = QString::fromStdString("Password: " + _player.getPassword());

    login = new QTextEdit(logstr, this);
    login->setGeometry(200, 100, 400, 70);
    login->setReadOnly(true);
    login->setFont( QFont( "lucida", 18) );

    password = new QTextEdit(passstr, this);
    password->setGeometry(200, 300, 400, 70);
    password->setFont( QFont( "lucida", 18) );
}

FormProfile::~FormProfile(){}


