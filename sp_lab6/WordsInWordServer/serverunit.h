#ifndef SERVERUNIT_H
#define SERVERUNIT_H

#include "server.h"

#include <QWidget>
#include <QPlainTextEdit>
#include <QPushButton>

class ServerUnit : public QWidget
{
public:
    ServerUnit(Server* server, QWidget *parent = nullptr);
    ~ServerUnit();
public slots:
    void log(const QString& msg);
    void startServer();
private:
    Server* _server;
    QPlainTextEdit* _logger;
    QPushButton* _startBtn;
};

#endif // SERVERUNIT_H
