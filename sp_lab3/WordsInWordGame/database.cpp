#include "database.h"

#include <vector>

using namespace std;

Database::Database()
{
    PlayedGames = new vector<PlayedGame>();
    Games = new vector<Game>();
    Players = new vector<Player>();
}
Database::~Database()
{
    delete(PlayedGames);
    delete(Games);
    delete(Players);
}

