#ifndef FORMMENU_H
#define FORMMENU_H

#include <QWidget>

#include "player.h"
#include "formprofile.h"
#include "formnewgame.h"
#include "formhistory.h"
#include "formaddgame.h"

#include "gameservices.h"
#include "playedgamesservices.h"
#include "playerservices.h"

namespace Ui {
class FormMenu;}

class FormMenu : public QWidget
{
    Q_OBJECT

public:
   // FormMenu();
    explicit FormMenu(Player &player, PlayerServices *ps, PlayedGamesServices *pgs, GameServices *gs, QWidget *parent = nullptr);
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

    FormProfile *_formProfile;

    PlayerServices *_ps;
    PlayedGamesServices *_pgs;
    GameServices *_gs;

    FormHistory *_formHistory;
    FormAddGame *_formAddGame;
    FormNewGame *_formNewGame;

};

#endif // FORMMENU_H
