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
    void loadFromFile();
    void loadToFile();
private:
    void readGames();
    void readPlayers();
    void readPlayedGames();

    void writeGames();
    void writePlayers();
    void writePlayedGames();

    bool isGameIdUnique(int id);
    bool isPlayerIdUnique(int id);
    bool isPlayedGameIdUnique(int id);

    string _gamesFileName;
    string _playersFileName;
    string _playedGamesFileName;
};







#endif // DATABASE_H
