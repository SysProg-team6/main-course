#include "formmenu.h"
#include "main.cpp"
#include "formnewgame.h"
#include "formaddgame.h"
#include "formhistory.h"
#include "formprofile.h"

#include "gameservices.h"
#include "playedgamesservices.h"
#include "playerservices.h"

#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

FormMenu::FormMenu(Player &player, PlayerServices *ps, PlayedGamesServices *pgs, GameServices *gs, QWidget *parent) : QWidget(parent)

{
    _player = player;

    _pgs = pgs;
    _gs = gs;
    _ps = ps;

    _formHistory = new FormHistory(_player, nullptr, _pgs);
    _formProfile = new FormProfile(_player, nullptr, _ps);
    _formAddGame = new FormAddGame(_player, nullptr, _gs);
    _formNewGame = new FormNewGame(_player, _pgs, _gs);

    connect(_formProfile, &FormProfile::openForm, this, &FormMenu::openProfileForm);
    connect(_formAddGame, &FormAddGame::open, this, &FormMenu::openAddGameForm);
    connect(_formHistory, &FormHistory::open, this, &FormMenu::openHistoryForm);
    connect(_formNewGame, &FormNewGame::open, this, &FormMenu::openGameForm);

    setGeometry(100, 100, 800, 600);
    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);

    QPushButton *newGameBtn = new QPushButton("Нова гра", this);
    newGameBtn->setGeometry(120, 70, 210, 160);
    newGameBtn->setFont( QFont( "lucida", 21));
    newGameBtn->setStyleSheet("background-color: white");
    connect(newGameBtn, SIGNAL (released()), this, SLOT (openGameForm()));


    QPushButton *addGameBtn = new QPushButton("Додати гру", this);
    addGameBtn->setGeometry(420, 70, 210, 160);
    addGameBtn->setFont( QFont( "lucida", 21));
    addGameBtn->setStyleSheet("background-color: white");
    connect(addGameBtn, SIGNAL (released()), this, SLOT (openAddGameForm()));


    QPushButton *profileBtn = new QPushButton("Профіль", this);
    profileBtn->setGeometry(120, 300, 210, 160);
    profileBtn->setFont( QFont( "lucida", 21));
    profileBtn->setStyleSheet("background-color: white");
    connect(profileBtn, SIGNAL (released()), this, SLOT (openProfileForm()));


    QPushButton *ratingBtn = new QPushButton("Історія", this);
    ratingBtn->setGeometry(420, 300, 210, 160);
    ratingBtn->setFont( QFont( "lucida", 21));
    ratingBtn->setStyleSheet("background-color: white");
    connect(ratingBtn, SIGNAL (released()), this, SLOT (openHistoryForm()));


    QPushButton *exitBtn = new QPushButton("Вийти", this);
    exitBtn->setGeometry(650, 500, 120, 70);
    exitBtn->setFont( QFont( "lucida", 19));
    exitBtn->setStyleSheet("background-color: darkgrey");
    connect(exitBtn, SIGNAL (released()), this, SLOT (exit()));
}



FormMenu::~FormMenu()
{

}

void FormMenu::openGameForm(){
    _formNewGame = new FormNewGame(_player, _pgs, _gs);
    _formNewGame->show();
}
void FormMenu::openAddGameForm(){
    _formAddGame = new FormAddGame(_player, nullptr, _gs);
    _formAddGame->show();
}

void FormMenu::openProfileForm(){
    _formProfile = new FormProfile(_player, nullptr, _ps);
    _formProfile->show();
}

void FormMenu:: openHistoryForm(){
    _formHistory = new FormHistory(_player, nullptr, _pgs);
    _formHistory->show();
}

void FormMenu:: exit(){
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,"Вихід","Ви впевнені, що хочете вийти?",
                                        QMessageBox::Ok| QMessageBox::Cancel);
    msgBox->setGeometry(400, 300, 100, 40);

       if(msgBox->exec() == QMessageBox::Ok)
       {
           QApplication::quit();
       }

      delete msgBox;
}
