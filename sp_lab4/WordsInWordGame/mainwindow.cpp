#include "mainwindow.h"
#include "formmenu.h"
#include <QPalette>

#include "playerservices.h"
#include "playersrepository.h"

#include <QPushButton>
#include<QRadioButton>



MainWindow::MainWindow(QWidget *parent, PlayerServices *ps, PlayedGamesServices *pgs, GameServices *gs) : QMainWindow(parent)
{
     _ps = ps;
     _gs = gs;
     _pgs = pgs;

    setWindowTitle("Words in word");
    setGeometry(100, 100, 800, 600);

    QPixmap bkgnd("C:/Users/admin/Documents/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);


    login = new QLineEdit(this);
    login->setGeometry(400, 100, 300, 50);
    login->setFont( QFont( "lucida", 18));

    password = new QLineEdit(this);
    password->setGeometry(400, 200, 300, 50);
    password->setFont( QFont( "lucida", 18));

    confirmPassword = new QLineEdit(this);
    confirmPassword->setGeometry(400, 300, 300, 50);
    confirmPassword->setFont( QFont( "lucida", 18));

    newAcc = new QRadioButton("Створити новий акаунт", this);
    newAcc->setGeometry(200, 400, 500, 50);
    newAcc->setFont( QFont( "lucida", 18));
    newAcc->setStyleSheet("background-color: lightblue");

    QLabel *login = new QLabel(this);
    login->setText("Логін :");
    login->setGeometry(200, 100, 125, 50);
    login->setFont( QFont( "lucida", 18));
    login->setStyleSheet("background-color: lightblue");


    QLabel *password = new QLabel(this);
    password->setText("Пароль :");
    password->setGeometry(200, 200, 125, 50);
    password->setFont( QFont( "lucida", 18));
    password->setStyleSheet("background-color: lightblue");


    QLabel *confirm = new QLabel(this);
    confirm->setText("Підтвердіть пароль :");
    confirm->setGeometry(200, 300, 127, 60);
    confirm->setWordWrap(true);
    confirm->setFont( QFont( "lucida", 18));
    confirm->setStyleSheet("background-color: lightblue");

    QPushButton *loginBtn = new QPushButton("Увійти", this);
    loginBtn->setGeometry(370, 500, 150, 50);
    loginBtn->setFont( QFont( "lucida", 18));
    loginBtn->setStyleSheet("background-color: lightblue");
    connect(loginBtn, SIGNAL (released()), this, SLOT (handleButton()));
}
void MainWindow::handleButton()
{
    if(newAcc){
        // Add new player
        bool isOk = _ps->registerNewPlayer(login->text().toStdString(), password->text().toStdString(), confirmPassword->text().toStdString());

        if(isOk) {
            Player p = _ps->logIn(login->text().toStdString(), password->text().toStdString());
            _menu = new FormMenu(p, _ps, _pgs, _gs);
            connect(_menu, &FormMenu::open, this, &MainWindow::show);
            _menu->show();
            this->close();
        } else {
            login->clear();
            password->clear();
            confirmPassword->clear();
        }

    } else {
        Player p = _ps->logIn(login->text().toStdString(), password->text().toStdString());
        _menu = new FormMenu(p, _ps, _pgs, _gs);
        connect(_menu, &FormMenu::open, this, &MainWindow::show);
        _menu->show();
        this->close();
    }
}
MainWindow::~MainWindow()
{
    delete(_menu);
    delete palette;
}

