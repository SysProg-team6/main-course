#ifndef FORMNEWGAME_H
#define FORMNEWGAME_H
#include "player.h"
#include "game.h"
#include "playedgame.h"

#include "gameservices.h"
#include "playedgamesservices.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormNewGame : public QWidget
{
     Q_OBJECT
public:
    explicit FormNewGame(Player &player, PlayedGamesServices *pgs, GameServices *gs, QWidget *parent = nullptr);
    ~FormNewGame();
private slots:
    void EnterWord();
    void FinishGame();
signals:
    void open();
private:
    Player _player;
    QLineEdit *inputField;
    QTextEdit *word;
    QLabel *score;
    QTextEdit *list;
    QTextEdit *scoreText;

    PlayedGamesServices *_pgs;
    GameServices *_gs;
    Game _game;

    PlayedGame *_playedGame;
};
#endif
