#ifndef FORMPROFILE_H
#define FORMPROFILE_H
#include "player.h"
#include "playerservices.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class FormProfile : public QWidget
{
     Q_OBJECT
public:
    explicit FormProfile(Player &player, QWidget *parent = nullptr,PlayerServices *ps = nullptr);
    ~FormProfile();
     QTextEdit *login;
      QTextEdit *password;

private slots:
signals:
      void openForm();
private:
    PlayerServices *_ps;
    Player _player;

};


#endif // FORMPROFILE_H
