#include "game.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

Game::Game()
{
    _word = "";
    _combinations = "";
    _authorId = -1;
}
Game::Game(int id, string word, vector<string> combinations, int authorId)
{
    _id = id;
    _word = word;
    setCombinations(combinations);
    _authorId = authorId;
}

Game::~Game()
{
}

int Game::getId() const
{
    return _id;
}
void Game::setId(int id)
{
    _id = id;
}

string Game::getWord() const
{
    return _word;
}
void Game::setWord(string word)
{
    _word = word;
}

string Game::getCombinationsStr() const
{
    return _combinations;
}

vector<string> Game::getCombinations() const
{
    istringstream iss(_combinations);
    vector<string> words{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    return words;
}
void Game::setCombinations(vector<string> combinations)
{
    string str = "";

    for(vector<string>::iterator it = combinations.begin(); it != combinations.end(); it++)
    {
        str += *it;
        str += " ";
    }

    _combinations = str;
}
void Game::addCombination(string combination)
{
    _combinations += combination + " ";
}

bool Game::isMatch(string q) const
{
    return _combinations.find(q) != string::npos;
}

int Game::getAmountOfCombinations() const
{
    return (int)getCombinations().size();
}

int Game::getAuthorId() const
{
    return _authorId;
}
void Game::setAuthorId(int id)
{
    _authorId = id;
}
