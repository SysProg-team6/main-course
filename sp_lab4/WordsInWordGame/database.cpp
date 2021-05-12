#include "database.h"
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

Database::Database()
{
    PlayedGames = new vector<PlayedGame>();
    Games = new vector<Game>();
    Players = new vector<Player>();

    _playersFileName = "players.txt";
    _gamesFileName = "games.txt";
    _playedGamesFileName = "playedgames.txt";

     loadFromFile();
}
Database::~Database()
{
    loadToFile();
    delete(PlayedGames);
    delete(Games);
    delete(Players);
}

void Database::loadFromFile()
{
    readGames();
    readPlayers();
    readPlayedGames();
}

void Database::loadToFile()
{
    writeGames();
    writePlayedGames();
    writePlayers();
}

void Database::writeGames()
{
    FILE* f;
    f = fopen(_gamesFileName.c_str(), "w+");
    std::ofstream fof (_gamesFileName.c_str(), std::ofstream::out);
   // ofstream fof(f);

    for(Game& g : *Games)
    {
        fof << g.getId() << endl << g.getWord() << endl << g.getAuthorId() << endl << g.getAmountOfCombinations() << endl;
        for(string s: g.getCombinations()){
            fof<<s<<endl;
        }
    }
    fof.close();
}
void Database::writePlayers()
{
    FILE* f;
    f = fopen(_playersFileName.c_str(), "w+");
    std::ofstream fof (_playersFileName.c_str(), std::ofstream::out);
    //ofstream fof(f);

    for(Player& p : *Players)
    {
        fof << p.getId() << endl << p.getName() << endl << p.getPassword() << endl << p.getScore() << endl;
    }
    fof.close();
}
void Database::writePlayedGames()
{
    FILE* f;
    f = fopen(_playedGamesFileName.c_str(), "w+");
    std::ofstream fof (_playedGamesFileName.c_str(), std::ofstream::out);
    //ofstream fof(f);

    for(PlayedGame& pg : *PlayedGames)
    {
        fof << pg.getId() << endl << pg.getGameId() << endl << pg.getPlayerId() << endl << pg.getScore() << endl;
    }
    fof.close();
}

void Database::readGames()
{
    FILE* f;
    f = fopen(_gamesFileName.c_str(), "r");
   // ifstream fin(f);
    std::ifstream fin (_gamesFileName.c_str(), std::ifstream::in);
    int id;
    string word;

    int amount;
    int authorId;
    string s;


    if (fin.is_open())
    {
        Games->clear();
        while (!fin.eof())
        {
            vector<string> combinations;
            fin >> id >> word >> authorId >> amount;
            for(int i=0; i<amount; i++){
                fin>>s;
                combinations.push_back(s);
            }
            if (id < 0 || !isGameIdUnique(id)) continue;
            Games->push_back(Game(id, word, combinations, authorId));
         }
         fin.close();
    }
    else
    {
        cout << "Error! Input file isn't opened!";
    }
}
void Database::readPlayers()
{
    FILE* f;
    f = fopen(_playersFileName.c_str(), "r");
   // ifstream fin(f);
     std::ifstream fin (_playersFileName.c_str(), std::ifstream::in);
    int id;
    string name;
    string password;

    int score;

    if (fin.is_open())
    {
        Players->clear();
        while (!fin.eof())
        {
            fin >> id >> name >> password >> score;
            if (id < 0 || !isPlayerIdUnique(id)) continue;
            Players->push_back(Player(id, name, password, score));
         }
         fin.close();
    }
    else
    {
        cout << "Error! Input file isn't opened!";
    }
}
void Database::readPlayedGames()
{
    FILE* f;
    f = fopen(_playedGamesFileName.c_str(), "r");
    //ifstream fin(f);
      std::ifstream fin(_playedGamesFileName.c_str(), std::ifstream::in);
    int id;
    int gameId;
    int playerId;
    int score;
    string time;

    if (fin.is_open())
    {
        PlayedGames->clear();
        while (!fin.eof())
        {
            fin >> id >> gameId >> playerId >> score;
            if (id < 0 || !isPlayedGameIdUnique(id)) continue;
            PlayedGames->push_back(PlayedGame(id, gameId, playerId, score));
         }
         fin.close();
    }
    else
    {
        cout << "Error! Input file isn't opened!";
    }
}

bool Database::isGameIdUnique(int id)
{
    for (vector<Game>::iterator it = Games->begin(); it != Games->end(); it++)
    {
        Game g = *it;
        if (g.getId() == id)
            return false;
    }

    return true;
}
bool Database::isPlayerIdUnique(int id)
{
    for (vector<Player>::iterator it = Players->begin(); it != Players->end(); it++)
    {
        Player p = *it;
        if (p.getId() == id)
            return false;
    }

    return true;
}
bool Database::isPlayedGameIdUnique(int id)
{
    for (vector<PlayedGame>::iterator it = PlayedGames->begin(); it != PlayedGames->end(); it++)
    {
        PlayedGame pg = *it;
        if (pg.getId() == id)
            return false;
    }

    return true;
}

