#include "playedgamesservices.h"
#include "playedgamesrepository.h"
#include "playedgame.h"

#include <vector>

PlayedGamesServices::PlayedGamesServices(PlayedGamesRepository &repo)
{
    _repo = repo;
}
PlayedGamesServices::~PlayedGamesServices()
{
}
 vector<PlayedGame> PlayedGamesServices::getHistory(int playerId)
 {
    vector<PlayedGame> pGames;

    vector<PlayedGame> games = _repo.findAll();
    for(vector<PlayedGame>::iterator it = games.begin(); it != games.end(); it++)
    {
        PlayedGame game = *it;
        if(game.getPlayerId() == playerId)
            pGames.push_back(game);
    }

    return pGames;
}
bool PlayedGamesServices::addPlayedGame(PlayedGame g)
{
    _repo.insert(g);
    return true;
}
