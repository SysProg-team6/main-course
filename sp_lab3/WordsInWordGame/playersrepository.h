#ifndef PLAYERSREPOSITORY_H
#define PLAYERSREPOSITORY_H

#include "player.h"
#include "repository.h"
#include "database.h"

#include <vector>

class PlayersRepository: public Repository<Player>
{
public:
    PlayersRepository(Database* db);
    PlayersRepository();
    virtual ~PlayersRepository() { }

    vector<Player> findAll();
    Player find(int id);
    void insert(Player item);
    void update(Player item);
    void remove(Player item);

private:
    Database* _db;
    int _playerNextId;
};
#endif // PLAYERSREPOSITORY_H
