#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player
{
public:
    Player();
    ~Player();

    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(string name);

    string getPassword() const;
    void setPassword(string password);

    int getScore() const;
    void setScore(int score);
    void addToScore(int amount);

    string getDescription() const;
    void setDescription(string description);

    // rating from service
    // history from service
    // created games from service

    bool operator > (const Player p) const
    {
        return _score > p.getScore();
    }

private:
    int _id;
    string _name;
    string _password;
    int _score;
    string _desc;
};

#endif // PLAYER_H
