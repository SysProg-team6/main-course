#include "mainwindow.h"
#include "player.h"
#include "game.h"
#include "playedgame.h"
#include "database.h"
#include "gamesrepository.h"
#include "playersrepository.h"
#include "playedgamesrepository.h"
#include "gameservices.h"
#include "playedgamesservices.h"
#include "playerservices.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    Database* db = new Database();
/*
    Player* p = new Player();
        p->setName("alexandro");


        Game* g2 = new Game();
        g2->setWord("beautiful");
        vector<string> comb2;
        comb2.push_back("bit");
        comb2.push_back("beaf");
        comb2.push_back("fail");
        g2->setCombinations(comb2);

        Game* g = new Game();
        g->setWord("helicopter");
        vector<string> comb;
        comb.push_back("he");
        comb.push_back("copter");
        g->setCombinations(comb);


        PlayedGame* pg = new PlayedGame();
        pg->setScore(5);
*/

    GamesRepository* grepo = new GamesRepository(db);
    PlayersRepository* prepo = new PlayersRepository(db);
    PlayedGamesRepository* pgrepo = new PlayedGamesRepository(db);

    GameServices* gs = new GameServices(*grepo);
    PlayedGamesServices* pgs = new PlayedGamesServices(*pgrepo);
    PlayerServices* ps = new PlayerServices(*prepo);
/*
    prepo->insert(*p);
    cout << p->getId() << endl;

    grepo->insert(*g);
    grepo->insert(*g2);
*/

    MainWindow *w = new MainWindow(nullptr, ps, pgs, gs);
    w->show();

    int code = a.exec();

    delete(ps);
    delete(pgs);
    delete(gs);
    delete(pgrepo);
    delete(prepo);
    delete(grepo);
    delete(db);
    delete(w);

    return code;
}
