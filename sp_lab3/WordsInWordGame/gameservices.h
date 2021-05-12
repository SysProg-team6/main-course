#ifndef GAMESERVICES_H
#define GAMESERVICES_H

#include "gamesrepository.h"
#include "game.h"

#include <vector>
#include <iostream>

using namespace std;

class GameServices
{
public:
    GameServices(GamesRepository &repo);
    ~GameServices();
    vector<Game> getPlayerGames(int playerId);
    Game getRandomGame();
    bool isUnique(string word);
    bool addNewGame(Game g);

private:
    GamesRepository _repo;
};

#endif // GAMESERVICES_H
