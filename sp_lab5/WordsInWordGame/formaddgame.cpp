#include "formaddgame.h"
#include "game.h"
#include "gameservices.h"
#include "gamesrepository.h"

#include <QPushButton>
#include<QMessageBox>
#include <QLabel>
#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
using namespace std;

FormAddGame::FormAddGame(Player &player,QWidget *parent, GameServices *services) : QWidget(parent)
{
    _player = player;
    _serv = services;
    string combinations;


    setWindowTitle("Add game");
    setGeometry(100, 100, 800, 600);
    QPixmap bkgnd("C:/Users/Olena/source/c++/WordsInWordGame/Resources/1.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette *palette = new QPalette;
    palette->setBrush(QPalette::Window, bkgnd);
    this->setPalette(*palette);

    word = new QLineEdit(this);
    word->setGeometry(50, 50, 350, 100);
    word->setFont( QFont( "lucida", 24, QFont::Bold) );
    word->setText("Слово");

    inputField = new QLineEdit(this);
    inputField->setGeometry(50, 230, 350, 50);
    inputField->setFont( QFont( "lucida", 22));

    list = new QTextEdit(this);
    list->setGeometry(530, 50, 250, 400);
    list->setFont( QFont( "lucida", 22));
    list->setReadOnly(true);

    //Buttons

    QPushButton *addCombination = new QPushButton("Додати комбінацію", this);
    addCombination->setGeometry(50, 350, 250, 70);
    addCombination->setFont( QFont( "lucida", 18) );
    addCombination->setStyleSheet("background-color:lightblue");
    connect(addCombination, SIGNAL (released()), this, SLOT (AddCombination()));


    QPushButton *addGameBtn = new QPushButton("Додати гру", this);
    addGameBtn->setGeometry(530, 500, 250, 70);
    addGameBtn->setFont( QFont( "lucida", 18) );
    connect(addGameBtn, SIGNAL (released()), this, SLOT (AddGame()));
    addGameBtn->setStyleSheet("background-color: lightblue");

    QPushButton *importCombBtn = new QPushButton("Відкрити файл", this);
    importCombBtn->setGeometry(50, 500, 250, 70);
    importCombBtn->setFont( QFont( "lucida", 18) );
    connect(importCombBtn, SIGNAL (released()), this, SLOT (ImportConbinations()));
    importCombBtn->setStyleSheet("background-color: lightblue");


}

FormAddGame::~FormAddGame()
{
}
std::vector<string> *comb = new vector<string>();

void FormAddGame::AddCombination(){
    if(inputField->text().toStdString().length()>1){
        comb->push_back(inputField->text().toStdString());
    }
    string text = "";
    for(auto s : *comb){
        text+=s+"\n";
    }
    list->setText(QString::fromStdString(text));
    inputField->clear();

}

void FormAddGame::ImportConbinations()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Text File", "../", "Text files(*.txt);;All files (*.*)");
    if(!path.isEmpty())
    {
        QFile myFile(path);
        if (myFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&myFile);
            QString allText;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                allText.append(line);
                allText.push_back('\n');
                comb->push_back(line.toLocal8Bit().constData());
            }

            list->setText(allText);
            myFile.close();
        }
    }
}
void FormAddGame::AddGame(){
    Game *g = new Game();
    if(word->text().toStdString().length()<3){
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,"Помилка","Слово було задано невірно",
                                            QMessageBox::Ok);
        msgBox->setGeometry(400, 300, 100, 40);

           if(msgBox->exec() == QMessageBox::Ok)
           {
               delete msgBox;
           }

    }
    g->setWord(word->text().toStdString());
    g->setCombinations(*comb);
    g->setAuthorId(_player.getId());
    _serv->addNewGame(*g);
    this->close();
}
