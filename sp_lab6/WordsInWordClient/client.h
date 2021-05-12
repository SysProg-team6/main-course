#ifndef CLIENT_H
#define CLIENT_H

#include "../WordsInWordGame/game.h"
#include "../WordsInWordGame/playedgame.h"
#include "../WordsInWordGame/player.h"

#include <iostream>
#include <vector>
#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

using namespace std;

class Client : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
public:
    explicit Client(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void loginOrRegister(const string username, const string password, bool isNew);
    void addNewGame(Game g);
    void playGame();
    void finishPlayingGame(PlayedGame pg);
    void getHistory(Player p); // must receive vector<PlayedGame>
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn(Player p);
    void disconnected();
    void gameStarted(Game g);
    void historyReceived(vector<PlayedGame> history);
    void error(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
};

#endif // CLIENT_H
