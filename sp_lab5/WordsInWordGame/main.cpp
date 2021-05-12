#include "mainwindow.h"
#include "database.h"
#include "gamesrepository.h"
#include "playersrepository.h"
#include "playedgamesrepository.h"
#include "gameservices.h"
#include "playedgamesservices.h"
#include "playerservices.h"

#include <QDebug>
#include <QSqlDatabase>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    Database* db = new Database();

    //qDebug() << QSqlDatabase::drivers();

    /*Player p = Player();
    p.setName("alexandro");
    p.setPassword("pass");*/

    Game g2 = Game();
    g2.setWord("beautiful");
    g2.setAuthorId(1);
    vector<string> comb2;
    comb2.push_back("bit");
    comb2.push_back("beaf");
    comb2.push_back("fail");
    g2.setCombinations(comb2);

    Game g = Game();
    g.setWord("helicopter");
    g.setAuthorId(1);
    vector<string> comb;
    comb.push_back("he");
    comb.push_back("copter");
    g.setCombinations(comb);


    PlayersRepository* prepo = new PlayersRepository(db);
    GamesRepository* grepo = new GamesRepository(db);
    PlayedGamesRepository* pgrepo = new PlayedGamesRepository(db);

    GameServices* gs = new GameServices(*grepo);
    PlayedGamesServices* pgs = new PlayedGamesServices(*pgrepo);
    PlayerServices* ps = new PlayerServices(*prepo);

    //prepo->insert(p);
    //vector<Player> pl = prepo->findAll();
    //grepo->insert(g);
    //grepo->insert(g2);
    //vector<Game> all = grepo->findAll();

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
