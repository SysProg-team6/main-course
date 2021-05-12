#include "formnewgame.h"
#include "player.h"
#include "playedgame.h"
#include "game.h"
#include <QPushButton>
#include <QLabel>
#include <QString>


FormNewGame::FormNewGame(Player &player,PlayedGamesServices *pgs, GameServices *gs, QWidget *parent) : QWidget(parent)
{
    _player = player;
    _pgs = pgs;
    _gs = gs;

    Game g = gs->getRandomGame();
    _game = g;
    _playedGame = new PlayedGame();
    _playedGame->setGameId(g.getId());
    _playedGame->setPlayerId(_player.getId());
    _playedGame->setScore(0);

    setWindowTitle("New game");
    setGeometry(100, 100, 800, 600);

    QPixmap bkgnd("C:/Users/admin/Documents/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);


    word = new QTextEdit("Some text here.", this);
    word->setGeometry(50, 150, 450, 100);
    word->setReadOnly(true);
    word->setFont( QFont( "lucida", 42, QFont::Bold) );
    word->setText(QString::fromStdString(g.getWord()));

    inputField = new QLineEdit(this);
    inputField->setGeometry(50, 350, 280, 40);
    inputField->setFont( QFont( "lucida", 22));

    scoreText = new QTextEdit(this);
    scoreText->setGeometry(680, 30, 100, 50);
    scoreText->setFont( QFont( "lucida", 20));

    list = new QTextEdit(this);
    list->setGeometry(530, 150, 250, 400);
    list->setFont( QFont( "lucida", 22));
    list->setReadOnly(true);



    QPushButton *okButton = new QPushButton("OK", this);
    okButton->setGeometry(400, 350, 60, 40);
    okButton->setFont( QFont( "lucida", 22) );
    okButton->setStyleSheet("background-color:white");
    connect(okButton, SIGNAL (released()), this, SLOT (EnterWord()));

    QPushButton *finish = new QPushButton("Finish", this);
    finish->setGeometry(400, 500, 100, 40);
    finish->setFont( QFont( "lucida", 22) );
    finish->setStyleSheet("background-color:white");
    connect(finish, SIGNAL (released()), this, SLOT (FinishGame()));

}
string combin = "";

void FormNewGame::EnterWord()
{
    std::string word = inputField->text().toStdString();
    bool isCombination = _game.isMatch(word);
    if(isCombination && combin.find(word) == string::npos){
        int s = _playedGame->getScore() + 10;
        _playedGame->setScore(s);
        scoreText->setText(QString::fromStdString(to_string(s)));
        combin += word + "\n";
    }

    list->setText(QString::fromStdString(combin));
    inputField->clear();
}

void FormNewGame::FinishGame(){
    _pgs->addPlayedGame(*_playedGame);
    this->close();
}
FormNewGame::~FormNewGame()
{
}
