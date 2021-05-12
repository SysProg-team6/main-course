#include "formhistory.h"
#include "formaddgame.h"
#include "game.h"
#include "gameservices.h"
#include "gamesrepository.h"
#include "playedgame.h"
#include "playedgamesservices.h"
#include "playedgamesrepository.h"

#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QListWidget>


FormHistory::FormHistory(Player &player,QWidget *parent, PlayedGamesServices *services) : QWidget(parent)
{
    _player = player;
    _serv = services;
    vector<PlayedGame> games = _serv->getHistory(_player.getId());

    setWindowTitle("History");
    setGeometry(100, 100, 800, 600);
    QPixmap bkgnd("C:/Users/admin/Documents/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);

    QTextEdit *history = new QTextEdit(this);
     history->setGeometry(10, 10, 700, 550);
     history->setFont( QFont( "lucida", 18));
     history->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

     string hist = "History:\n";

     for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
     {
         PlayedGame game = *it;
         hist+= game.getTime() + "  score: " + to_string(game.getScore())+"\n";

     }

     history->setText(QString::fromStdString(hist));

}

FormHistory::~FormHistory(){}

