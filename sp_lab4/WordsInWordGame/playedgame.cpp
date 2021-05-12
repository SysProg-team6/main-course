#include "playedgame.h"

#include <ctime>
#include <chrono>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

PlayedGame::PlayedGame()
{
    time_t now = time(0);
    tm * ptm = localtime(&now);
    char buffer[28];
    std::strftime(buffer, 28, "%d.%m.%Y %H:%M:%S", ptm);

    _time = "";
    for (int i = 0; i < 28; i++)
    {
        _time += buffer[i];
    }
}

PlayedGame::PlayedGame(int id, int gameId, int playerId, int score)
{
    _id = id;
    _gameId = gameId;
    _playerId = playerId;
    _score = score;

}

PlayedGame::~PlayedGame()
{}

int PlayedGame::getId() const
{
    return _id;
}
void PlayedGame::setId(int id)
{
    _id = id;
}

int PlayedGame::getPlayerId() const
{
    return _playerId;
}
void PlayedGame::setPlayerId(int id)
{
    _playerId = id;
}

int PlayedGame::getGameId() const
{
    return _gameId;
}
void PlayedGame::setGameId(int id)
{
    _gameId = id;
}

int PlayedGame::getScore() const
{
    return _score;
}
void PlayedGame::setScore(int score)
{
    _score = score;
}

string PlayedGame::getTime() const
{
    return _time;
}
void PlayedGame::setTime(string time)
{
    _time = time;
}

vector<string> PlayedGame::getQuesedWords() const
{
    istringstream iss(_quesedWords);
    vector<string> words;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(words));

    return words;
}
void PlayedGame::setQuesedWords(vector<string> words)
{
    string str = "";

    for(vector<string>::iterator it = words.begin(); it != words.end(); it++)
    {
        str += *it;
        str += " ";
    }

    _quesedWords = str;
}
void PlayedGame::addWord(string word)
{
    _quesedWords += word + " ";
}
