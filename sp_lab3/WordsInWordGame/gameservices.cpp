#include "gameservices.h"
#include "gamesrepository.h"
#include "game.h"

#include <vector>
#include <iostream>

using namespace std;

GameServices::GameServices(GamesRepository &repo)
{
    _repo = repo;
}
GameServices::~GameServices() {}

vector<Game> GameServices::getPlayerGames(int playerId)
{
    vector<Game> pGames;

    vector<Game> games = _repo.findAll();
    for(vector<Game>::iterator it = games.begin(); it != games.end(); it++)
    {
        Game game = *it;
        if(game.getAuthorId() == playerId)
            pGames.push_back(game);
    }

    return pGames;
}
Game GameServices::getRandomGame()
{
    vector<Game> games = _repo.findAll();
    int size = games.size();
    int number = rand() % size;

    return games.at(number);
}
bool GameServices::isUnique(string word)
{
    vector<Game> games = _repo.findAll();

    for(vector<Game>::iterator it = games.begin(); it != games.end(); it++)
    {
        Game game = *it;
        if(game.getWord() == word)
            return false;
    }
}
bool GameServices::addNewGame(Game g)
{
    if(!isUnique(g.getWord()))
        return false;

    _repo.insert(g);
    return true;
}
