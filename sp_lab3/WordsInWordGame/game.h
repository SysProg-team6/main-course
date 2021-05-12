#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    int getId() const;
    void setId(int id);

    string getWord() const;
    void setWord(string word);

    vector<string> getCombinations() const;
    void setCombinations(vector<string> combinations);
    void addCombination(string combination);
    bool isMatch(string q) const;

    int getAmountOfCombinations() const;

    int getAuthorId() const;
    void setAuthorId(int id);

private:
    int _id;
    string _word;
    string _combinations;
    int _authorId;
};

#endif // GAME_H
