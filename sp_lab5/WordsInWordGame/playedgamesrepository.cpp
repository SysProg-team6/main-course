#include "playedgamesrepository.h"
#include "playedgame.h"

#include <vector>
#include <iterator>
#include <QSqlQuery>
#include <QVariant>

using namespace std;

PlayedGamesRepository::PlayedGamesRepository(Database* db)
{
    _db = db;
    /*_playedGameNextId = 0;
    for (vector<PlayedGame>::iterator it = _db->PlayedGames->begin(); it != _db->PlayedGames->end(); it++)
    {
       PlayedGame g = *it;
       if (g.getId() > _playedGameNextId)
           _playedGameNextId = g.getId();
    }
    _playedGameNextId++;*/

    QSqlQuery query;
    QString qstr = "CREATE TABLE IF NOT EXISTS PLAYED_GAMES ("
    "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
    "GameId INTEGER, "
    "PlayerId INTEGER, "
    "Score INTEGER, "
    "Time VARCHAR(50) NOT NULL, "
    "QuessedWords VARCHAR(255),"
    "FOREIGN KEY (PlayerId) REFERENCES PLAYERS (Id)"
           "ON DELETE CASCADE ON UPDATE NO ACTION, "
    "FOREIGN KEY (GameId) REFERENCES GAMES (Id)"
           "ON DELETE CASCADE ON UPDATE NO ACTION"
    ");";

    if(!query.exec(qstr))
    {
        throw "could not execute query for PLAYED_GAMES table";
    }
}

PlayedGamesRepository::PlayedGamesRepository()
{
}

vector<PlayedGame> PlayedGamesRepository::findAll()
{
    //return *_db->PlayedGames;

    vector<PlayedGame> games;
    QSqlQuery query;
    QString qstr = "select Id, GameId, PlayerId, Time, QuessedWords, Score from PLAYED_GAMES;";

    if(!query.exec(qstr))
    {
        throw "could not execute query for findAll from PLAYED_GAMES table";
    }

    while(query.next())
    {
        int id = query.value(0).toInt();
        int gameId = query.value(1).toInt();
        int playerId = query.value(2).toInt();
        string time = query.value(3).toString().toLocal8Bit().constData();
        string quessedWords = query.value(4).toString().toLocal8Bit().constData();
        int score = query.value(5).toInt();

        PlayedGame pg = PlayedGame(id, gameId, playerId, score);
        pg.setTime(time);
        pg.setQuessedWordsStr(quessedWords);
        games.push_back(pg);
    }

    return games;
}
PlayedGame PlayedGamesRepository::find(int id)
{
    /*vector<PlayedGame> games = *_db->PlayedGames;
    for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
    {
        PlayedGame game = *it;
        if(game.getId() == id)
            return game;
    }*/

    QSqlQuery query;
    query.prepare("select Id, GameId, PlayerId, Time, QuessedWords, Score from PLAYED_GAMES where Id = ?;");
    query.bindValue(0, id);

    if( !query.exec() )
    {
      throw "could not execute query for find from PLAYED_GAMES table";
    }

    PlayedGame pg;

    while(query.next())
    {
        id = query.value(0).toInt();
        int gameId = query.value(1).toInt();
        int playerId = query.value(2).toInt();
        string time = query.value(3).toString().toLocal8Bit().constData();
        string quessedWords = query.value(4).toString().toLocal8Bit().constData();
        int score = query.value(5).toInt();

        pg = PlayedGame(id, gameId, playerId, score);
        pg.setTime(time);
        pg.setQuessedWordsStr(quessedWords);
    }

    return pg;
}
void PlayedGamesRepository::insert(PlayedGame item)
{
    //item.setId(++_playedGameNextId);
    //_db->PlayedGames->push_back(item);

    QSqlQuery query(_db->getDb());
    query.prepare("INSERT INTO PLAYED_GAMES (GameId, PlayerId, Time, QuessedWords, Score) "
                   "VALUES (:gameId, :playerId, :time, :words, :score);");

    query.bindValue(":time", QString::fromStdString(item.getTime()));
    query.bindValue(":words", QString::fromStdString(item.getQuessedWordsStr()));
    query.bindValue(":gameId", item.getGameId());
    query.bindValue(":playerId", item.getPlayerId());
    query.bindValue(":score", item.getScore());

    if(!query.exec())
    {
        throw "could not execute query for insert for PLAYEDGAMES table";
    }
}
void PlayedGamesRepository::update(PlayedGame item)
{
    /*remove(item);
    insert(item);*/

    QSqlQuery query(_db->getDb());
    query.prepare("UPDATE PLAYED_GAMES SET "
                   "GameId = :gameId, "
                   "PlayerId = :playerId, "
                   "Time = :time, "
                   "QuessedWords = :words, "
                   "Score = :score "
                   "WHERE Id = :id;");

    query.bindValue(":time", QString::fromStdString(item.getTime()));
    query.bindValue(":words", QString::fromStdString(item.getQuessedWordsStr()));
    query.bindValue(":gameId", item.getGameId());
    query.bindValue(":playerId", item.getPlayerId());
    query.bindValue(":score", item.getScore());
    query.bindValue(":id", item.getId());

    if(!query.exec())
    {
        throw "could not execute query for update PLAYED_GAMES table";
    }
}
void PlayedGamesRepository::remove(PlayedGame item)
{
    /*vector<PlayedGame>::iterator ind;
    vector<PlayedGame> games = *_db->PlayedGames;
    for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
    {
        PlayedGame game = *it;
        if(game.getId() == item.getId())
        {
            ind = it;
            break;
        }

    }

    _db->PlayedGames->erase(ind);*/

    QSqlQuery query;
    query.prepare("DELETE FROM PLAYED_GAMES WHERE Id = ?;");
    query.bindValue(0, item.getId());

    if(!query.exec())
    {
        throw "could not execute query for remove from PLAYED_GAMES table";
    }
}

