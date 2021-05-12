#ifndef FORMADDGAME_H
#define FORMADDGAME_H
#include "../WordsInWordGame/player.h"
#include "client.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormAddGame : public QWidget
{
     Q_OBJECT
public:
    explicit FormAddGame(Player &player, Client *client, QWidget *parent = nullptr);
    explicit FormAddGame(Player &player, QWidget *parent = nullptr);
    ~FormAddGame();
private slots:
    void AddGame();
    void AddCombination();
    void ImportConbinations();
signals:
    void open();
private:
    Player _player;
    QLineEdit *word;
    QLineEdit *inputField;
    QTextEdit *list;
    QLabel *one;

    Client *_client;
};

#endif // FORMADDGAME_H
