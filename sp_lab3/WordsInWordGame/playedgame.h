#ifndef PLAYEDGAME_H
#define PLAYEDGAME_H

#include <iostream>
#include <vector>

using namespace std;

class PlayedGame
{
public:
    PlayedGame();
    ~PlayedGame();

    int getId() const;
    void setId(int id);

    int getPlayerId() const;
    void setPlayerId(int id);

    int getGameId() const;
    void setGameId(int id);

    int getScore() const;
    void setScore(int score);

    string getTime() const;
    void setTime(string time);

    vector<string> getQuesedWords() const;
    void setQuesedWords(vector<string> words);
    void addWord(string word);

private:
    int _id;
    int _gameId;
    int _playerId;
    int _score;
    string _time;
    string _quesedWords;
};

#endif // PLAYEDGAME_H
