#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#include <vector>

#include "server.h"

using namespace std;

Server::Server(GameServices *gs, PlayerServices *ps, PlayedGamesServices *pgs, QObject *parent)
    : QTcpServer(parent)
{
    _gs = gs;
    _ps = ps;
    _pgs = pgs;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    ServerWorker *worker = new ServerWorker(this);
    // we attempt to bind the worker to the client
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        // if we fail we clean up
        worker->deleteLater();
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&Server::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    _clients.append(worker);
    // we log the event
    emit logMessage(QStringLiteral("New client Connected"));
}

void Server::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination); // make sure destination is not null
    destination->sendJson(message); // call directly the worker method
}

void Server::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    // iterate over all the workers that interact with the clients
    for (ServerWorker *worker : _clients) {
        if (worker == exclude)
            continue; // skip the worker that should be excluded
        sendJson(worker, message); //send the message to the worker
    }
}

void Server::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->getPlayer() == nullptr)
        return jsonFromLoggedOut(sender, doc);

    jsonFromLoggedIn(sender, doc);
}

void Server::userDisconnected(ServerWorker *sender)
{
    _clients.removeAll(sender);
    sender->deleteLater();
}

void Server::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + QString::fromStdString(sender->getPlayer()->getName()));
}

void Server::stopServer()
{
    for (ServerWorker *worker : _clients) {
        worker->disconnectFromClient();
    }
    close();
}

void Server::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;

    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0 && typeVal.toString().compare(QLatin1String("register"), Qt::CaseInsensitive) != 0 )
        return;

    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    const QJsonValue passwordVal = docObj.value(QLatin1String("password"));

    if (usernameVal.isNull() || !usernameVal.isString() || passwordVal.isNull() || !passwordVal.isString())
        return;

    const QString username = usernameVal.toString().simplified();
    const QString password = passwordVal.toString().simplified();

    if (username.isEmpty() || password.isEmpty())
        return;

    Player p;

    if(typeVal.toString().compare(QLatin1String("register"), Qt::CaseInsensitive) == 0) {
        _ps->registerNewPlayer(username.toLocal8Bit().toStdString(), password.toLocal8Bit().toStdString(), password.toLocal8Bit().toStdString());
    }

    p = _ps->logIn(username.toLocal8Bit().toStdString(), password.toLocal8Bit().toStdString());
    sender->setPlayer(&p);

    QJsonObject successMessage;
    QJsonObject player;
    p.toJsonObject(player);
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("player")] = player;
    sendJson(sender, successMessage);
}

void Server::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;

    if (typeVal.toString().compare(QLatin1String("addGame"), Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value(QLatin1String("game"));
        if (textVal.isNull() || !textVal.isObject())
            return;
        const QJsonObject json = textVal.toObject();
        Game g;
        g.fromJsonObject(json);
        if(g.getWord() == "") {
            return;
        }
        _gs->addNewGame(g);

    } else if (typeVal.toString().compare(QLatin1String("playGame"), Qt::CaseInsensitive) == 0) {

        Game g = _gs->getRandomGame();
        QJsonObject json;
        g.toJsonObject(json);

        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("playGame");
        message[QStringLiteral("game")] = json;
        sendJson(sender, message);

    } else if (typeVal.toString().compare(QLatin1String("finishGame"), Qt::CaseInsensitive) == 0) {

        const QJsonValue textVal = docObj.value(QLatin1String("playedGame"));
        if (textVal.isNull() || !textVal.isObject())
            return;
        const QJsonObject json = textVal.toObject();
        PlayedGame g;
        g.fromJsonObject(json);
        if(g.getTime() == "") {
            return;
        }
        _pgs->addPlayedGame(g);

    } else if (typeVal.toString().compare(QLatin1String("getHistory"), Qt::CaseInsensitive) == 0) {

        const QJsonValue textVal = docObj.value(QLatin1String("player"));
        if (textVal.isNull() || !textVal.isObject())
            return;
        const QJsonObject json = textVal.toObject();
        Player p;
        p.fromJsonObject(json);
        if(p.getId() == sender->getPlayer()->getId()) {
            return;
        }

        vector<PlayedGame> history = _pgs->getHistory(p.getId());
        QJsonArray historyJson;
        foreach (const PlayedGame& pg, history) {
            QJsonObject json;
            pg.toJsonObject(json);
            historyJson.push_back(json);
        }

        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("history");
        message[QStringLiteral("history")] = historyJson;
        sendJson(sender, message);

    }

}
