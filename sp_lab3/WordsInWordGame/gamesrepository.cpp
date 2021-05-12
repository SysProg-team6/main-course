#include "gamesrepository.h"
#include "game.h"

#include <vector>
#include <iterator>

using namespace std;

GamesRepository::GamesRepository(Database* db)
{
    _db = db;
    _gameNextId = 0;
}

GamesRepository::GamesRepository()
{
}

vector<Game> GamesRepository::findAll()
{
    return *_db->Games;
}
Game GamesRepository::find(int id)
{
    vector<Game> games = *_db->Games;
    for(vector<Game>::iterator it = games.begin(); it != games.end(); it++)
    {
        Game game = *it;
        if(game.getId() == id)
            return game;
     }
}
void GamesRepository::insert(Game item)
{
    item.setId(++_gameNextId);
    _db->Games->push_back(item);
}
void GamesRepository::update(Game item)
{
    remove(item);
    insert(item);
}
void GamesRepository::remove(Game item)
{
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
}
