#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "world.h"

class Location;

class Game
{
public:
    Game(QString map ="", int enemies=0, int health=0);
    std::vector<std::shared_ptr<Tile>> getWorldToDraw();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Tile>> getHealthPacks();
    std::shared_ptr<Protagonist> getHero();

    int getColms();
    int getRows();

    float getTileValue(Location &location);

    Location relocate(int posX,int posY);

    float getHeroEnergy();
    float getHeroHealth();
private:
    World world;
    std::vector<std::shared_ptr<Tile>> worldTiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthPacks;
    std::shared_ptr<Protagonist> hero;


public slots:
};

#endif // GAME_H
