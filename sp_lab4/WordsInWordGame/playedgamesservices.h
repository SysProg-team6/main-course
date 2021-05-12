#ifndef PLAYEDGAMESSERVICES_H
#define PLAYEDGAMESSERVICES_H

#include "playedgamesrepository.h"
#include "playedgame.h"

#include <vector>

class PlayedGamesServices
{
public:
    PlayedGamesServices(PlayedGamesRepository &repo);
    ~PlayedGamesServices();
    vector<PlayedGame> getHistory(int playerId);
    bool addPlayedGame(PlayedGame g);

private:
    PlayedGamesRepository _repo;
};

#endif // PLAYEDGAMESSERVICES_H
