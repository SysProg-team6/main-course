#ifndef FORMNEWGAME_H
#define FORMNEWGAME_H

#include "../WordsInWordGame/player.h"
#include "../WordsInWordGame/game.h"
#include "../WordsInWordGame/playedgame.h"
#include "client.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormNewGame : public QWidget
{
     Q_OBJECT
public:
    explicit FormNewGame(Player &player, Client *client, QWidget *parent = nullptr);
    explicit FormNewGame(Player &player, QWidget *parent = nullptr);
    ~FormNewGame();
private slots:
    void EnterWord();
    void FinishGame();
    void startGame(Game g);
signals:
    void open();
private:
    QLineEdit *inputField;
    QTextEdit *word;
    QLabel *score;
    QTextEdit *list;
    QTextEdit *scoreText;

    Game _game;
    Player _player;
    PlayedGame *_playedGame;

    Client *_client;
};
#endif
