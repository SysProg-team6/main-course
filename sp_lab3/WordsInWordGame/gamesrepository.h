#ifndef GAMESREPOSITORY_H
#define GAMESREPOSITORY_H

#include "game.h"
#include "repository.h"
#include "database.h"

#include <vector>

class GamesRepository: public Repository<Game>
{
public:
    GamesRepository(Database* db);
    GamesRepository();
    virtual ~GamesRepository() {}

    vector<Game> findAll();
    Game find(int id);
    void insert(Game item);
    void update(Game item);
    void remove(Game item);

private:
    Database* _db;
    int _gameNextId;
};

#endif // GAMESREPOSITORY_H
