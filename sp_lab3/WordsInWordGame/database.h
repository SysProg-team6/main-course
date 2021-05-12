#ifndef DATABASE_H
#define DATABASE_H

#include "game.h"
#include "player.h"
#include "playedgame.h"

#include<vector>

using namespace std;

class Database
{
public:
    Database();
    ~Database();

    vector<Game>* Games;
    vector<Player>* Players;
    vector<PlayedGame>* PlayedGames;
};


#endif // DATABASE_H
