#include "player.h"

#include <iostream>

using namespace std;

Player::Player()
{
   // _desc = "Not set";
    _name = "Not set";
    _password = "";
    _score = 0;
}

Player::Player(int id, string name, string password, int score)
{
    _id = id;
    _name = name;
    _password = password;
    _score = score;
   // _desc = description;
}

Player::~Player()
{}

int Player::getId() const
{
    return _id;
}
void Player::setId(int id)
{
    _id = id;
}

string Player::getName() const
{
    return _name;
}
void Player::setName(string name)
{
    _name = name;
}

string Player::getPassword() const
{
    return _password;
}
void Player::setPassword(string password)
{
    _password = password;
}

int Player::getScore() const
{
    return _score;
}
void Player::setScore(int score)
{
    _score = score;
}
void Player::addToScore(int amount)
{
    _score += amount;
}
/*
string Player::getDescription() const
{
    return _desc;
}
void Player::setDescription(string description)
{
    _desc = description;
}
*/
