#include "playerservices.h"
#include "playersrepository.h"
#include "player.h"

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

PlayerServices::PlayerServices(PlayersRepository &repo)
{
    _repo = repo;
}

PlayerServices::~PlayerServices() {}

bool PlayerServices::isUnique(string username, string password)
{
    vector<Player> players = _repo.findAll();

    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player &player = *it;
        if(player.getName() == username || player.getPassword() == password)
            return false;
    }
}

bool PlayerServices::registerNewPlayer(string name, string password, string confirmPassword)
{
    if (password != confirmPassword)
        return false;

    Player* p = new Player();
    p->setName(name);
    p->setPassword(password);
    _repo.insert(*p);

    return true;
}
Player PlayerServices::logIn(string username, string password)
{
    vector<Player> players = _repo.findAll();

    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player player = *it;
        if(player.getName() == username || player.getPassword() == password)
            return player;
    }

}
int PlayerServices::getPlayerRating(int playerId)
{
    vector<Player> players = _repo.findAll();
    std::sort(players.begin(), players.end(), greater<Player>());
    int i = 1;

    for(vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        Player player = *it;
        if(player.getId() == playerId)
            return i;
        i++;
    }
}
bool PlayerServices::updateInfo(Player p)
{
    if(!isUnique(p.getName(), p.getPassword()))
        return false;
    _repo.update(p);
    return true;
}
