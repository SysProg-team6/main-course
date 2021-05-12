#include "playedgamesrepository.h"
#include "playedgame.h"

#include <vector>
#include <iterator>

using namespace std;

PlayedGamesRepository::PlayedGamesRepository(Database* db)
{
    _db = db;
    _playedGameNextId = 0;
    for (vector<PlayedGame>::iterator it = _db->PlayedGames->begin(); it != _db->PlayedGames->end(); it++)
    {
       PlayedGame g = *it;
       if (g.getId() > _playedGameNextId)
           _playedGameNextId = g.getId();
    }
    _playedGameNextId++;
}

PlayedGamesRepository::PlayedGamesRepository()
{
}

vector<PlayedGame> PlayedGamesRepository::findAll()
{
    return *_db->PlayedGames;
}
PlayedGame PlayedGamesRepository::find(int id)
{
    vector<PlayedGame> games = *_db->PlayedGames;
    for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
    {
        PlayedGame game = *it;
        if(game.getId() == id)
            return game;
    }
}
void PlayedGamesRepository::insert(PlayedGame item)
{
    item.setId(++_playedGameNextId);
    _db->PlayedGames->push_back(item);
}
void PlayedGamesRepository::update(PlayedGame item)
{
    remove(item);
    insert(item);
}
void PlayedGamesRepository::remove(PlayedGame item)
{
    vector<PlayedGame>::iterator ind;
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

    _db->PlayedGames->erase(ind);
}

