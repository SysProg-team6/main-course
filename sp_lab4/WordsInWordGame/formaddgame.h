#ifndef FORMADDGAME_H
#define FORMADDGAME_H
#include "player.h"
#include "gameservices.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormAddGame : public QWidget
{
     Q_OBJECT
public:
    explicit FormAddGame(Player &player, QWidget *parent = nullptr, GameServices *services = nullptr);
    ~FormAddGame();
private slots:
    void AddGame();
    void AddCombination();
    void ImportConbinations();
signals:
    void open();
private:
    Player _player;
    GameServices *_serv;
    QLineEdit *word;
    QLineEdit *inputField;
    QTextEdit *list;
   // QTextEdit *answers;
    QLabel *one;

};

#endif // FORMADDGAME_H
