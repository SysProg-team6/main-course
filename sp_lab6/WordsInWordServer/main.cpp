
#include <QApplication>
#include <QTcpServer>

#include "server.h"
#include "serverunit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database* db = new Database();
    QStringList text = QSqlDatabase::drivers();

    qDebug() << QSqlDatabase::drivers();

    Player p = Player();
    p.setName("alexandro");
    p.setPassword("pass");

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
    vector<Player> pl = prepo->findAll();
    //grepo->insert(g);
    //grepo->insert(g2);
    vector<Game> all = grepo->findAll();

    Server* server = new Server(gs, ps, pgs);
    ServerUnit* su = new ServerUnit(server);
    su->show();

    int res = a.exec();

    delete(su);
    delete(server);
    delete(ps);
    delete(pgs);
    delete(gs);
    delete(pgrepo);
    delete(prepo);
    delete(grepo);
    delete(db);

    return res;
}
