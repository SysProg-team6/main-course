#ifndef FORMMENU_H
#define FORMMENU_H

#include <QWidget>

#include "formprofile.h"
#include "formnewgame.h"
#include "formhistory.h"
#include "formaddgame.h"
#include "client.h"

namespace Ui {
class FormMenu;}

class FormMenu : public QWidget
{
    Q_OBJECT

public:
   // FormMenu();
    explicit FormMenu(Player &player, Client *client, QWidget *parent = nullptr);
    ~FormMenu();
signals:
    void open();
private slots:
    void openGameForm();
    void openAddGameForm();
    void openProfileForm();
    void openHistoryForm();
    void exit();

private:
    Player _player;
    Client *_client;

    FormHistory *_formHistory;
    FormAddGame *_formAddGame;
    FormNewGame *_formNewGame;
    FormProfile *_formProfile;
};

#endif // FORMMENU_H

