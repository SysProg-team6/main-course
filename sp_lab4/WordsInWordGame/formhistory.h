#ifndef FORMHISTORY_H
#define FORMHISTORY_H

#include "player.h"
#include "playedgamesservices.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormHistory : public QWidget
{
     Q_OBJECT
public:
    explicit FormHistory(Player &player, QWidget *parent = nullptr, PlayedGamesServices *services = nullptr);
    ~FormHistory();
signals:
    void open();
private slots:

private:
    Player _player;
    PlayedGamesServices *_serv;
};

#endif // FORMHISTORY_H
