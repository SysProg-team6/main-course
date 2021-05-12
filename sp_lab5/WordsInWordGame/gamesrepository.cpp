#include "gamesrepository.h"
#include "game.h"

#include <vector>
#include <iterator>
#include <QSqlQuery>
#include <QVariant>

#include <QDebug>
#include <QSqlError>

using namespace std;

GamesRepository::GamesRepository(Database* db)
{
    _db = db;
    /*_gameNextId = 0;
    for (vector<Game>::iterator it = _db->Games->begin(); it != _db->Games->end(); it++)
    {
       Game g = *it;
       if (g.getId() > _gameNextId)
           _gameNextId = g.getId();
    }
    _gameNextId++;*/

    QSqlQuery query;
    QString qstr = "CREATE TABLE IF NOT EXISTS GAMES ("
    "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
    "Word VARCHAR(50) NOT NULL, "
    "Combinations VARCHAR(255), "
    "AuthorId INTEGER,"
    "FOREIGN KEY (AuthorId) REFERENCES PLAYERS (Id)"
            "ON DELETE CASCADE ON UPDATE NO ACTION"
    ");";

    if(!query.exec(qstr))
    {
        throw "could not execute query for GAMES table";
    }
}

GamesRepository::GamesRepository()
{

}

vector<Game> GamesRepository::findAll()
{
    //return *_db->Games;
    vector<Game> games;
    QSqlQuery query(_db->getDb());
    QString qstr = "select Id, Word, Combinations, AuthorId from GAMES;";

    if(!query.exec(qstr))
    {
        throw "could not execute query for findAll from GAMES table";
    }

    while(query.next())
    {
        int id = query.value(0).toInt();
        string word = query.value(1).toString().toLocal8Bit().constData();
        string combinations = query.value(2).toString().toLocal8Bit().constData();
        int authorId = query.value(3).toInt();

        Game g = Game();
        g.setId(id);
        g.setAuthorId(authorId);
        g.setWord(word);
        g.setCombinationsStr(combinations);
        games.push_back(g);
    }

    return games;
}
Game GamesRepository::find(int id)
{
    /*
    vector<Game> games = *_db->Games;
    for(vector<Game>::iterator it = games.begin(); it != games.end(); it++)
    {
        Game game = *it;
        if(game.getId() == id)
            return game;
     }
     */
    QSqlQuery query;
    query.prepare("select Id, Word, Combinations, AuthorId from GAMES where Id = ?;");
    query.bindValue(0, id);

    if( !query.exec() )
    {
      throw "could not execute query for find from GAMES table";
    }

    Game g;

    while(query.next())
    {
        id = query.value(0).toInt();
        string word = query.value(1).toString().toLocal8Bit().constData();
        string combinations = query.value(2).toString().toLocal8Bit().constData();
        int authorId = query.value(3).toInt();

        g = Game();
        g.setId(id);
        g.setAuthorId(authorId);
        g.setWord(word);
        g.setCombinationsStr(combinations);

    }

    return g;
}
void GamesRepository::insert(Game item)
{
    //item.setId(++_gameNextId);
    //_db->Games->push_back(item);

    QSqlQuery query(_db->getDb());
    query.prepare("INSERT INTO GAMES (Word, Combinations, AuthorId) "
                   "VALUES (:word, :combinations, :authorId);");

    query.bindValue(":word", QString::fromStdString(item.getWord()));
    query.bindValue(":combinations", QString::fromStdString(item.getCombinationsStr()));
    query.bindValue(":authorId", item.getAuthorId());

    if(!query.exec())
    {
        throw "could not execute query for insert for GAMES table";
    }
}
void GamesRepository::update(Game item)
{
    QSqlQuery query(_db->getDb());
    query.prepare("UPDATE GAMES SET "
                   "Word = :word, "
                   "Combinations = :combinations "
                   "WHERE Id = :id;");

    query.bindValue(":word", QString::fromStdString(item.getWord()));
    query.bindValue(":combinations", QString::fromStdString(item.getCombinationsStr()));
    query.bindValue(":id", item.getId());

    QString text;

    if(!query.exec())
    {
        text = query.lastError().text();
        throw "could not execute query for update GAMES table";
    }
}
void GamesRepository::remove(Game item)
{
    QSqlQuery query(_db->getDb());
    query.prepare("DELETE FROM GAMES WHERE Id = ?;");
    query.bindValue(0, item.getId());

    if(!query.exec())
    {
        throw "could not execute query for remove from GAMES table";
    }

    /*
    vector<Game>::iterator ind;
    vector<Game> games = *_db->Games;
    for(vector<Game>::iterator it = games.begin(); it != games.end(); it++)
    {
        Game game = *it;
        if(game.getId() == item.getId())
        {
            ind = it;
            break;
        }

    }

    _db->Games->erase(ind);
    */
}
