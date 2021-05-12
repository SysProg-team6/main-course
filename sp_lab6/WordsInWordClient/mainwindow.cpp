#include "mainwindow.h"
#include "formmenu.h"
#include "client.h"

#include <QPalette>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(Client *client, QWidget *parent) : QMainWindow(parent)
{
    _client = client;

    setWindowTitle("Words in word");
    setGeometry(100, 100, 800, 600);

    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);

    login = new QLineEdit(this);
    login->setGeometry(400, 100, 300, 50);
    login->setFont( QFont( "lucida", 18));

    password = new QLineEdit(this);
    password->setGeometry(400, 200, 300, 50);
    password->setFont( QFont( "lucida", 18));

    confirmPassword = new QLineEdit(this);
    confirmPassword->setGeometry(400, 300, 300, 50);
    confirmPassword->setFont( QFont( "lucida", 18));

    newAcc = new QRadioButton("Створити новий акаунт", this);
    newAcc->setGeometry(200, 400, 500, 50);
    newAcc->setFont( QFont( "lucida", 18));
    newAcc->setStyleSheet("background-color: lightblue");

    QLabel *login = new QLabel(this);
    login->setText("Логін :");
    login->setGeometry(200, 100, 125, 50);
    login->setFont( QFont( "lucida", 18));
    login->setStyleSheet("background-color: lightblue");

    QLabel *password = new QLabel(this);
    password->setText("Пароль :");
    password->setGeometry(200, 200, 125, 50);
    password->setFont( QFont( "lucida", 18));
    password->setStyleSheet("background-color: lightblue");

    QLabel *confirm = new QLabel(this);
    confirm->setText("Підтвердіть пароль :");
    confirm->setGeometry(200, 300, 127, 60);
    confirm->setWordWrap(true);
    confirm->setFont( QFont( "lucida", 18));
    confirm->setStyleSheet("background-color: lightblue");

    QPushButton *loginBtn = new QPushButton("Увійти", this);
    loginBtn->setGeometry(370, 500, 150, 50);
    loginBtn->setFont( QFont( "lucida", 18));
    loginBtn->setStyleSheet("background-color: lightblue");
    connect(loginBtn, SIGNAL (released()), this, SLOT (handleButton()));

    connect(_client, &Client::loggedIn, this, &MainWindow::loggedIn);
    connect(_client, &Client::connected, this, &MainWindow::connected);
    connect(_client, &Client::disconnectFromHost, this, &MainWindow::disconnected);
    tryConnect();
}
void MainWindow::handleButton()
{
    if(newAcc->isChecked()){

        if(password->text() != confirmPassword->text()) {
            login->clear();
            password->clear();
            confirmPassword->clear();
            return;
        }

        // Add new player
        _client->loginOrRegister(login->text().toStdString(), password->text().toStdString(), true);

    } else {
        _client->loginOrRegister(login->text().toStdString(), password->text().toStdString(), false);
    }
}
void MainWindow::loggedIn(Player p) {
    _menu = new FormMenu(p, _client);
    connect(_menu, &FormMenu::open, this, &MainWindow::show);
    _menu->show();
    this->close();
}
void MainWindow::disconnected()
{
    // if the client loses connection to the server
    // communicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    tryConnect();
}
void MainWindow::connected()
{

}
void MainWindow::tryConnect()
{
    // We ask the user for the address of the server, we use 127.0.0.1 (aka localhost) as default
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );

    if (hostAddress.isEmpty())
        return; // the user pressed cancel or typed nothing
    _client->connectToServer(QHostAddress(hostAddress), 1967);
}
MainWindow::~MainWindow()
{
    delete(_menu);
    delete palette;
}



