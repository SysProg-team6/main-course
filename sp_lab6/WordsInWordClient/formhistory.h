#ifndef FORMHISTORY_H
#define FORMHISTORY_H

#include "../WordsInWordGame/player.h"
#include "client.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormHistory : public QWidget
{
     Q_OBJECT
public:
    explicit FormHistory(Player &player, Client *client, QWidget *parent = nullptr);
    explicit FormHistory(Player &player, QWidget *parent = nullptr);
    ~FormHistory();
signals:
    void open();
private slots:
    void displayHistory(vector<PlayedGame> history);
private:
    Player _player;
    Client *_client;
    QTextEdit *_historyTE;
};

#endif // FORMHISTORY_H
