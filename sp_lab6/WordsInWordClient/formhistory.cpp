#include "formhistory.h"
#include "formaddgame.h"
#include "client.h"

#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QListWidget>


FormHistory::FormHistory(Player &player, Client *client, QWidget *parent) : QWidget(parent) {
    _player = player;
    _client = client;

    setWindowTitle("History");
    setGeometry(100, 100, 800, 600);
    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);

    _historyTE = new QTextEdit(this);
    _historyTE->setGeometry(10, 10, 700, 550);
    _historyTE->setFont( QFont( "lucida", 18));
    _historyTE->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _historyTE->setText("History:\n");

    connect(_client, &Client::historyReceived, this, &FormHistory::displayHistory);
    _client->getHistory(_player);
}

FormHistory::FormHistory(Player &player, QWidget *parent) : QWidget(parent) {
    _player = player;

    setWindowTitle("History");
    setGeometry(100, 100, 800, 600);
    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);
}

void FormHistory::displayHistory(vector<PlayedGame> games) {

    string hist = "History:\n";

    for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
    {
        PlayedGame game = *it;
        hist += game.getTime() + "  score: " + to_string(game.getScore())+"\n";

    }

    _historyTE->setText(QString::fromStdString(hist));
}

FormHistory::~FormHistory(){}
