#ifndef FORMPROFILE_H
#define FORMPROFILE_H
#include "../WordsInWordGame/player.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormProfile : public QWidget
{
     Q_OBJECT
public:
    explicit FormProfile(Player &player, QWidget *parent = nullptr);
    ~FormProfile();
     QTextEdit *login;
     QTextEdit *password;

private slots:
signals:
      void openForm();
private:
    Player _player;

};


#endif // FORMPROFILE_H
