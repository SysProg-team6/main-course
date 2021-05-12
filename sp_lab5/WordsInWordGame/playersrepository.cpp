#include "playersrepository.h"
#include "player.h"

#include <vector>
#include <iterator>
#include <QSqlQuery>
#include <QVariant>

using namespace std;

PlayersRepository::PlayersRepository(Database* db)
{
    _db = db;
    _playerNextId = 0;
    for (vector<Player>::iterator it = _db->Players->begin(); it != _db->Players->end(); it++)
    {
       Player p = *it;
       if (p.getId() > _playerNextId)
           _playerNextId = p.getId();
    }
    _playerNextId++;

    QSqlQuery query;
    QString qstr = "CREATE TABLE IF NOT EXISTS PLAYERS ("
    "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
    "Name VARCHAR(50) NOT NULL, "
    "Password VARCHAR(50), "
    "Score INTEGER"
    ");";

    if(!query.exec(qstr))
    {
        throw "could not execute query for PLAYERS table";
    }

}

PlayersRepository::PlayersRepository() {}

vector<Player> PlayersRepository::findAll()
{
    vector<Player> players;
    QSqlQuery query;
    QString qstr = "select Id, Name, Password, Score from PLAYERS;";

    if(!query.exec(qstr))
    {
        throw "could not execute query for findAll from PLAYERS table";
    }

    while(query.next())
    {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toLocal8Bit().constData();
        string password = query.value(2).toString().toLocal8Bit().constData();
        int score = query.value(3).toInt();

        Player p = Player(id, name, password, score);
        players.push_back(p);
    }

    return players;
   // return *_db->Players;
}
Player PlayersRepository::find(int id)
{
    QSqlQuery query;
    query.prepare("select Id, Name, Password, Score from PLAYERS where Id = ?;");
    query.bindValue(0, id);

    if( !query.exec() )
    {
        throw "could not execute query for find from PLAYERS table";
    }

    Player p;

    while(query.next())
    {
        id = query.value(0).toInt();
        string name = query.value(1).toString().toLocal8Bit().constData();
        string password = query.value(2).toString().toLocal8Bit().constData();
        int score = query.value(3).toInt();

        p = Player(id, name, password, score);
    }

    return p;

    /*
    vector<Player> players = *_db->Players;
    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player player = *it;
        if(player.getId() == id)
            return player;
    }
    */
}
void PlayersRepository::insert(Player item)
{
    QSqlQuery query(_db->getDb());

    query.prepare("INSERT INTO PLAYERS (Name, Password, Score) "
                  "VALUES (:name, :password, :score);");
    query.bindValue(":name", QString::fromStdString(item.getName()));
    query.bindValue(":password", QString::fromStdString(item.getPassword()));
    query.bindValue(":score", item.getScore());

    if(!query.exec())
    {
        throw "could not execute query for insert for PLAYERS table";
    }

    /*
    item.setId(++_playerNextId);
    _db->Players->push_back(item);
    */
}
void PlayersRepository::update(Player item)
{
    QSqlQuery query(_db->getDb());

    query.prepare("UPDATE PLAYERS SET "
                  "Name = :name, Password = :password, Score = :score"
                  "WHERE Id = :id;");
    query.bindValue(":name", QString::fromStdString(item.getName()));
    query.bindValue(":password", QString::fromStdString(item.getPassword()));
    query.bindValue(":score", item.getScore());
    query.bindValue(":id", item.getId());

    if(!query.exec())
    {
        throw "could not execute query for update PLAYERS table";
    }
    /*
    remove(item);
    insert(item);
    */
}
void PlayersRepository::remove(Player item)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PLAYERS WHERE Id = ?;");
    query.bindValue(0, item.getId());

    if(!query.exec())
    {
        throw "could not execute query for remove from PLAYERS table";
    }
    /*
    vector<Player>::iterator ind;
    vector<Player> players = *_db->Players;
    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player player = *it;
        if(player.getId() == item.getId())
        {
            ind = it;
            break;
        }

    }

    _db->Players->erase(ind);
    */
}

