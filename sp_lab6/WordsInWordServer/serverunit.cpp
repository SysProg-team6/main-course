#include "serverunit.h"
#include "server.h"

#include <iostream>

using namespace std;

ServerUnit::ServerUnit(Server* server, QWidget* parent)
{
    _server = server;
    connect(_server, &Server::logMessage, this, &ServerUnit::log);

    this->setWindowTitle("WordsInWord server");

    _logger = new QPlainTextEdit(this);
    _logger->setReadOnly(true);
    _logger->setGeometry(0, 0, 400, 300);
    _logger->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    _startBtn = new QPushButton(this);
    _startBtn->setText("Start/Stop server");
    _startBtn->setGeometry(300, 310, 100, 20);

    connect(_startBtn, &QPushButton::released, this, &ServerUnit::startServer);
}

void ServerUnit::startServer()
{
    if (_server->isListening()) {
        _server->stopServer();
        log(QStringLiteral("Server Stopped"));
    } else {
        if (!_server->listen(QHostAddress::Any, 1967)) {
            log(QStringLiteral("Unable to start the server"));
            return;
        }
        log(QStringLiteral("Server Started"));
    }
}
ServerUnit::~ServerUnit() {}
void ServerUnit::log(const QString &msg)
{
    _logger->appendPlainText(msg + QLatin1Char('\n'));
}
