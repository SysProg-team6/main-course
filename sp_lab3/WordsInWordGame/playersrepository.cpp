#include "playersrepository.h"
#include "player.h"

#include <vector>
#include <iterator>

using namespace std;

PlayersRepository::PlayersRepository(Database* db)
{
    _db = db;
    _playerNextId = 0;
}

PlayersRepository::PlayersRepository() {}

vector<Player> PlayersRepository::findAll()
{
    return *_db->Players;
}
Player PlayersRepository::find(int id)
{
    vector<Player> players = *_db->Players;
    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player player = *it;
        if(player.getId() == id)
            return player;
    }
}
void PlayersRepository::insert(Player item)
{
    item.setId(++_playerNextId);
    _db->Players->push_back(item);
}
void PlayersRepository::update(Player item)
{
    remove(item);
    insert(item);
}
void PlayersRepository::remove(Player item)
{
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
}

