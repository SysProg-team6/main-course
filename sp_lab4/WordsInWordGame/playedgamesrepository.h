#ifndef PLAYEDGAMESREPOSITORY_H
#define PLAYEDGAMESREPOSITORY_H

#include "playedgame.h"
#include "repository.h"
#include "database.h"

#include <vector>

class PlayedGamesRepository: public Repository<PlayedGame>
{
public:
    PlayedGamesRepository(Database* db);
    PlayedGamesRepository();
    virtual ~PlayedGamesRepository() { }

    vector<PlayedGame> findAll();
    PlayedGame find(int id);
    void insert(PlayedGame item);
    void update(PlayedGame item);
    void remove(PlayedGame item);

private:
    Database* _db;
    int _playedGameNextId;
};
#endif // PLAYEDGAMESREPOSITORY_H
