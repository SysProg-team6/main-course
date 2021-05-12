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
    return (int)getCombinations().size() - 1;
}

int Game::getAuthorId() const
{
    return _authorId;
}
void Game::setAuthorId(int id)
{
    _authorId = id;
}
