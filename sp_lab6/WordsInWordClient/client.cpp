#include "client.h"
#include "../WordsInWordGame/game.h"
#include "../WordsInWordGame/player.h"
#include "../WordsInWordGame/playedgame.h"

#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Client::Client(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &Client::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &Client::disconnected);

    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);

    // Reset the m_loggedIn variable when we disconnect. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void Client::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void Client::loginOrRegister(const string username, const string password, bool isNew)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);

        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("login");
        if(isNew) {
            message["type"] = QStringLiteral("register");
        }

        message["username"] = QString::fromStdString(username);
        message["password"] = QString::fromStdString(password);

        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}

void Client::addNewGame(Game g)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);

        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("addGame");
        QJsonObject* json = new QJsonObject();
        g.toJsonObject(*json);
        message["game"] = *json;

        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}

void Client::playGame() { // must receive Game
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);

        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("playGame");

        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}
void Client::finishPlayingGame(PlayedGame pg) {

    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);

        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("finishGame");
        QJsonObject* json = new QJsonObject();
        pg.toJsonObject(*json);
        message["playedGame"] = *json;

        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}
void Client::getHistory(Player p){ // must receive vector<PlayedGame>
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);

        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("getHistory");
        QJsonObject* json = new QJsonObject();
        p.toJsonObject(*json);
        message["player"] = *json;

        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}

void Client::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));

    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it

    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return; // if we are already logged in we ignore

        const QJsonValue resultVal = docObj.value(QLatin1String("player"));
        if (resultVal.isNull() || !resultVal.isObject())
            return; // no player -> ignore
        Player p;
        p.fromJsonObject(resultVal.toObject());
        emit loggedIn(p);

    } else if (typeVal.toString().compare(QLatin1String("playGame"), Qt::CaseInsensitive) == 0) {

        const QJsonValue resultVal = docObj.value(QLatin1String("game"));
        if (resultVal.isNull() || !resultVal.isObject())
            return; // no game -> ignore
        Game g;
        g.fromJsonObject(resultVal.toObject());
        emit gameStarted(g);

    } else if (typeVal.toString().compare(QLatin1String("history"), Qt::CaseInsensitive) == 0) {

        const QJsonValue resultVal = docObj.value(QLatin1String("history"));
        if (resultVal.isNull() || !resultVal.isArray())
            return; // ignore

        vector<PlayedGame> history;
        QJsonArray arr = resultVal.toArray();
        foreach (const QJsonValue & value, arr) {
            PlayedGame pg;
            pg.fromJsonObject(value.toObject());
            history.push_back(pg);
        }

        emit historyReceived(history);

    }
}

void Client::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}

