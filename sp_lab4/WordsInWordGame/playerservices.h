#ifndef PLAYERSERVICES_H
#define PLAYERSERVICES_H

#include "playersrepository.h"
#include "player.h"

#include <iostream>

using namespace std;

class PlayerServices
{
public:
    PlayerServices(PlayersRepository &repo);
    ~PlayerServices();

    bool isUnique(string username, string password);
    bool registerNewPlayer(string name, string password, string confirmPassword);
    Player logIn(string username, string password);
    int getPlayerRating(int playerId);
    bool updateInfo(Player p);

private:
    PlayersRepository _repo;
};

#endif // PLAYERSERVICES_H
